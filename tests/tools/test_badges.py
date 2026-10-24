"""Badge colors, endpoint format and table rows of tools/badges.py."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import badges


class Badges(unittest.TestCase):
    def test_colors(self):
        self.assertEqual([badges.color(p) for p in (0, 4.9, 5, 15.1, 30, 49.9, 74, 75, 100)],
                         ['red', 'red', 'orange', 'yellow', 'yellowgreen', 'yellowgreen', 'green', 'brightgreen', 'brightgreen'])

    def test_endpoint(self):
        self.assertEqual(badges.badge('code', 15.113), dict(schemaVersion=1, label='code', message='15.1%', color='yellow'))

    def test_table_total(self):
        libs = {'game': dict(functions=10, matched_functions=5, bytes=1000, matched_bytes=250),
                'libc': dict(functions=2, matched_functions=0, bytes=100, matched_bytes=0)}
        text, total = badges.table(libs)
        self.assertEqual(total, dict(functions=12, matched_functions=5, bytes=1100, matched_bytes=250))
        self.assertIn('| game | 5 / 10 | 50.0 % | 250 / 1,000 | 25.0 % |', text)
        self.assertIn('| **Total** | **5 / 12** | **41.7 %** | **250 / 1,100** | **22.7 %** |', text)

    def test_replace_between(self):
        self.assertEqual(badges.replace_between('a\n%s\nold\n%s\nb' % (badges.BEGIN, badges.END), 'T'),
                         'a\n%s\n\nT\n\n%s\nb' % (badges.BEGIN, badges.END))
        self.assertIsNone(badges.replace_between('none', 'T'))


if __name__ == '__main__':
    unittest.main()
