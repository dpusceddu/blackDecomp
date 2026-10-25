#!/usr/bin/env python3
"""Name the source file that owns a function, and the line where it is: assembly, draft or source.

Usage: where.py func_XXXXXXXX|ADDRESS [...]
Works offline from config/SLUS_213.76/splits.yaml and the sources; no game files and no build are needed. Every function belongs
to exactly one file (docs/units.md): this prints that file with its address range and compile flags, and the line of the
INCLUDE_ASM marker (still assembly), of the marker under `#ifdef NON_MATCHING` (a draft that does not match yet) or of the
definition (recovered; found by its `func_XXXXXXXX` name, its bound name in symbols.txt or `Class::method`).
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import re, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build')]
import ownership
import preflight
import splits as S

MEANING = {'assembly': 'INCLUDE_ASM line: still assembly', 'draft': 'INCLUDE_ASM line under #ifdef NON_MATCHING: a draft above it does not match yet',
           'source': 'definition: recovered, compiled from source'}


def parse_target(text):
    m = re.fullmatch(r'(?:func_|0x)?([0-9A-Fa-f]{1,8})', text.strip())
    if not m:
        raise SystemExit('where.py: expected func_XXXXXXXX or an address, got %r' % text)
    return int(m.group(1), 16)


def describe(addr, splits, symbols):
    split, kind, line, path = ownership.locate(addr, splits, symbols)
    head = 'func_%08X' % addr
    if split is None:
        return '%s: no file owns it (not a function start of this version, or outside every range of splits.yaml)' % head
    try:
        where = path.relative_to(S.ROOT).as_posix()
    except ValueError:
        where = str(path)
    rng = '0x%x-0x%x' % (split.start, split.end) if split.functions is None else 'functions %s' % ', '.join('0x%x' % a for a in split.functions[:4])
    out = ['%s: %s%s' % (head, where, ':%d' % line if line else '')]
    out.append('  %s' % MEANING.get(kind, 'the file lists no marker and no definition by name; if it has no INCLUDE_ASM line it is recovered'))
    out.append('  entry %s, compiler %s %s' % (rng, split.compiler, ' '.join(split.flags)))
    names = symbols.function_names(addr)
    if names:
        out.append('  bound name %s' % names[0])
    return '\n'.join(out)


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    if not argv or argv[0] in ('-h', '--help'):
        print(__doc__.strip())
        return 0 if argv else 2
    try:
        splits = S.load_splits()
        symbols = S.load_symbols()
    except (OSError, ValueError) as e:
        print('where.py: cannot read config/SLUS_213.76/splits.yaml or symbols.txt: %s' % e, file=sys.stderr)
        return 1
    if not splits:
        print('where.py: config/SLUS_213.76/splits.yaml is missing or empty: run it from a checkout of the repository.', file=sys.stderr)
        return 1
    for text in argv:
        print(describe(parse_target(text), splits, symbols))
    return 0


if __name__ == '__main__':
    sys.exit(preflight.guard(main))
