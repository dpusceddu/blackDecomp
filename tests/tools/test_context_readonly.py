"""Tools must not rewrite tracked files: the m2c context is built in build/auto/ only.

The access views under include/ are hand-maintained source. No tool of this repository writes them: context_recovery.py has no
header writer and no flag for one, and decompile.py and autodecomp.py only write under build/auto/."""
import contextlib, hashlib, io, json, os, subprocess, sys, tempfile, unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import autodecomp
import context_recovery as cr
import decompile

REPO = Path(__file__).resolve().parents[2]
LAYOUT = dict(fields=[dict(offset=4, size=4, type='s32')], extent=8, nodes=[], verified_by=[])


def digest(root, pattern='include/**/*'):
    """Hashes of the files under a directory, to compare before and after."""
    return {p.relative_to(root).as_posix(): hashlib.sha256(p.read_bytes()).hexdigest()
            for p in sorted(root.glob(pattern)) if p.is_file()}


def result():
    return dict(layouts={'Recovered_Thing': dict(LAYOUT)}, signatures={}, summary={})


class BuildContext(unittest.TestCase):
    def test_build_context_writes_only_build_auto(self):
        """In a throwaway repository: after the context is built, git sees nothing but the ignored build/ directory."""
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            headers = root / 'include/game/layouts'
            headers.mkdir(parents=True)
            (headers / 'Recovered_Thing.h').write_text('/* committed */\n')
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

    def test_main_writes_only_the_build_context_and_has_no_header_writer(self):
        self.assertFalse(hasattr(cr, 'write_outputs'))
        for argv, builds in ((['context_recovery.py'], True), (['context_recovery.py', '--report'], False)):
            with patch.object(sys, 'argv', argv), patch.object(cr, 'recover', return_value=result()), \
                 patch.object(cr, 'write_build_context') as write_build:
                cr.main()
            self.assertEqual(builds, write_build.called, argv)
        with patch.object(sys, 'argv', ['context_recovery.py', '--write-headers']), \
             patch.object(cr, 'recover', return_value=result()), self.assertRaises(SystemExit), \
             contextlib.redirect_stderr(io.StringIO()):
            cr.main()


class DecompileContext(unittest.TestCase):
    def test_first_run_builds_the_context_without_touching_tracked_files(self):
        """decompile.py's first run (no build/auto context yet) recovers and writes the context; the repository's
        include/ tree and its git status are identical afterwards, and nothing outside build/auto/ is created."""
        before = digest(REPO)
        status = subprocess.run(['git', 'status', '--porcelain'], cwd=REPO, capture_output=True, text=True).stdout
        fn = dict(addr=0x100258, name='func_00100258', words=[0, 0, 0], size=12, strings=None)
        env = {k: v for k, v in os.environ.items() if k != 'AUTODECOMP_FREEZE_CONTEXT'}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'build/auto').mkdir(parents=True)
            with patch.dict(os.environ, env, clear=True), \
                 patch.object(decompile, 'ROOT', root), patch.object(cr, 'ROOT', root), \
                 patch.object(autodecomp, 'AUTO', root / 'build/auto'), patch.object(autodecomp, 'RECOVERED', None), \
                 patch.object(cr, 'recover', return_value=result()), \
                 patch.object(autodecomp, 'load_inventory', return_value=[fn]), \
                 patch.object(autodecomp, 'is_orphan', return_value=False), \
                 patch.object(autodecomp, 'run_m2c', return_value={fn['name']: dict(body='', ret='void', params='')}), \
                 patch.object(autodecomp, 'clean_function', return_value=('void func_00100258(void) {}\n', 'sig')):
                decompile.draft(0x100258, 'ctx.c')
            self.assertTrue((root / 'build/auto/recovered_layouts.c').is_file())
            self.assertTrue((root / 'build/auto/ctx.c').is_file())
            self.assertEqual(['build'], sorted(p.name for p in root.iterdir()))
        self.assertEqual(before, digest(REPO))
        self.assertEqual(status, subprocess.run(['git', 'status', '--porcelain'], cwd=REPO, capture_output=True,
                                                text=True).stdout)

    def test_recovered_context_writes_only_the_build_context(self):
        """The shared context loader writes the ignored build context and nothing else."""
        with patch.dict(os.environ, {k: v for k, v in os.environ.items() if k != 'AUTODECOMP_FREEZE_CONTEXT'}, clear=True), \
             patch.object(autodecomp, 'RECOVERED', None), patch.object(cr, 'recover', return_value=result()), \
             patch.object(cr, 'write_build_context') as build:
            autodecomp.recovered_context()
        build.assert_called_once()


if __name__ == '__main__':
    unittest.main()
