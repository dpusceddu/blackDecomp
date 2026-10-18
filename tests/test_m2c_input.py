"""Data sections must reach m2c without altering the real build's assembly."""
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from m2c_input import normalize_sections


class Sections(unittest.TestCase):
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
