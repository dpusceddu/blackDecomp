"""EE square roots retain their encoded operands and hardware/libc distinction."""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from m2c_input import decode_raw_instructions, prepare


class EeSquareRoot(unittest.TestCase):
    def test_generic_cop1_uses_ee_ft_source_and_fd_destination(self):
        # Authored R5900 SQRT.S f1,f12: FT12, FS0, FD1, funct4.
        source = '.section .text\n/* 0 00F00000 44000C46 */ c1 0xc0044\n'
        self.assertIn('sqrt.s $f1, $f12', decode_raw_instructions(source))

    def test_escaped_word_has_same_ee_operand_order(self):
        source = '.section .text\n/* 0 00F00000 44000C46 */ .word 0x460C0044\n'
        self.assertIn('sqrt.s $f1, $f12', decode_raw_instructions(source))

    def test_data_unannotated_and_other_cop1_forms_stay_opaque(self):
        for source in (
            '.section .rodata\n/* 0 00F00000 44000C46 */ c1 0xc0044\n',
            '.section .text\nc1 0xc0044\n',
            # Generic MIPS source-in-FS encoding is not the EE instruction.
            '.section .text\n/* 0 00F00000 04600046 */ c1 0x6004\n',
            '.section .text\n/* 0 00F00000 44002C46 */ c1 0x2c0044\n',
            '.section .text\n/* 0 00F00000 45000C46 */ c1 0xc0045\n',
            '.section .text\n/* 0 00F00000 00000000 */ c1 0x2000000\n',
        ):
            self.assertEqual(decode_raw_instructions(source), source)

    def decompile(self, body, target='mipsee-gcc-c'):
        source, _ = prepare('.section .text\nglabel probe_sqrt\n' + body)
        with tempfile.TemporaryDirectory() as directory:
            assembly = Path(directory) / 'probe.s'
            context = Path(directory) / 'ctx.c'
            assembly.write_text(source)
            context.write_text('float probe_sqrt(float); float sqrtf(float); float __ee_sqrt_s(float);')
            result = subprocess.run([
                sys.executable, str(ROOT / 'tools/m2c_wrap.py'), '-t', target,
                '--valid-syntax', '--context', str(context), '--no-cache', str(assembly)
            ], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertNotIn('M2C_ERROR', result.stdout)
        self.assertNotIn('Decompilation failure', result.stdout)
        return result.stdout

    def test_hardware_root_lowers_to_generic_fpr_helper(self):
        result = self.decompile('''
    /* 0 00F00000 44000C46 */ c1 0xc0044
    mov.s $f0, $f1
    jr $ra
     nop
''')
        self.assertIn('__ee_sqrt_s(', result)
        self.assertNotIn('return sqrtf(', result)

    def test_real_libc_call_is_not_replaced(self):
        result = self.decompile('''
    addiu $sp, $sp, -16
    sw $ra, 12($sp)
    jal sqrtf
     nop
    lw $ra, 12($sp)
    jr $ra
     addiu $sp, $sp, 16
''')
        self.assertIn('sqrtf(', result)
        self.assertNotIn('__ee_sqrt_s(', result)

    def test_non_ee_target_keeps_upstream_square_root(self):
        result = self.decompile('''
    sqrt.s $f0, $f12
    jr $ra
     nop
''', target='mips-gcc-c')
        self.assertIn('sqrtf(', result)
        self.assertNotIn('__ee_sqrt_s(', result)

    def test_errno_fallback_patterns_keep_libc_semantics(self):
        for call in ('jal sqrtf', '''lui $t9, %hi(sqrtf)
    addiu $t9, $t9, %lo(sqrtf)
    jalr $ra, $t9'''):
            result = self.decompile('''
    addiu $sp, $sp, -16
    sw $ra, 12($sp)
    sqrt.s $f0, $f12
    c.eq.s $f0, $f0
    nop
    bc1t .Ldone
     nop
    ''' + call + '''
     nop
.Ldone:
    lw $ra, 12($sp)
    jr $ra
     addiu $sp, $sp, 16
''')
            self.assertIn('sqrtf(', result)
            self.assertNotIn('__ee_sqrt_s(', result)


if __name__ == '__main__':
    unittest.main()
