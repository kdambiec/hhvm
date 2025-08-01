

#
# Autogenerated by Thrift
#
# DO NOT EDIT
#  @generated
#

from __future__ import annotations

import abc as _abc
import typing as _typing
import builtins as _fbthrift_builtins

import builtins



import folly.iobuf as _fbthrift_iobuf
import thrift.python.abstract_types as _fbthrift_python_abstract_types
import my

class _fbthrift_unadapted_AnnotationWithContainers(_abc.ABC):
    # pyre-ignore[16]: Module `_fbthrift_builtins` has no attribute `property`.
    @_fbthrift_builtins.property
    @_abc.abstractmethod
    def names(self) -> _typing.Sequence[builtins.str]: ...
    # pyre-ignore[16]: Module `_fbthrift_builtins` has no attribute `property`.
    @_fbthrift_builtins.property
    @_abc.abstractmethod
    def counts(self) -> _typing.Mapping[builtins.str, builtins.int]: ...
    @_abc.abstractmethod
    def __iter__(self) -> _typing.Iterator[_typing.Tuple[builtins.str, _typing.Union[_typing.Sequence[builtins.str], _typing.Mapping[builtins.str, builtins.int]]]]: ...
    @_abc.abstractmethod
    def _to_mutable_python(self) -> "with_containers.thrift_mutable_types._fbthrift_unadapted_AnnotationWithContainers": ...  # type: ignore
    @_abc.abstractmethod
    def _to_python(self) -> "with_containers.thrift_types._fbthrift_unadapted_AnnotationWithContainers": ...  # type: ignore
    @_abc.abstractmethod
    def _to_py3(self) -> "with_containers.types._fbthrift_unadapted_AnnotationWithContainers": ...  # type: ignore
    @_abc.abstractmethod
    def _to_py_deprecated(self) -> "with_containers.ttypes._fbthrift_unadapted_AnnotationWithContainers": ...  # type: ignore

AnnotationWithContainers = my.AdaptedType[_fbthrift_unadapted_AnnotationWithContainers]
_fbthrift_AnnotationWithContainers = AnnotationWithContainers
class _fbthrift_unadapted_MyStruct(_abc.ABC):
    # pyre-ignore[16]: Module `_fbthrift_builtins` has no attribute `property`.
    @_fbthrift_builtins.property
    @_abc.abstractmethod
    def abc(self) -> my.AdaptedType[int]: ...
    @_abc.abstractmethod
    def __iter__(self) -> _typing.Iterator[_typing.Tuple[builtins.str, _typing.Union[my.AdaptedType[int]]]]: ...
    @_abc.abstractmethod
    def _to_mutable_python(self) -> "with_containers.thrift_mutable_types._fbthrift_unadapted_MyStruct": ...  # type: ignore
    @_abc.abstractmethod
    def _to_python(self) -> "with_containers.thrift_types._fbthrift_unadapted_MyStruct": ...  # type: ignore
    @_abc.abstractmethod
    def _to_py3(self) -> "with_containers.types._fbthrift_unadapted_MyStruct": ...  # type: ignore
    @_abc.abstractmethod
    def _to_py_deprecated(self) -> "with_containers.ttypes._fbthrift_unadapted_MyStruct": ...  # type: ignore

MyStruct = my.AdaptedType[_fbthrift_unadapted_MyStruct]
_fbthrift_MyStruct = MyStruct
