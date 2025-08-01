/**
 * Autogenerated by Thrift for thrift/compiler/test/fixtures/default_values_rectification_before/src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#include "thrift/compiler/test/fixtures/default_values_rectification_before/gen-cpp2/module_types.h"
#include "thrift/compiler/test/fixtures/default_values_rectification_before/gen-cpp2/module_types.tcc"

#include <thrift/lib/cpp2/gen/module_types_cpp.h>

#include "thrift/compiler/test/fixtures/default_values_rectification_before/gen-cpp2/module_data.h"
[[maybe_unused]] static constexpr std::string_view kModuleName = "module";


namespace apache {
namespace thrift {
namespace detail {

void TccStructTraits<::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct>::translateFieldName(
    std::string_view _fname,
    int16_t& fid,
    apache::thrift::protocol::TType& _ftype) noexcept {
  using data = apache::thrift::TStructDataStorage<::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct>;
  static const st::translate_field_name_table table{
      data::fields_size,
      data::fields_names.data(),
      data::fields_ids.data(),
      data::fields_types.data()};
  st::translate_field_name(_fname, fid, _ftype, table);
}

} // namespace detail
} // namespace thrift
} // namespace apache

namespace facebook::thrift::compiler::test::fixtures::default_values_rectification {

std::string_view EmptyStruct::__fbthrift_thrift_uri() {
  return "facebook.com/thrift/compiler/test/fixtures/default_values_rectification/EmptyStruct";
}

std::string_view EmptyStruct::__fbthrift_get_field_name(::apache::thrift::FieldOrdinal ord) {
  if (ord == ::apache::thrift::FieldOrdinal{0}) { return {}; }
  return apache::thrift::TStructDataStorage<EmptyStruct>::fields_names[folly::to_underlying(ord) - 1];
}
std::string_view EmptyStruct::__fbthrift_get_class_name() {
  return apache::thrift::TStructDataStorage<EmptyStruct>::name;
}


EmptyStruct::EmptyStruct(apache::thrift::FragileConstructor) {}


void EmptyStruct::__fbthrift_clear() {
  // clear all fields
}

void EmptyStruct::__fbthrift_clear_terse_fields() {
}

bool EmptyStruct::__fbthrift_is_empty() const {
  return true;
}

bool EmptyStruct::operator==([[maybe_unused]] const EmptyStruct& rhs) const {
  return ::apache::thrift::op::detail::StructEquality{}(*this, rhs);
}

bool EmptyStruct::operator<([[maybe_unused]] const EmptyStruct& rhs) const {
  return ::apache::thrift::op::detail::StructLessThan{}(*this, rhs);
}


void swap([[maybe_unused]] EmptyStruct& a, [[maybe_unused]] EmptyStruct& b) {
  using ::std::swap;
}



} // namespace facebook::thrift::compiler::test::fixtures::default_values_rectification

namespace apache {
namespace thrift {
namespace detail {

void TccStructTraits<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>::translateFieldName(
    std::string_view _fname,
    int16_t& fid,
    apache::thrift::protocol::TType& _ftype) noexcept {
  using data = apache::thrift::TStructDataStorage<::facebook::thrift::compiler::test::fixtures::default_values_rectification::TestStruct>;
  static const st::translate_field_name_table table{
      data::fields_size,
      data::fields_names.data(),
      data::fields_ids.data(),
      data::fields_types.data()};
  st::translate_field_name(_fname, fid, _ftype, table);
}

} // namespace detail
} // namespace thrift
} // namespace apache

namespace facebook::thrift::compiler::test::fixtures::default_values_rectification {

std::string_view TestStruct::__fbthrift_thrift_uri() {
  return "facebook.com/thrift/compiler/test/fixtures/default_values_rectification/TestStruct";
}

std::string_view TestStruct::__fbthrift_get_field_name(::apache::thrift::FieldOrdinal ord) {
  if (ord == ::apache::thrift::FieldOrdinal{0}) { return {}; }
  return apache::thrift::TStructDataStorage<TestStruct>::fields_names[folly::to_underlying(ord) - 1];
}
std::string_view TestStruct::__fbthrift_get_class_name() {
  return apache::thrift::TStructDataStorage<TestStruct>::name;
}

TestStruct::TestStruct(const TestStruct&) = default;
TestStruct& TestStruct::operator=(const TestStruct&) = default;
TestStruct::TestStruct() :
    __fbthrift_field_unqualified_int_field(static_cast<::std::int32_t>(0)),
    __fbthrift_field_unqualified_bool_field(false),
    __fbthrift_field_optional_int_field(static_cast<::std::int32_t>(42)),
    __fbthrift_field_optional_bool_field(true),
    __fbthrift_field_optional_list_field(std::initializer_list<::std::int32_t>{ static_cast<::std::int32_t>(1),
  static_cast<::std::int32_t>(2) }) {
}


TestStruct::~TestStruct() {}

TestStruct::TestStruct([[maybe_unused]] TestStruct&& other) noexcept :
    __fbthrift_field_unqualified_int_field(std::move(other.__fbthrift_field_unqualified_int_field)),
    __fbthrift_field_unqualified_bool_field(std::move(other.__fbthrift_field_unqualified_bool_field)),
    __fbthrift_field_unqualified_list_field(std::move(other.__fbthrift_field_unqualified_list_field)),
    __fbthrift_field_unqualified_struct_field(std::move(other.__fbthrift_field_unqualified_struct_field)),
    __fbthrift_field_optional_int_field(std::move(other.__fbthrift_field_optional_int_field)),
    __fbthrift_field_optional_bool_field(std::move(other.__fbthrift_field_optional_bool_field)),
    __fbthrift_field_optional_list_field(std::move(other.__fbthrift_field_optional_list_field)),
    __fbthrift_field_optional_struct_field(std::move(other.__fbthrift_field_optional_struct_field)),
    __isset(other.__isset) {
}

TestStruct& TestStruct::operator=([[maybe_unused]] TestStruct&& other) noexcept {
    this->__fbthrift_field_unqualified_int_field = std::move(other.__fbthrift_field_unqualified_int_field);
    this->__fbthrift_field_unqualified_bool_field = std::move(other.__fbthrift_field_unqualified_bool_field);
    this->__fbthrift_field_unqualified_list_field = std::move(other.__fbthrift_field_unqualified_list_field);
    this->__fbthrift_field_unqualified_struct_field = std::move(other.__fbthrift_field_unqualified_struct_field);
    this->__fbthrift_field_optional_int_field = std::move(other.__fbthrift_field_optional_int_field);
    this->__fbthrift_field_optional_bool_field = std::move(other.__fbthrift_field_optional_bool_field);
    this->__fbthrift_field_optional_list_field = std::move(other.__fbthrift_field_optional_list_field);
    this->__fbthrift_field_optional_struct_field = std::move(other.__fbthrift_field_optional_struct_field);
    __isset = other.__isset;
    return *this;
}


TestStruct::TestStruct(apache::thrift::FragileConstructor, ::std::int32_t unqualified_int_field__arg, bool unqualified_bool_field__arg, ::std::vector<::std::int32_t> unqualified_list_field__arg, ::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct unqualified_struct_field__arg, ::std::int32_t optional_int_field__arg, bool optional_bool_field__arg, ::std::vector<::std::int32_t> optional_list_field__arg, ::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct optional_struct_field__arg) :
    __fbthrift_field_unqualified_int_field(std::move(unqualified_int_field__arg)),
    __fbthrift_field_unqualified_bool_field(std::move(unqualified_bool_field__arg)),
    __fbthrift_field_unqualified_list_field(std::move(unqualified_list_field__arg)),
    __fbthrift_field_unqualified_struct_field(std::move(unqualified_struct_field__arg)),
    __fbthrift_field_optional_int_field(std::move(optional_int_field__arg)),
    __fbthrift_field_optional_bool_field(std::move(optional_bool_field__arg)),
    __fbthrift_field_optional_list_field(std::move(optional_list_field__arg)),
    __fbthrift_field_optional_struct_field(std::move(optional_struct_field__arg)) { 
  __isset.set(folly::index_constant<0>(), true);
  __isset.set(folly::index_constant<1>(), true);
  __isset.set(folly::index_constant<2>(), true);
  __isset.set(folly::index_constant<3>(), true);
  __isset.set(folly::index_constant<4>(), true);
  __isset.set(folly::index_constant<5>(), true);
  __isset.set(folly::index_constant<6>(), true);
  __isset.set(folly::index_constant<7>(), true);
}


void TestStruct::__fbthrift_clear() {
  // clear all fields
  this->__fbthrift_field_unqualified_int_field = ::std::int32_t();
  this->__fbthrift_field_unqualified_bool_field = bool();
  this->__fbthrift_field_unqualified_list_field.clear();
  this->__fbthrift_field_optional_int_field = ::std::int32_t();
  this->__fbthrift_field_optional_bool_field = bool();
  this->__fbthrift_field_optional_list_field.clear();
  __isset = {};
}

void TestStruct::__fbthrift_clear_terse_fields() {
}

bool TestStruct::__fbthrift_is_empty() const {
  return false;
}

bool TestStruct::operator==([[maybe_unused]] const TestStruct& rhs) const {
  return ::apache::thrift::op::detail::StructEquality{}(*this, rhs);
}

bool TestStruct::operator<([[maybe_unused]] const TestStruct& rhs) const {
  return ::apache::thrift::op::detail::StructLessThan{}(*this, rhs);
}


::std::int32_t TestStruct::get_unqualified_int_field() const {
  return __fbthrift_field_unqualified_int_field;
}

::std::int32_t& TestStruct::set_unqualified_int_field(::std::int32_t unqualified_int_field_) {
  unqualified_int_field_ref() = unqualified_int_field_;
  return __fbthrift_field_unqualified_int_field;
}

bool TestStruct::get_unqualified_bool_field() const {
  return __fbthrift_field_unqualified_bool_field;
}

bool& TestStruct::set_unqualified_bool_field(bool unqualified_bool_field_) {
  unqualified_bool_field_ref() = unqualified_bool_field_;
  return __fbthrift_field_unqualified_bool_field;
}

const ::std::vector<::std::int32_t>& TestStruct::get_unqualified_list_field() const& {
  return __fbthrift_field_unqualified_list_field;
}

::std::vector<::std::int32_t> TestStruct::get_unqualified_list_field() && {
  return static_cast<::std::vector<::std::int32_t>&&>(__fbthrift_field_unqualified_list_field);
}

const ::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct& TestStruct::get_unqualified_struct_field() const& {
  return __fbthrift_field_unqualified_struct_field;
}

::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct TestStruct::get_unqualified_struct_field() && {
  return static_cast<::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct&&>(__fbthrift_field_unqualified_struct_field);
}

const ::std::int32_t* TestStruct::get_optional_int_field() const& {
  return optional_int_field_ref().has_value() ? std::addressof(__fbthrift_field_optional_int_field) : nullptr;
}

::std::int32_t* TestStruct::get_optional_int_field() & {
  return optional_int_field_ref().has_value() ? std::addressof(__fbthrift_field_optional_int_field) : nullptr;
}

::std::int32_t& TestStruct::set_optional_int_field(::std::int32_t optional_int_field_) {
  optional_int_field_ref() = optional_int_field_;
  return __fbthrift_field_optional_int_field;
}

const bool* TestStruct::get_optional_bool_field() const& {
  return optional_bool_field_ref().has_value() ? std::addressof(__fbthrift_field_optional_bool_field) : nullptr;
}

bool* TestStruct::get_optional_bool_field() & {
  return optional_bool_field_ref().has_value() ? std::addressof(__fbthrift_field_optional_bool_field) : nullptr;
}

bool& TestStruct::set_optional_bool_field(bool optional_bool_field_) {
  optional_bool_field_ref() = optional_bool_field_;
  return __fbthrift_field_optional_bool_field;
}

const ::std::vector<::std::int32_t>* TestStruct::get_optional_list_field() const& {
  return optional_list_field_ref().has_value() ? std::addressof(__fbthrift_field_optional_list_field) : nullptr;
}

::std::vector<::std::int32_t>* TestStruct::get_optional_list_field() & {
  return optional_list_field_ref().has_value() ? std::addressof(__fbthrift_field_optional_list_field) : nullptr;
}

const ::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct* TestStruct::get_optional_struct_field() const& {
  return optional_struct_field_ref().has_value() ? std::addressof(__fbthrift_field_optional_struct_field) : nullptr;
}

::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct* TestStruct::get_optional_struct_field() & {
  return optional_struct_field_ref().has_value() ? std::addressof(__fbthrift_field_optional_struct_field) : nullptr;
}

void swap([[maybe_unused]] TestStruct& a, [[maybe_unused]] TestStruct& b) {
  using ::std::swap;
  swap(a.__fbthrift_field_unqualified_int_field, b.__fbthrift_field_unqualified_int_field);
  swap(a.__fbthrift_field_unqualified_bool_field, b.__fbthrift_field_unqualified_bool_field);
  swap(a.__fbthrift_field_unqualified_list_field, b.__fbthrift_field_unqualified_list_field);
  swap(a.__fbthrift_field_unqualified_struct_field, b.__fbthrift_field_unqualified_struct_field);
  swap(a.__fbthrift_field_optional_int_field, b.__fbthrift_field_optional_int_field);
  swap(a.__fbthrift_field_optional_bool_field, b.__fbthrift_field_optional_bool_field);
  swap(a.__fbthrift_field_optional_list_field, b.__fbthrift_field_optional_list_field);
  swap(a.__fbthrift_field_optional_struct_field, b.__fbthrift_field_optional_struct_field);
  swap(a.__isset, b.__isset);
}


static_assert(
    ::apache::thrift::detail::st::gen_check_json<
        TestStruct,
        ::apache::thrift::type_class::structure,
        ::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct>,
    "inconsistent use of json option");
static_assert(
    ::apache::thrift::detail::st::gen_check_json<
        TestStruct,
        ::apache::thrift::type_class::structure,
        ::facebook::thrift::compiler::test::fixtures::default_values_rectification::EmptyStruct>,
    "inconsistent use of json option");

} // namespace facebook::thrift::compiler::test::fixtures::default_values_rectification

namespace facebook::thrift::compiler::test::fixtures::default_values_rectification { namespace {
[[maybe_unused]] FOLLY_ERASE void validateAdapters() {
}
}} // namespace facebook::thrift::compiler::test::fixtures::default_values_rectification
namespace apache::thrift::detail::annotation {
}
