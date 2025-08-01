/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <folly/Utility.h>

#include <thrift/lib/cpp2/dynamic/TypeSystem.h>
#include <thrift/lib/cpp2/runtime/SchemaRegistry.h>
#include <thrift/lib/cpp2/schema/SyntaxGraph.h>

#include <thrift/annotation/gen-cpp2/thrift_types.h>
#include <thrift/lib/cpp2/schema/test/gen-cpp2/syntax_graph_2_handlers.h>
#include <thrift/lib/cpp2/schema/test/gen-cpp2/syntax_graph_3_types.h>
#include <thrift/lib/cpp2/schema/test/gen-cpp2/syntax_graph_handlers.h>
#include <thrift/lib/cpp2/schema/test/gen-cpp2/syntax_graph_types.h>

#include <fmt/core.h>

#include <algorithm>

namespace type = apache::thrift::type;

namespace apache::thrift::syntax_graph {

namespace {

class ServiceSchemaTest : public testing::Test {
 public:
  template <typename ServiceTag>
  static type::Schema schemaFor() {
    return apache::thrift::ServiceHandler<ServiceTag>()
        .getServiceSchema()
        .value()
        .schema;
  }

  template <typename ServiceTag>
  std::vector<type::DefinitionKey> definitionKeysFor() {
    return apache::thrift::ServiceHandler<ServiceTag>()
        .getServiceSchema()
        .value()
        .definitions;
  }

  static folly::not_null<const ProgramNode*> findProgramByName(
      const SyntaxGraph& graph, std::string_view name) {
    auto programs = graph.programs();
    auto program = std::find_if(
        programs.begin(),
        programs.end(),
        [name](folly::not_null<const ProgramNode*> program) {
          return program->name() == name;
        });
    if (program != programs.end()) {
      return *program;
    }
    throw std::logic_error(fmt::format("Program named {} not found", name));
  }
};

} // namespace

TEST_F(ServiceSchemaTest, Programs) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto programs = syntaxGraph.programs();
  EXPECT_EQ(programs.size(), 3);

  auto mainProgram = findProgramByName(syntaxGraph, "syntax_graph");
  EXPECT_EQ(mainProgram->definitionsByName().size(), 13);
  EXPECT_EQ(mainProgram->namespaces().size(), 1);
  EXPECT_EQ(
      mainProgram->namespaces().at("cpp2"), "apache.thrift.syntax_graph.test");
  {
    ProgramNode::IncludesList includes = mainProgram->includes();
    EXPECT_EQ(includes.size(), 2);

    EXPECT_EQ(includes[0]->name(), "scope");
    EXPECT_EQ(includes[1]->name(), "thrift");

    EXPECT_EQ(includes[0], findProgramByName(syntaxGraph, "scope"));
    EXPECT_EQ(includes[1], findProgramByName(syntaxGraph, "thrift"));
  }

  EXPECT_THROW(
      { findProgramByName(syntaxGraph, "syntax_graph_2"); }, std::logic_error);
}

TEST_F(ServiceSchemaTest, TransitivePrograms) {
  // TestService2 is in a different file, so we should have an *extra* program.
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService2>());
  auto programs = syntaxGraph.programs();
  EXPECT_EQ(programs.size(), 4);

  auto mainProgram = findProgramByName(syntaxGraph, "syntax_graph");
  {
    ProgramNode::IncludesList includes = mainProgram->includes();
    EXPECT_EQ(includes.size(), 2);
    EXPECT_EQ(includes[0], findProgramByName(syntaxGraph, "scope"));
    EXPECT_EQ(includes[1], findProgramByName(syntaxGraph, "thrift"));
  }

  auto secondProgram = findProgramByName(syntaxGraph, "syntax_graph_2");
  EXPECT_EQ(secondProgram->definitionsByName().size(), 2);
  {
    ProgramNode::IncludesList includes = secondProgram->includes();
    EXPECT_EQ(includes.size(), 1);

    EXPECT_EQ(includes[0]->name(), "syntax_graph");
    EXPECT_EQ(includes[0], mainProgram);
  }
}

TEST_F(ServiceSchemaTest, RawSchemaLifetime) {
  // moved type::Schema&&
  {
    std::optional<type::Schema> schema = schemaFor<test::TestService>();
    auto syntaxGraph = SyntaxGraph::fromSchema(std::move(schema.value()));
    schema.reset();
    EXPECT_NO_THROW({ findProgramByName(syntaxGraph, "syntax_graph"); });
  }
  // copied type::Schema&&
  {
    std::optional<type::Schema> schema = schemaFor<test::TestService>();
    auto syntaxGraph = SyntaxGraph::fromSchema(folly::copy(schema.value()));
    schema.reset();
    EXPECT_NO_THROW({ findProgramByName(syntaxGraph, "syntax_graph"); });
  }
  // const type::Schema&
  {
    const type::Schema& schema = schemaFor<test::TestService>();
    auto syntaxGraph = SyntaxGraph::fromSchema(&schema);
    EXPECT_NO_THROW({ findProgramByName(syntaxGraph, "syntax_graph"); });
  }
}

TEST_F(ServiceSchemaTest, Enum) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> testEnum =
      program->definitionsByName().at("TestEnum");
  EXPECT_EQ(&testEnum->program(), program.unwrap());
  EXPECT_EQ(testEnum->kind(), DefinitionNode::Kind::ENUM);
  EXPECT_EQ(testEnum->name(), "TestEnum");
  const EnumNode& e = testEnum->asEnum();
  EXPECT_EQ(&e.definition(), testEnum.unwrap());
  EXPECT_EQ(e.uri(), "meta.com/thrift_test/TestEnum");

  const std::vector<EnumNode::Value> expected = {
      {"UNSET", 0},
      {"VALUE_1", 1},
      {"VALUE_2", 2},
  };
  EXPECT_THAT(e.values(), testing::ElementsAreArray(expected));

  EXPECT_EQ(
      e.toDebugString(),
      "EnumNode 'TestEnum'\n"
      "├─ 'UNSET' → 0\n"
      "├─ 'VALUE_1' → 1\n"
      "╰─ 'VALUE_2' → 2\n");
}

TEST_F(ServiceSchemaTest, Struct) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> testStruct =
      program->definitionsByName().at("TestStruct");
  EXPECT_EQ(&testStruct->program(), program.unwrap());
  EXPECT_EQ(testStruct->kind(), DefinitionNode::Kind::STRUCT);
  EXPECT_EQ(testStruct->name(), "TestStruct");
  EXPECT_STREQ(testStruct->name().data(), "TestStruct");
  const StructNode& s = testStruct->asStruct();
  EXPECT_EQ(&s.definition(), testStruct.unwrap());
  EXPECT_EQ(s.uri(), "");

  EXPECT_EQ(s.fields().size(), 2);

  EXPECT_EQ(s.fields()[0].id(), FieldId{1});
  EXPECT_EQ(
      s.fields()[0].presence(), FieldNode::PresenceQualifier::UNQUALIFIED);
  EXPECT_EQ(s.fields()[0].type().asPrimitive(), Primitive::I32);
  EXPECT_EQ(s.fields()[0].name(), "field1");
  EXPECT_STREQ(s.fields()[0].name().data(), "field1");
  EXPECT_EQ(s.fields()[0].customDefault()->as_i32(), 10);

  EXPECT_EQ(s.fields()[1].id(), FieldId{2});
  EXPECT_EQ(s.fields()[1].presence(), FieldNode::PresenceQualifier::OPTIONAL_);
  EXPECT_EQ(
      &s.fields()[1].type().asEnum(),
      &program->definitionsByName().at("TestEnum")->asEnum());
  EXPECT_EQ(s.fields()[1].name(), "field2");
  EXPECT_STREQ(s.fields()[1].name().data(), "field2");
  EXPECT_EQ(s.fields()[1].customDefault(), nullptr);

  EXPECT_EQ(
      s.toDebugString(),
      "StructNode 'TestStruct'\n"
      "├─ FieldNode (id=1, presence=UNQUALIFIED, name='field1')\n"
      "│  ├─ type = I32\n"
      "│  ╰─ customDefault = ...\n"
      "╰─ FieldNode (id=2, presence=OPTIONAL, name='field2')\n"
      "   ╰─ type = EnumNode 'TestEnum'\n"
      "      ├─ 'UNSET' → 0\n"
      "      ├─ 'VALUE_1' → 1\n"
      "      ╰─ 'VALUE_2' → 2\n");
}

TEST_F(ServiceSchemaTest, Union) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> testUnion =
      program->definitionsByName().at("TestUnion");
  EXPECT_EQ(&testUnion->program(), program.unwrap());
  EXPECT_EQ(testUnion->kind(), DefinitionNode::Kind::UNION);
  EXPECT_EQ(testUnion->name(), "TestUnion");
  EXPECT_STREQ(testUnion->name().data(), "TestUnion");
  const UnionNode& u = testUnion->asUnion();

  EXPECT_EQ(u.fields().size(), 2);

  EXPECT_EQ(u.fields()[0].id(), FieldId{1});
  EXPECT_EQ(u.fields()[0].name(), "s");
  EXPECT_EQ(
      &u.fields()[0].type().asStruct(),
      &program->definitionsByName().at("TestStruct")->asStruct());

  EXPECT_EQ(u.fields()[1].id(), FieldId{2});
  EXPECT_EQ(u.fields()[1].name(), "e");
  EXPECT_EQ(
      &u.fields()[1].type().asEnum(),
      &program->definitionsByName().at("TestEnum")->asEnum());

  EXPECT_EQ(
      u.toDebugString(),
      "UnionNode 'TestUnion'\n"
      "├─ FieldNode (id=1, presence=UNQUALIFIED, name='s')\n"
      "│  ╰─ type = StructNode 'TestStruct'\n"
      "│     ├─ FieldNode (id=1, presence=UNQUALIFIED, name='field1')\n"
      "│     │  ├─ type = I32\n"
      "│     │  ╰─ customDefault = ...\n"
      "│     ╰─ FieldNode (id=2, presence=OPTIONAL, name='field2')\n"
      "│        ╰─ type = EnumNode 'TestEnum'\n"
      "│           ├─ 'UNSET' → 0\n"
      "│           ├─ 'VALUE_1' → 1\n"
      "│           ╰─ 'VALUE_2' → 2\n"
      "╰─ FieldNode (id=2, presence=UNQUALIFIED, name='e')\n"
      "   ╰─ type = EnumNode 'TestEnum'\n");
}

TEST_F(ServiceSchemaTest, Typedefs) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> listOfTestStructTypedef =
      program->definitionsByName().at("ListOfTestStruct");
  EXPECT_EQ(&listOfTestStructTypedef->program(), program.unwrap());
  EXPECT_EQ(listOfTestStructTypedef->kind(), DefinitionNode::Kind::TYPEDEF);
  EXPECT_EQ(listOfTestStructTypedef->name(), "ListOfTestStruct");
  const TypedefNode& t = listOfTestStructTypedef->asTypedef();

  EXPECT_EQ(
      &t.targetType().asList().elementType().asStruct(),
      &program->definitionsByName().at("TestStruct")->asStruct());

  folly::not_null<const DefinitionNode*> typedefToListOfTestStructTypedef =
      program->definitionsByName().at("TypedefToListOfTestStruct");
  EXPECT_EQ(&typedefToListOfTestStructTypedef->program(), program.unwrap());
  EXPECT_EQ(
      typedefToListOfTestStructTypedef->kind(), DefinitionNode::Kind::TYPEDEF);
  EXPECT_EQ(
      typedefToListOfTestStructTypedef->name(), "TypedefToListOfTestStruct");
  const TypedefNode& t2 = typedefToListOfTestStructTypedef->asTypedef();
  EXPECT_EQ(t2.targetType().kind(), TypeRef::Kind::TYPEDEF);

  EXPECT_EQ(t2.targetType(), *listOfTestStructTypedef);
  EXPECT_EQ(t2.targetType().trueType(), t.targetType());

  EXPECT_EQ(
      t.toDebugString(),
      "TypedefNode 'ListOfTestStruct'\n"
      "╰─ targetType = List\n"
      "   ╰─ elementType = StructNode 'TestStruct'\n"
      "      ├─ FieldNode (id=1, presence=UNQUALIFIED, name='field1')\n"
      "      │  ├─ type = I32\n"
      "      │  ╰─ customDefault = ...\n"
      "      ╰─ FieldNode (id=2, presence=OPTIONAL, name='field2')\n"
      "         ╰─ type = EnumNode 'TestEnum'\n"
      "            ├─ 'UNSET' → 0\n"
      "            ├─ 'VALUE_1' → 1\n"
      "            ╰─ 'VALUE_2' → 2\n");

  EXPECT_EQ(
      t2.toDebugString(),
      "TypedefNode 'TypedefToListOfTestStruct'\n"
      "╰─ targetType = TypedefNode 'ListOfTestStruct'\n"
      "   ╰─ targetType = List\n"
      "      ╰─ elementType = StructNode 'TestStruct'\n"
      "         ├─ FieldNode (id=1, presence=UNQUALIFIED, name='field1')\n"
      "         │  ├─ type = I32\n"
      "         │  ╰─ customDefault = ...\n"
      "         ╰─ FieldNode (id=2, presence=OPTIONAL, name='field2')\n"
      "            ╰─ type = EnumNode 'TestEnum'\n"
      "               ├─ 'UNSET' → 0\n"
      "               ├─ 'VALUE_1' → 1\n"
      "               ╰─ 'VALUE_2' → 2\n");
}

TEST_F(ServiceSchemaTest, Exception) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> testException =
      program->definitionsByName().at("TestException");
  EXPECT_EQ(&testException->program(), program.unwrap());
  EXPECT_EQ(testException->kind(), DefinitionNode::Kind::EXCEPTION);
  EXPECT_EQ(testException->name(), "TestException");
  const ExceptionNode& e = testException->asException();

  EXPECT_EQ(e.fields().size(), 1);

  EXPECT_EQ(e.fields()[0].id(), FieldId{1});
  EXPECT_EQ(e.fields()[0].name(), "blob");
  EXPECT_EQ(e.fields()[0].type().asPrimitive(), Primitive::BINARY);

  EXPECT_EQ(
      e.toDebugString(),
      "ExceptionNode 'TestException'\n"
      "╰─ FieldNode (id=1, presence=UNQUALIFIED, name='blob')\n"
      "   ╰─ type = BINARY\n");
}

TEST_F(ServiceSchemaTest, Constant) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> testConst =
      program->definitionsByName().at("testConst");
  EXPECT_EQ(&testConst->program(), program.unwrap());
  EXPECT_EQ(testConst->kind(), DefinitionNode::Kind::CONSTANT);
  EXPECT_EQ(testConst->name(), "testConst");
  const ConstantNode& c = testConst->asConstant();

  EXPECT_EQ(
      &c.type().asStruct(),
      &program->definitionsByName().at("TestStruct")->asStruct());
  const auto& value = c.value().as_object();
  EXPECT_EQ(value.at(FieldId{1}).as_i32(), 2);

  EXPECT_EQ(
      c.toDebugString(),
      "ConstantNode 'testConst'\n"
      "├─ type = StructNode 'TestStruct'\n"
      "│  ├─ FieldNode (id=1, presence=UNQUALIFIED, name='field1')\n"
      "│  │  ├─ type = I32\n"
      "│  │  ╰─ customDefault = ...\n"
      "│  ╰─ FieldNode (id=2, presence=OPTIONAL, name='field2')\n"
      "│     ╰─ type = EnumNode 'TestEnum'\n"
      "│        ├─ 'UNSET' → 0\n"
      "│        ├─ 'VALUE_1' → 1\n"
      "│        ╰─ 'VALUE_2' → 2\n"
      "╰─ value = ...\n");
}

TEST_F(ServiceSchemaTest, Service) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService2>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");
  auto program2 = findProgramByName(syntaxGraph, "syntax_graph_2");

  folly::not_null<const DefinitionNode*> testService =
      program->definitionsByName().at("TestService");
  EXPECT_EQ(&testService->program(), program.unwrap());
  EXPECT_EQ(testService->kind(), DefinitionNode::Kind::SERVICE);
  EXPECT_EQ(testService->name(), "TestService");
  const ServiceNode& s = testService->asService();
  EXPECT_EQ(s.baseService(), nullptr);

  EXPECT_EQ(s.functions().size(), 4);

  EXPECT_EQ(s.functions()[0].name(), "foo");
  EXPECT_EQ(
      s.functions()[0].response().type()->asStruct().definition().name(),
      "TestStruct");
  EXPECT_EQ(s.functions()[0].response().sink(), nullptr);
  EXPECT_EQ(s.functions()[0].response().stream(), nullptr);
  EXPECT_EQ(s.functions()[0].response().interaction(), nullptr);
  EXPECT_EQ(s.functions()[0].params().size(), 1);
  EXPECT_EQ(s.functions()[0].params()[0].id(), FieldId{1});
  EXPECT_EQ(s.functions()[0].params()[0].name(), "input");
  EXPECT_EQ(s.functions()[0].params()[0].type(), TypeRef::of(Primitive::I32));

  const InteractionNode& i =
      program->definitionsByName().at("TestInteraction")->asInteraction();

  EXPECT_EQ(s.functions()[1].name(), "createInteraction");
  EXPECT_EQ(s.functions()[1].response().type(), nullptr);
  EXPECT_EQ(s.functions()[1].response().sink(), nullptr);
  EXPECT_EQ(s.functions()[1].response().stream(), nullptr);
  EXPECT_EQ(s.functions()[1].response().interaction(), &i);

  EXPECT_EQ(s.functions()[2].name(), "createStream");
  EXPECT_EQ(*s.functions()[2].response().type(), TypeRef::of(Primitive::I32));
  EXPECT_EQ(
      s.functions()[2].response().stream()->payloadType(),
      TypeRef::of(Primitive::I32));

  EXPECT_EQ(s.functions()[3].name(), "createInteractionAndStream");
  EXPECT_EQ(*s.functions()[3].response().type(), TypeRef::of(Primitive::I32));
  EXPECT_EQ(s.functions()[3].response().interaction(), &i);
  EXPECT_EQ(
      s.functions()[3].response().stream()->payloadType(),
      TypeRef::of(Primitive::I32));
  EXPECT_EQ(s.functions()[3].response().sink(), nullptr);

  folly::not_null<const DefinitionNode*> testService2 =
      program2->definitionsByName().at("TestService2");
  EXPECT_EQ(&testService2->program(), program2.unwrap());
  EXPECT_EQ(testService2->kind(), DefinitionNode::Kind::SERVICE);
  EXPECT_EQ(testService2->name(), "TestService2");
  const ServiceNode& s2 = testService2->asService();

  EXPECT_EQ(s2.functions().size(), 0);
  EXPECT_EQ(s2.baseService(), &s);

  EXPECT_EQ(
      s2.toDebugString(),
      "ServiceNode (name='TestService2')\n"
      "╰─ baseService = ServiceNode (name='TestService')\n"
      "   ╰─ functions\n"
      "      ├─ FunctionNode (name='foo')\n"
      "      │  ├─ FunctionNode::Response\n"
      "      │  │  ╰─ returnType = StructNode 'TestStruct'\n"
      "      │  │     ├─ FieldNode (id=1, presence=UNQUALIFIED, name='field1')\n"
      "      │  │     │  ├─ type = I32\n"
      "      │  │     │  ╰─ customDefault = ...\n"
      "      │  │     ╰─ FieldNode (id=2, presence=OPTIONAL, name='field2')\n"
      "      │  │        ╰─ type = EnumNode 'TestEnum'\n"
      "      │  │           ├─ 'UNSET' → 0\n"
      "      │  │           ├─ 'VALUE_1' → 1\n"
      "      │  │           ╰─ 'VALUE_2' → 2\n"
      "      │  ╰─ params\n"
      "      │     ╰─ FunctionNode::Param (id=1, name='input')\n"
      "      │        ╰─ type = I32\n"
      "      ├─ FunctionNode (name='createInteraction')\n"
      "      │  ╰─ FunctionNode::Response\n"
      "      │     ├─ returnType = void\n"
      "      │     ╰─ InteractionNode (name='TestInteraction')\n"
      "      │        ╰─ functions\n"
      "      │           ╰─ FunctionNode (name='foo')\n"
      "      │              ├─ FunctionNode::Response\n"
      "      │              │  ╰─ returnType = I32\n"
      "      │              ├─ params\n"
      "      │              │  ╰─ FunctionNode::Param (id=1, name='input')\n"
      "      │              │     ╰─ type = StructNode 'TestRecursiveStruct'\n"
      "      │              │        ╰─ FieldNode (id=1, presence=OPTIONAL, name='myself')\n"
      "      │              │           ╰─ type = StructNode 'TestRecursiveStruct'\n"
      "      │              ╰─ exceptions\n"
      "      │                 ╰─ FunctionNode::Exception (id=1, name='ex')\n"
      "      │                    ╰─ type = ExceptionNode 'TestException'\n"
      "      │                       ╰─ FieldNode (id=1, presence=UNQUALIFIED, name='blob')\n"
      "      │                          ╰─ type = BINARY\n"
      "      ├─ FunctionNode (name='createStream')\n"
      "      │  ╰─ FunctionNode::Response\n"
      "      │     ├─ returnType = I32\n"
      "      │     ╰─ FunctionNode::Stream\n"
      "      │        ╰─ payloadType = I32\n"
      "      ╰─ FunctionNode (name='createInteractionAndStream')\n"
      "         ╰─ FunctionNode::Response\n"
      "            ├─ returnType = I32\n"
      "            ├─ InteractionNode (name='TestInteraction')\n"
      "            ╰─ FunctionNode::Stream\n"
      "               ╰─ payloadType = I32\n");
}

TEST_F(ServiceSchemaTest, Interaction) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> testInteraction =
      program->definitionsByName().at("TestInteraction");
  EXPECT_EQ(&testInteraction->program(), program.unwrap());
  EXPECT_EQ(testInteraction->kind(), DefinitionNode::Kind::INTERACTION);
  EXPECT_EQ(testInteraction->name(), "TestInteraction");
  const InteractionNode& i = testInteraction->asInteraction();

  EXPECT_EQ(i.functions().size(), 1);
  EXPECT_EQ(i.functions()[0].name(), "foo");
  EXPECT_EQ(*i.functions()[0].response().type(), TypeRef::of(Primitive::I32));
  EXPECT_EQ(i.functions()[0].response().sink(), nullptr);
  EXPECT_EQ(i.functions()[0].response().stream(), nullptr);
  EXPECT_EQ(i.functions()[0].response().interaction(), nullptr);

  const StructNode& testRecursiveStruct =
      program->definitionsByName().at("TestRecursiveStruct")->asStruct();
  EXPECT_EQ(i.functions()[0].params().size(), 1);
  EXPECT_EQ(i.functions()[0].params()[0].id(), FieldId{1});
  EXPECT_EQ(i.functions()[0].params()[0].name(), "input");
  EXPECT_EQ(
      i.functions()[0].params()[0].type(), TypeRef::of(testRecursiveStruct));

  EXPECT_EQ(
      i.toDebugString(),
      "InteractionNode (name='TestInteraction')\n"
      "╰─ functions\n"
      "   ╰─ FunctionNode (name='foo')\n"
      "      ├─ FunctionNode::Response\n"
      "      │  ╰─ returnType = I32\n"
      "      ├─ params\n"
      "      │  ╰─ FunctionNode::Param (id=1, name='input')\n"
      "      │     ╰─ type = StructNode 'TestRecursiveStruct'\n"
      "      │        ╰─ FieldNode (id=1, presence=OPTIONAL, name='myself')\n"
      "      │           ╰─ type = StructNode 'TestRecursiveStruct'\n"
      "      ╰─ exceptions\n"
      "         ╰─ FunctionNode::Exception (id=1, name='ex')\n"
      "            ╰─ type = ExceptionNode 'TestException'\n"
      "               ╰─ FieldNode (id=1, presence=UNQUALIFIED, name='blob')\n"
      "                  ╰─ type = BINARY\n");
}

TEST_F(ServiceSchemaTest, StructuredAnnotation) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> testUnion =
      program->definitionsByName().at("TestUnion");

  const auto& annotations = testUnion->annotations();
  EXPECT_EQ(annotations.size(), 1);
  EXPECT_EQ(
      &annotations[0].type().asStruct(),
      &program->definitionsByName().at("TestStructuredAnnotation")->asStruct());
  EXPECT_EQ(annotations[0].fields().size(), 1);
  EXPECT_EQ(annotations[0].fields().at("field1").as_i64(), 3);
}

TEST_F(ServiceSchemaTest, StructuredAnnotationWithoutUri) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> testException =
      program->definitionsByName().at("TestException");

  const auto& annotations = testException->annotations();
  EXPECT_EQ(annotations.size(), 1);
  EXPECT_EQ(
      &annotations[0].type().asStruct(),
      &program->definitionsByName()
           .at("TestStructuredAnnotationWithoutUri")
           ->asStruct());
  EXPECT_EQ(annotations[0].fields().size(), 1);
  EXPECT_EQ(annotations[0].fields().at("field1").as_i64(), 3);
}

TEST_F(ServiceSchemaTest, StructuredAnnotationWhichIsATypedef) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  const ServiceNode& testService =
      program->definitionsByName().at("TestService")->asService();
  folly::span<const FunctionNode> functions = testService.functions();
  const FunctionNode& foo = *std::find_if(
      functions.begin(), functions.end(), [](const FunctionNode& f) {
        return f.name() == "foo";
      });

  const auto& annotations = foo.annotations();
  EXPECT_EQ(annotations.size(), 1);
  EXPECT_EQ(
      &annotations[0].type().asTypedef(),
      &program->definitionsByName()
           .at("TypedefToTestStructuredAnnotation")
           ->asTypedef());
  EXPECT_EQ(
      &annotations[0].type().trueType().asStruct(),
      &program->definitionsByName().at("TestStructuredAnnotation")->asStruct());
}

TEST_F(ServiceSchemaTest, StructuredAnnotationOnField) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  const ExceptionNode& testException =
      program->definitionsByName().at("TestException")->asException();
  folly::span<const Annotation> annotations =
      testException.fields()[0].annotations();
  EXPECT_EQ(annotations.size(), 1);

  EXPECT_EQ(
      &annotations[0].type().asStruct(),
      &program->definitionsByName().at("TestStructuredAnnotation")->asStruct());
}

TEST_F(ServiceSchemaTest, RecursiveStruct) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto program = findProgramByName(syntaxGraph, "syntax_graph");

  folly::not_null<const DefinitionNode*> testRecursiveStruct =
      program->definitionsByName().at("TestRecursiveStruct");
  const StructNode& s = testRecursiveStruct->asStruct();

  EXPECT_EQ(s.fields().size(), 1);
  EXPECT_EQ(s.fields()[0].type(), TypeRef::of(s));

  EXPECT_EQ(
      s.toDebugString(),
      "StructNode 'TestRecursiveStruct'\n"
      "╰─ FieldNode (id=1, presence=OPTIONAL, name='myself')\n"
      "   ╰─ type = StructNode 'TestRecursiveStruct'\n");
}

TEST_F(ServiceSchemaTest, LookupByDefinitionKeys) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  std::vector<type::DefinitionKey> serviceDefinitionKeys =
      definitionKeysFor<test::TestService>();

  // Otherwise, the test is not meaningful
  ASSERT_FALSE(serviceDefinitionKeys.empty());

  for (const auto& definitionKey : serviceDefinitionKeys) {
    const DefinitionNode& definition =
        detail::lookUpDefinition(syntaxGraph, definitionKey);
    EXPECT_TRUE(definition.isService());
  }
}

TEST_F(ServiceSchemaTest, getServiceSchemaNodes) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  std::vector<type::DefinitionKey> serviceDefinitionKeys =
      definitionKeysFor<test::TestService>();

  ASSERT_EQ(serviceDefinitionKeys.size(), 1);

  const auto* dynamicService =
      &detail::lookUpDefinition(syntaxGraph, serviceDefinitionKeys.back())
           .asService();

  const auto staticServiceNodes =
      apache::thrift::ServiceHandler<test::TestService>()
          .getServiceSchemaNodes();
  ASSERT_EQ(staticServiceNodes.size(), 1);

  const auto* staticService = staticServiceNodes.back().unwrap();

  // static service uses the global registry while dynamic service has its  own
  // SyntaxGraph instance.
  EXPECT_NE(dynamicService, staticService);

  EXPECT_EQ(
      dynamicService->definition().name(), staticService->definition().name());
}

TEST(SyntaxGraphTest, getDefinitionNode) {
  auto& registry = SchemaRegistry::get();

  const DefinitionNode& testStruct =
      registry.getDefinitionNode<test::TestStruct>();
  const StructNode& stct = testStruct.asStruct();
  EXPECT_EQ(stct.definition().name(), "TestStruct");

  const DefinitionNode& testEnum = registry.getDefinitionNode<test::TestEnum>();
  const EnumNode& enm = testEnum.asEnum();
  EXPECT_EQ(enm.definition().name(), "TestEnum");

  const DefinitionNode& testService =
      registry.getDefinitionNode<test::TestService>();
  const ServiceNode& serv = testService.asService();
  EXPECT_EQ(serv.definition().name(), "TestService");

  // Adding to the SyntaxGraph should not invalidate old nodes
  registry.getDefinitionNode<test::OtherTestStruct>();
  EXPECT_EQ(serv.definition().name(), "TestService");
}

TEST(SyntaxGraphTest, getNode) {
  auto& registry = SchemaRegistry::get();

  const StructNode& stct = registry.getNode<test::TestStruct>();
  EXPECT_EQ(stct.definition().name(), "TestStruct");

  const EnumNode& enm = registry.getNode<test::TestEnum>();
  EXPECT_EQ(enm.definition().name(), "TestEnum");

  const ServiceNode& serv = registry.getNode<test::TestService>();
  EXPECT_EQ(serv.definition().name(), "TestService");

  const StructNode& annot =
      registry.getNode<facebook::thrift::annotation::Experimental>();
  EXPECT_EQ(annot.definition().name(), "Experimental");
}

TEST_F(ServiceSchemaTest, asTypeSystem) {
  auto syntaxGraph = SyntaxGraph::fromSchema(schemaFor<test::TestService>());
  auto mainProgram = findProgramByName(syntaxGraph, "syntax_graph");
  auto def = mainProgram->definitionsByName().at("TestRecursiveStruct");
  auto uri = "meta.com/thrift_test/TestRecursiveStruct";
  ASSERT_EQ(def->asStruct().uri(), uri);

  auto& typeSystem = syntaxGraph.asTypeSystem();

  const type_system::StructNode& structNode =
      typeSystem.getUserDefinedTypeOrThrow(uri).asStruct();
  EXPECT_EQ(structNode.uri(), uri);
  EXPECT_EQ(structNode.fields().size(), 1);
  EXPECT_EQ(structNode.fields()[0].identity().name(), "myself");
  EXPECT_EQ(structNode.fields()[0].identity().id(), FieldId{1});
  EXPECT_EQ(
      structNode.fields()[0].presence(),
      type_system::PresenceQualifier::OPTIONAL_);
  EXPECT_EQ(structNode.fields()[0].type().asStruct().uri(), uri);
  EXPECT_EQ(&structNode.fields()[0].type().asStruct(), &structNode);
  EXPECT_EQ(&syntaxGraph.asTypeSystemStructNode(def->asStruct()), &structNode);

  uri = "meta.com/thrift_test/TestUnion";
  const type_system::UnionNode& unionNode =
      typeSystem.getUserDefinedTypeOrThrow(uri).asUnion();
  EXPECT_EQ(unionNode.uri(), uri);
  EXPECT_EQ(unionNode.fields().size(), 2);
  EXPECT_EQ(unionNode.fields()[0].identity().name(), "s");
  EXPECT_EQ(unionNode.fields()[0].identity().id(), FieldId{1});
  EXPECT_EQ(
      unionNode.fields()[0].presence(),
      type_system::PresenceQualifier::OPTIONAL_);

  uri = "meta.com/thrift_test/TestEnum";
  const type_system::EnumNode& enumNode =
      typeSystem.getUserDefinedTypeOrThrow(uri).asEnum();
  EXPECT_EQ(enumNode.uri(), uri);
  EXPECT_EQ(enumNode.values().size(), 3);
  EXPECT_EQ(enumNode.values()[0].name, "UNSET");
  EXPECT_EQ(enumNode.values()[0].i32, 0);
  EXPECT_EQ(enumNode.values()[1].name, "VALUE_1");
  EXPECT_EQ(enumNode.values()[1].i32, 1);
  EXPECT_EQ(enumNode.values()[2].name, "VALUE_2");
  EXPECT_EQ(enumNode.values()[2].i32, 2);
}

TEST(SyntaxGraphTest, getSchemaMerge) {
  auto& registry = SchemaRegistry::get();

  // getNode will merge new schemas to the existing one.
  // This test will check after the merging, old nodes are still valid.
  const auto& other = registry.getNode<test::OtherTestStruct>();
  const auto& test = registry.getNode<test::TestStruct>();
  const auto& prog = registry.getDefinitionNode<test::TestStruct2>().program();
  ASSERT_EQ(prog.includes().size(), 1);
  EXPECT_EQ(prog.includes()[0]->name(), "syntax_graph");
  EXPECT_EQ(test.definition().name(), "TestStruct");
  EXPECT_EQ(other.definition().name(), "OtherTestStruct");
}

TEST(SyntaxGraphTest, anyField) {
  auto& registry = SchemaRegistry::get();
  const auto& s = registry.getNode<test::StructWithAny>();
  const auto& f = s.fields()[0];
  const auto& anyStruct = f.type().trueType();
  EXPECT_EQ(anyStruct.asStruct().uri(), "facebook.com/thrift/type/Any");
}

} // namespace apache::thrift::syntax_graph
