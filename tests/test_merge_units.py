import copy
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from merge_units import merge


def unit(name, address, source):
    return dict(name=name, source=source, functions=[dict(addr=address, status='source')])


class UnitMerges(unittest.TestCase):
    def test_disjoint_edits_keep_both(self):
        base = [unit('a', 1, 'a.c'), unit('b', 2, 'b.c')]
        ours, theirs = copy.deepcopy(base), copy.deepcopy(base)
        ours[0]['source'] = 'a.cpp'
        theirs[1]['source'] = 'b.cpp'
        self.assertEqual([u['source'] for u in merge(base, ours, theirs)], ['a.cpp', 'b.cpp'])

    def test_overlapping_sources_are_not_silently_selected(self):
        base = [unit('a', 1, 'a.c')]
        with self.assertRaises(ValueError):
            merge(base, [unit('a', 1, 'left.c')], [unit('a', 1, 'right.c')])

    def test_duplicate_source_address_is_rejected(self):
        with self.assertRaises(ValueError):
            merge([], [unit('a', 1, 'a.c')], [unit('b', 1, 'b.c')])

    def test_address_formatting_does_not_create_a_conflict(self):
        before = [unit('a', '0x001', 'a.c')]
        ours = [unit('a', '0x1', 'a.c')]
        theirs = [unit('a', 1, 'a.cpp')]
        self.assertEqual(merge(before, ours, theirs)[0]['source'], 'a.cpp')


if __name__ == '__main__':
    unittest.main()
