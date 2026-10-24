"""Function boundaries come from the image and the committed boundaries.txt alone (splat's function list, no outside data)."""
import struct
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import boundaries as B

BASE = 0x100000
JR_RA, NOP, ADDIU_SP, MTC1_ZERO_F1, LUI_AT, MTC1_AT_F0 = 0x03E00008, 0, 0x27BD0020, 0x44800800, 0x3C013F80, 0x44810000
# 0x100010 ends a function; 0x100018 is an orphan piece (addiu; nop); 0x100020 is a real function that opens with
# `mtc1 $zero, $f1; nop`, which looks like one more orphan piece; the code behind it is its body.
WORDS = [JR_RA, NOP, NOP, NOP,
         JR_RA, NOP, ADDIU_SP, NOP,
         MTC1_ZERO_F1, NOP, LUI_AT, MTC1_AT_F0,
         JR_RA, NOP, NOP, NOP]


class FakeElf:
    sections = []

    def __init__(self, words):
        self.data = struct.pack('<%dI' % len(words), *words)

    def section(self, name):
        return dict(addr=BASE, size=len(self.data)) if name == '.text' else None

    def content(self, section):
        return self.data


class OrphanScan(unittest.TestCase):
    def test_without_a_known_start_the_real_function_is_cut_one_piece_late(self):
        self.assertEqual(([0x100028], 2), B.orphan_splits(FakeElf(WORDS)))

    def test_an_explicit_start_ends_the_run_there(self):
        self.assertEqual(([0x100020], 1), B.orphan_splits(FakeElf(WORDS), frozenset({0x100020})))


class BoundariesFile(unittest.TestCase):
    TEXT = ('// header\n'
            'func_00100338 = 0x00100338; // type:func\n'
            '// explicit: opens with `mtc1 $zero, $f1; nop`\n'
            'func_001B0BD0 = 0x001B0BD0; // type:func\n'
            '// an unrelated comment\n'
            'func_001B0C10 = 0x001B0C10; // type:func\n')

    def test_explicit_entries_carry_their_reason_and_apply_to_the_next_entry_only(self):
        explicit, starts = B.parse_boundaries(self.TEXT)
        self.assertEqual({0x1B0BD0: 'opens with `mtc1 $zero, $f1; nop`'}, explicit)
        self.assertEqual([0x100338, 0x1B0BD0, 0x1B0C10], starts)

    def test_writing_keeps_the_explicit_reasons_and_every_start(self):
        explicit, starts = B.parse_boundaries(self.TEXT)
        text = B.format_boundaries(starts + [0x200000], explicit)
        again_explicit, again_starts = B.parse_boundaries(text)
        self.assertEqual(explicit, again_explicit)
        self.assertEqual(sorted(starts + [0x200000]), again_starts)
        self.assertEqual(text, B.format_boundaries(again_starts, again_explicit))

    def test_a_listed_explicit_start_is_written_even_if_the_scan_does_not_find_it(self):
        text = B.format_boundaries([0x100338], {0x1B0BD0: 'reason'})
        self.assertEqual({0x1B0BD0: 'reason'}, B.parse_boundaries(text)[0])
        self.assertEqual([0x100338, 0x1B0BD0], B.parse_boundaries(text)[1])

    def test_committed_usa_file_lists_the_four_special_starts_with_reasons(self):
        explicit = B.explicit_starts('SLUS_213.76')
        self.assertEqual([0x1B0BD0, 0x280500, 0x316840, 0x384E28], sorted(explicit))
        for address, reason in explicit.items():
            self.assertTrue(reason.strip(), hex(address))
            self.assertNotIn('\n', reason)

    def test_other_versions_have_no_explicit_starts(self):
        self.assertEqual({}, B.explicit_starts('SLES_538.86'))


@unittest.skipUnless((ROOT / 'orig/SLUS_213.76/SLUS_213.76').exists(), 'needs your own SLUS_213.76 executable')
class DerivedFromTheImage(unittest.TestCase):
    def test_committed_file_is_what_the_scan_derives_from_the_image(self):
        import json
        from elfinfo import Elf
        boot = json.loads((ROOT / 'config/variants.json').read_text())['SLUS_213.76']['boot']
        elf = Elf((ROOT / 'orig/SLUS_213.76' / boot).read_bytes())
        explicit = B.explicit_starts('SLUS_213.76')
        splits, _ = B.orphan_splits(elf, frozenset(explicit))
        derived = sorted(set(splits) | set(B.ctor_list_starts(elf)) | set(explicit))
        committed = B.parse_boundaries((ROOT / 'config/SLUS_213.76/boundaries.txt').read_text())[1]
        self.assertEqual(derived, committed)


if __name__ == '__main__':
    unittest.main()
