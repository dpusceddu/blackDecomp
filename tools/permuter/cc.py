#!/usr/bin/env python3
"""Compile script for decomp-permuter: run the pinned SN compiler on one self-contained source file.

Usage: cc.py [compiler flags] SOURCE.c -o OUTPUT.o        (permuter_settings.toml makes import.py call it this way)
The compiler runs through tools/build/backend.py: wibo and the pinned toolchain of `python3 tools/toolchain.py install` by
default. Flags are passed to the compiler as given (the TU's flags are in config/SLUS_213.76/splits.yaml; -I and -D flags
only matter to the permuter's import step, which expands the includes). Set CC to use another pinned compiler.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import base64, os, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / _d) for _d in ('', 'build', 'pipeline', 'maint')]
import backend
from elfobj import normalize_object

COMPILER = os.environ.get('CC', 'ee-gcc2.95.3-136')


def main(args):
    if '-o' not in args or args.index('-o') + 1 >= len(args):
        raise SystemExit(__doc__)
    at = args.index('-o')
    output = Path(args[at + 1])
    rest = args[:at] + args[at + 2:]
    sources = [a for a in rest if not a.startswith('-') and Path(a).is_file()]
    if len(sources) != 1:
        raise SystemExit('expected exactly one source file')
    source = Path(sources[0])
    name = 'input' + source.suffix
    flags = [name if a == sources[0] else a for a in rest]
    if '-c' not in flags:
        flags.append('-c')
    reply = backend.compile_standalone(dict(compiler=COMPILER, args=flags + ['-o', 'output.o'],
                                            files={name: base64.b64encode(source.read_bytes()).decode()}))
    sys.stdout.write(reply['stdout'])
    sys.stderr.write(reply['stderr'])
    if reply['returncode'] == 0 and 'output.o' in reply['artifacts']:
        output.write_bytes(normalize_object(base64.b64decode(reply['artifacts']['output.o'])))
        return 0
    return reply['returncode'] or 1


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
