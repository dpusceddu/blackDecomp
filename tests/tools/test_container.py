"""Container mounts keep real linked-worktree Git pointers accessible."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline')]
import container as C


class Container(unittest.TestCase):
    def test_real_linked_worktree_keeps_host_git_paths(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder).resolve()
            main, tree = root / 'main', root / 'linked tree'
            metadata = main / '.git'
            def git(*args, cwd=None):
                return subprocess.run(['git', *args], cwd=cwd or root, check=True,
                                      capture_output=True, text=True)
            git('init', str(main))
            git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid', 'commit', '--allow-empty', '-m', 'base', cwd=main)
            git('worktree', 'add', '--detach', str(tree), cwd=main)
            mounts = dict(C.mounts(tree))
            self.assertEqual(mounts[tree], 'rw')
            self.assertEqual(mounts[main], 'ro')
            self.assertEqual(mounts[metadata], 'rw')
            self.assertEqual(mounts[C.git_path(tree, '--absolute-git-dir')], 'rw')
            cmd = C.command(tree, 'docker', 'image', ['git', 'status', '--short'])
            self.assertEqual(cmd[-5:], [str(tree), 'image', 'git', 'status', '--short'])
            for path, access in mounts.items():
                self.assertIn('%s:%s:%s' % (path, path, access), cmd)
            self.assertTrue(any(arg.startswith('GIT_CONFIG_VALUE_') and arg.endswith('=%s' % main) for arg in cmd))


if __name__ == "__main__":
    unittest.main()
