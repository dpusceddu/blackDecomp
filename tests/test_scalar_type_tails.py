import sys
import unittest
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
from split_objects import split_scalar_type_tails


class ScalarTypeTails(unittest.TestCase):
    def object(self, directive='.word', second=0x1004):
        return dict(name='D_00001000', addr=0x1000, lines=[
            '.align 2', 'dlabel D_00001000',
            '/* 0000 00001000 01000000 */ ' + directive + ' 1',
            '/* 0004 %08X 00000000 */ .word 0' % second,
            'enddlabel D_00001000'])

    def test_encoded_class_boundary_preserves_data_and_alignment(self):
        original = self.object()
        result = split_scalar_type_tails([original], lambda a: 'Q24Demo6Widget')
        self.assertEqual([o['addr'] for o in result], [0x1000, 0x1004])
        self.assertEqual(result[0]['lines'][0], '.align 2')
        self.assertEqual(result[1]['name'], 'D_00001004')
        items = lambda objects: [line for o in objects for line in o['lines'] if line.startswith('/*')]
        self.assertEqual(items(result), items([original]))

    def test_runtime_exception_after_float(self):
        self.assertEqual(len(split_scalar_type_tails([self.object('.float')], lambda a: 'bad_alloc')), 2)

    def test_arbitrary_string_is_not_boundary_evidence(self):
        original = self.object()
        self.assertEqual(split_scalar_type_tails([original], lambda a: 'ordinary label'), [original])

    def test_malformed_encoded_name_is_rejected(self):
        original = self.object()
        self.assertEqual(split_scalar_type_tails([original], lambda a: 'Q24Demo99Missing'), [original])

    def test_wide_scalar_and_nonadjacent_item_are_rejected(self):
        for original in (self.object('.double'), self.object(second=0x1008)):
            self.assertEqual(split_scalar_type_tails([original], lambda a: 'Q24Demo6Widget'), [original])


if __name__ == '__main__':
    unittest.main()
