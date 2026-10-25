"""tools/relocate_sources.py: 'old new' on the command line or a file of pairs; every reference follows the file."""
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]


class Relocate(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.TemporaryDirectory()
        self.addCleanup(self.dir.cleanup)
        self.root = root = Path(self.dir.name)
        (root / 'tools').mkdir()
        shutil.copy(REPO / 'tools/relocate_sources.py', root / 'tools/relocate_sources.py')
        for name, text in {'src/game/unsorted/tu_100000.c': 'int x;\n', 'src/game/unsorted/tu_100100.c': 'int y;\n',
                           'config/SLUS_213.76/splits.yaml': 'splits:\n  - {src: src/game/unsorted/tu_100000.c, range: [0x100000, 0x100010]}\n'
                           '  - {src: src/game/unsorted/tu_100100.c, range: [0x100100, 0x100110]}\n'
                           '  - {src: src/game/unsorted/tu_100000.c, range: [0x100020, 0x100030]}\n',
                           'docs/note.md': 'See src/game/unsorted/tu_100000.c and src/game/unsorted/tu_100000.cpp.\n'}.items():
            (root / name).parent.mkdir(parents=True, exist_ok=True)
            (root / name).write_text(text)
        git = lambda *a: subprocess.run(['git', '-c', 'user.name=t', '-c', 'user.email=t@t', *a], cwd=root, check=True, capture_output=True)
        git('init', '-q')
        git('add', '-A')
        git('commit', '-qm', 'start')

    def run_tool(self, *args):
        return subprocess.run([sys.executable, 'tools/relocate_sources.py', *args], cwd=self.root, capture_output=True, text=True)

    def test_one_file_old_new(self):
        result = self.run_tool('src/game/unsorted/tu_100000.c', 'src/game/ai/tu_100000.c')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual('1 files moved', result.stdout.strip())
        self.assertTrue((self.root / 'src/game/ai/tu_100000.c').is_file())
        self.assertFalse((self.root / 'src/game/unsorted/tu_100000.c').exists())
        splits = (self.root / 'config/SLUS_213.76/splits.yaml').read_text()
        self.assertEqual(2, splits.count('src/game/ai/tu_100000.c'))          # both entries of the file follow it
        self.assertIn('src/game/unsorted/tu_100100.c', splits)
        self.assertEqual('See src/game/ai/tu_100000.c and src/game/unsorted/tu_100000.cpp.\n', (self.root / 'docs/note.md').read_text())

    def test_dry_run_changes_nothing_and_a_missing_file_is_one_line(self):
        result = self.run_tool('src/game/unsorted/tu_100000.c', 'src/game/ai/tu_100000.c', '--dry-run')
        self.assertEqual('1 files would move', result.stdout.strip())
        self.assertTrue((self.root / 'src/game/unsorted/tu_100000.c').is_file())
        result = self.run_tool('src/game/unsorted/nothing.c', 'src/game/ai/nothing.c')
        self.assertEqual(1, result.returncode)
        self.assertEqual(['no such file: src/game/unsorted/nothing.c (give repo-relative paths)'], result.stderr.strip().splitlines())

    def test_a_file_of_pairs_still_works(self):
        (self.root / 'pairs.txt').write_text('# comment\nsrc/game/unsorted/tu_100000.c src/game/ai/a.c\nsrc/game/unsorted/tu_100100.c src/game/ui/b.c\n')
        result = self.run_tool('pairs.txt')
        self.assertEqual('2 files moved', result.stdout.strip())
        self.assertTrue((self.root / 'src/game/ui/b.c').is_file())


if __name__ == '__main__':
    unittest.main()
