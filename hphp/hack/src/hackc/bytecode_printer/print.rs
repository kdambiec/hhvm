// Copyright (c) Facebook, Inc. and its affiliates.
//
// This source code is licensed under the MIT license found in the
// LICENSE file in the "hack" directory of this source tree.

use std::borrow::Cow;
use std::io;
use std::io::Result;
use std::io::Write;
use std::write;

use bstr::ByteSlice;
use ffi::Maybe;
use ffi::Maybe::*;
use ffi::Vector;
use hash::HashSet;
use hhbc::AdataState;
use hhbc::Attribute;
use hhbc::Body;
use hhbc::Class;
use hhbc::ClassName;
use hhbc::Coeffects;
use hhbc::ConstName;
use hhbc::Constant;
use hhbc::CtxConstant;
use hhbc::DefaultValue;
use hhbc::DictEntry;
use hhbc::FCallArgs;
use hhbc::Fatal;
use hhbc::FatalOp;
use hhbc::Function;
use hhbc::FunctionName;
use hhbc::IncludePath;
use hhbc::Instruct;
use hhbc::Label;
use hhbc::Method;
use hhbc::MethodFlags;
use hhbc::Module;
use hhbc::ModuleName;
use hhbc::Param;
use hhbc::ParamEntry;
use hhbc::Property;
use hhbc::Pseudo;
use hhbc::Requirement;
use hhbc::Span;
use hhbc::SrcLoc;
use hhbc::StringId;
use hhbc::SymbolRefs;
use hhbc::TParamInfo;
use hhbc::TraitReqKind;
use hhbc::TypeConstant;
use hhbc::TypeInfo;
use hhbc::TypedValue;
use hhbc::Typedef;
use hhbc::Unit;
use hhbc::UpperBound;
use hhbc_string_utils::float;
use hhvm_types_ffi::ffi::*;
use itertools::Itertools;
use write_bytes::write_bytes;

use crate::coeffects;
use crate::context::Context;
use crate::write;
use crate::write::Error;
use crate::write::angle;
use crate::write::braces;
use crate::write::concat;
use crate::write::concat_by;
use crate::write::concat_str;
use crate::write::concat_str_by;
use crate::write::fmt_separated;
use crate::write::fmt_separated_with;
use crate::write::newline;
use crate::write::option;
use crate::write::option_or;
use crate::write::paren;
use crate::write::quotes;
use crate::write::square;
use crate::write::triple_quotes;
use crate::write::wrap_by;

macro_rules! write_if {
    ($pred:expr_2021, $($rest:tt)*) => {
        if ($pred) { write!($($rest)*) } else { Ok(()) }
    };
}

fn print_unit(ctx: &Context<'_>, w: &mut dyn Write, prog: &Unit) -> Result<()> {
    match ctx.path {
        Some(p) => {
            let abs = p.path(); // consider: should we also show prefix?
            let p = escaper::escape(
                abs.to_str()
                    .ok_or_else(|| <io::Error as From<Error>>::from(Error::InvalidUTF8))?,
            );

            concat_str_by(w, " ", ["#", p.as_ref(), "starts here"])?;

            newline(w)?;

            newline(w)?;
            concat_str(w, [".filepath ", &format!("\"{}\"", p), ";"])?;

            newline(w)?;
            handle_not_impl(|| print_unit_(ctx, w, prog))?;

            newline(w)?;
            concat_str_by(w, " ", ["#", p.as_ref(), "ends here"])?;

            newline(w)
        }
        None => {
            w.write_all(b"#starts here")?;

            newline(w)?;
            handle_not_impl(|| print_unit_(ctx, w, prog))?;

            newline(w)?;
            w.write_all(b"#ends here")?;

            newline(w)
        }
    }
}

fn get_fatal_op(f: &FatalOp) -> &str {
    match *f {
        FatalOp::Parse => "Parse",
        FatalOp::Runtime => "Runtime",
        FatalOp::RuntimeOmitFrame => "RuntimeOmitFrame",
        _ => panic!("Enum value does not match one of listed variants"),
    }
}

fn print_unit_(ctx: &Context<'_>, w: &mut dyn Write, prog: &Unit) -> Result<()> {
    if let Just(Fatal {
        op,
        loc:
            SrcLoc {
                line_begin,
                line_end,
                col_begin,
                col_end,
            },
        message,
    }) = &prog.fatal
    {
        newline(w)?;
        write_bytes!(
            w,
            ".fatal {}:{},{}:{} {} \"{}\";",
            line_begin,
            col_begin,
            line_end,
            col_end,
            get_fatal_op(op),
            escaper::escape_bstr(message.as_bstr()),
        )?;
    }

    let mut adata = AdataState::default();
    for body in prog.functions.iter().map(|f| &f.body).chain(
        prog.classes
            .iter()
            .flat_map(|c| c.methods.iter().map(|m| &m.body)),
    ) {
        for instr in &body.repr.instrs {
            use hhbc::Opcode;
            match instr {
                Instruct::Opcode(Opcode::Vec(a) | Opcode::Dict(a) | Opcode::Keyset(a)) => {
                    adata.intern_value(a.clone());
                }
                _ => {}
            }
        }
    }

    newline(w)?;
    print_module_use(w, &prog.module_use)?;
    concat(w, adata.clone().finish(), |w, i, a| {
        print_adata_region(ctx, w, i, a)
    })?;
    concat(w, &prog.functions, |w, _, f| {
        print_fun_def(ctx, w, f, &adata)
    })?;
    concat(w, &prog.classes, |w, _, cd| {
        print_class_def(ctx, w, cd, &adata)
    })?;
    concat(w, &prog.modules, |w, _, cd| print_module_def(ctx, w, cd))?;
    concat(w, &prog.constants, |w, _, c| print_constant(ctx, w, c))?;
    concat(w, &prog.typedefs, |w, _, td| print_typedef(ctx, w, td))?;
    print_file_attributes(ctx, w, prog.file_attributes.as_ref())?;
    print_include_region(w, &prog.symbol_refs.includes)?;
    print_symbol_ref_regions(ctx, w, &prog.symbol_refs)?;
    Ok(())
}

fn print_include_region(w: &mut dyn Write, includes: &[IncludePath]) -> Result<()> {
    fn print_include(w: &mut dyn Write, inc: &IncludePath) -> Result<()> {
        let (s1, s2) = inc.extract_str();
        write_bytes!(w, "\n  {}{}", s1, s2)?;
        Ok(())
    }
    if !includes.is_empty() {
        w.write_all(b"\n.includes {")?;
        for inc in includes.as_ref().iter() {
            print_include(w, inc)?;
        }
        w.write_all(b"\n}\n")?;
    }
    Ok(())
}

fn print_symbol_ref_regions(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    symbol_refs: &SymbolRefs,
) -> Result<()> {
    fn print_region<'a, T, F>(
        ctx: &Context<'_>,
        w: &mut dyn Write,
        name: &str,
        refs: impl IntoIterator<Item = T>,
        f: F,
    ) -> Result<()>
    where
        F: Fn(T) -> &'a [u8],
    {
        let mut iter = refs.into_iter();
        if let Some(first) = iter.next() {
            ctx.newline(w)?;
            write!(w, ".{} {{", name)?;
            ctx.block(w, |c, w| {
                c.newline(w)?;
                w.write_all(f(first))?;
                for s in iter {
                    c.newline(w)?;
                    w.write_all(f(s))?;
                }
                Ok(())
            })?;
            w.write_all(b"\n}\n")?;
        }
        Ok(())
    }

    print_region(
        ctx,
        w,
        "constant_refs",
        &symbol_refs.constants,
        ConstName::as_bytes,
    )?;
    print_region(
        ctx,
        w,
        "function_refs",
        &symbol_refs.functions,
        FunctionName::as_bytes,
    )?;
    print_region(
        ctx,
        w,
        "class_refs",
        &symbol_refs.classes,
        ClassName::as_bytes,
    )
}

fn print_adata_region(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    id: usize,
    value: &TypedValue,
) -> Result<()> {
    write_bytes!(w, ".adata A_{} = ", id)?;
    triple_quotes(w, |w| print_adata(ctx, w, value))?;
    w.write_all(b";")?;
    ctx.newline(w)
}

fn print_typedef(ctx: &Context<'_>, w: &mut dyn Write, td: &Typedef) -> Result<()> {
    newline(w)?;
    w.write_all(if td.case_type {
        b".case_type "
    } else {
        b".alias "
    })?;
    print_special_and_user_attrs(
        ctx,
        w,
        td.attributes.as_ref(),
        &AttrContext::Alias,
        td.attrs,
    )?;
    w.write_all(td.name.as_bstr())?;
    w.write_all(b" = ")?;
    print_typedef_info_union(w, td.type_info_union.as_ref())?;
    w.write_all(b" ")?;
    print_span(w, &td.span)?;
    w.write_all(b" ")?;
    triple_quotes(w, |w| print_adata(ctx, w, &td.type_structure))?;
    w.write_all(b";")
}

fn handle_not_impl<F>(f: F) -> Result<()>
where
    F: FnOnce() -> Result<()>,
{
    f().or_else(|e| {
        match write::get_embedded_error(&e) {
            Some(Error::NotImpl(msg)) => {
                println!("#### NotImpl: {}", msg);
                eprintln!("NotImpl: {}", msg);
                return Ok(());
            }
            _ => {}
        }
        Err(e)
    })
}

fn print_fun_def(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    fun_def: &Function,
    adata: &AdataState,
) -> Result<()> {
    let body = &fun_def.body;
    newline(w)?;
    w.write_all(b".function ")?;
    print_tparam_info(w, &body.tparam_info)?;
    print_upper_bounds_(w, &body.upper_bounds)?;
    w.write_all(b" ")?;
    print_special_and_user_attrs(
        ctx,
        w,
        body.attributes.as_ref(),
        &AttrContext::Func,
        body.attrs,
    )?;
    print_span(w, &body.span)?;
    w.write_all(b" ")?;
    option(w, body.return_type.as_ref(), |w, ti| {
        print_type_info(w, ti)?;
        w.write_all(b" ")
    })?;
    w.write_all(fun_def.name.as_bstr())?;
    let params = fun_def.params();
    let dv_labels = find_dv_labels(params);
    print_params(ctx, w, fun_def.params(), &dv_labels)?;
    if fun_def.is_generator() {
        w.write_all(b" isGenerator")?;
    }
    if fun_def.is_async() {
        w.write_all(b" isAsync")?;
    }
    if fun_def.is_pair_generator() {
        w.write_all(b" isPairGenerator")?;
    }
    w.write_all(b" ")?;
    braces(w, |w| {
        ctx.block(w, |c, w| {
            print_body(c, w, body, &body.coeffects, &dv_labels, adata)
        })?;
        newline(w)
    })?;

    newline(w)
}

fn print_requirement(ctx: &Context<'_>, w: &mut dyn Write, r: &Requirement) -> Result<()> {
    ctx.newline(w)?;
    w.write_all(b".require ")?;
    match r.kind {
        TraitReqKind::MustExtend => {
            write_bytes!(w, "extends <{}>;", r.name)
        }
        TraitReqKind::MustImplement => {
            write_bytes!(w, "implements <{}>;", r.name)
        }
        TraitReqKind::MustBeClass => {
            write_bytes!(w, "class <{}>;", r.name)
        }
        TraitReqKind::MustBeAs => {
            write_bytes!(w, "this as <{}>;", r.name)
        }
    }
}

fn print_type_constant(ctx: &Context<'_>, w: &mut dyn Write, c: &TypeConstant) -> Result<()> {
    ctx.newline(w)?;
    write_bytes!(w, ".const {} isType", c.name.as_str())?;
    if c.is_abstract {
        w.write_all(b" isAbstract")?;
    }
    option(w, c.initializer.as_ref(), |w, init| {
        w.write_all(b" = ")?;
        triple_quotes(w, |w| print_adata(ctx, w, init))
    })?;
    w.write_all(b";")
}

fn print_ctx_constant(ctx: &Context<'_>, w: &mut dyn Write, c: &CtxConstant) -> Result<()> {
    ctx.newline(w)?;
    write_bytes!(w, ".ctx {}", c.name.as_str())?;
    if c.is_abstract {
        w.write_all(b" isAbstract")?;
    }
    let recognized = c.recognized.as_ref();
    if !recognized.is_empty() {
        write_bytes!(
            w,
            " {}",
            fmt_separated(" ", recognized.iter().map(|s| s.as_str()))
        )?;
    }
    let unrecognized = c.unrecognized.as_ref();
    if !unrecognized.is_empty() {
        write_bytes!(
            w,
            " {}",
            fmt_separated(" ", unrecognized.iter().map(|s| s.as_str()))
        )?;
    }
    w.write_all(b";")?;
    Ok(())
}

fn print_property_doc_comment(w: &mut dyn Write, p: &Property) -> Result<()> {
    if let Just(s) = p.doc_comment.as_ref() {
        write_bytes!(w, r#""""{}""""#, escaper::escape_bstr(s.as_bstr()))?;
        w.write_all(b" ")?;
    }
    Ok(())
}

fn print_property_type_info(w: &mut dyn Write, p: &Property) -> Result<()> {
    print_type_info(w, &p.type_info)?;
    w.write_all(b" ")
}

fn print_property(ctx: &Context<'_>, w: &mut dyn Write, property: &Property) -> Result<()> {
    newline(w)?;
    w.write_all(b"  .property ")?;
    print_special_and_user_attrs(
        ctx,
        w,
        property.attributes.as_ref(),
        &AttrContext::Prop,
        property.flags,
    )?;
    print_property_doc_comment(w, property)?;
    print_property_type_info(w, property)?;
    w.write_all(property.name.as_bstr())?;
    w.write_all(b" =\n    ")?;
    let initial_value = property.initial_value.as_ref();
    if initial_value == Just(&TypedValue::Uninit) {
        w.write_all(b"uninit;")
    } else {
        triple_quotes(w, |w| match initial_value {
            Nothing => w.write_all(b"N;"),
            Just(value) => print_adata(ctx, w, value),
        })?;
        w.write_all(b";")
    }
}

fn print_constant(ctx: &Context<'_>, w: &mut dyn Write, c: &Constant) -> Result<()> {
    ctx.newline(w)?;
    w.write_all(b".const ")?;
    print_special_and_user_attrs(ctx, w, &[], &AttrContext::Constant, c.attrs)?;
    w.write_all(c.name.as_bstr())?;
    match c.value.as_ref() {
        Just(TypedValue::Uninit) => w.write_all(b" = uninit")?,
        Just(value) => {
            w.write_all(b" = ")?;
            triple_quotes(w, |w| print_adata(ctx, w, value))?;
        }
        Nothing => {}
    }
    w.write_all(b";")
}

fn print_enum_ty(ctx: &Context<'_>, w: &mut dyn Write, c: &Class) -> Result<()> {
    if let Just(et) = c.enum_type.as_ref() {
        ctx.newline(w)?;
        w.write_all(b".enum_ty ")?;
        print_type_info_(w, true, et)?;
        w.write_all(b";")?;
    }
    Ok(())
}

fn print_doc_comment(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    doc_comment: Maybe<&Vector<u8>>,
) -> Result<()> {
    if let Just(cmt) = doc_comment {
        ctx.newline(w)?;
        write_bytes!(w, r#".doc """{}""";"#, escaper::escape_bstr(cmt.as_bstr()))?;
    }
    Ok(())
}

fn print_uses(w: &mut dyn Write, c: &Class) -> Result<()> {
    if c.uses.is_empty() {
        Ok(())
    } else {
        newline(w)?;
        write_bytes!(w, "  .use {}", fmt_separated(" ", c.uses.iter()))?;
        w.write_all(b";")
    }
}

fn print_implements(w: &mut dyn Write, implements: &[ClassName]) -> Result<()> {
    if implements.is_empty() {
        return Ok(());
    }
    write_bytes!(w, " implements ({})", fmt_separated(" ", implements))
}

fn print_enum_includes(w: &mut dyn Write, enum_includes: &[ClassName]) -> Result<()> {
    if enum_includes.is_empty() {
        return Ok(());
    }
    write_bytes!(w, " enum_includes ({})", fmt_separated(" ", enum_includes))
}

fn print_tparam_info(w: &mut dyn Write, tparam_info: &[TParamInfo]) -> Result<()> {
    if tparam_info.is_empty() {
        return Ok(());
    }
    write_bytes!(
        w,
        "<{}> ",
        fmt_separated(
            ",",
            tparam_info
                .iter()
                .map(|t| { format!("[{} {}]", t.name.as_str(), t.shadows_class_tparam) })
        )
    )
}

fn print_method_def(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    method_def: &Method,
    adata: &AdataState,
) -> Result<()> {
    let body = &method_def.body;
    newline(w)?;
    w.write_all(b"  .method ")?;
    print_tparam_info(w, &body.tparam_info)?;
    print_upper_bounds_(w, &body.upper_bounds)?;
    w.write_all(b" ")?;
    print_special_and_user_attrs(
        ctx,
        w,
        body.attributes.as_ref(),
        &AttrContext::Func,
        body.attrs,
    )?;
    print_span(w, &body.span)?;
    w.write_all(b" ")?;
    option(w, body.return_type.as_ref(), |w, t| {
        print_type_info(w, t)?;
        w.write_all(b" ")
    })?;
    w.write_all(method_def.name.as_bstr())?;
    let dv_labels = find_dv_labels(&body.repr.params);
    print_params(ctx, w, &body.repr.params, &dv_labels)?;
    if method_def.flags.contains(MethodFlags::IS_GENERATOR) {
        w.write_all(b" isGenerator")?;
    }
    if method_def.flags.contains(MethodFlags::IS_ASYNC) {
        w.write_all(b" isAsync")?;
    }
    if method_def.flags.contains(MethodFlags::IS_PAIR_GENERATOR) {
        w.write_all(b" isPairGenerator")?;
    }
    if method_def.flags.contains(MethodFlags::IS_CLOSURE_BODY) {
        w.write_all(b" isClosureBody")?;
    }
    w.write_all(b" ")?;
    braces(w, |w| {
        ctx.block(w, |c, w| {
            print_body(c, w, body, &body.coeffects, &dv_labels, adata)
        })?;
        newline(w)?;
        w.write_all(b"  ")
    })
}

fn print_tparams(w: &mut dyn Write, tparams: &[ClassName]) -> Result<()> {
    if tparams.is_empty() {
        return Ok(());
    }
    write_bytes!(
        w,
        "<{}> ",
        fmt_separated(",", tparams.iter().map(|s| s.as_str()))
    )
}

fn print_class_def(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    class_def: &Class,
    adata: &AdataState,
) -> Result<()> {
    newline(w)?;
    w.write_all(b".class ")?;
    print_tparams(w, class_def.tparams.as_ref())?;
    print_upper_bounds(w, class_def.upper_bounds.as_ref())?;
    w.write_all(b" ")?;
    print_special_and_user_attrs(
        ctx,
        w,
        class_def.attributes.as_ref(),
        &AttrContext::Class,
        class_def.flags,
    )?;
    w.write_all(class_def.name.as_bstr())?;
    w.write_all(b" ")?;
    print_span(w, &class_def.span)?;
    print_extends(
        w,
        class_def
            .base
            .as_ref()
            .map(|x: &ClassName| x.as_str())
            .into(),
    )?;
    print_implements(w, class_def.implements.as_ref())?;
    print_enum_includes(w, class_def.enum_includes.as_ref())?;
    w.write_all(b" {")?;
    ctx.block(w, |c, w| {
        print_doc_comment(c, w, class_def.doc_comment.as_ref())?;
        print_uses(w, class_def)?;
        print_enum_ty(c, w, class_def)?;
        for x in class_def.requirements.as_ref() {
            print_requirement(c, w, x)?;
        }
        for x in class_def.constants.as_ref() {
            print_constant(c, w, x)?;
        }
        for x in class_def.type_constants.as_ref() {
            print_type_constant(c, w, x)?;
        }
        for x in class_def.ctx_constants.as_ref() {
            print_ctx_constant(c, w, x)?;
        }
        for x in class_def.properties.as_ref() {
            print_property(c, w, x)?;
        }
        for m in class_def.methods.as_ref() {
            print_method_def(c, w, m, adata)?;
        }
        Ok(())
    })?;
    newline(w)?;
    w.write_all(b"}")?;
    newline(w)
}

fn print_module_def(ctx: &Context<'_>, w: &mut dyn Write, module_def: &Module) -> Result<()> {
    newline(w)?;
    w.write_all(b".module ")?;
    print_special_and_user_attrs(
        ctx,
        w,
        module_def.attributes.as_ref(),
        &AttrContext::Module,
        Attr::AttrNone,
    )?;
    w.write_all(module_def.name.as_bstr())?;
    w.write_all(b" ")?;
    print_span(w, &module_def.span)?;
    w.write_all(b" {")?;
    print_doc_comment(ctx, w, module_def.doc_comment.as_ref())?;
    newline(w)?;
    w.write_all(b"}")?;
    newline(w)
}

fn print_adata_mapped_argument<F, V>(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    col_type: &str,
    values: &[V],
    f: F,
) -> Result<()>
where
    F: Fn(&Context<'_>, &mut dyn Write, &V) -> Result<()>,
{
    write!(w, "{}:{}:{{", col_type, values.len(),)?;
    for v in values {
        f(ctx, w, v)?
    }
    write!(w, "}}")
}

fn print_adata_collection_argument(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    col_type: &str,
    values: &[TypedValue],
) -> Result<()> {
    print_adata_mapped_argument(ctx, w, col_type, values, print_adata)
}

fn print_adata_dict_collection_argument(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    col_type: &str,
    pairs: &[DictEntry],
) -> Result<()> {
    print_adata_mapped_argument(ctx, w, col_type, pairs, |ctx, w, e| {
        print_adata(ctx, w, &e.key)?;
        print_adata(ctx, w, &e.value)
    })
}

fn print_adata(ctx: &Context<'_>, w: &mut dyn Write, tv: &TypedValue) -> Result<()> {
    match tv {
        TypedValue::Uninit => w.write_all(b"uninit"),
        TypedValue::Null => w.write_all(b"N;"),
        TypedValue::String(s) => {
            write_bytes!(
                w,
                r#"s:{}:\"{}\";"#,
                s.len(),
                escaper::escape_bstr(s.as_bytes().as_bstr())
            )
        }
        TypedValue::LazyClass(s) => {
            write_bytes!(
                w,
                r#"l:{}:\"{}\";"#,
                s.as_str().len(),
                escaper::escape_bstr(s.as_bytes().as_bstr())
            )
        }
        TypedValue::Float(f) => {
            write!(w, "d:{};", float::to_string(f.to_f64()))
        }
        TypedValue::Int(i) => write!(w, "i:{};", i),
        // TODO: The False case seems to sometimes be b:0 and sometimes i:0.  Why?
        TypedValue::Bool(false) => w.write_all(b"b:0;"),
        TypedValue::Bool(true) => w.write_all(b"b:1;"),
        TypedValue::Vec(values) => print_adata_collection_argument(ctx, w, "v", values.as_ref()),
        TypedValue::Dict(entries) => {
            print_adata_dict_collection_argument(ctx, w, "D", entries.as_ref())
        }
        TypedValue::Keyset(values) => print_adata_collection_argument(ctx, w, "k", values.as_ref()),
    }
}

fn print_attribute(ctx: &Context<'_>, w: &mut dyn Write, a: &Attribute) -> Result<()> {
    let unescaped = a.name.as_str().as_bytes().as_bstr();
    let escaped = if a.name.as_str().starts_with("__") {
        Cow::Borrowed(unescaped)
    } else {
        escaper::escape_bstr(unescaped)
    };
    write_bytes!(w, "\"{}\"(\"\"\"v:{}:{{", escaped, a.arguments.len())?;
    concat(w, &a.arguments, |w, _, arg| print_adata(ctx, w, arg))?;
    w.write_all(b"}\"\"\")")
}

fn print_attributes(ctx: &Context<'_>, w: &mut dyn Write, al: &[Attribute]) -> Result<()> {
    // Adjust for underscore coming before alphabet
    let al = al
        .iter()
        .sorted_by_key(|a| (!a.name.as_str().starts_with("__"), a.name));
    write_bytes!(
        w,
        "{}",
        fmt_separated_with(" ", al, |w, a| print_attribute(ctx, w, a))
    )
}

fn print_file_attributes(ctx: &Context<'_>, w: &mut dyn Write, al: &[Attribute]) -> Result<()> {
    if al.is_empty() {
        return Ok(());
    }
    newline(w)?;
    w.write_all(b".file_attributes [")?;
    print_attributes(ctx, w, al)?;
    w.write_all(b"] ;")?;
    newline(w)
}

fn print_module_use(w: &mut dyn Write, m_opt: &Maybe<ModuleName>) -> Result<()> {
    if let Just(m) = m_opt {
        newline(w)?;
        write_bytes!(w, ".module_use \"{}\";", m.as_bstr())?;
        newline(w)?;
    }
    Ok(())
}

fn is_bareword_char(c: &u8) -> bool {
    match *c {
        b'_' | b'.' | b'$' | b'\\' => true,
        c => c.is_ascii_alphanumeric(),
    }
}

fn print_body(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    body: &Body,
    coeffects: &Coeffects,
    dv_labels: &HashSet<Label>,
    adata: &AdataState,
) -> Result<()> {
    print_doc_comment(ctx, w, body.doc_comment.as_ref())?;
    if body.is_memoize_wrapper {
        ctx.newline(w)?;
        w.write_all(b".ismemoizewrapper;")?;
    }
    if body.is_memoize_wrapper_lsb {
        ctx.newline(w)?;
        w.write_all(b".ismemoizewrapperlsb;")?;
    }
    if body.num_iters > 0 {
        ctx.newline(w)?;
        write!(w, ".numiters {};", body.num_iters)?;
    }
    if !body.repr.decl_vars.is_empty() {
        ctx.newline(w)?;
        w.write_all(b".declvars ")?;
        concat_by(w, " ", &body.repr.decl_vars, |w, _, var| {
            let var = var.as_str().as_bytes();
            if var.iter().all(is_bareword_char) {
                w.write_all(var)
            } else {
                quotes(w, |w| w.write_all(&escaper::escape_bstr(var.as_bstr())))
            }
        })?;
        w.write_all(b";")?;
    }
    coeffects::coeffects_to_hhas(ctx, w, coeffects)?;
    let local_names: Vec<_> = body
        .repr
        .params
        .iter()
        .map(|e| e.param.name)
        .chain(body.repr.decl_vars.iter().copied())
        .collect();
    print_instructions(ctx, w, &body.repr.instrs, dv_labels, &local_names, adata)
}

fn print_instructions(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    instrs: &[Instruct],
    dv_labels: &HashSet<Label>,
    local_names: &[StringId],
    adata: &AdataState,
) -> Result<()> {
    let mut ctx = ctx.clone();
    for instr in instrs {
        match instr {
            Instruct::Pseudo(Pseudo::Continue | Pseudo::Break) => {
                return Err(Error::fail("Cannot break/continue").into());
            }
            Instruct::Pseudo(Pseudo::Label(_)) => ctx.unblock(w, |c, w| {
                c.newline(w)?;
                print_instr(w, instr, dv_labels, local_names, adata)
            })?,
            Instruct::Pseudo(Pseudo::TryCatchBegin) => {
                ctx.newline(w)?;
                print_instr(w, instr, dv_labels, local_names, adata)?;
                ctx.indent_inc();
            }
            Instruct::Pseudo(Pseudo::TryCatchMiddle) => ctx.unblock(w, |c, w| {
                c.newline(w)?;
                print_instr(w, instr, dv_labels, local_names, adata)
            })?,
            Instruct::Pseudo(Pseudo::TryCatchEnd) => {
                ctx.indent_dec();
                ctx.newline(w)?;
                print_instr(w, instr, dv_labels, local_names, adata)?;
            }
            _ => {
                ctx.newline(w)?;
                print_instr(w, instr, dv_labels, local_names, adata)?;
            }
        }
    }
    Ok(())
}

pub(crate) fn print_fcall_args(
    w: &mut dyn Write,
    args @ FCallArgs {
        flags,
        num_args,
        num_rets,
        inouts,
        readonly,
        async_eager_target,
        context,
    }: &FCallArgs,
    dv_labels: &HashSet<Label>,
) -> Result<()> {
    angle(w, |w| {
        let flags = hhvm_hhbc_defs_ffi::ffi::fcall_flags_to_string_ffi(*flags);
        write!(w, "{}", flags)
    })?;
    w.write_all(b" ")?;
    print_int(w, num_args)?;
    w.write_all(b" ")?;
    print_int(w, num_rets)?;
    w.write_all(b" ")?;
    quotes(w, |w| {
        concat_by(w, "", inouts, |w, _, i| {
            w.write_all(if *i { b"1" } else { b"0" })
        })
    })?;
    w.write_all(b" ")?;
    quotes(w, |w| {
        concat_by(w, "", readonly, |w, _, i| {
            w.write_all(if *i { b"1" } else { b"0" })
        })
    })?;
    w.write_all(b" ")?;
    if args.has_async_eager_target() {
        print_label(w, async_eager_target, dv_labels)?;
    } else {
        w.write_all(b"-")?;
    }
    w.write_all(b" ")?;
    quotes(w, |w| w.write_all(context.as_str().as_bytes()))
}

fn print_pseudo(w: &mut dyn Write, instr: &Pseudo, dv_labels: &HashSet<Label>) -> Result<()> {
    match instr {
        Pseudo::Label(l) => {
            print_label(w, l, dv_labels)?;
            w.write_all(b":")
        }
        Pseudo::TryCatchBegin => w.write_all(b".try {"),
        Pseudo::TryCatchMiddle => w.write_all(b"} .catch {"),
        Pseudo::TryCatchEnd => w.write_all(b"}"),
        Pseudo::SrcLoc(p) => write!(
            w,
            ".srcloc {}:{},{}:{};",
            p.line_begin, p.col_begin, p.line_end, p.col_end
        ),
        Pseudo::Break | Pseudo::Continue => Err(Error::fail("invalid instruction").into()),
    }
}

fn print_instr(
    w: &mut dyn Write,
    instr: &Instruct,
    dv_labels: &HashSet<Label>,
    local_names: &[StringId],
    adata: &AdataState,
) -> Result<()> {
    match instr {
        Instruct::Opcode(opcode) => {
            crate::print_opcode::PrintOpcode::new(opcode, dv_labels, local_names)
                .print_opcode(w, adata)
        }
        Instruct::Pseudo(pseudo) => print_pseudo(w, pseudo, dv_labels),
    }
}

/// Build a set containing the labels for param default-value initializers
/// so they can be formatted as `DV123` instead of `L123`.
fn find_dv_labels(params: &[ParamEntry]) -> HashSet<Label> {
    params
        .iter()
        .filter_map(|e| match &e.dv {
            Just(dv) => Some(dv.label),
            _ => None,
        })
        .collect()
}

fn print_params(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    params: &[ParamEntry],
    dv_labels: &HashSet<Label>,
) -> Result<()> {
    paren(w, |w| {
        concat_by(w, ", ", params, |w, _, i| print_param(ctx, w, i, dv_labels))
    })
}

fn print_param(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    ParamEntry { param, dv }: &ParamEntry,
    dv_labels: &HashSet<Label>,
) -> Result<()> {
    print_param_user_attributes(ctx, w, param)?;
    write_if!(param.is_inout, w, "inout ")?;
    write_if!(param.is_readonly, w, "readonly ")?;
    write_if!(param.is_optional, w, "optional ")?;
    write_if!(param.is_splat, w, "splat ")?;
    write_if!(param.is_variadic, w, "...")?;
    option(w, param.type_info.as_ref(), |w, ty| {
        print_type_info(w, ty)?;
        w.write_all(b" ")
    })?;
    w.write_all(param.name.as_str().as_bytes())?;
    option(w, dv.as_ref(), |w, dv: &DefaultValue| {
        print_param_default_value(w, dv.label, &dv.expr, dv_labels)
    })
}

fn print_param_default_value(
    w: &mut dyn Write,
    label: Label,
    php_code: &[u8],
    dv_labels: &HashSet<Label>,
) -> Result<()> {
    w.write_all(b" = ")?;
    print_label(w, &label, dv_labels)?;
    paren(w, |w| {
        triple_quotes(w, |w| {
            w.write_all(&escaper::escape_bstr(php_code.as_bstr()))
        })
    })
}

pub(crate) fn print_label(
    w: &mut dyn Write,
    label: &Label,
    dv_labels: &HashSet<Label>,
) -> Result<()> {
    let prefix = if dv_labels.contains(label) { "DV" } else { "L" };
    write!(w, "{}{}", prefix, label.0)
}

pub(crate) fn print_int<T: std::fmt::Display>(w: &mut dyn Write, i: T) -> Result<()> {
    write!(w, "{}", i)
}

fn print_param_user_attributes(ctx: &Context<'_>, w: &mut dyn Write, param: &Param) -> Result<()> {
    match param.user_attributes.as_ref()[..] {
        [] => Ok(()),
        _ => square(w, |w| print_attributes(ctx, w, &param.user_attributes)),
    }
}

fn print_span(
    w: &mut dyn Write,
    &Span {
        line_begin,
        line_end,
    }: &Span,
) -> Result<()> {
    write!(w, "({},{})", line_begin, line_end)
}

fn print_special_and_user_attrs(
    ctx: &Context<'_>,
    w: &mut dyn Write,
    users: &[Attribute],
    attr_ctx: &AttrContext,
    attrs: Attr,
) -> Result<()> {
    if !users.is_empty() || !attrs.is_empty() {
        square(w, |w| {
            write!(w, "{}", attrs_to_string_ffi(*attr_ctx, attrs))?;
            if !users.is_empty() {
                w.write_all(b" ")?;
            }
            print_attributes(ctx, w, users)
        })?;
        w.write_all(b" ")?;
    }
    Ok(())
}

fn print_upper_bounds(w: &mut dyn Write, ubs: impl AsRef<[UpperBound]>) -> Result<()> {
    braces(w, |w| {
        concat_by(w, ", ", ubs, |w, _, ub| print_upper_bound(w, ub))
    })
}

fn print_upper_bound(w: &mut dyn Write, ub: &UpperBound) -> Result<()> {
    paren(w, |w| {
        write!(w, "{} as ", ub.name)?;
        concat_by(w, ", ", &ub.bounds, |w, _, t| print_type_info(w, t))
    })
}

fn print_upper_bounds_(w: &mut dyn Write, ubs: impl AsRef<[UpperBound]>) -> Result<()> {
    braces(w, |w| {
        concat_by(w, ", ", ubs, |w, _, ub| print_upper_bound_(w, ub))
    })
}

fn print_upper_bound_(w: &mut dyn Write, ub: &UpperBound) -> Result<()> {
    paren(w, |w| {
        write!(w, "{} as ", ub.name)?;
        concat_by(w, ", ", &ub.bounds, |w, _, t| print_type_info(w, t))
    })
}

fn print_type_info(w: &mut dyn Write, ti: &TypeInfo) -> Result<()> {
    print_type_info_(w, false, ti)
}

fn print_type_flags(w: &mut dyn Write, flag: TypeConstraintFlags) -> Result<()> {
    write!(w, "{}", type_flags_to_string_ffi(flag))
}

fn print_type_info_(w: &mut dyn Write, is_enum: bool, ti: &TypeInfo) -> Result<()> {
    let print_quote_str = |w: &mut dyn Write, opt: Option<&str>| {
        option_or(
            w,
            opt,
            |w, s: &str| quotes(w, |w| w.write_all(escaper::escape(s).as_ref().as_bytes())),
            "N",
        )
    };
    angle(w, |w| {
        print_quote_str(w, ti.user_type.map(|s| s.as_str()).into())?;
        w.write_all(b" ")?;
        if !is_enum {
            print_quote_str(w, ti.type_constraint.name.map(|n| n.as_str()).into())?;
            w.write_all(b" ")?;
        }
        print_type_flags(w, ti.type_constraint.flags)
    })
}

// T125888411: User type not printed
// T126391106: also -- no name and "" as a name both print as "", which is ambiguous for the assembler
fn print_typedef_info(w: &mut dyn Write, ti: &TypeInfo) -> Result<()> {
    angle(w, |w| {
        write_bytes!(
            w,
            r#""{}""#,
            escaper::escape(
                ti.type_constraint
                    .name
                    .as_ref()
                    .unwrap_or(&StringId::EMPTY)
                    .as_str()
            )
        )?;
        let flags = ti.type_constraint.flags & TypeConstraintFlags::Nullable;
        if !flags.is_empty() {
            wrap_by(w, " ", |w| print_type_flags(w, flags))?;
        }
        Ok(())
    })
}

fn print_typedef_info_union(w: &mut dyn Write, tis: &[TypeInfo]) -> Result<()> {
    concat_by(w, ",", tis, |w, _, td| print_typedef_info(w, td))
}

fn print_extends(w: &mut dyn Write, base: Option<&str>) -> Result<()> {
    match base {
        None => Ok(()),
        Some(b) => concat_str_by(w, " ", [" extends", b]),
    }
}

pub fn external_print_unit(
    ctx: &Context<'_>,
    w: &mut dyn std::io::Write,
    prog: &Unit,
) -> std::result::Result<(), Error> {
    print_unit(ctx, w, prog).map_err(write::into_error)?;
    w.flush().map_err(write::into_error)?;
    Ok(())
}
