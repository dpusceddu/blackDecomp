#!/usr/bin/env python3
"""m2c with one formatting change for the pipeline: a dereference at offset 0 of an expression that m2c has not typed as
a pointer (an integer holding an address, say `lw $v0, 0($a0)` with $a0 an untyped argument) is written as
`M2C_FIELD(expr, T *, 0)` instead of `*expr`, which is not valid C. Everything else is m2c unchanged.
Usage: m2c_wrap.py <m2c arguments>"""
import sys
from m2c import translate
from m2c.translate import StructAccess, AddressOf, BinaryOp, late_unwrap
from m2c.types import Type
from m2c.main import main

_format = StructAccess.format


SIZES = {'s8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'f32': 4, 's64': 8, 'u64': 8, 'f64': 8}
UNSIGNED = {1: 'u8', 2: 'u16', 4: 'u32', 8: 'u64'}


def sized_ptr(self, fmt):
    """The pointer type of the access; the width is the instruction's when m2c's type disagrees (it leaves it s32)."""
    t = Type.ptr(self.type).format(fmt)
    base = t.replace('*', '').strip()
    sb = self.type.get_size_bits()
    size = sb // 8 if sb else self.target_size
    if size in UNSIGNED and SIZES.get(base) != size:
        return UNSIGNED[size] + ' *'
    return t


def format(self, fmt):
    if fmt.valid_syntax and self.offset == 0:
        var = late_unwrap(self.struct_var)
        has_nonzero = self.stack_info.has_nonzero_access(var) if self.stack_info is not None else False
        path = self.late_field_path()
        if (path is None or path == [0]) and not has_nonzero and not isinstance(var, AddressOf) \
                and (isinstance(var, BinaryOp) or not var.type.is_pointer_or_array()):
            return f"M2C_FIELD({var.format(fmt)}, {sized_ptr(self, fmt)}, 0)"
    return _format(self, fmt)


StructAccess.format = format

if __name__ == '__main__':
    sys.exit(main())
