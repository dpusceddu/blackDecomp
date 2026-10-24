"""Whole-unit exception ownership uses authored symbolic handlers, never game data."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from split_objects import shared_exception_owners


class SharedExceptionTables(unittest.TestCase):
    def setUp(self):
        self.starts = [0x1000, 0x1100, 0x1200]
        self.objects = [dict(addr=0x2000, lines=['.word $LEH_00001010', '.word .L00001120'])]
        self.unit = dict(name='owner', shared_exception_tables=['0x2000'], functions=[
            dict(addr=0x1000, status='source'), dict(addr='0x1100', status='source')])

    def test_multi_function_table_requires_explicit_same_unit_ownership(self):
        self.assertEqual(shared_exception_owners([self.unit], self.objects, self.starts), {0x2000: 0x1000})
        self.unit.pop('shared_exception_tables')
        self.assertEqual(shared_exception_owners([self.unit], self.objects, self.starts), {})

    def test_foreign_or_unmatched_handler_is_rejected(self):
        self.unit['functions'][1]['status'] = 'asm'
        with self.assertRaisesRegex(ValueError, 'crosses'):
            shared_exception_owners([self.unit], self.objects, self.starts)
        self.unit['functions'][1]['status'] = 'source'
        self.objects[0]['lines'].append('.word $LEH_00001210')
        with self.assertRaisesRegex(ValueError, 'crosses'):
            shared_exception_owners([self.unit], self.objects, self.starts)

    def test_only_unique_existing_object_boundary_can_be_selected(self):
        self.unit['shared_exception_tables'] = ['0x2004']
        with self.assertRaisesRegex(ValueError, 'boundary'):
            shared_exception_owners([self.unit], self.objects, self.starts)
        self.unit['shared_exception_tables'] = ['0x2000', '0x2000']
        with self.assertRaisesRegex(ValueError, 'unique'):
            shared_exception_owners([self.unit], self.objects, self.starts)

    def test_empty_or_pre_text_target_cannot_authorize_ownership(self):
        for lines in (['.word -1, -1'], ['.word $LEH_00000010']):
            self.objects[0]['lines'] = lines
            with self.assertRaisesRegex(ValueError, 'valid code targets'):
                shared_exception_owners([self.unit], self.objects, self.starts)


if __name__ == '__main__':
    unittest.main()
