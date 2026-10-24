import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from split_objects import split_literal_type_tails


class LiteralTypeTails(unittest.TestCase):
    def object(self, address=0x1008, directive='.asciz'):
        return dict(name='D_00001000', addr=0x1000, lines=[
            '.align 3', 'dlabel D_00001000',
            '/* 0000 00001000 */ ' + directive + ' "UNKNOWN"',
            '/* 554E4B4E4F574E00 */', '.align 2', '.align 3',
            '/* 0008 %08X */ .asciz "bad_alloc"' % address,
            '/* 6261645F616C6C6F6300 */', 'enddlabel D_00001000'])

    def split(self, obj, name='bad_alloc', prefix='UNKNOWN'):
        return split_literal_type_tails([obj], lambda a: prefix if a == 0x1000 else name)

    def test_complete_string_boundary_preserves_items_and_alignment(self):
        original = self.object()
        result = self.split(original)
        self.assertEqual([o['addr'] for o in result], [0x1000, 0x1008])
        content = lambda objects: [line for o in objects for line in o['lines']
                                   if not line.startswith(('dlabel ', 'enddlabel '))]
        self.assertEqual(content(result), content([original]))
        self.assertEqual(result[1]['lines'][:3], ['.align 2', '.align 3', 'dlabel D_00001008'])

    def test_valid_encoded_name_is_also_a_boundary(self):
        self.assertEqual(len(self.split(self.object(), name='Q24Demo6Widget')), 2)

    def test_build_only_splits_requested_boundaries(self):
        original = self.object()
        literal = lambda a: 'UNKNOWN' if a == 0x1000 else 'bad_alloc'
        self.assertEqual(split_literal_type_tails([original], literal, set()), [original])
        self.assertEqual(len(split_literal_type_tails([original], literal, {0x1008})), 2)
        with self.assertRaisesRegex(ValueError, 'not a complete string/type split'):
            split_literal_type_tails([original], literal, {0x1004})
        with self.assertRaisesRegex(ValueError, 'not a complete string/type split'):
            split_literal_type_tails([original], lambda a: 'ordinary label', {0x1008})

    def test_arbitrary_or_malformed_names_are_not_evidence(self):
        for name in ('ordinary label', 'Q24Demo99Missing', None):
            original = self.object()
            self.assertEqual(self.split(original, name=name), [original])

    def test_incomplete_string_or_nonadjacent_item_is_rejected(self):
        for original, prefix in ((self.object(address=0x1010), 'UNKNOWN'),
                                 (self.object(), 'longer than the span'),
                                 (self.object(), None),
                                 (self.object(directive='.word'), 'UNKNOWN')):
            self.assertEqual(self.split(original, prefix=prefix), [original])


if __name__ == '__main__':
    unittest.main()
