#
# Autogenerated by Thrift
#
# DO NOT EDIT
#  @generated
#

from __future__ import annotations
import builtins

import apache.thrift.metadata.thrift_types as _fbthrift_metadata
import thrift.python.types as _fbthrift_python_types
import typing as _std_python_typing



class MyEnum(_fbthrift_python_types.Enum, int):
    MyValue1 = 0
    MyValue2 = 1
    MyValue3 = 3
    MyValue4 = 4
    MyValue5 = 5
    @staticmethod
    def __get_thrift_name__() -> builtins.str:
        return "module.MyEnum"

    @staticmethod
    def __get_thrift_uri__() -> _std_python_typing.Optional[builtins.str]:
        return None

    @staticmethod
    def __get_metadata__() -> _fbthrift_metadata.ThriftMetadata:
        return gen_metadata_enum_MyEnum()

    def _to_python(self) -> "MyEnum":
        return self

    def _to_py3(self) -> "MyEnum":
        return self

    def _to_py_deprecated(self) -> int:
        return self.value

def _fbthrift_gen_metadata_enum_MyEnum(metadata_struct: _fbthrift_metadata.ThriftMetadata) -> _fbthrift_metadata.ThriftMetadata:
    qualified_name = "module.MyEnum"

    if qualified_name in metadata_struct.enums:
        return metadata_struct
    elements = {
        0: "MyValue1",
        1: "MyValue2",
        3: "MyValue3",
        4: "MyValue4",
        5: "MyValue5",
    }
    structured_annotations = [
    ]
    enum_dict = dict(metadata_struct.enums)
    enum_dict[qualified_name] = _fbthrift_metadata.ThriftEnum(name=qualified_name, elements=elements, structured_annotations=structured_annotations)
    new_struct = metadata_struct(enums=enum_dict)

    return new_struct

def gen_metadata_enum_MyEnum() -> _fbthrift_metadata.ThriftMetadata:
    return _fbthrift_gen_metadata_enum_MyEnum(
        _fbthrift_metadata.ThriftMetadata(structs={}, enums={}, exceptions={}, services={})
    )

