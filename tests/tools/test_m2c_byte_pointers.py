"""Synthetic MIPS fixtures for byte-address arithmetic, without target tools."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class BytePointers(unittest.TestCase):
    def decompile(self, declaration, body):
        with tempfile.TemporaryDirectory() as directory:
            context = Path(directory) / 'context.c'
            assembly = Path(directory) / 'probe.s'
            context.write_text(declaration + '\n')
            assembly.write_text('.section .text\nglabel probe\n' + body + '\n')
            result = subprocess.run([sys.executable, str(ROOT / 'tools/m2c_wrap.py'),
                                     '-t', 'mipsee-gcc-c', '--valid-syntax', '--no-cache',
                                     '--context', str(context), str(assembly)],
                                    capture_output=True, text=True, timeout=20)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertNotIn('Decompilation failure', result.stdout)
        return result.stdout

    def test_in_place_float_pointer_loop_advances_four_bytes(self):
        output = self.decompile('void probe(float *p, int count);',
            'blez $a1, .Ldone\n nop\n.Lloop:\nsw $zero, 0($a0)\n'
            'addiu $a1, $a1, -1\nbnez $a1, .Lloop\n addiu $a0, $a0, 4\n'
            '.Ldone:\njr $ra\n nop')
        self.assertIn('((s8 *) var_a0) + 4', output)
        self.assertNotIn('var_a0 += 4', output)

    def test_dynamic_byte_offset_is_not_scaled_by_element_width(self):
        output = self.decompile('float *probe(float *p, int bytes);',
                               'jr $ra\n addu $v0, $a0, $a1')
        self.assertIn('(s8 *) p', output)
        self.assertIn('+ bytes', output)

    def test_recognized_element_index_is_still_a_typed_array_access(self):
        output = self.decompile('float probe(float *p, int index);',
            'sll $v0, $a1, 2\naddu $v0, $a0, $v0\njr $ra\n lwc1 $f0, 0($v0)')
        self.assertIn('p[index]', output)
        self.assertNotIn('(s8 *)', output)

    def test_subtraction_of_addresses_returns_byte_difference(self):
        output = self.decompile('int probe(float *left, float *right);',
                               'jr $ra\n subu $v0, $a0, $a1')
        self.assertIn('((u32) left) - ((u32) right)', output)
        self.assertNotIn('/ 4', output)

    def test_wide_pointer_difference_preserves_negative_results_before_subtraction(self):
        output = self.decompile('long long probe(float *left, float *right);',
                               'jr $ra\n dsubu $v0, $a0, $a1')
        self.assertIn('((u64) (s32) left) - ((u64) (s32) right)', output)
        self.assertNotIn('((u32) left) - ((u32) right)', output)


if __name__ == '__main__':
    unittest.main()
