#!/usr/bin/env python3
"""Edit the translation unit files and the split list: the "register a match" step of the automatic pipeline.

  add_function(...)   put recovered code in the TU file that lists the function as INCLUDE_ASM (declarations first), or give
                      the function a small file of its own when its compiler flags differ or the TU has no file yet
  revert_function(..) put the INCLUDE_ASM line back (a function that did not place identically), delete a file made for it

Everything here is plain text editing of src/, config/<GAME_ID>/splits.yaml and symbols.txt; the build decides whether the
result is byte-identical. Used by tools/autodecomp.py (register, settle); contributors edit the files by hand.
Usage: tu_files.py --help
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import bisect, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import include_asm
import splits as S
import units as U
import layout

ROOT = S.ROOT
ASM_DIR = 'asm/SLUS_213.76/nonmatchings'
SPLIT_LINE = re.compile(r'^\s*- \{src: (\S+), range: \[(0x[0-9a-f]+)')


def marker(addr):
    return include_asm.marker_line('func_%08X' % addr, ASM_DIR)


def insert_declarations(text, decls):
    """Add declaration lines (those not already present) after the file's leading #include lines."""
    lines = text.split('\n')
    new = [d for d in decls if d.strip() and d not in lines]
    if not new:
        return text
    at = 0
    for i, line in enumerate(lines[:60]):
        if line.startswith('#include'):
            at = i + 1
    return '\n'.join(lines[:at] + new + lines[at:])


def insert_split_line(text, line, start):
    """Insert a split-list entry keeping the list ordered by start address."""
    lines = text.split('\n')
    for i, l in enumerate(lines):
        m = SPLIT_LINE.match(l)
        if m and int(m.group(2), 16) > start:
            lines.insert(i, line)
            return '\n'.join(lines)
    at = max((i for i, l in enumerate(lines) if SPLIT_LINE.match(l)), default=len(lines) - 1) + 1
    lines.insert(at, line)
    return '\n'.join(lines)


def remove_split_line(text, src, start):
    lines = text.split('\n')
    keep = [l for l in lines if not ((m := SPLIT_LINE.match(l)) and m.group(1) == src and int(m.group(2), 16) == start)]
    return '\n'.join(keep)


def same_recipe(split, compiler, flags):
    base = lambda fl: [f for f in fl if f != '-ffunction-sections']
    return split.compiler == compiler and base(split.flags) == base(flags) and not split.assembler and split.sections


def find_split(addr, compiler, flags, slug=S.DEFAULT_SLUG):
    """(split, text) of a C file whose range holds the function, whose recipe agrees and which lists it as INCLUDE_ASM."""
    name = 'func_%08X' % addr
    for s in S.load_splits(slug):
        if s.start <= addr < s.end and s.functions is None and s.src.endswith('.c') and same_recipe(s, compiler, flags):
            path = ROOT / s.src
            if path.exists() and any(m.name == name for m in include_asm.markers(path.read_text(), s.defines())):
                return s, path.read_text()
    return None


def new_file(path, lo, hi, table, header=('#include "include_asm.h"', '#include "ps2/prelude.h"')):
    """Text of a fresh TU file for [lo, hi): INCLUDE_ASM for every function."""
    starts = [a for a, _ in table]
    funcs = starts[bisect.bisect_left(starts, lo):bisect.bisect_left(starts, hi)]
    return '\n'.join(header) + '\n\n' + '\n'.join(marker(a) for a in funcs) + '\n'


def unique_path(addr, suffix='.c', taken=()):
    base = layout.source_path(addr, suffix)
    path, n = base, 1
    while (ROOT / path).exists() or path in taken:
        n += 1
        path = base[:-len(suffix)] + '_%d' % n + suffix
    return path


def add_function(addr, code, decls, compiler, flags, symbol=None, single=False, slug=S.DEFAULT_SLUG):
    """Register recovered code for the function at `addr`; returns a record for revert_function."""
    table = U.function_table(slug)
    ends = dict(table)
    found = None if single else find_split(addr, compiler, flags, slug)
    record = dict(addr=addr, code=code, symbol=symbol, created=None)
    split_file = S.config_dir(slug) / 'splits.yaml'
    if found:
        split, text = found
        record['path'] = split.src
        (ROOT / split.src).write_text(insert_declarations(include_asm.replace(text, 'func_%08X' % addr, code.rstrip('\n')), decls))
    else:
        path = unique_path(addr)
        entry = {'src': path, 'range': [addr, ends[addr]]}
        if compiler != S.DEFAULT_COMPILER:
            entry['compiler'] = compiler
        if [f for f in flags if f != '-ffunction-sections'] != S.DEFAULT_FLAGS:
            entry['flags'] = [f for f in flags if f != '-ffunction-sections']
        body = '#include "include_asm.h"\n#include "ps2/prelude.h"\n' + ''.join(d + '\n' for d in decls) + '\n' + code.rstrip('\n') + '\n'
        (ROOT / path).parent.mkdir(parents=True, exist_ok=True)
        (ROOT / path).write_text(body)
        split_file.write_text(insert_split_line(split_file.read_text(), '  ' + S.format_split(entry), addr))
        record.update(path=path, created=entry)
    if symbol and symbol != 'func_%08X' % addr:
        rows = [(n, a, k or 'func') for n, a, k in S.parse_symbols((S.config_dir(slug) / 'symbols.txt').read_text())]
        rows.append((symbol, addr, 'func'))
        (S.config_dir(slug) / 'symbols.txt').write_text(S.format_symbols(rows))
    return record


def revert_function(record, slug=S.DEFAULT_SLUG):
    """Undo add_function: restore the INCLUDE_ASM line, or remove the file made for the function."""
    path = ROOT / record['path']
    if record.get('created'):
        path.unlink(missing_ok=True)
        split_file = S.config_dir(slug) / 'splits.yaml'
        split_file.write_text(remove_split_line(split_file.read_text(), record['path'], record['addr']))
    elif path.exists():
        text = path.read_text()
        code = record['code'].rstrip('\n')
        if code in text:
            path.write_text(text.replace(code, marker(record['addr']), 1))
    if record.get('symbol') and record['symbol'] != 'func_%08X' % record['addr']:
        sym = S.config_dir(slug) / 'symbols.txt'
        rows = [(n, a, k or 'func') for n, a, k in S.parse_symbols(sym.read_text())
                if not (n == record['symbol'] and a == record['addr'])]
        sym.write_text(S.format_symbols(rows))


if __name__ == '__main__':
    print(__doc__.strip())
