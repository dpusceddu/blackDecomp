"""Normal picks revisit drafts while respecting claims and size limits."""
import contextlib
import importlib.util
import io
import json
import datetime
import subprocess
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline')]
def module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


N = module("next_work", ROOT / "tools/next.py")


class Picker(unittest.TestCase):
    def test_unknown_claims_stop_selection(self):
        for pick in (False, True):
            with self.subTest(pick=pick), \
                 patch.object(N, 'pr_claims', return_value=(None, 'gh failed')), \
                 patch.object(N, 'load_units', return_value=[]), contextlib.redirect_stdout(io.StringIO()) as output:
                with self.assertRaisesRegex(SystemExit, 'fix GitHub access'):
                    N.files(15, 256, None, None, pick=pick)
                self.assertEqual(output.getvalue(), '')

    def test_claims_include_changed_files_and_body_and_expire_only_stale_drafts(self):
        now = datetime.datetime.now(datetime.timezone.utc)
        prs = [dict(number=i, isDraft=draft, updatedAt=(now - datetime.timedelta(hours=hours)).isoformat(),
                    files=[dict(path='src/changed%d.c' % i)], body='Claims: src/claimed%d.cpp' % i)
               for i, draft, hours in [(1, True, 0), (2, True, 49), (3, False, 49)]]
        with patch.object(N.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0, json.dumps(prs), '')):
            claims, problem = N.pr_claims('owner/repo')
        self.assertIsNone(problem)
        self.assertEqual(claims, {'src/changed1.c': [1], 'src/claimed1.cpp': [1],
                                  'src/changed3.c': [3], 'src/claimed3.cpp': [3]})

    def pick(self, claims=None, max_size=256):
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
                 patch.object(N.random, 'random', return_value=0.1), \
                 contextlib.redirect_stdout(io.StringIO()) as output:
                N.files(15, max_size, 'game', 'repo', pick=True)
            return output.getvalue().strip()

    def test_revisits_respect_claims_and_size_and_fall_back(self):
        self.assertEqual(self.pick({'draft.c': [1]}), 'fresh.c')
        self.assertEqual(self.pick(max_size=32), 'fresh.c')
        self.assertEqual(self.pick({'fresh.c': [1]}), 'draft.c')
        self.assertEqual(self.pick({'fresh.c': [1], 'draft.c': [2]}), '')

if __name__ == "__main__":
    unittest.main()
