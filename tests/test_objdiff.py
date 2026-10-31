"""Native data labels must identify the same compiler-owned comparison data."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import objdiff


class OwnedDataLabels(unittest.TestCase):
    def test_switch_table_and_constant_references_keep_native_names(self):
        text = '''lui $2, %hi(jtbl_003F89D0)
addiu $2, $2, %lo(jtbl_003F89D0)
lwc1 $f0, %lo(D_003F8A08)($3)'''
        self.assertEqual(
            objdiff.local_data_symbols([text], {'.rodata': 0x3F89D0}, {'.rodata': 64}, set()),
            {'jtbl_003F89D0': ('.rodata', 0), 'D_003F8A08': ('.rodata', 56)},
        )

    def test_only_missing_labels_inside_the_owned_section_are_added(self):
        text = 'jtbl_003F89CC jtbl_003F89D0 jtbl_003F8A10 D_003F89D8'
        self.assertEqual(
            objdiff.local_data_symbols([text], {'.rodata': 0x3F89D0}, {'.rodata': 64}, {'D_003F89D8'}),
            {'jtbl_003F89D0': ('.rodata', 0)},
        )


if __name__ == '__main__':
    unittest.main()
