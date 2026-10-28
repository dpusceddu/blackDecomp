#!/usr/bin/env python3
"""Prepare the environment, assembly and objdiff metadata for a matching session; optionally verify the full image.

Usage: python3 tools/setup.py [--provision | --build] [--iso PATH]
The user or harness runs --provision once on a native Linux host to install system prerequisites, Python dependencies and
the pinned toolchain. It needs no game files and does not generate assembly or build an image.
Normal agent sessions omit it: they reuse the installed environment and prepare their local metadata.
Steps, each skipped when already done (so it is safe to run again at the start of every session):
  1. Linux x86-64 (natively, in WSL 2 or in the repository's Dockerfile); anything else stops with what to use instead.
  2. System tools: ninja, the little-endian MIPS binutils (or $BLACK_BINUTILS_PREFIX), the 32-bit loader, xz, git and gh;
     a missing one stops with the one-time provisioning command. Ordinary sessions do not install system packages.
     Normal sessions also check Git identity and authenticated GitHub access to the main repository.
  3. Python packages of requirements.txt: in the active virtual environment, or in .venv (created when missing).
     An active virtual environment takes priority. In another worktree, the game directories in orig/ and build/toolchain/
     can be shared with the main worktree (symbolic links); .venv is shared only when no environment is active.
  4. Verify your USA executable at orig/SLUS_213.76/SLUS_213.76, or extract it from --iso PATH or one ISO in orig/.
     --provision skips game input. ISO extraction preserves the image and checks the executable before saving it.
  5. The pinned toolchain (tools/toolchain.py install --objdiff).
  6. configure.py, `ninja objdiff.json` and the TU map prepare metadata and assembly without compiling all objects or linking.
     --provision stops before this step. --build also verifies the full image; normal setup only prepares metadata.
Then it prints the next step of a work session. Stdlib only, so it runs before anything is installed.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import argparse, hashlib, json, os, platform, re, shutil, subprocess, sys, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from preparation_lock import preparation_lock
from github import contribution_problem
from maint.iso import Iso
SLUG = 'SLUS_213.76'
MODULES = ('yaml', 'splat', 'spimdisasm', 'rabbitizer', 'm2c', 'pycparser')
PACKAGES = {
    'apt-get': ['git', 'gh', 'ninja-build', 'python3', 'python3-venv', 'python3-pip', 'python3-dev', 'build-essential',
                'binutils-mipsel-linux-gnu', 'libc6-i386', 'xz-utils', 'cpp', 'ca-certificates'],
    'dnf': ['git', 'gh', 'ninja-build', 'python3', 'python3-pip', 'python3-devel', 'gcc', 'make',
            'binutils-mips64-linux-gnu', 'glibc.i686', 'xz', 'cpp', 'ca-certificates'],
}


def step(text):
    print('==> ' + text, flush=True)


def stop(text):
    raise SystemExit('setup: ' + text)


def run(*args):
    if subprocess.run(args, cwd=ROOT).returncode:
        stop('`%s` failed (output above)' % ' '.join(str(a) for a in args))


def provision_system():
    """Explicit one-time provisioning; ordinary preparation never invokes a package manager."""
    release = platform.freedesktop_os_release()
    family = {release.get('ID', '')} | set(release.get('ID_LIKE', '').split())
    manager = 'apt-get' if family & {'debian', 'ubuntu'} else 'dnf' if 'fedora' in family else None
    if manager is None or not shutil.which(manager):
        stop('automatic system installation supports Debian/Ubuntu and Fedora; install the prerequisites in docs/setup.md')
    privilege = [] if os.geteuid() == 0 else ['sudo']
    if privilege and not shutil.which('sudo'):
        stop('system installation needs root or sudo; have the user or harness provision the host')
    step('one-time native system prerequisites')
    if manager == 'apt-get':
        run(*(privilege + [manager, 'update']))
    run(*(privilege + [manager, 'install', '-y'] + PACKAGES[manager]))


def binutils_prefix():
    """Select the installed native MIPS tools using the same prefix list as toolchain.py."""
    chosen = os.environ.get('BLACK_BINUTILS_PREFIX')
    prefixes = [chosen] if chosen else json.loads((ROOT / 'config/toolchain-local.json').read_text())['binutils_prefixes']
    return next((p for p in prefixes if all(shutil.which(p + t) for t in ('ld', 'objcopy'))), prefixes[0])


def verify_native_linker(prefix):
    """Verify the required little-endian emulation once during host provisioning."""
    result = subprocess.run([prefix + 'ld', '-V'], cwd=ROOT, capture_output=True, text=True)
    if result.returncode or 'elf32ltsmip' not in (result.stdout + result.stderr).split():
        stop('the native MIPS linker must support elf32ltsmip; see docs/setup.md')


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
    """Share dropped-in ISOs and the USA executable from the main worktree."""
    names = ['orig/' + p.name for p in sorted((main / 'orig').glob('*'))
             if p.is_file() and p.suffix.lower() == '.iso']
    executable = 'orig/%s/%s' % (SLUG, SLUG)
    if (main / executable).is_file():
        names.append(executable)
    return names


def prepare(python, build=False):
    """Prepare comparison metadata; full-image compilation and verification are opt-in."""
    step('comparison metadata and assembly')
    with preparation_lock(ROOT):
        run(python, 'configure.py')
        run('ninja', 'objdiff.json')
        run(python, 'tools/build/tus.py', 'map')
    if build:
        step('full-image verification')
        run('ninja')
        # An up-to-date Ninja build need not print OK; check the image explicitly.
        run(python, 'tools/check_elf.py', SLUG, 'build/%s/%s.elf' % (SLUG, SLUG))


def prepare_game(image=None):
    """Validate the USA executable, or import only its verified boot executable from an ISO."""
    expected = json.loads((ROOT / 'config/versions.json').read_text())[SLUG]
    dest = ROOT / 'orig' / SLUG / expected['boot']

    def verify(data):
        if hashlib.sha256(data).hexdigest() != expected['executable_sha256']:
            stop('executable checksum mismatch; provide an unmodified USA retail copy (%s)' % SLUG)

    if image is None and dest.is_file():
        verify(dest.read_bytes())
        return
    if image is None:
        images = sorted(p for p in (ROOT / 'orig').glob('*') if p.is_file() and p.suffix.lower() == '.iso')
        if len(images) > 1:
            stop('multiple ISOs in orig/; choose your USA copy with --iso PATH')
        if not images:
            stop('put your USA game ISO in orig/, pass --iso PATH, or put its executable at orig/%s/%s' % (SLUG, SLUG))
        image = images[0]
    try:
        with Iso(image) as disc:
            cnf = disc.find('SYSTEM.CNF')
            if cnf['dir'] or cnf['size'] > 65536:
                raise ValueError('Invalid SYSTEM.CNF')
            config = disc.read(cnf['lba'], cnf['size'])
            boot = re.search(rb'^\s*BOOT2\s*=\s*cdrom0:[\\/]*([^;\s]+)', config, re.I | re.M)
            if not boot:
                raise ValueError('SYSTEM.CNF has no BOOT2 executable')
            name = boot.group(1).decode('ascii').replace('\\', '/')
            if name.rsplit('/', 1)[-1].upper() != expected['boot']:
                stop('ISO is not USA retail (%s); provide your unmodified USA copy' % SLUG)
            record = disc.find(name)
            if record['dir'] or record['size'] > 32 << 20:
                raise ValueError('Invalid boot executable size')
            data = disc.read(record['lba'], record['size'])
    except (OSError, ValueError) as error:
        stop('cannot import ISO: %s' % error)
    verify(data)
    if dest.exists() or dest.is_symlink():
        if dest.is_file() and dest.read_bytes() == data:
            return
        stop('an executable already exists at orig/%s/%s; move it aside before importing another' % (SLUG, SLUG))
    dest.parent.mkdir(parents=True, exist_ok=True)
    # Publish a complete verified file, without overwriting another session's input or a shared worktree symlink.
    with tempfile.NamedTemporaryFile(dir=dest.parent, prefix='.import-', delete=False) as tmp:
        temporary = Path(tmp.name)
        try:
            tmp.write(data)
            tmp.flush()
            os.link(temporary, dest)
        except FileExistsError:
            stop('another session supplied the executable; rerun setup to verify it')
        finally:
            temporary.unlink(missing_ok=True)
    print('    imported verified %s from ISO; original image preserved' % SLUG)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument('--build', action='store_true', help='also build and verify the full image')
    mode.add_argument('--provision', action='store_true', help='provision the native host once, without game files or image builds')
    ap.add_argument('--iso', type=Path, metavar='PATH', help='import your USA boot executable from a game ISO (otherwise look in orig/)')
    args = ap.parse_args()
    if args.provision and args.iso:
        ap.error('--iso is for session setup; --provision needs no game input')
    step('platform')
    if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64'):
        stop('the toolchain needs a prepared Linux x86-64 shell; have the user or harness provide it (docs/setup.md)')
    (ROOT / '.local').mkdir(exist_ok=True)
    if args.provision:
        provision_system()

    step('system tools')
    prefix = binutils_prefix()
    required = ['ninja', 'git', 'gh', 'xz', 'cpp'] + [prefix + t for t in ('ld', 'as', 'objcopy', 'objdump')]
    missing = [t for t in required if not shutil.which(t)]
    if not Path('/lib/ld-linux.so.2').exists():
        missing.append('32-bit loader /lib/ld-linux.so.2 (libc6-i386)')
    if missing:
        stop('missing %s; have the user or harness run python3 tools/setup.py --provision once (docs/setup.md)' % ', '.join(missing))
    if args.provision:
        verify_native_linker(prefix)
    else:
        step('Git identity and GitHub access')
        problem = contribution_problem(ROOT)
        if problem:
            stop(problem)

    main = main_worktree()
    if main:
        step('sharing the environment, the game files and the toolchain with the main worktree')
        shared = ['build/toolchain'] + game_files(main)
        if sys.prefix == sys.base_prefix:
            shared.insert(0, '.venv')
        for name in shared:
            share(main, name)

    step('Python packages')
    python = Path(sys.executable)
    if sys.prefix == sys.base_prefix:
        python = ROOT / '.venv' / 'bin' / 'python3'
        if not python.exists():
            run(sys.executable, '-m', 'venv', '.venv')
    if args.provision or not has_modules(python):
        run(python, '-m', 'pip', 'install', '-q', '-r', 'requirements.txt')

    if not args.provision:
        step('game executable')
        prepare_game(args.iso)

    step('toolchain')
    run(python, 'tools/toolchain.py', 'install', '--objdiff')

    hint = ' Activate the environment first: . .venv/bin/activate.' if not os.environ.get('VIRTUAL_ENV') and \
        python.parent.parent.resolve() == (ROOT / '.venv').resolve() else ''
    if args.provision:
        print('\nNative environment ready.%s Supply your USA ISO in orig/ (or its executable), authenticate gh, then run python3 tools/setup.py.' % hint)
        return 0

    prepare(python, build=args.build)
    print('\nReady.%s Next: python3 tools/next.py --pick, then python3 tools/brief.py <file>.' % hint)
    return 0


if __name__ == '__main__':
    sys.exit(main())
