#!/usr/bin/env python3
"""Run commands in the Linux x86-64 container with linked-worktree Git paths accessible.

Usage: python3 tools/container.py [--engine docker|podman] [--image black-decomp] [--relabel] [--dry-run] [COMMAND ...]
Build the image first: docker build --platform linux/amd64 -t black-decomp .
With no command, opens bash. The current checkout is writable; other registered
worktrees are read-only for claims and shared inputs. Git metadata is writable.
Paths retain their host locations so .git pointers and setup.py symlinks work.
Use --relabel on SELinux hosts (shared :z labels, including Git metadata).
"""
import argparse
import os
from pathlib import Path
import shlex
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def git_path(root, option):
    return Path(subprocess.check_output(['git', 'rev-parse', '--path-format=absolute', option], cwd=root, text=True).strip())


def mounts(root):
    """Exact host/container paths and access; also supports separate Git directories."""
    root = root.resolve()
    result = {root: 'rw'}
    data = subprocess.check_output(['git', 'worktree', 'list', '--porcelain', '-z'], cwd=root)
    for field in os.fsdecode(data).split('\0'):
        if field.startswith('worktree '):
            tree = Path(field[9:]).resolve()
            if tree.is_dir() and tree != root:
                result[tree] = 'ro'
    for option in ('--git-common-dir', '--absolute-git-dir'):
        path = git_path(root, option).resolve()
        if not path.is_relative_to(root):
            result[path] = 'rw'
    # Parent mounts first; writable Git metadata overrides a read-only main tree.
    return sorted(result.items(), key=lambda item: (len(item[0].parts), str(item[0])))


def command(root, engine, image, args, relabel=False, tty=False):
    mounted = mounts(root)
    cmd = [engine, 'run', '--rm', '--init', '--platform', 'linux/amd64', '-i']
    if tty:
        cmd.append('-t')
    if sys.platform.startswith('linux'):
        if engine == 'podman':
            cmd += ['--userns=keep-id']
        cmd += ['--user', '%d:%d' % (os.getuid(), os.getgid())]
    for path, access in mounted:
        cmd += ['--volume', '%s:%s:%s%s' % (path, path, access, ',z' if relabel else '')]
    # Ownership may differ on Docker Desktop. Scope trust to mounted worktrees,
    # without changing the user's persistent Git configuration.
    trees = [p for p, _ in mounted if (p / '.git').exists()]
    cmd += ['--env', 'GIT_CONFIG_COUNT=%d' % len(trees)]
    for i, path in enumerate(trees):
        cmd += ['--env', 'GIT_CONFIG_KEY_%d=safe.directory' % i,
                '--env', 'GIT_CONFIG_VALUE_%d=%s' % (i, path)]
    return cmd + ['--workdir', str(root.resolve()), image] + (args or ['bash'])


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--engine', choices=('docker', 'podman'), default='docker')
    ap.add_argument('--image', default='black-decomp')
    ap.add_argument('--relabel', action='store_true')
    ap.add_argument('--dry-run', action='store_true', help='print the launch command without running a container')
    ap.add_argument('command', nargs=argparse.REMAINDER)
    a = ap.parse_args(argv)
    args = a.command[1:] if a.command[:1] == ['--'] else a.command
    cmd = command(ROOT, a.engine, a.image, args, a.relabel, sys.stdin.isatty() and sys.stdout.isatty())
    if a.dry_run:
        print(shlex.join(cmd))
        return 0
    try:
        return subprocess.run(cmd, cwd=ROOT).returncode
    except FileNotFoundError:
        raise SystemExit('container: %s is missing; see docs/setup.md' % a.engine)


if __name__ == '__main__':
    sys.exit(main())
