"""Authored EE ABI fixtures only; these tests run no target tools on the host."""
import importlib.util
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
WRAPPER = Path(os.environ.get('BLACK_M2C_WRAPPER', ROOT / 'tools/pipeline/m2c_wrap.py'))
spec = importlib.util.spec_from_file_location('black_m2c_double_abi', WRAPPER)
wrapper = importlib.util.module_from_spec(spec)
spec.loader.exec_module(wrapper)
from m2c.arch_mips import MipseeArch, MipsArch
from m2c.asm_instruction import Register
from m2c.error import DecompFailure
from m2c.translate import ErrorExpr, Literal
from m2c.types import FunctionParam, FunctionSignature, Type


def sig(params, ret=None, variadic=False):
    return FunctionSignature(return_type=ret or Type.s32(), params=[FunctionParam(type=t, name='p%d'%n) for n,t in enumerate(params)], params_known=True, is_variadic=variadic)


class DoubleAbi(unittest.TestCase):
    def test_mixed_banks_preserve_float_double_and_integer_types(self):
        signature = sig([Type.s32(), Type.f64(), Type.s32(), Type.f32(), Type.f64(), Type.f32()], Type.f64())
        for is_call in (False, True):
            arch = MipseeArch()
            abi = arch.function_abi(signature, {}, for_call=is_call)
            self.assertEqual([s.loc.reg.register_name for s in abi.arg_slots], ['a0','a1','a2','f12','a3','f13'])
            self.assertEqual([s.type.get_size_bits() for s in abi.arg_slots], [32,64,32,32,64,32])
            self.assertTrue(abi.arg_slots[1].type.is_float())

    def test_double_return_is_full_f64_in_v0(self):
        expression = Literal(0, Type.f64())
        values = MipseeArch.function_return(expression)
        self.assertIs(values[Register('v0')], expression)
        self.assertTrue(values[Register('v0')].type.is_float())
        for reg in ('v1','f0','f1'):
            self.assertIsInstance(values[Register(reg)], ErrorExpr)

    def test_return_bank_resets_for_each_function(self):
        arch = MipseeArch()
        arch.function_abi(sig([],Type.f64()),{},for_call=False)
        self.assertEqual(arch.base_return_regs, [(Register('v0'),False)])
        arch.function_abi(sig([],Type.f32()),{},for_call=False)
        self.assertEqual(arch.base_return_regs, MipsArch.base_return_regs)

    def test_non_ee_mips_double_abi_is_untouched(self):
        original = MipsArch().function_abi(sig([Type.f64()]),{},for_call=False)
        self.assertEqual(original.arg_slots[0].loc.reg, Register('f12'))

    def test_unverified_double_stack_and_varargs_are_explicit(self):
        for signature in (sig([Type.f64()]+[Type.s32()]*8),sig([Type.f64()],variadic=True)):
            with self.assertRaises(DecompFailure):
                MipseeArch().function_abi(signature,{},for_call=False)

    def decompile(self, context, body, name='probe_double'):
        with tempfile.TemporaryDirectory() as directory:
            context_path=Path(directory)/'context.c'; asm=Path(directory)/'probe.s'
            context_path.write_text('typedef double f64; typedef float f32;\n'+context)
            asm.write_text('.section .text\nglabel '+name+'\n'+body+'\n')
            result=subprocess.run([sys.executable,str(WRAPPER),'-t','mipsee-gcc-c','--valid-syntax','--no-cache','--context',str(context_path),str(asm)],capture_output=True,text=True,timeout=20)
            self.assertEqual(result.returncode,0,result.stdout+result.stderr)
            self.assertNotIn('M2C_ERROR',result.stdout)
            self.assertNotIn('second half',result.stdout)
            return result.stdout

    def test_actual_m2c_double_identity_uses_gpr_input(self):
        output=self.decompile('f64 probe_double(f64 value);','jr $ra\n daddu $v0, $a0, $zero')
        self.assertIn('f64 probe_double(f64 value)',output)
        self.assertIn('return value;',output)

    def test_actual_m2c_mixed_double_identity_keeps_separate_banks(self):
        output=self.decompile('f64 probe_double(int i, f64 value, int j, f32 f);','jr $ra\n daddu $v0, $a1, $zero')
        self.assertIn('f64 value',output)
        self.assertIn('f32 f',output)
        self.assertIn('return value;',output)

    def test_actual_m2c_double_call_uses_gpr_result_even_with_fp_scratch(self):
        output=self.decompile('f64 callee(f64 value); f64 probe_double(f64 value);',
            'addiu $sp, $sp, -16\nsd $ra, 0($sp)\njal callee\n nop\nmtc1 $zero, $f0\nld $ra, 0($sp)\njr $ra\n addiu $sp, $sp, 16')
        self.assertIn('callee(value)',output)


if __name__=='__main__':
    unittest.main()
