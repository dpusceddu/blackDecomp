"""Normal picks revisit drafts while respecting claims and size limits."""
import contextlib
import importlib.util
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline')]
def module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


N = module("next_work", ROOT / "tools/next.py")


class Picker(unittest.TestCase):
    def pick(self, chance, claims=None, max_size=256, top=15):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root / 'fresh.c').write_text('INCLUDE_ASM("asm/x", func_00100000);\n')
            (root / 'draft.c').write_text('#ifdef NON_MATCHING\nint func_00200000(void) {return 1;}\n#else\n'
                                         'INCLUDE_ASM("asm/x", func_00200000);\n#endif\n')
            units = [dict(source='fresh.c', library='game', functions=[dict(addr=0x100000, size=32)]),
                     dict(source='draft.c', library='game', functions=[dict(addr=0x200000, size=64)])]
            with patch.object(N, 'ROOT', root), patch.object(N, 'RESULTS', root / 'no-results.json'), \
                 patch.object(N, 'load_units', return_value=units), \
                 patch.object(N, 'pr_claims', return_value=(claims or {}, None)), \
                 patch.object(N, 'worktree_claims', return_value={}), \
                 patch.object(N.random, 'random', return_value=chance), \
                 contextlib.redirect_stdout(io.StringIO()) as output:
                N.files(top, max_size, 'game', 'repo', pick=True)
            return output.getvalue().strip()

    def test_normal_picker_sometimes_revisits_without_pipeline_results(self):
        self.assertEqual(self.pick(0.1), 'draft.c')
        self.assertEqual(self.pick(0.9), 'fresh.c')

    def test_revisits_respect_claims_and_size_and_fall_back(self):
        self.assertEqual(self.pick(0.1, {'draft.c': [1]}), 'fresh.c')
        self.assertEqual(self.pick(0.1, max_size=32), 'fresh.c')
        self.assertEqual(self.pick(0.9, {'fresh.c': [1]}), 'draft.c')
        self.assertEqual(self.pick(0.1, {'fresh.c': [1], 'draft.c': [2]}), '')

    def test_revisit_ranking_prefers_saved_near_miss_over_smaller_unscored_draft(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            units = []
            for name, addr, size in [('small', 0x100000, 32), ('near', 0x200000, 64)]:
                (root / (name + '.c')).write_text('#ifdef NON_MATCHING\nint func_%08X(void) {return 1;}\n#else\n'
                    'INCLUDE_ASM("asm/x", func_%08X);\n#endif\n' % (addr, addr))
                units.append(dict(source=name + '.c', library='game', functions=[dict(addr=addr, size=size)]))
            results = root / 'results.json'
            results.write_text(json.dumps({'0x200000': dict(status='near', score=2)}))
            with patch.object(N, 'ROOT', root), patch.object(N, 'RESULTS', results), \
                 patch.object(N, 'load_units', return_value=units), \
                 patch.object(N, 'pr_claims', return_value=({}, None)), \
                 patch.object(N, 'worktree_claims', return_value={}), contextlib.redirect_stdout(io.StringIO()) as output:
                N.files(1, 256, 'game', 'repo', pick=True)
            self.assertEqual(output.getvalue().strip(), 'near.c')


if __name__ == "__main__":
    unittest.main()
