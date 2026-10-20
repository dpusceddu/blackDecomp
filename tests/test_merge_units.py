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

    def test_moved_assembly_claim_can_gain_an_inventory_size(self):
        before = [dict(name='old', source='old.cpp', functions=[dict(addr=1, status='asm', reason='claim')])]
        ours = copy.deepcopy(before)
        ours[0]['functions'][0]['size'] = 352
        moved = copy.deepcopy(before[0])
        moved.update(name='new', source='new.cpp')
        result = merge(before, ours, [moved])
        self.assertEqual([u['name'] for u in result], ['new'])

    def test_source_size_conflict_still_requires_review(self):
        before = [unit('a', 1, 'a.cpp')]
        before[0]['functions'][0]['size'] = 32
        ours, theirs = copy.deepcopy(before), copy.deepcopy(before)
        ours[0]['functions'][0]['size'] = 36
        theirs[0]['source'] = 'other.cpp'
        with self.assertRaises(ValueError):
            merge(before, ours, theirs)

    def test_assembly_only_size_change_preserves_existing_metadata(self):
        before = [dict(name='a', source='a.cpp', functions=[dict(addr=1, status='asm')])]
        ours = copy.deepcopy(before)
        ours[0]['functions'][0]['size'] = 352
        self.assertEqual(merge(before, ours, before)[0]['functions'][0]['size'], 352)


if __name__ == '__main__':
    unittest.main()
