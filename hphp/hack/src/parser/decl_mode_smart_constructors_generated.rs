/**
 * Copyright (c) 2016, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the "hack" directory of this source tree. An additional
 * directory.
 *
 **
 *
 * THIS FILE IS @generated; DO NOT EDIT IT
 * To regenerate this file, run
 *
 *   buck run //hphp/hack/src:generate_full_fidelity
 *
 **
 *
 */
use parser_core_types::{
    lexable_token::LexableToken, syntax::SyntaxValueType, syntax_by_ref::syntax::Syntax,
    token_factory::TokenFactory,
};
use smart_constructors::SmartConstructors;
use syntax_smart_constructors::SyntaxSmartConstructors;
use crate::*;

impl<'s, 'a, Token, Value, TF> SmartConstructors
    for DeclModeSmartConstructors<'s, 'a, Syntax<'a, Token, Value>, Token, Value, TF>
where
    TF: TokenFactory<Token = SyntaxToken<'s, 'a, Token, Value>>,
    Token: LexableToken + Copy,
    Value: SyntaxValueType<Token> + Clone,
{
    type State = State<'s, 'a, Syntax<'a, Token, Value>>;
    type Factory = TF;
    type Output = Syntax<'a, Token, Value>;

    fn state_mut(&mut self) -> &mut State<'s, 'a, Syntax<'a, Token, Value>> {
        &mut self.state
    }

    fn into_state(self) -> State<'s, 'a, Syntax<'a, Token, Value>> {
        self.state
    }

    fn token_factory_mut(&mut self) -> &mut Self::Factory {
        &mut self.token_factory
    }

    fn make_missing(&mut self, o: usize) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_missing(self, o)
    }

    fn make_token(&mut self, token: <Self::Factory as TokenFactory>::Token) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_token(self, token)
    }

    fn make_list(&mut self, items: Vec<Self::Output>, offset: usize) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_list(self, items, offset)
    }

    fn make_end_of_file(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_end_of_file(self, arg0)
    }

    fn make_script(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_script(self, arg0)
    }

    fn make_qualified_name(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_qualified_name(self, arg0)
    }

    fn make_module_name(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_module_name(self, arg0)
    }

    fn make_simple_type_specifier(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_simple_type_specifier(self, arg0)
    }

    fn make_literal_expression(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_literal_expression(self, arg0)
    }

    fn make_prefixed_string_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_prefixed_string_expression(self, arg0, arg1)
    }

    fn make_prefixed_code_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_prefixed_code_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_variable_expression(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_variable_expression(self, arg0)
    }

    fn make_pipe_variable_expression(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_pipe_variable_expression(self, arg0)
    }

    fn make_file_attribute_specification(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_file_attribute_specification(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_enum_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output, arg10: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_enum_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)
    }

    fn make_enum_use(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_enum_use(self, arg0, arg1, arg2)
    }

    fn make_enumerator(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_enumerator(self, arg0, arg1, arg2, arg3)
    }

    fn make_enum_class_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output, arg10: Self::Output, arg11: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_enum_class_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)
    }

    fn make_enum_class_enumerator(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_enum_class_enumerator(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_alias_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_alias_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
    }

    fn make_context_alias_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_context_alias_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
    }

    fn make_case_type_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output, arg10: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_case_type_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)
    }

    fn make_case_type_variant(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_case_type_variant(self, arg0, arg1, arg2)
    }

    fn make_property_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_property_declaration(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_property_declarator(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_property_declarator(self, arg0, arg1)
    }

    fn make_namespace_declaration(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_namespace_declaration(self, arg0, arg1)
    }

    fn make_namespace_declaration_header(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_namespace_declaration_header(self, arg0, arg1)
    }

    fn make_namespace_body(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_namespace_body(self, arg0, arg1, arg2)
    }

    fn make_namespace_empty_body(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_namespace_empty_body(self, arg0)
    }

    fn make_namespace_use_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_namespace_use_declaration(self, arg0, arg1, arg2, arg3)
    }

    fn make_namespace_group_use_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_namespace_group_use_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6)
    }

    fn make_namespace_use_clause(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_namespace_use_clause(self, arg0, arg1, arg2, arg3)
    }

    fn make_function_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_function_declaration(self, arg0, arg1, arg2)
    }

    fn make_function_declaration_header(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output, arg10: Self::Output, arg11: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_function_declaration_header(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)
    }

    fn make_contexts(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_contexts(self, arg0, arg1, arg2)
    }

    fn make_where_clause(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_where_clause(self, arg0, arg1)
    }

    fn make_where_constraint(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_where_constraint(self, arg0, arg1, arg2)
    }

    fn make_methodish_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_methodish_declaration(self, arg0, arg1, arg2, arg3)
    }

    fn make_methodish_trait_resolution(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_methodish_trait_resolution(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_classish_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output, arg10: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_classish_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)
    }

    fn make_classish_body(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_classish_body(self, arg0, arg1, arg2)
    }

    fn make_trait_use(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_trait_use(self, arg0, arg1, arg2)
    }

    fn make_require_clause(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_require_clause(self, arg0, arg1, arg2, arg3)
    }

    fn make_require_clause_constraint(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_require_clause_constraint(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_const_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_const_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5)
    }

    fn make_constant_declarator(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_constant_declarator(self, arg0, arg1)
    }

    fn make_type_const_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_type_const_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
    }

    fn make_context_const_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_context_const_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
    }

    fn make_decorated_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_decorated_expression(self, arg0, arg1)
    }

    fn make_parameter_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output, arg10: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_parameter_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10)
    }

    fn make_old_attribute_specification(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_old_attribute_specification(self, arg0, arg1, arg2)
    }

    fn make_attribute_specification(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_attribute_specification(self, arg0)
    }

    fn make_attribute(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_attribute(self, arg0, arg1)
    }

    fn make_inclusion_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_inclusion_expression(self, arg0, arg1)
    }

    fn make_inclusion_directive(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_inclusion_directive(self, arg0, arg1)
    }

    fn make_compound_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_compound_statement(self, arg0, arg1, arg2)
    }

    fn make_expression_statement(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_expression_statement(self, arg0, arg1)
    }

    fn make_markup_section(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_markup_section(self, arg0, arg1)
    }

    fn make_markup_suffix(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_markup_suffix(self, arg0, arg1)
    }

    fn make_unset_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_unset_statement(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_declare_local_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_declare_local_statement(self, arg0, arg1, arg2, arg3, arg4, arg5)
    }

    fn make_using_statement_block_scoped(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_using_statement_block_scoped(self, arg0, arg1, arg2, arg3, arg4, arg5)
    }

    fn make_using_statement_function_scoped(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_using_statement_function_scoped(self, arg0, arg1, arg2, arg3)
    }

    fn make_while_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_while_statement(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_if_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_if_statement(self, arg0, arg1, arg2, arg3, arg4, arg5)
    }

    fn make_else_clause(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_else_clause(self, arg0, arg1)
    }

    fn make_try_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_try_statement(self, arg0, arg1, arg2, arg3)
    }

    fn make_catch_clause(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_catch_clause(self, arg0, arg1, arg2, arg3, arg4, arg5)
    }

    fn make_finally_clause(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_finally_clause(self, arg0, arg1)
    }

    fn make_do_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_do_statement(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6)
    }

    fn make_for_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_for_statement(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
    }

    fn make_foreach_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_foreach_statement(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9)
    }

    fn make_switch_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_switch_statement(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6)
    }

    fn make_switch_section(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_switch_section(self, arg0, arg1, arg2)
    }

    fn make_switch_fallthrough(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_switch_fallthrough(self, arg0, arg1)
    }

    fn make_case_label(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_case_label(self, arg0, arg1, arg2)
    }

    fn make_default_label(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_default_label(self, arg0, arg1)
    }

    fn make_match_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_match_statement(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6)
    }

    fn make_match_statement_arm(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_match_statement_arm(self, arg0, arg1, arg2)
    }

    fn make_return_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_return_statement(self, arg0, arg1, arg2)
    }

    fn make_yield_break_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_yield_break_statement(self, arg0, arg1, arg2)
    }

    fn make_throw_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_throw_statement(self, arg0, arg1, arg2)
    }

    fn make_break_statement(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_break_statement(self, arg0, arg1)
    }

    fn make_continue_statement(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_continue_statement(self, arg0, arg1)
    }

    fn make_echo_statement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_echo_statement(self, arg0, arg1, arg2)
    }

    fn make_concurrent_statement(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_concurrent_statement(self, arg0, arg1)
    }

    fn make_simple_initializer(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_simple_initializer(self, arg0, arg1)
    }

    fn make_anonymous_class(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_anonymous_class(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
    }

    fn make_anonymous_function(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output, arg10: Self::Output, arg11: Self::Output, arg12: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_anonymous_function(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12)
    }

    fn make_anonymous_function_use_clause(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_anonymous_function_use_clause(self, arg0, arg1, arg2, arg3)
    }

    fn make_variable_pattern(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_variable_pattern(self, arg0)
    }

    fn make_constructor_pattern(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_constructor_pattern(self, arg0, arg1, arg2, arg3)
    }

    fn make_refinement_pattern(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_refinement_pattern(self, arg0, arg1, arg2)
    }

    fn make_lambda_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_lambda_expression(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_lambda_signature(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_lambda_signature(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)
    }

    fn make_cast_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_cast_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_scope_resolution_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_scope_resolution_expression(self, arg0, arg1, arg2)
    }

    fn make_member_selection_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_member_selection_expression(self, arg0, arg1, arg2)
    }

    fn make_safe_member_selection_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_safe_member_selection_expression(self, arg0, arg1, arg2)
    }

    fn make_embedded_member_selection_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_embedded_member_selection_expression(self, arg0, arg1, arg2)
    }

    fn make_yield_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_yield_expression(self, arg0, arg1)
    }

    fn make_prefix_unary_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_prefix_unary_expression(self, arg0, arg1)
    }

    fn make_postfix_unary_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_postfix_unary_expression(self, arg0, arg1)
    }

    fn make_binary_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_binary_expression(self, arg0, arg1, arg2)
    }

    fn make_is_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_is_expression(self, arg0, arg1, arg2)
    }

    fn make_as_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_as_expression(self, arg0, arg1, arg2)
    }

    fn make_nullable_as_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_nullable_as_expression(self, arg0, arg1, arg2)
    }

    fn make_upcast_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_upcast_expression(self, arg0, arg1, arg2)
    }

    fn make_conditional_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_conditional_expression(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_eval_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_eval_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_isset_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_isset_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_nameof_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_nameof_expression(self, arg0, arg1)
    }

    fn make_function_call_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_function_call_expression(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_function_pointer_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_function_pointer_expression(self, arg0, arg1)
    }

    fn make_parenthesized_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_parenthesized_expression(self, arg0, arg1, arg2)
    }

    fn make_braced_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_braced_expression(self, arg0, arg1, arg2)
    }

    fn make_et_splice_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_et_splice_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_embedded_braced_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_embedded_braced_expression(self, arg0, arg1, arg2)
    }

    fn make_list_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_list_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_collection_literal_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_collection_literal_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_object_creation_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_object_creation_expression(self, arg0, arg1)
    }

    fn make_constructor_call(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_constructor_call(self, arg0, arg1, arg2, arg3)
    }

    fn make_darray_intrinsic_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_darray_intrinsic_expression(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_dictionary_intrinsic_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_dictionary_intrinsic_expression(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_keyset_intrinsic_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_keyset_intrinsic_expression(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_varray_intrinsic_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_varray_intrinsic_expression(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_vector_intrinsic_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_vector_intrinsic_expression(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_element_initializer(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_element_initializer(self, arg0, arg1, arg2)
    }

    fn make_subscript_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_subscript_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_embedded_subscript_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_embedded_subscript_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_awaitable_creation_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_awaitable_creation_expression(self, arg0, arg1, arg2)
    }

    fn make_xhp_children_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_children_declaration(self, arg0, arg1, arg2)
    }

    fn make_xhp_children_parenthesized_list(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_children_parenthesized_list(self, arg0, arg1, arg2)
    }

    fn make_xhp_category_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_category_declaration(self, arg0, arg1, arg2)
    }

    fn make_xhp_enum_type(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_enum_type(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_xhp_lateinit(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_lateinit(self, arg0, arg1)
    }

    fn make_xhp_required(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_required(self, arg0, arg1)
    }

    fn make_xhp_class_attribute_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_class_attribute_declaration(self, arg0, arg1, arg2)
    }

    fn make_xhp_class_attribute(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_class_attribute(self, arg0, arg1, arg2, arg3)
    }

    fn make_xhp_simple_class_attribute(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_simple_class_attribute(self, arg0)
    }

    fn make_xhp_simple_attribute(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_simple_attribute(self, arg0, arg1, arg2)
    }

    fn make_xhp_spread_attribute(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_spread_attribute(self, arg0, arg1, arg2, arg3)
    }

    fn make_xhp_open(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_open(self, arg0, arg1, arg2, arg3)
    }

    fn make_xhp_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_expression(self, arg0, arg1, arg2)
    }

    fn make_xhp_close(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_xhp_close(self, arg0, arg1, arg2)
    }

    fn make_type_constant(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_type_constant(self, arg0, arg1, arg2)
    }

    fn make_vector_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_vector_type_specifier(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_keyset_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_keyset_type_specifier(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_tuple_type_explicit_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_tuple_type_explicit_specifier(self, arg0, arg1, arg2, arg3)
    }

    fn make_varray_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_varray_type_specifier(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_function_ctx_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_function_ctx_type_specifier(self, arg0, arg1)
    }

    fn make_type_parameter(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_type_parameter(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_type_constraint(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_type_constraint(self, arg0, arg1)
    }

    fn make_context_constraint(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_context_constraint(self, arg0, arg1)
    }

    fn make_darray_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_darray_type_specifier(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6)
    }

    fn make_dictionary_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_dictionary_type_specifier(self, arg0, arg1, arg2, arg3)
    }

    fn make_closure_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output, arg6: Self::Output, arg7: Self::Output, arg8: Self::Output, arg9: Self::Output, arg10: Self::Output, arg11: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_closure_type_specifier(self, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11)
    }

    fn make_closure_parameter_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_closure_parameter_type_specifier(self, arg0, arg1, arg2, arg3, arg4, arg5)
    }

    fn make_tuple_or_union_or_intersection_element_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_tuple_or_union_or_intersection_element_type_specifier(self, arg0, arg1, arg2, arg3)
    }

    fn make_type_refinement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_type_refinement(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_type_in_refinement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_type_in_refinement(self, arg0, arg1, arg2, arg3, arg4, arg5)
    }

    fn make_ctx_in_refinement(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_ctx_in_refinement(self, arg0, arg1, arg2, arg3, arg4, arg5)
    }

    fn make_classname_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_classname_type_specifier(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_class_ptr_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_class_ptr_type_specifier(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_field_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_field_specifier(self, arg0, arg1, arg2, arg3)
    }

    fn make_field_initializer(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_field_initializer(self, arg0, arg1, arg2)
    }

    fn make_shape_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_shape_type_specifier(self, arg0, arg1, arg2, arg3, arg4)
    }

    fn make_shape_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_shape_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_tuple_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_tuple_expression(self, arg0, arg1, arg2, arg3)
    }

    fn make_generic_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_generic_type_specifier(self, arg0, arg1)
    }

    fn make_nullable_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_nullable_type_specifier(self, arg0, arg1)
    }

    fn make_like_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_like_type_specifier(self, arg0, arg1)
    }

    fn make_soft_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_soft_type_specifier(self, arg0, arg1)
    }

    fn make_attributized_specifier(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_attributized_specifier(self, arg0, arg1)
    }

    fn make_reified_type_argument(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_reified_type_argument(self, arg0, arg1)
    }

    fn make_type_arguments(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_type_arguments(self, arg0, arg1, arg2)
    }

    fn make_type_parameters(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_type_parameters(self, arg0, arg1, arg2)
    }

    fn make_tuple_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_tuple_type_specifier(self, arg0, arg1, arg2)
    }

    fn make_union_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_union_type_specifier(self, arg0, arg1, arg2)
    }

    fn make_intersection_type_specifier(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_intersection_type_specifier(self, arg0, arg1, arg2)
    }

    fn make_error(&mut self, arg0: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_error(self, arg0)
    }

    fn make_list_item(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_list_item(self, arg0, arg1)
    }

    fn make_enum_class_label_expression(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_enum_class_label_expression(self, arg0, arg1, arg2)
    }

    fn make_module_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output, arg3: Self::Output, arg4: Self::Output, arg5: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_module_declaration(self, arg0, arg1, arg2, arg3, arg4, arg5)
    }

    fn make_module_membership_declaration(&mut self, arg0: Self::Output, arg1: Self::Output, arg2: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_module_membership_declaration(self, arg0, arg1, arg2)
    }

    fn make_package_expression(&mut self, arg0: Self::Output, arg1: Self::Output) -> Self::Output {
        <Self as SyntaxSmartConstructors<Self::Output, Self::Factory, State<'_, '_, Self::Output>>>::make_package_expression(self, arg0, arg1)
    }

}
