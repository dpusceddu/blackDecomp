"""Registering a match edits the TU file and the split list as text (tools/tu_files.py)."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import tu_files as T
import splits as S

LIST = '''variant: SLUS_213.76
splits:
  - {src: src/game/a.c, range: [0x100000, 0x100100]}
  - {src: src/game/c.c, range: [0x100300, 0x100400]}
'''


class TextEdits(unittest.TestCase):
    def test_declarations_go_after_the_includes_once(self):
        text = '#include "include_asm.h"\n#include "ps2/prelude.h"\n\nextern int f(void);\nINCLUDE_ASM("asm/x", func_00100000);\n'
        out = T.insert_declarations(text, ['extern int f(void);', 'extern int g(void);'])
        self.assertEqual(out.count('extern int f(void);'), 1)
        self.assertLess(out.index('extern int g(void);'), out.index('INCLUDE_ASM'))
        self.assertEqual(T.insert_declarations(out, ['extern int g(void);']), out)

    def test_split_line_keeps_the_list_sorted(self):
        line = '  - {src: src/game/b.c, range: [0x100200, 0x100210]}'
        out = T.insert_split_line(LIST, line, 0x100200)
        starts = [S.num(r.entry['range'][0]) for r in S.load_splits(path=self._write(out))]
        self.assertEqual(starts, [0x100000, 0x100200, 0x100300])
        tail = T.insert_split_line(LIST, '  - {src: src/game/z.c, range: [0x100500, 0x100510]}', 0x100500)
        self.assertTrue(tail.rstrip().endswith('0x100510]}'))
        self.assertEqual(T.remove_split_line(out, 'src/game/b.c', 0x100200), LIST)

    def _write(self, text):
        import tempfile
        d = tempfile.mkdtemp()
        p = Path(d) / 'splits.yaml'
        p.write_text(text)
        return p

    def test_same_recipe_ignores_function_sections_only(self):
        split = S.Split({'src': 'a.c', 'range': [1, 2]}, {})
        self.assertTrue(T.same_recipe(split, 'ee-gcc2.95.3-136', ['-O2', '-G0', '-snas', '-ffunction-sections']))
        self.assertFalse(T.same_recipe(split, 'ee-gcc2.95.3-136', ['-O1', '-G0', '-snas']))

    def test_new_file_lists_every_function(self):
        text = T.new_file('x.c', 0x100000, 0x100020, [(0x100000, 0x100008), (0x100008, 0x100020), (0x100020, 0x100030)])
        self.assertIn('func_00100000', text)
        self.assertIn('func_00100008', text)
        self.assertNotIn('func_00100020', text)


if __name__ == '__main__':
    unittest.main()
