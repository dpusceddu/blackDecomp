"""Authored stack-escape fixtures; only the host text decompiler runs here."""
import importlib.util
from pathlib import Path
import subprocess
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
WRAPPER = ROOT / 'tools/pipeline/m2c_wrap.py'
spec = importlib.util.spec_from_file_location('black_m2c_stack_escape', WRAPPER)
wrapper = importlib.util.module_from_spec(spec)
spec.loader.exec_module(wrapper)
from m2c.asm_instruction import Register
from m2c.options import Target


class StackEscapeTests(unittest.TestCase):
    def analyze_moves(self, moves, frame_pointer=None, leaf=False, target=Target.ArchEnum.MIPS):
        stack_regs = {Register('sp')}
        if frame_pointer:
            stack_regs.add(Register(frame_pointer))
        info = SimpleNamespace(is_leaf=leaf, subroutine_arg_top=16,
                               is_stack_reg=lambda reg: reg in stack_regs)
        instructions = [SimpleNamespace(args=[Register(dst), Register(src)],
                                        arch_mnemonic=lambda arch: 'mips:move')
                        for dst, src in moves]
        graph = SimpleNamespace(nodes=[SimpleNamespace(block=SimpleNamespace(instructions=instructions))])
        global_info = SimpleNamespace(arch=SimpleNamespace(arch=target))
        with patch.object(wrapper, '_get_stack_info', return_value=info):
            result = wrapper.get_stack_info(None, None, global_info, graph)
        self.assertIs(result, info)
        return result.subroutine_arg_top

    def test_stack_and_established_frame_pointer_escape(self):
        self.assertEqual(self.analyze_moves([('a0', 'sp')]), 0)
        self.assertEqual(self.analyze_moves([('a0', 'fp')], frame_pointer='fp'), 0)

    def test_ordinary_moves_and_stack_frame_setup_keep_original_boundary(self):
        for moves in ([('s0', 'a0')], [('fp', 'sp')], [('sp', 'fp')], [('sp', 'sp')], [('zero', 'sp')]):
            self.assertEqual(self.analyze_moves(moves, frame_pointer='fp'), 16)
        self.assertEqual(self.analyze_moves([('a0', 'fp')]), 16)
        self.assertEqual(self.analyze_moves([('a0', 'sp')], leaf=True), 16)
        self.assertEqual(self.analyze_moves([('a0', 'sp')], target=Target.ArchEnum.ARM), 16)

    def decompile_error_record(self, frame_pointer=False):
        setup = 'sd $fp, 8($sp)\nmove $fp, $sp\n' if frame_pointer else ''
        restore = 'ld $fp, 8($sp)\n' if frame_pointer else ''
        base = '$fp' if frame_pointer else '$sp'
        # The record begins before the first call and finishes in the second
        # call's delay slot. Neither word is an outgoing stack argument.
        body = ('.section .text\nglabel probe_error\n'
                'addiu $sp, $sp, -32\nsd $ra, 16($sp)\n' + setup +
                'addiu $v0, $zero, 1\nsw $v0, 0($sp)\n'
                'addiu $a1, $zero, 64\njal ErrorCode\n addiu $a0, $zero, 13\n'
                'daddu $a0, ' + base + ', $zero\n'
                'jal ErrorSet\n sw $v0, 4($sp)\n' + restore +
                'ld $ra, 16($sp)\njr $ra\n addiu $sp, $sp, 32\n')
        context = ('typedef struct ErrorRecord { int plugin; int code; } ErrorRecord;\n'
                   'int ErrorCode(int code, ...);\n'
                   'ErrorRecord *ErrorSet(ErrorRecord *error);\nvoid probe_error(void);\n')
        with tempfile.TemporaryDirectory() as directory:
            assembly = Path(directory) / 'probe.s'
            header = Path(directory) / 'context.c'
            assembly.write_text(body)
            header.write_text(context)
            result = subprocess.run([sys.executable, str(WRAPPER), '-t', 'mipsee-gcc-c',
                                     '--valid-syntax', '--no-cache', '--context', str(header),
                                     str(assembly)], capture_output=True, text=True, timeout=20)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertNotIn('Decompilation failure', result.stdout)
        self.assertNotIn('M2C_ERROR', result.stdout)
        return result.stdout

    def test_actual_m2c_retains_error_record_across_calls(self):
        for frame_pointer in (False, True):
            with self.subTest(frame_pointer=frame_pointer):
                output = self.decompile_error_record(frame_pointer)
                self.assertIn('ErrorCode(0xD, 0x40)', output)
                self.assertIn('s32 sp0;', output)
                self.assertIn('s32 sp4;', output)
                self.assertIn('sp0 = 1;', output)
                self.assertIn('sp4 = ErrorCode(0xD, 0x40);', output)
                self.assertIn('ErrorSet(sp);', output)
                self.assertNotIn('extra?', output)


if __name__ == '__main__':
    unittest.main()
