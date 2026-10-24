"""INCLUDE_ASM markers: scanning with conditionals, NON_MATCHING blocks, replacement by C."""
import sys
import unittest
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import include_asm as I

SOURCE = '''#include "include_asm.h"
INCLUDE_ASM("asm/x", func_00100000);
/* INCLUDE_ASM("asm/x", func_00100004); */
// INCLUDE_ASM("asm/x", func_00100006);
int func_00100008(void) { return 1; }
#ifdef NON_MATCHING
// Unmatched: scheduling.
int func_00100010(int a) { return a + 1; }
#else
INCLUDE_ASM("asm/x", func_00100010);
#endif
#ifndef NON_MATCHING
INCLUDE_ASM("asm/x", func_00100020);
#endif
#if defined(FOO)
INCLUDE_ASM("asm/x", func_00100030);
#endif
'''


class Markers(unittest.TestCase):
    def names(self, defines=()):
        return [m.name for m in I.markers(SOURCE, defines)]

    def test_normal_build_sees_the_else_branches(self):
        self.assertEqual(self.names(), ['func_00100000', 'func_00100010', 'func_00100020'])

    def test_non_matching_build_drops_the_drafted_functions(self):
        self.assertEqual(self.names({'NON_MATCHING'}), ['func_00100000'])

    def test_compiler_defines_select_branches(self):
        self.assertIn('func_00100030', self.names({'FOO'}))

    def test_comments_are_not_markers(self):
        self.assertNotIn('func_00100004', self.names())
        self.assertNotIn('func_00100006', self.names())

    def test_addresses(self):
        self.assertEqual(I.marker_addresses(SOURCE), [0x100000, 0x100010, 0x100020])
        with self.assertRaises(ValueError):
            I.marker_addresses('INCLUDE_ASM("asm/x", Foo__Fv);')

    def test_line_numbers(self):
        self.assertEqual([m.line for m in I.markers(SOURCE)], [2, 10, 13])

    def test_replace_plain_marker(self):
        out = I.replace(SOURCE, 'func_00100000', 'int func_00100000(void) { return 0; }')
        self.assertIn('int func_00100000(void) { return 0; }', out)
        self.assertEqual([m.name for m in I.markers(out)], ['func_00100010', 'func_00100020'])

    def test_replace_removes_the_draft_block(self):
        out = I.replace(SOURCE, 'func_00100010', 'int func_00100010(int a) { return a + 1; }')
        self.assertNotIn('NON_MATCHING\n// Unmatched', out)
        self.assertNotIn('#else\n', out)
        self.assertEqual([m.name for m in I.markers(out)], ['func_00100000', 'func_00100020'])
        self.assertEqual(out.count('func_00100010'), 1)

    def test_replace_unknown_function(self):
        with self.assertRaises(KeyError):
            I.replace(SOURCE, 'func_00999999', 'x')


if __name__ == '__main__':
    unittest.main()
