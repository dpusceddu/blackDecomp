"""Explicit compiler -S / catalog assembler configurations.

The default remains the compiler driver's assembler. Alternate recipes never
rewrite assembly or instruction bytes; selection is part of the unit's flags.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import atexit, hashlib, os, shutil, tempfile, threading
from pathlib import Path
import subprocess

TOOLCHAINS = os.environ.get('BLACK_TOOLCHAINS', '/toolchains')
# SN's Ps2EeAs.exe overflows a buffer when its own path is long: it crashes as soon as it has to print a warning if the
# Windows form of the path (Z:\... with backslashes) exceeds about 80 characters. A toolchain below a deep checkout
# directory is that long, so the Windows tools run from a short copy in the temporary directory.
SHORT_LIMIT = 56
_staged, _lock, _stage_root = {}, threading.Lock(), []


def short_path(path):
    """Return PATH itself when it is short, otherwise the path of a copy of that file or directory under /tmp."""
    path = str(path)
    if len(path) <= SHORT_LIMIT:
        return path
    with _lock:
        if path not in _staged:
            if not _stage_root:
                _stage_root.append(tempfile.mkdtemp(prefix='sn', dir='/tmp' if os.path.isdir('/tmp') else None))
                atexit.register(shutil.rmtree, _stage_root[0], True)
            target = os.path.join(_stage_root[0], 's%d' % len(_staged))
            if os.path.isdir(path):
                os.makedirs(target)
                for name in os.listdir(path):
                    source = os.path.join(path, name)
                    if os.path.isfile(source):
                        shutil.copy2(source, os.path.join(target, name))
            else:
                os.makedirs(target)
                target = os.path.join(target, os.path.basename(path))
                shutil.copy2(path, target)
            _staged[path] = target
        return _staged[path]


CHOICES = ('gas-2.40', 'gas-2.40-fix', 'sn-2.73a', 'sony-2.9', 'sn-min6')
# Only this alternate added matches in the paired whole-inventory study.
FALLBACKS = ('sn-min6', 'sn-2.73a')
MIN6_SHA256 = '4a4bf6f8ae63ee10e4eda6db837a9df4b331b08a71c8f360bb9f0283e84a7813'


def selection(args):
    choices = [x.split('=', 1)[1] for x in args if x.startswith('--assembler=')]
    if len(choices) > 1 or choices and choices[0] not in CHOICES:
        raise ValueError('unknown or repeated --assembler configuration')
    return (choices[0] if choices else None,
            [x for x in args if not x.startswith('--assembler=')])


def command(choice, args, source, output):
    if choice not in CHOICES:
        raise ValueError('unknown assembler configuration')
    small = next((x for x in reversed(args) if x.startswith('-G')), '-G0')
    common = [small, '-mabi=eabi', '-I', 'include']
    if choice.startswith('gas-2.40'):
        return [shutil.which(os.environ.get('BLACK_BINUTILS_PREFIX', 'mipsel-linux-gnu-') + 'as') or TOOLCHAINS + '/binutils/root/usr/bin/mipsel-linux-gnu-as',
                '-EL', '-march=r5900', '-O2',
                '-mfix-r5900' if choice.endswith('-fix') else '-mno-fix-r5900',
                *common, '-o', output, source]
    if choice == 'sn-2.73a':
        return ['wibo', short_path(TOOLCHAINS + '/compilers/ee-gcc2.95.2-273a/lib/gcc-lib/ee/2.95.2/ps2eeas.exe'),
                '-O2', *common, '-o', output, source]
    if choice == 'sn-min6':
        return ['wibo', short_path(TOOLCHAINS + '/assemblers/ps2eeas-1.9.25.758-min6/Ps2EeAs.exe'),
                '-O2', *common, '-o', output, source]
    if choice == 'sony-2.9':
        return [TOOLCHAINS + '/compilers/ee-gcc2.9-991111-01/ee/bin/as',
                '-EL', '-m5900', *common, '-o', output, source]
    raise ValueError('unknown assembler configuration')


def compile_with_assembler(prefix, args, source, output, env, timeout):
    choice, flags = selection(args)
    if choice == 'sn-min6':
        assembler = command(choice, flags, output + '.s', output)
        try:
            valid = hashlib.sha256(Path(assembler[1]).read_bytes()).hexdigest() == MIN6_SHA256
        except OSError:
            valid = False
        if not valid:
            return subprocess.CompletedProcess(assembler, 1, '',
                'sn-min6 assembler missing or hash mismatch; run tools/toolchain.py install')
    if choice is None:
        return subprocess.run(prefix + flags + ['-c', source, '-o', output], env=env,
                              capture_output=True, text=True, timeout=timeout)
    assembly = output + '.s'
    p = subprocess.run(prefix + flags + ['-S', source, '-o', assembly], env=env,
                       capture_output=True, text=True, timeout=timeout)
    if p.returncode:
        return p
    q = subprocess.run(command(choice, flags, assembly, output), env=env,
                       capture_output=True, text=True, timeout=timeout)
    q.stdout = p.stdout + q.stdout
    q.stderr = p.stderr + q.stderr
    return q
