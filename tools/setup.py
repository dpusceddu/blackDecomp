#!/usr/bin/env python3
"""One command from a fresh checkout to a verified build: checks the system, installs what is missing, builds, checks OK.

Usage: python3 tools/setup.py [--no-build]
Steps, each skipped when already done (so it is safe to run again at the start of every session):
  1. Linux x86-64 (natively, in WSL 2 or in the repository's Dockerfile); anything else stops with what to use instead.
  2. System tools: ninja, the little-endian MIPS binutils (or $BLACK_BINUTILS_PREFIX), the 32-bit loader, xz and git;
     a missing one stops with the apt command that installs it.
  3. Python packages of requirements.txt: in the active virtual environment, or in .venv (created when missing).
     In a second worktree of the repository, .venv, the game directories in orig/ and build/toolchain/ are shared with the main worktree
     (symbolic links), so another session costs only its own build.
  4. Your executable at orig/SLUS_213.76/SLUS_213.76 (the build checks its SHA-256).
  5. The pinned toolchain (tools/toolchain.py install --objdiff).
  6. configure.py and ninja, which must end with `OK  SLUS_213.76` (skipped with --no-build).
Then it prints the next step of a work session. Stdlib only, so it runs before anything is installed.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import os, platform, shutil, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SLUG = 'SLUS_213.76'
APT = 'sudo apt install -y git ninja-build python3-venv binutils-mipsel-linux-gnu libc6-i386 xz-utils'
MODULES = ('yaml', 'splat', 'spimdisasm', 'rabbitizer', 'm2c', 'pycparser')


def step(text):
    print('==> ' + text, flush=True)


def stop(text):
    raise SystemExit('setup: ' + text)


def run(*args):
    if subprocess.run(args, cwd=ROOT).returncode:
        stop('`%s` failed (output above)' % ' '.join(str(a) for a in args))


def has_modules(python):
    probe = 'import importlib.util, sys; sys.exit(any(importlib.util.find_spec(m) is None for m in %r))' % (MODULES,)
    return subprocess.run([str(python), '-c', probe], cwd=ROOT).returncode == 0


def main_worktree():
    """The first worktree of this repository when it is not this one (several sessions on one machine), else None."""
    r = subprocess.run(['git', 'worktree', 'list', '--porcelain'], cwd=ROOT, capture_output=True, text=True)
    first = next((Path(l[9:]) for l in r.stdout.splitlines() if l.startswith('worktree ')), None)
    return first if first and first.resolve() != ROOT.resolve() else None


def share(main, name):
    """Link name to the main worktree's copy when this worktree has none."""
    here, there = ROOT / name, main / name
    if not here.exists() and not here.is_symlink() and there.exists():
        here.parent.mkdir(parents=True, exist_ok=True)
        here.symlink_to(there.resolve(), target_is_directory=True)
        print('    %s: shared with %s' % (name, main))


def game_files(main):
    """The untracked entries of the main worktree's orig/ (game files), at the level below the tracked placeholders."""
    r = subprocess.run(['git', 'ls-files', 'orig'], cwd=ROOT, capture_output=True, text=True)
    tracked, names = set(r.stdout.split()), []
    for d in sorted(p for p in (main / 'orig').iterdir() if p.is_dir()):
        rel = 'orig/' + d.name
        if any(t.startswith(rel + '/') for t in tracked):
            names += [rel + '/' + f.name for f in sorted(d.iterdir()) if rel + '/' + f.name not in tracked]
        else:
            names.append(rel)
    return names


def main():
    no_build = '--no-build' in sys.argv[1:]
    step('platform')
    if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64'):
        stop('the toolchain needs Linux x86-64; on Windows use WSL 2, elsewhere the Dockerfile (docs/setup.md)')

    step('system tools')
    prefix = os.environ.get('BLACK_BINUTILS_PREFIX', 'mipsel-linux-gnu-')
    missing = [t for t in ('ninja', 'git', 'xz', prefix + 'ld', prefix + 'objcopy') if not shutil.which(t)]
    if not Path('/lib/ld-linux.so.2').exists():
        missing.append('32-bit loader /lib/ld-linux.so.2 (libc6-i386)')
    if missing:
        stop('missing %s; on Debian or Ubuntu: %s' % (', '.join(missing), APT))

    main = main_worktree()
    if main:
        step('sharing the environment, the game files and the toolchain with the main worktree')
        for name in ['.venv', 'build/toolchain'] + game_files(main):
            share(main, name)

    step('Python packages')
    python = Path(sys.executable)
    if not has_modules(python):
        if sys.prefix == sys.base_prefix:            # not in a virtual environment: use .venv
            python = ROOT / '.venv' / 'bin' / 'python3'
            if not python.exists():
                run(sys.executable, '-m', 'venv', '.venv')
        if not has_modules(python):
            run(python, '-m', 'pip', 'install', '-q', '-r', 'requirements.txt')
    if python != Path(sys.executable):               # continue inside the environment that has the packages
        os.execv(str(python), [str(python), str(Path(__file__).resolve())] + sys.argv[1:])

    step('game executable')
    if not (ROOT / 'orig' / SLUG / SLUG).is_file():
        stop('put the executable of your copy of the game (USA) at orig/%s/%s' % (SLUG, SLUG))

    step('toolchain')
    run(python, 'tools/toolchain.py', 'install', '--objdiff')

    if not no_build:
        step('build')
        run(python, 'configure.py')
        result = subprocess.run(['ninja'], cwd=ROOT, capture_output=True, text=True)
        sys.stdout.write(result.stdout[-2000:])
        if result.returncode or not any(l.startswith('OK  ' + SLUG) for l in result.stdout.splitlines()):
            sys.stderr.write(result.stderr[-2000:])
            stop('the build did not print OK for %s (output above)' % SLUG)

    hint = ' Activate the environment first: . .venv/bin/activate.' if not os.environ.get('VIRTUAL_ENV') and \
        Path(sys.prefix).resolve() == (ROOT / '.venv').resolve() else ''
    print('\nReady.%s Next: python3 tools/next.py --pick, then python3 tools/brief.py <file>.' % hint)
    return 0


if __name__ == '__main__':
    sys.exit(main())
