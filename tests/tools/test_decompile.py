"""tools/decompile.py: target parsing, marker lookup, printing and --write, with a synthetic source file and draft."""
import contextlib, io, sys, tempfile, unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import decompile

TU = '''#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100258);

int other(void) { return 1; }
'''
DRAFT = '''#include "ps2/prelude.h"
#include "ps2/recovered_types.h"
extern s32 D_00400000;

s32 func_00100258(void) {
    return D_00400000;
}
'''


class Decompile(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        (self.root / 'asm/SLUS_213.76/nonmatchings').mkdir(parents=True)
        (self.root / 'asm/SLUS_213.76/nonmatchings/func_00100258.s').write_text('')
        (self.root / 'src').mkdir()
        self.path = self.root / 'src/tu_100258.c'
        self.path.write_text(TU)
        self.split = SimpleNamespace(start=0x100258, end=0x100300, src='src/tu_100258.c', compiler='cc', flags=['-O2'],
                                     functions=None, defines=lambda: set())
        for target in (patch.object(decompile, 'ROOT', self.root), patch.object(decompile.S, 'ROOT', self.root),
                       patch.object(decompile.S, 'load_splits', return_value=[self.split]),
                       patch.object(decompile, 'draft', return_value=(dict(size=8), {}, DRAFT, 'sig'))):
            target.start()
            self.addCleanup(target.stop)

    def run_main(self, *args):
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            code = decompile.main(list(args))
        return code, out.getvalue()

    def test_target_forms(self):
        for text in ('func_00100258', '0x100258', '100258'):
            self.assertEqual(0x100258, decompile.parse_target(text))
        with self.assertRaises(SystemExit):
            decompile.parse_target('not a function')

    def test_locates_the_marker(self):
        split, path, line = decompile.locate(0x100258)
        self.assertEqual((path, line), (self.path, 4))
        self.assertIsNone(decompile.locate(0x100300))

    def test_prints_file_line_and_draft_without_touching_the_file(self):
        code, out = self.run_main('func_00100258')
        self.assertEqual(0, code)
        self.assertIn('src/tu_100258.c line 4', out)
        self.assertIn('s32 func_00100258(void) {', out)
        self.assertIn('extern s32 D_00400000;', out)
        self.assertEqual(TU, self.path.read_text())

    def test_write_replaces_the_marker_and_adds_the_declarations(self):
        self.run_main('func_00100258', '--write')
        text = self.path.read_text()
        self.assertNotIn('INCLUDE_ASM', text)
        self.assertIn('s32 func_00100258(void) {\n    return D_00400000;\n}', text)
        self.assertLess(text.index('extern s32 D_00400000;'), text.index('func_00100258'))
        self.assertIn('int other(void)', text)

    def test_an_already_recovered_function_is_refused(self):
        self.path.write_text(TU.replace('INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100258);', 'int func_00100258(void) { return 0; }'))
        with self.assertRaisesRegex(SystemExit, 'already recovered'):
            self.run_main('func_00100258')


if __name__ == '__main__':
    unittest.main()
