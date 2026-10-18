"""Data sections must reach m2c without altering the real build's assembly."""
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from m2c_input import normalize_sections, decode_raw_instructions


class Sections(unittest.TestCase):
    def test_raw_short_branch_and_ee_odd_float_are_instructions(self):
        text = '''.section .text.00F00000, "ax"
    /* 0 00F00000 00000000 */ nop
    /* 4 00F00004 FEFF8014 */ .word 0x1480FFFE
    /* 8 00F00008 64000046 */ .word 0x46000064
.section .rodata.00F10000, "a"
    /* C 00F10000 64000046 */ .word 0x46000064
'''
        result = decode_raw_instructions(text)
        self.assertIn('.Lm2c_00F00000:', result)
        self.assertIn('bnez', result)
        self.assertIn('cvt.w.s', result)
        self.assertIn('$f1, $f0', result)
        self.assertIn('/* C 00F10000 64000046 */ .word 0x46000064', result)

    def test_raw_branch_outside_function_stays_opaque(self):
        text = '.section .text\n/* 0 00F00000 FEFF8014 */ .word 0x1480FFFE\n'
        self.assertEqual(decode_raw_instructions(text), text)

    def test_m2c_reads_raw_odd_register_conversion(self):
        import subprocess
        text = '''.section .text
glabel probe_convert
    /* 0 00F00000 64600046 */ .word 0x46006064
    mfc1 $v0, $f1
    jr $ra
     nop
'''
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'probe.s'
            context = Path(directory) / 'ctx.c'
            path.write_text(decode_raw_instructions(text))
            context.write_text('int probe_convert(float value);')
            result = subprocess.run([sys.executable, str(ROOT / 'tools/m2c_wrap.py'), '-t', 'mipsee-gcc-c', '--context', str(context), '--no-cache', str(path)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertNotIn('second half of f64', result.stdout)
        self.assertNotIn('Decompilation failure', result.stdout)
        self.assertIn('value', result.stdout)
        self.assertIn('return', result.stdout)

    def test_split_sections_and_small_data(self):
        text = '.section .rodata.003F0000, "a"\n.section .lit4.00440000, "wa"\n.section .sbss.00440010, "wa"\n'
        self.assertEqual(normalize_sections(text), '.section .rodata, "a"\n.section .rodata, "wa"\n.section .bss, "wa"\n')

    def test_does_not_rewrite_labels_or_unrelated_sections(self):
        text = '.section .text.00100000, "ax"\n.section .rodata.custom, "a"\n.asciz ".rodata.003F0000"\n'
        self.assertEqual(normalize_sections(text), text)

    def test_switch_table_reaches_parser(self):
        # Authored probe, independent of the game: one address-suffixed table.
        import subprocess
        asm = '''.section .text.00F00000, "ax"
glabel probe_switch
    sltiu $v0, $a0, 3
    beqz $v0, .Ldefault
     sll $a0, $a0, 2
    lui $v0, %hi(jtbl_probe)
    addiu $v0, $v0, %lo(jtbl_probe)
    addu $v0, $v0, $a0
    lw $v0, 0($v0)
    jr $v0
     nop
.Lzero:
    jr $ra
     addiu $v0, $zero, 10
.Lone:
    jr $ra
     addiu $v0, $zero, 20
.Ltwo:
    jr $ra
     addiu $v0, $zero, 30
.Ldefault:
    jr $ra
     addiu $v0, $zero, -1
.section .rodata.00F10000, "a"
glabel jtbl_probe
    .word .Lzero, .Lone, .Ltwo
'''
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'probe.s'
            path.write_text(normalize_sections(asm))
            result = subprocess.run([sys.executable, str(ROOT / 'tools/m2c_wrap.py'), '-t', 'mipsee-gcc-c', str(path)], capture_output=True, text=True)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('switch', result.stdout)
        self.assertIn('case 2:', result.stdout)
        self.assertNotIn('Decompilation failure', result.stdout)


if __name__ == '__main__':
    unittest.main()
