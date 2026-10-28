"""Tools must not rewrite tracked files: the m2c context is built in build/auto/ only.

The headers under include/ are hand-maintained source. No tool of this repository writes them: context_recovery.py has no
header writer and no flag for one, and decompile.py and autodecomp.py only write under build/auto/."""
import subprocess, sys, tempfile, unittest
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import context_recovery as cr

LAYOUT = dict(fields=[dict(offset=4, size=4, type='s32')], extent=8, nodes=[], verified_by=[])


def result():
    return dict(layouts={'Recovered_Thing': dict(LAYOUT)}, signatures={}, summary={})


class BuildContext(unittest.TestCase):
    def test_build_context_writes_only_build_auto(self):
        """In a throwaway repository: after the context is built, git sees nothing but the ignored build/ directory."""
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            headers = root / 'include/game'
            headers.mkdir(parents=True)
            (headers / 'thing.h').write_text('/* committed */\n')
            (headers / 'layouts.h').write_text('/* committed */\n')
            (root / '.gitignore').write_text('build/\n')
            git = lambda *a: subprocess.run(['git', '-c', 'user.name=t', '-c', 'user.email=t@t', *a], cwd=root,
                                            capture_output=True, text=True, check=True).stdout
            git('init', '-q')
            git('add', '-A')
            git('commit', '-qm', 'committed headers')
            cr.write_build_context(result(), root)
            self.assertTrue((root / 'build/auto/recovered_layouts.c').is_file())
            self.assertEqual('', git('status', '--porcelain'))

if __name__ == '__main__':
    unittest.main()
