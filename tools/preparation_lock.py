"""Serialize expensive preparation across worktrees of the same Git repository."""
import sys
if __name__ == '__main__' and sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
from contextlib import contextmanager
import fcntl
from pathlib import Path
import subprocess


def lock_path(root):
    """Use Git's shared directory, or a local lock for non-Git fixture trees."""
    root = Path(root).resolve()
    result = subprocess.run(['git', 'rev-parse', '--path-format=absolute', '--git-common-dir'],
                            cwd=root, capture_output=True, text=True)
    directory = Path(result.stdout.strip()) if result.returncode == 0 else root / '.local'
    directory.mkdir(parents=True, exist_ok=True)
    return directory / 'blackdecomp-preparation.lock'


@contextmanager
def preparation_lock(root):
    """Hold a kernel-managed lock until preparation finishes, including on exceptions."""
    with lock_path(root).open('a') as lock:
        try:
            fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            print('Waiting for another worktree to finish preparation...', flush=True)
            fcntl.flock(lock, fcntl.LOCK_EX)
        try:
            yield
        finally:
            fcntl.flock(lock, fcntl.LOCK_UN)
