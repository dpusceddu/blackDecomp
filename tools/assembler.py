"""Explicit compiler -S / catalog assembler configurations.

The default remains the compiler driver's assembler. Alternate recipes never
rewrite assembly or instruction bytes; selection is part of the unit's flags.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import hashlib, os, shutil
from pathlib import Path
import subprocess

TOOLCHAINS = os.environ.get('BLACK_TOOLCHAINS', '/toolchains')


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
        return ['wibo', TOOLCHAINS + '/compilers/ee-gcc2.95.2-273a/lib/gcc-lib/ee/2.95.2/ps2eeas.exe',
                '-O2', *common, '-o', output, source]
    if choice == 'sn-min6':
        return ['wibo', TOOLCHAINS + '/assemblers/ps2eeas-1.9.25.758-min6/Ps2EeAs.exe',
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
