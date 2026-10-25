"""A missing game executable or a missing first build ends a tool with one sentence, never a traceback (tools/build/preflight.py)."""
import shutil
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

REPO = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(REPO / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import preflight

VERSIONS = '{"SLUS_213.76": {"boot": "SLUS_213.76"}}'


def empty_checkout(root):
    """A checkout without game files and without a build: the tools and the version table, nothing else."""
    shutil.copytree(REPO / 'tools', root / 'tools', ignore=shutil.ignore_patterns('__pycache__'))
    (root / 'config').mkdir()
    (root / 'config' / 'versions.json').write_text(VERSIONS)
    (root / 'include').mkdir()
    return root


class Preflight(unittest.TestCase):
    def test_the_executable_and_the_build_are_told_apart(self):
        with tempfile.TemporaryDirectory() as d, patch.object(preflight, 'ROOT', Path(d)):
            (Path(d) / 'config').mkdir()
            (Path(d) / 'config' / 'versions.json').write_text(VERSIONS)
            with self.assertRaises(SystemExit) as raised:
                preflight.require()
            self.assertEqual(str(raised.exception),
                             'orig/SLUS_213.76/SLUS_213.76 is missing: put the executable of your copy of the game in orig/SLUS_213.76/ '
                             '(see README.md); run ninja first.')
            (Path(d) / 'orig' / 'SLUS_213.76').mkdir(parents=True)
            (Path(d) / 'orig' / 'SLUS_213.76' / 'SLUS_213.76').write_bytes(b'')
            with self.assertRaises(SystemExit) as raised:
                preflight.require()
            self.assertEqual(str(raised.exception), 'the build has not run (build/SLUS_213.76/placement.json is missing): run ninja first.')
            (Path(d) / 'build' / 'SLUS_213.76').mkdir(parents=True)
            (Path(d) / 'build' / 'SLUS_213.76' / 'placement.json').write_text('{}')
            preflight.require()                                   # nothing to complain about

    def test_guard_turns_a_missing_file_under_orig_or_build_into_the_sentence(self):
        with tempfile.TemporaryDirectory() as d, patch.object(preflight, 'ROOT', Path(d)):
            (Path(d) / 'config').mkdir()
            (Path(d) / 'config' / 'versions.json').write_text(VERSIONS)

            def reads(name):
                return lambda: (Path(d) / name).read_bytes()
            with self.assertRaisesRegex(SystemExit, 'orig/SLUS_213.76/SLUS_213.76 is missing'):
                preflight.guard(reads('orig/SLUS_213.76/SLUS_213.76'))
            with self.assertRaisesRegex(SystemExit, r'the build has not run \(asm/SLUS_213.76/nonmatchings/x.s is missing\): run ninja first'):
                preflight.guard(reads('asm/SLUS_213.76/nonmatchings/x.s'))
            with self.assertRaises(FileNotFoundError):            # any other missing file is a genuine error
                preflight.guard(reads('src/nothing.c'))


class Tools(unittest.TestCase):
    def run_tool(self, root, *args):
        return subprocess.run([sys.executable, *args], cwd=root, capture_output=True, text=True, timeout=120)

    def test_every_front_door_says_it_in_one_line(self):
        with tempfile.TemporaryDirectory() as d:
            root = empty_checkout(Path(d))
            for args in (['tools/next.py'], ['tools/progress.py'], ['tools/decompile.py', 'func_00100258'],
                         ['tools/trysrc.py', '100258', 'x.c'], ['tools/objdiff.py'], ['tools/badges.py']):
                result = self.run_tool(root, *args)
                with self.subTest(tool=args[0]):
                    self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
                    self.assertNotIn('Traceback', result.stderr)
                    lines = result.stderr.strip().splitlines()
                    self.assertEqual(len(lines), 1, result.stderr)
                    self.assertIn('put the executable of your copy of the game in orig/SLUS_213.76/', lines[0])
                    self.assertTrue(lines[0].endswith('run ninja first.'))

    def test_the_build_is_asked_for_once_the_executable_is_there(self):
        with tempfile.TemporaryDirectory() as d:
            root = empty_checkout(Path(d))
            (root / 'orig' / 'SLUS_213.76').mkdir(parents=True)
            (root / 'orig' / 'SLUS_213.76' / 'SLUS_213.76').write_bytes(b'')
            result = self.run_tool(root, 'tools/next.py', 'near')
            self.assertEqual(result.stderr.strip(), 'the build has not run (build/SLUS_213.76/placement.json is missing): run ninja first.')

    def test_help_needs_neither(self):
        with tempfile.TemporaryDirectory() as d:
            root = empty_checkout(Path(d))
            for tool in ('next', 'progress', 'decompile', 'trysrc', 'objdiff', 'badges', 'where'):
                with self.subTest(tool=tool):
                    self.assertEqual(self.run_tool(root, 'tools/%s.py' % tool, '--help').returncode, 0)

    def test_where_works_without_the_game_and_without_a_build(self):
        result = self.run_tool(REPO, 'tools/where.py', 'func_00100258')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn('func_00100258: src/', result.stdout)
        self.assertEqual(self.run_tool(REPO, 'tools/where.py', 'banana').stderr.strip(), "where.py: expected func_XXXXXXXX or an address, got 'banana'")

    def test_where_outside_a_checkout_is_one_line_too(self):
        with tempfile.TemporaryDirectory() as d:
            root = empty_checkout(Path(d))
            result = self.run_tool(root, 'tools/where.py', 'func_00100258')
            self.assertEqual(result.returncode, 1)
            self.assertEqual(len(result.stderr.strip().splitlines()), 1)
            self.assertNotIn('Traceback', result.stderr)


@unittest.skipUnless(shutil.which('ninja'), 'ninja is not installed')
class NinjaRule(unittest.TestCase):
    def test_ninja_says_where_the_executable_goes_and_is_quiet_once_it_is_there(self):
        with tempfile.TemporaryDirectory() as d:
            root = empty_checkout(Path(d))
            (root / 'build.ninja').write_text(
                'rule needexe\n  command = %s tools/build/preflight.py exe SLUS_213.76\n  description = the original executable\n  generator = 1\n'
                'rule touch\n  command = touch $out\n'
                'build orig/SLUS_213.76/SLUS_213.76: needexe\nbuild done.stamp: touch | orig/SLUS_213.76/SLUS_213.76\n' % sys.executable)
            first = subprocess.run(['ninja'], cwd=root, capture_output=True, text=True)
            self.assertNotEqual(first.returncode, 0)
            self.assertIn('orig/SLUS_213.76/SLUS_213.76 is missing: put the executable of your copy of the game', first.stdout + first.stderr)
            self.assertNotIn('Traceback', first.stdout + first.stderr)
            (root / 'orig' / 'SLUS_213.76').mkdir(parents=True, exist_ok=True)
            (root / 'orig' / 'SLUS_213.76' / 'SLUS_213.76').write_bytes(b'x')
            second = subprocess.run(['ninja'], cwd=root, capture_output=True, text=True)
            self.assertEqual(second.returncode, 0, second.stdout + second.stderr)

    def test_configure_writes_that_rule(self):
        text = (REPO / 'configure.py').read_text()
        self.assertIn('rule needexe', text)
        self.assertIn('build orig/{slug}/{boot}: needexe', text)


if __name__ == '__main__':
    unittest.main()
