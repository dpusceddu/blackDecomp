"""Explicit compiler -S / catalog assembler configurations.

The default remains the compiler driver's assembler. Alternate recipes never
rewrite assembly or instruction bytes; selection is part of the unit's flags.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import atexit, hashlib, os, shutil, tempfile, threading, signal
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
    if len(path) <= SHORT_LIMIT or not os.path.exists(path):
        return path
    with _lock:
        if path not in _staged:
            if not _stage_root:
                _stage_root.append(tempfile.mkdtemp(prefix='sn', dir='/tmp' if os.path.isdir('/tmp') else None))
                atexit.register(shutil.rmtree, _stage_root[0], True)
            target = tempfile.mkdtemp(prefix='s', dir=_stage_root[0])
            if os.path.isdir(path):
                for name in os.listdir(path):
                    source = os.path.join(path, name)
                    if os.path.isfile(source):
                        shutil.copy2(source, os.path.join(target, name))
            else:
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


def command(choice, args, source, output, env=None):
    if choice not in CHOICES:
        raise ValueError('unknown assembler configuration')
    small = next((x for x in reversed(args) if x.startswith('-G')), '-G0')
    common = [small, '-mabi=eabi', '-I', 'include']
    if choice.startswith('gas-2.40'):
        env = os.environ if env is None else env
        return [shutil.which(env.get('BLACK_BINUTILS_PREFIX', 'mipsel-linux-gnu-') + 'as', path=env.get('PATH')) or TOOLCHAINS + '/binutils/root/usr/bin/mipsel-linux-gnu-as',
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


def run_tool(command, env, timeout):
    """Bound the whole SDK process tree, including a stalled assembler child."""
    with subprocess.Popen(command, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                          text=True, start_new_session=True) as process:
        try:
            stdout, stderr = process.communicate(timeout=timeout)
        except subprocess.TimeoutExpired:
            try:
                os.killpg(process.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            stdout, stderr = process.communicate()
            return subprocess.CompletedProcess(command, 124, stdout,
                stderr+'\nToolchain timed out after %s seconds; its process group was stopped.\n' % timeout)
        return subprocess.CompletedProcess(command, process.returncode, stdout, stderr)


def compile_with_assembler(prefix, args, source, output, env, timeout):
    choice, flags = selection(args)
    if choice == 'sn-min6':
        assembler = command(choice, flags, output + '.s', output, env=env)
        try:
            valid = hashlib.sha256(Path(assembler[1]).read_bytes()).hexdigest() == MIN6_SHA256
        except OSError:
            valid = False
        if not valid:
            return subprocess.CompletedProcess(assembler, 1, '',
                'sn-min6 assembler missing or hash mismatch; run tools/toolchain.py install')
    if choice is None:
        return run_tool(prefix + flags + ['-c', source, '-o', output], env, timeout)
    with tempfile.TemporaryDirectory(prefix='black-assembler-') as directory:
        assembly = str(Path(directory)/'input.s')
        p = run_tool(prefix + flags + ['-S', source, '-o', assembly], env, timeout)
        if p.returncode:
            return p
        q = run_tool(command(choice, flags, assembly, output, env=env), env, timeout)
        q.stdout = p.stdout + q.stdout
        q.stderr = p.stderr + q.stderr
        return q
