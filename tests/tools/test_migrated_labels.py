"""Link-script ownership checks on synthetic section slots; no target tools."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
from make_ld import migrated_data_aliases


class MigratedLabelsTests(unittest.TestCase):
    def test_only_replaced_owned_slots_keep_original_global_names(self):
        placement = {'sections': {'.gcc_except_table': [
            {'key': 0x2000, 'owner': 'factory'}, {'key': 0x2020, 'owner': 'other'}]}}
        layout = {'sections': [{'name': '.gcc_except_table', 'addr': 0x2000, 'orig_size': 0x40}]}
        labels = [[0x1000, 'text'], [0x2000, 'ehtbl_00002000'], [0x2010, 'ehtbl_inside'],
                  [0x2018, '.Lprivate'], [0x2020, 'ehtbl_other'], [0x2040, 'outside']]
        self.assertEqual(migrated_data_aliases(placement, labels, {'factory': 'source'}, layout), [
            'PROVIDE(ehtbl_00002000 = ADDR(.gcc_except_table) + 0x0);',
            'PROVIDE(ehtbl_inside = ADDR(.gcc_except_table) + 0x10);'])
        aliases = migrated_data_aliases(placement, labels, {'other': 'source'}, layout)
        self.assertEqual(aliases, ['PROVIDE(ehtbl_other = ADDR(.gcc_except_table) + 0x20);'])


if __name__ == '__main__':
    unittest.main()
