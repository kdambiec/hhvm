#
# Autogenerated by Thrift
#
# DO NOT EDIT
#  @generated
#

from __future__ import annotations

import typing as _typing
import builtins


import folly.iobuf as _fbthrift_iobuf
import meta.example.thrift.service.thrift_abstract_types as _fbthrift_python_abstract_types
import thrift.python.types as _fbthrift_python_types
import thrift.python.mutable_types as _fbthrift_python_mutable_types
import thrift.python.mutable_exceptions as _fbthrift_python_mutable_exceptions
import thrift.python.mutable_containers as _fbthrift_python_mutable_containers

import test.fixtures.basic.module.thrift_mutable_types as _fbthrift__test__fixtures__basic__module__thrift_mutable_types


class EchoRequest(_fbthrift_python_mutable_types.MutableStruct, _fbthrift_python_abstract_types.EchoRequest):
    @property
    def text(self) -> builtins.str: ...
    @text.setter
    def text(self, value: builtins.str) -> None: ...

    def __init__(
        self, *,
        text: _typing.Optional[builtins.str]=...
    ) -> None: ...

    def __call__(
        self, *,
        text: _typing.Optional[builtins.str]=...
    ) -> _typing.Self: ...
    def __iter__(self) -> _typing.Iterator[_typing.Tuple[builtins.str, _typing.Union[builtins.str]]]: ...
    def _to_python(self) -> "meta.example.thrift.service.thrift_types.EchoRequest": ...  # type: ignore
    def _to_mutable_python(self) -> _typing.Self: ...
    def _to_py3(self) -> "meta.example.thrift.service.types.EchoRequest": ...  # type: ignore
    def _to_py_deprecated(self) -> "service.ttypes.EchoRequest": ...  # type: ignore
_fbthrift_EchoRequest = EchoRequest

class EchoResponse(_fbthrift_python_mutable_types.MutableStruct, _fbthrift_python_abstract_types.EchoResponse):
    @property
    def text(self) -> builtins.str: ...
    @text.setter
    def text(self, value: builtins.str) -> None: ...

    def __init__(
        self, *,
        text: _typing.Optional[builtins.str]=...
    ) -> None: ...

    def __call__(
        self, *,
        text: _typing.Optional[builtins.str]=...
    ) -> _typing.Self: ...
    def __iter__(self) -> _typing.Iterator[_typing.Tuple[builtins.str, _typing.Union[builtins.str]]]: ...
    def _to_python(self) -> "meta.example.thrift.service.thrift_types.EchoResponse": ...  # type: ignore
    def _to_mutable_python(self) -> _typing.Self: ...
    def _to_py3(self) -> "meta.example.thrift.service.types.EchoResponse": ...  # type: ignore
    def _to_py_deprecated(self) -> "service.ttypes.EchoResponse": ...  # type: ignore
_fbthrift_EchoResponse = EchoResponse

class WhisperException(_fbthrift_python_mutable_exceptions.MutableGeneratedError, _fbthrift_python_abstract_types.WhisperException):
    @property
    def message(self) -> builtins.str: ...
    @message.setter
    def message(self, value: builtins.str) -> None: ...

    def __init__(
        self, *,
        message: _typing.Optional[builtins.str]=...
    ) -> None: ...

    def __iter__(self) -> _typing.Iterator[_typing.Tuple[builtins.str, _typing.Union[builtins.str]]]: ...
    def _to_python(self) -> "meta.example.thrift.service.thrift_types.WhisperException": ...  # type: ignore
    def _to_mutable_python(self) -> _typing.Self: ...
    def _to_py3(self) -> "meta.example.thrift.service.types.WhisperException": ...  # type: ignore
    def _to_py_deprecated(self) -> "service.ttypes.WhisperException": ...  # type: ignore
_fbthrift_WhisperException = WhisperException


class _fbthrift_EchoService_echo_args(_fbthrift_python_mutable_types.MutableStruct):
    request: _typing.Final[_fbthrift_EchoRequest] = ...

    def __init__(
        self, *,
        request: _typing.Optional[_fbthrift_EchoRequest]=...
    ) -> None: ...

    def __iter__(self) -> _typing.Iterator[_typing.Tuple[
        str,
        _typing.Union[None, _fbthrift_EchoRequest]]]: ...


class _fbthrift_EchoService_echo_result(_fbthrift_python_mutable_types.MutableStruct):
    success: _typing.Final[_fbthrift_EchoResponse]
    ex: _typing.Final[_fbthrift_WhisperException]

    def __init__(
        self, *, success: _typing.Optional[_fbthrift_EchoResponse] = ..., _ex0__ex: _typing.Optional[_fbthrift_WhisperException]=...
    ) -> None: ...

    def __iter__(self) -> _typing.Iterator[_typing.Tuple[
        str,
        _typing.Union[
            _fbthrift_EchoResponse,
            _fbthrift_WhisperException,
        ]]]: ...


class _fbthrift_ExtendedEchoService_echo_2_args(_fbthrift_python_mutable_types.MutableStruct):
    request: _typing.Final[_fbthrift_EchoRequest] = ...

    def __init__(
        self, *,
        request: _typing.Optional[_fbthrift_EchoRequest]=...
    ) -> None: ...

    def __iter__(self) -> _typing.Iterator[_typing.Tuple[
        str,
        _typing.Union[None, _fbthrift_EchoRequest]]]: ...


class _fbthrift_ExtendedEchoService_echo_2_result(_fbthrift_python_mutable_types.MutableStruct):
    success: _typing.Final[_fbthrift_EchoResponse]
    ex: _typing.Final[_fbthrift_WhisperException]

    def __init__(
        self, *, success: _typing.Optional[_fbthrift_EchoResponse] = ..., _ex0__ex: _typing.Optional[_fbthrift_WhisperException]=...
    ) -> None: ...

    def __iter__(self) -> _typing.Iterator[_typing.Tuple[
        str,
        _typing.Union[
            _fbthrift_EchoResponse,
            _fbthrift_WhisperException,
        ]]]: ...


class _fbthrift_ExtendedMyService_putDataById_2_args(_fbthrift_python_mutable_types.MutableStruct):
    id: _typing.Final[builtins.int] = ...
    data: _typing.Final[builtins.str] = ...

    def __init__(
        self, *,
        id: _typing.Optional[builtins.int]=...,
        data: _typing.Optional[builtins.str]=...
    ) -> None: ...

    def __iter__(self) -> _typing.Iterator[_typing.Tuple[
        str,
        _typing.Union[None, builtins.int, builtins.str]]]: ...


class _fbthrift_ExtendedMyService_putDataById_2_result(_fbthrift_python_mutable_types.MutableStruct):
    success: _typing.Final[None]

    def __init__(
        self, *, success: _typing.Optional[None] = ...
    ) -> None: ...

    def __iter__(self) -> _typing.Iterator[_typing.Tuple[
        str,
        _typing.Union[
            None,
        ]]]: ...
