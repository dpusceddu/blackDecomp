#!/usr/bin/env python3
"""Local build toolchain: download, verify and unpack the pinned compilers, assemblers and wibo.

Usage:
  toolchain.py install [--root DIR] [--binutils prebuilt] [--objdiff]
                                                            download everything the build needs (idempotent)
  toolchain.py check   [--root DIR]                         report what is present and what is missing
  toolchain.py env     [--root DIR]                         print the environment the build jobs use

The compilers are the decomp.me archives pinned in config/toolchain-compilers.json; the patched short-loop assembler is
reproduced from the original Ps2EeAs.exe with tools/patch_ps2eeas.py; wibo (a small loader for Windows command-line
programs) is pinned in config/toolchain-local.json. Everything is verified by SHA-256 and unpacked into an ignored cache
(`build/toolchain/` by default, or $BLACK_TOOLCHAIN_DIR):

  compilers/<id>/...   one directory per compiler archive
  assemblers/<id>/...  assembler derivatives (patched Ps2EeAs.exe)
  bin/wibo             runs the Windows compilers on Linux x86-64

The linker and binutils (mipsel-linux-gnu-ld, -objcopy) come from the distribution package binutils-mipsel-linux-gnu
(version 2.40 tested) or, with `install --binutils prebuilt`, from the decompals binutils-mips-ps2-decompals release.
Nothing downloaded here is ever committed. The Sony compilers and the EE assembler are 32-bit Linux programs and the SN
compiler is a Windows program, so the build needs Linux x86-64 (natively, in WSL or in the Dockerfile of this repository).
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import argparse, hashlib, json, os, platform, shutil, stat, sys, tarfile, tempfile, urllib.request
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import patch_ps2eeas

ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / 'config'


def settings():
    return json.loads((CONFIG / 'toolchain-local.json').read_text())


def root(override=None):
    """Directory that holds the downloaded toolchain."""
    chosen = override or os.environ.get('BLACK_TOOLCHAIN_DIR')
    return Path(chosen).resolve() if chosen else ROOT / 'build' / 'toolchain'


def sha256_file(path):
    h = hashlib.sha256()
    with open(path, 'rb') as stream:
        for block in iter(lambda: stream.read(1 << 20), b''):
            h.update(block)
    return h.hexdigest()


def download(url, sha256, destination):
    """Fetch URL into DESTINATION (a file), verifying SHA-256 before the file appears under its final name."""
    destination = Path(destination)
    if destination.is_file() and sha256_file(destination) == sha256:
        return False
    destination.parent.mkdir(parents=True, exist_ok=True)
    fd, temp = tempfile.mkstemp(prefix='.download-', dir=destination.parent)
    try:
        with os.fdopen(fd, 'wb') as out, urllib.request.urlopen(url, timeout=120) as response:
            shutil.copyfileobj(response, out)
        got = sha256_file(temp)
        if got != sha256:
            raise SystemExit('SHA-256 mismatch for %s\n  want %s\n  got  %s' % (url, sha256, got))
        os.replace(temp, destination)
    finally:
        if os.path.exists(temp):
            os.unlink(temp)
    return True


def safe_extract(archive, destination):
    """Unpack a tar archive, refusing paths outside DESTINATION and links that point outside it."""
    destination = Path(destination).resolve()
    with tarfile.open(archive) as tar:
        for member in tar.getmembers():
            target = (destination / member.name).resolve()
            if not target.is_relative_to(destination):
                raise SystemExit('unsafe path in %s: %s' % (archive, member.name))
            if member.issym() or member.islnk():
                link = (target.parent / member.linkname).resolve()
                if not link.is_relative_to(destination):
                    raise SystemExit('unsafe link in %s: %s' % (archive, member.name))
            elif not (member.isfile() or member.isdir()):
                raise SystemExit('unsupported member in %s: %s' % (archive, member.name))
        tar.extractall(destination)


def compiler_table():
    return {c['id']: c for c in json.loads((CONFIG / 'toolchain-compilers.json').read_text())['compilers']}


def assembler_table():
    return {a['id']: a for a in json.loads((CONFIG / 'toolchain-assemblers.json').read_text())['assemblers']}


def count_files(directory):
    return sum(1 for p in Path(directory).rglob('*') if p.is_file() or p.is_symlink())


def install_compiler(base, ident):
    entry = compiler_table()[ident]
    destination = base / 'compilers' / ident
    marker = destination / '.verified'
    if marker.is_file() and marker.read_text().strip() == entry['archive_sha256']:
        return False
    cache = base / 'downloads'
    archive = cache / entry['archive']
    download(entry['source'], entry['archive_sha256'], archive)
    shutil.rmtree(destination, ignore_errors=True)
    destination.mkdir(parents=True)
    safe_extract(archive, destination)
    found = count_files(destination)
    if found != entry['files']:
        raise SystemExit('%s: expected %d files, unpacked %d' % (ident, entry['files'], found))
    marker.write_text(entry['archive_sha256'] + '\n')
    return True


def install_assembler(base, ident):
    entry = assembler_table()[ident]
    source = base / 'compilers' / entry['source_compiler'] / 'lib/gcc-lib/ee' / '2.95.3' / entry['source_filename']
    target = base / entry['root'] / entry['executable']
    if target.is_file() and sha256_file(target) == entry['sha256']:
        return False
    if sha256_file(source) != entry['original_sha256']:
        raise SystemExit('%s has an unexpected SHA-256; the pinned archive was not unpacked' % source)
    patch_ps2eeas.write_derivative(source, target)
    if sha256_file(target) != entry['sha256']:
        raise SystemExit('patched assembler hash mismatch')
    return True


def install_wibo(base):
    entry = settings()['wibo']
    target = base / 'bin' / 'wibo'
    changed = download(entry['url'], entry['sha256'], target)
    target.chmod(target.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
    return changed


def install_binutils(base):
    entry = settings()['binutils_prebuilt']
    archive = base / 'downloads' / Path(entry['url']).name
    download(entry['url'], entry['sha256'], archive)
    destination = base / 'binutils'
    marker = destination / '.verified'
    if marker.is_file() and marker.read_text().strip() == entry['sha256']:
        return False
    shutil.rmtree(destination, ignore_errors=True)
    (destination / 'bin').mkdir(parents=True)
    safe_extract(archive, destination / 'bin')
    marker.write_text(entry['sha256'] + '\n')
    return True


def objdiff_asset():
    system = {'Linux': 'linux', 'Darwin': 'macos'}.get(platform.system())
    machine = {'x86_64': 'x86_64', 'AMD64': 'x86_64', 'arm64': 'arm64', 'aarch64': 'aarch64'}.get(platform.machine())
    entry = settings()['objdiff']
    asset = entry['assets'].get('%s-%s' % (system, machine))
    if not asset:
        raise SystemExit('no pinned objdiff-cli for %s/%s; download one from the objdiff releases' % (platform.system(), platform.machine()))
    return entry['url'] + asset['name'], asset['sha256']


def install_objdiff(base):
    url, digest = objdiff_asset()
    target = base / 'bin' / 'objdiff-cli'
    changed = download(url, digest, target)
    target.chmod(target.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
    return changed


def find_binutils(base=None):
    """Return (directory or None, prefix) of the first usable linker: the cache, then the PATH."""
    base = base or root()
    for prefix in settings()['binutils_prefixes']:
        for directory in [str(base / 'binutils' / 'bin')] + os.environ.get('PATH', '').split(os.pathsep):
            if directory and shutil.which(prefix + 'ld', path=directory) and shutil.which(prefix + 'objcopy', path=directory):
                return Path(directory), prefix
    return None, settings()['binutils_prefixes'][0]


def problems(base=None):
    """Everything that is missing for a local build, as readable lines (empty when ready)."""
    base = base or root()
    missing = []
    for ident in settings()['compilers']:
        marker = base / 'compilers' / ident / '.verified'
        if not marker.is_file():
            missing.append('compiler %s is not installed' % ident)
    for ident in settings()['assemblers']:
        entry = assembler_table()[ident]
        target = base / entry['root'] / entry['executable']
        if not target.is_file() or sha256_file(target) != entry['sha256']:
            missing.append('assembler %s is not installed' % ident)
    if not (base / 'bin' / 'wibo').is_file():
        missing.append('wibo is not installed')
    if find_binutils(base)[0] is None:
        missing.append('no MIPS linker found (install binutils-mipsel-linux-gnu or run: toolchain.py install --binutils prebuilt)')
    return missing


def require(base=None):
    """Exit with an actionable message unless the local toolchain is complete."""
    missing = problems(base)
    if missing:
        raise SystemExit('The local toolchain is incomplete:\n  - ' + '\n  - '.join(missing) +
                         '\nRun: python3 tools/toolchain.py install   (see README.md)')


def job_environment(base=None):
    """Variables the build jobs read (see tools/sandbox.py and tools/build_job.py)."""
    base = base or root()
    binutils, prefix = find_binutils(base)
    path = [str(base / 'bin')] + ([str(binutils)] if binutils else [])
    return {'BLACK_TOOLCHAINS': str(base), 'BLACK_BINUTILS_PREFIX': prefix,
            'BLACK_PATH_PREFIX': os.pathsep.join(path)}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('command', choices=['install', 'check', 'env'])
    ap.add_argument('--root', help='toolchain directory (default build/toolchain or $BLACK_TOOLCHAIN_DIR)')
    ap.add_argument('--binutils', choices=['prebuilt'], help='also install the decompals prebuilt binutils')
    ap.add_argument('--objdiff', action='store_true', help='also install the pinned objdiff-cli (for `ninja report`)')
    ap.add_argument('--only-objdiff', action='store_true', help='install nothing but objdiff-cli (no compilers)')
    a = ap.parse_args()
    base = root(a.root)
    if a.command == 'env':
        for key, value in job_environment(base).items():
            print('%s=%s' % (key, value))
        return 0
    if a.command == 'install' and a.only_objdiff:
        print('objdiff-cli %s %s' % (settings()['objdiff']['version'], 'installed' if install_objdiff(base) else 'present'))
        return 0
    if a.command == 'install':
        if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64'):
            print('note: this machine is %s/%s; the downloaded tools only run on Linux x86-64 (use WSL or the Dockerfile)'
                  % (platform.system(), platform.machine()), file=sys.stderr)
        for ident in settings()['compilers']:
            print('%-28s %s' % (ident, 'installed' if install_compiler(base, ident) else 'present'), flush=True)
        for ident in settings()['assemblers']:
            print('%-28s %s' % (ident, 'written' if install_assembler(base, ident) else 'present'), flush=True)
        print('%-28s %s' % ('wibo ' + settings()['wibo']['version'], 'installed' if install_wibo(base) else 'present'), flush=True)
        if a.binutils:
            print('%-28s %s' % ('binutils ' + settings()['binutils_prebuilt']['version'],
                                'installed' if install_binutils(base) else 'present'), flush=True)
        if a.objdiff:
            print('%-28s %s' % ('objdiff-cli ' + settings()['objdiff']['version'],
                                'installed' if install_objdiff(base) else 'present'), flush=True)
    missing = problems(base)
    directory, prefix = find_binutils(base)
    print('toolchain root: %s' % (base.relative_to(ROOT) if base.is_relative_to(ROOT) else base))
    print('linker: %s' % (('%s%sld' % (directory, os.sep + prefix)) if directory else 'not found'))
    for line in missing:
        print('missing: ' + line)
    return 1 if missing else 0


if __name__ == '__main__':
    sys.exit(main())
