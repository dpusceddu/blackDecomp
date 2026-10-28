"""Preparation locking coordinates real Git worktrees without serializing other repositories."""
from pathlib import Path
import select
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
WORKER = '''
import sys
sys.path.insert(0, sys.argv[1])
from preparation_lock import preparation_lock
with preparation_lock(sys.argv[2]):
    print("entered", flush=True)
    command = sys.stdin.readline().strip()
    if command == "fail":
        raise RuntimeError("deliberate failure")
'''


SETUP_WORKER = """
import sys
from pathlib import Path
sys.path.insert(0, sys.argv[1])
import setup
setup.ROOT = Path(sys.argv[2])
def run(*args):
    if args[-1] == 'configure.py':
        print('entered', flush=True)
        sys.stdin.readline()
setup.run = run
setup.prepare(sys.executable)
"""
RECOVERY_WORKER = """
import sys
from pathlib import Path
sys.path[:0] = [sys.argv[1], str(Path(sys.argv[1]) / 'pipeline')]
import context_recovery as cr
cr.fingerprint = lambda root: 'stamp'
def recover(*args):
    print('entered', flush=True)
    sys.stdin.readline()
    return {}
cr._recover = recover
cr.recover(root=Path(sys.argv[2]))
"""


def git(root, *args):
    subprocess.run(['git', *args], cwd=root, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)


def worker(root, code=WORKER):
    return subprocess.Popen([sys.executable, '-u', '-c', code, str(ROOT / 'tools'), str(root)],
                            stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=0)


def line(process):
    ready, _, _ = select.select([process.stdout], [], [], 10)
    if not ready:
        raise AssertionError('worker did not report its state')
    return process.stdout.readline().decode().strip()


def finish(process, command='done'):
    process.stdin.write((command + '\n').encode())
    process.stdin.flush()
    return process.wait(timeout=10)


class PreparationLock(unittest.TestCase):
    def test_linked_worktrees_wait_and_unrelated_repositories_do_not(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder) / 'repo'
            root.mkdir()
            git(root, 'init', '-q')
            git(root, '-c', 'user.name=Test', '-c', 'user.email=test@example.invalid', 'commit', '--allow-empty', '-qm', 'init')
            linked = Path(folder) / 'linked'
            git(root, 'worktree', 'add', '-q', '--detach', str(linked))
            other = Path(folder) / 'other'
            other.mkdir()
            git(other, 'init', '-q')
            first, second, third = worker(root), None, None
            try:
                self.assertEqual(line(first), 'entered')
                second = worker(linked)
                self.assertIn('Waiting', line(second))
                third = worker(other)
                self.assertEqual(line(third), 'entered')
                self.assertEqual(finish(third), 0)
                self.assertEqual(finish(first), 0)
                self.assertEqual(line(second), 'entered')
                self.assertEqual(finish(second), 0)
            finally:
                for process in (first, second, third):
                    if process and process.poll() is None:
                        process.kill()
                        process.wait()
                    if process:
                        for stream in (process.stdin, process.stdout, process.stderr):
                            stream.close()

    def test_setup_and_cold_recovery_share_the_lock(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            git(root, 'init', '-q')
            setup, recovery = worker(root, SETUP_WORKER), None
            try:
                self.assertIn('comparison metadata', line(setup))
                self.assertEqual(line(setup), 'entered')
                recovery = worker(root, RECOVERY_WORKER)
                self.assertIn('Waiting', line(recovery))
                self.assertEqual(finish(setup), 0)
                self.assertEqual(line(recovery), 'entered')
                self.assertEqual(finish(recovery), 0)
            finally:
                for process in (setup, recovery):
                    if process and process.poll() is None:
                        process.kill()
                        process.wait()
                    if process:
                        for stream in (process.stdin, process.stdout, process.stderr):
                            stream.close()

    def test_exception_and_process_termination_release_lock(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            git(root, 'init', '-q')
            for command in ('fail', 'kill'):
                with self.subTest(command=command):
                    first = worker(root)
                    try:
                        self.assertEqual(line(first), 'entered')
                        if command == 'kill':
                            first.kill()
                            first.wait(timeout=10)
                        else:
                            self.assertNotEqual(finish(first, command), 0)
                        second = worker(root)
                        try:
                            self.assertEqual(line(second), 'entered')
                            self.assertEqual(finish(second), 0)
                        finally:
                            if second.poll() is None:
                                second.kill()
                                second.wait()
                            for stream in (second.stdin, second.stdout, second.stderr):
                                stream.close()
                    finally:
                        if first.poll() is None:
                            first.kill()
                            first.wait()
                        for stream in (first.stdin, first.stdout, first.stderr):
                            stream.close()


if __name__ == '__main__':
    unittest.main()
