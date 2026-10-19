#!/usr/bin/env python3
"""m2c with one formatting change for the pipeline: a dereference at offset 0 of an expression that m2c has not typed as
a pointer (an integer holding an address, say `lw $v0, 0($a0)` with $a0 an untyped argument) is written as
`M2C_FIELD(expr, T *, 0)` instead of `*expr`, which is not valid C. Local adapters keep software doubles in GPRs and escaped stack locals out of call arguments; they do not modify the installed package.
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

# Raw BinaryOp additions/subtractions model machine byte addresses. Upstream
# converts recognized element accesses to ArrayAccess/AddressOf instead. A loop
# induction variable (or a pointer discovered late) can retain a raw BinaryOp;
# printing `float_pointer += 4` would incorrectly advance it sixteen bytes.
_binary_format = BinaryOp.format
_format_assignment = translate.format_assignment


def byte_pointer_op(expression):
    return (isinstance(expression, BinaryOp) and expression.op in ('+', '-')
            and (expression.left.type.is_pointer_or_array()
                 or expression.right.type.is_pointer_or_array()))


def byte_binary_format(self, fmt):
    if not fmt.valid_syntax or not byte_pointer_op(self):
        return _binary_format(self, fmt)
    left, right = late_unwrap(self.left), late_unwrap(self.right)
    lp, rp = left.type.is_pointer_or_array(), right.type.is_pointer_or_array()
    # Two addresses are integer arithmetic; C pointer subtraction would divide
    # by the element size. Preserve a genuinely wide result before subtracting
    # (a 32-bit unsigned subtraction followed by a 64-bit cast loses its sign).
    width = self.type.get_size_bits() or 32
    integer = (lp and rp) or width > 32 or (rp and not lp and self.op == '-')
    cast = 'u128' if width > 64 else 'u64' if width > 32 else 'u32'
    def address(expression):
        value = expression.format(fmt)
        if not integer:
            return '((s8 *) %s)' % value
        if width > 32:
            return '((%s) (s32) %s)' % (cast, value)
        return '((u32) %s)' % value
    lhs = address(left) if lp else left.format(fmt)
    rhs = address(right) if rp else right.format(fmt)
    return '((%s) (%s %s %s))' % (self.type.decay().format(fmt), lhs, self.op, rhs)


def byte_format_assignment(dest, source, fmt):
    source = late_unwrap(source)
    if fmt.valid_syntax and byte_pointer_op(source):
        # Upstream's compound-assignment shortcut bypasses BinaryOp.format.
        return '%s = %s;' % (dest.format(fmt), translate.format_expr(source, fmt))
    return _format_assignment(dest, source, fmt)


BinaryOp.format = byte_binary_format
translate.format_assignment = byte_format_assignment

# SN EE's software double ABI differs from upstream m2c's generic EE ABI:
# one f64 uses one GPR argument slot and returns in v0. A float still uses
# its own f12..f19 bank. Keep f64 as a floating C type, not an integer typedef.
from dataclasses import replace
from m2c.arch_mips import MipseeArch
from m2c.asm_instruction import Register
from m2c.error import DecompFailure
from m2c.translate import ErrorExpr
from m2c.types import FunctionParam
from m2c.options import Target

_ee_function_abi = MipseeArch.function_abi
_ee_function_return = MipseeArch.function_return
_ee_base_return_regs = list(MipseeArch.base_return_regs)
_get_stack_info = translate.get_stack_info


def get_stack_info(function, persistent_state, global_info, flow_graph):
    """A MIPS copy of sp/fp can expose a local at stack offset zero.

    Upstream handles addiu dst,sp,offset and ARM mov, but normalized MIPS
    move dst,sp otherwise leaves these local stores classified as call args.
    Let upstream identify the frame pointer before checking for escapes.
    """
    info = _get_stack_info(function, persistent_state, global_info, flow_graph)
    arch = global_info.arch
    if arch.arch == Target.ArchEnum.MIPS and not info.is_leaf:
        for node in flow_graph.nodes:
            for inst in node.block.instructions:
                if (inst.arch_mnemonic(arch) == 'mips:move'
                        and isinstance(inst.args[0], Register)
                        and isinstance(inst.args[1], Register)
                        and info.is_stack_reg(inst.args[1])
                        and inst.args[0] != Register('zero')
                        and not info.is_stack_reg(inst.args[0])):
                    info.subroutine_arg_top = 0
    return info


translate.get_stack_info = get_stack_info


def is_ee_double(type):
    return type.is_float() and type.get_size_bits() == 64


def ee_function_abi(self, fn_sig, likely_regs, *, for_call):
    """Correct known register parameters; never guess double stack/varargs layout.

    Unknown signatures retain m2c's inference. Double register parameters and known
    double returns are supported. A double signature that spills either argument
    bank to the stack, or has varargs, is explicitly unsupported until the build backend
    establishes its alignment and promotion rules.
    """
    if not for_call:
        self.base_return_regs = [(Register('v0'), False)] if is_ee_double(fn_sig.return_type) else list(_ee_base_return_regs)
    doubles = fn_sig.params_known and any(is_ee_double(p.type.decay()) for p in fn_sig.params)
    if not doubles:
        return _ee_function_abi(self, fn_sig, likely_regs, for_call=for_call)
    if fn_sig.is_variadic:
        raise DecompFailure('SN EE double ABI: variadic double parameters are not verified')
    fp = sum(p.type.decay().is_float() and not is_ee_double(p.type.decay()) for p in fn_sig.params)
    gp = len(fn_sig.params) - fp
    if gp > 8 or fp > 8:
        raise DecompFailure('SN EE double ABI: stack arguments with doubles are not verified')
    # Reuse upstream location allocation/filtering with an integer proxy, then
    # restore each double's real C type in the resulting ABI slot.
    params = [FunctionParam(type=Type.s64(), name=p.name) if is_ee_double(p.type.decay()) else p for p in fn_sig.params]
    abi = _ee_function_abi(self, replace(fn_sig, params=params), likely_regs, for_call=for_call)
    for slot, param in zip(abi.arg_slots, fn_sig.params):
        if is_ee_double(param.type.decay()):
            slot.type = param.type.decay()
    return abi


def ee_function_return(expr):
    if not is_ee_double(expr.type):
        return _ee_function_return(expr)
    result = {reg: ErrorExpr('SN EE double result is only in $v0') for reg in MipseeArch.all_return_regs}
    result[Register('v0')] = expr
    return result


MipseeArch.function_abi = ee_function_abi
MipseeArch.function_return = staticmethod(ee_function_return)


if __name__ == '__main__':
    sys.exit(main())
