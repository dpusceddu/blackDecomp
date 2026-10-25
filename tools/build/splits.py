#!/usr/bin/env python3
"""Readers and writers for the committed, human-edited build inputs of one version (config/<GAME_ID>/).

  splits.yaml      the split list: one entry per source file that replaces assembly, with the address range it covers and
                   how to compile it. Example:
                     - {src: src/game/unsorted/tu_100518.c, range: [0x100518, 0x103858]}
                     - {src: src/kynapse/behaviors_hide.cpp, range: [0x2d4148, 0x2d4a20], flags: [-O2, -G0, -snas, -fbyte-bool]}
                   Keys: src, range (start inclusive, end exclusive), compiler, flags, assembler (a variant such as sn-min6),
                   sections (false: no -ffunction-sections), note; rare ones: externs, data_ranges,
                   rodata_type_splits, shared_exception_tables, full_tu_context, unlinked_context_helpers.
                   `defaults:` at the top holds compiler, flags and sections for entries that omit them.
  symbols.txt      names and addresses, one per line in splat's symbol_addrs form:  name = 0xADDRESS; // type:func
                   A compiled function may be defined under the name given for its address (a mangled C++ name); names
                   the source uses without defining are bound to their original address. A line marked `alias`
                   (`GameObjectManager_FindByName = 0x129160; // type:func alias`) is a readable name for documentation and
                   tools: it never defines or binds a symbol and cannot change the build.

Ownership: every function belongs to exactly one entry, and the ranges of the entries do not overlap. An entry owns every
function in its range; one that is still assembly is an INCLUDE_ASM line in the entry's file, every other function of the
range must be defined by the file (tools/build/include_asm.py, tools/build/units.py). A file that owns several separate
stretches has several entries, the first one with all the options and the others with only `src`, `range` and `note`. Every
file is compiled once, with one set of options; code that needs other options is a file of its own.
`python3 tools/build/splits.py check` validates the files and the ownership; `python3 tools/where.py ADDRESS` names the owner.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import re
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_SLUG = 'SLUS_213.76'
DEFAULT_COMPILER = 'ee-gcc2.95.3-136'
DEFAULT_FLAGS = ['-O2', '-G0', '-snas']

SPLIT_KEYS = {'src', 'range', 'compiler', 'flags', 'assembler', 'sections', 'note', 'externs', 'data_ranges',
              'rodata_type_splits', 'shared_exception_tables', 'full_tu_context', 'unlinked_context_helpers'}
SYMBOL_LINE = re.compile(r'^\s*([^\s=;/]+)\s*=\s*(0[xX][0-9a-fA-F]+|\d+)\s*;\s*(?://\s*(.*))?$')


def num(value):
    return int(value, 0) if isinstance(value, str) else int(value)


def config_dir(slug=DEFAULT_SLUG):
    return ROOT / 'config' / slug


class Split:
    """One entry of splits.yaml."""

    def __init__(self, entry, defaults):
        unknown = set(entry) - SPLIT_KEYS
        if unknown:
            raise ValueError('split %s: unknown keys %s' % (entry.get('src'), ', '.join(sorted(unknown))))
        self.src = entry['src']
        lo, hi = entry['range']
        self.start, self.end = num(lo), num(hi)
        if not 0 <= self.start < self.end:
            raise ValueError('split %s: empty or reversed range' % self.src)
        self.compiler = entry.get('compiler', defaults.get('compiler', DEFAULT_COMPILER))
        self.flags = list(entry.get('flags', defaults.get('flags', DEFAULT_FLAGS)))
        self.assembler = entry.get('assembler')
        self.sections = bool(entry.get('sections', defaults.get('sections', True)))
        self.note = entry.get('note')
        self.extra = {k: entry[k] for k in SPLIT_KEYS - {'src', 'range', 'compiler', 'flags', 'assembler', 'sections', 'note'}
                      if k in entry}
        self.entry = entry

    @property
    def library(self):
        parts = Path(self.src).parts
        return parts[1] if len(parts) > 2 and parts[0] == 'src' else 'game'

    def compile_flags(self, non_matching=False):
        """Flags handed to the compiler: the listed ones, the assembler variant, -ffunction-sections, -DNON_MATCHING."""
        flags = list(self.flags)
        if self.assembler:
            flags.append('--assembler=' + self.assembler)
        if self.sections or non_matching:          # drafts add functions anywhere in the range
            flags.append('-ffunction-sections')
        if non_matching:
            flags.append('-DNON_MATCHING')
        return flags

    def defines(self, non_matching=False):
        """Preprocessor names the compiler gets from the flags (for evaluating conditionals in the source)."""
        names = {f[2:].split('=')[0] for f in self.flags if f.startswith('-D') and len(f) > 2}
        if non_matching:
            names.add('NON_MATCHING')
        return names


def load_splits(slug=DEFAULT_SLUG, path=None):
    """The entries of config/<slug>/splits.yaml as Split objects, in file order; [] when the version has none."""
    path = Path(path) if path else config_dir(slug) / 'splits.yaml'
    if not path.exists():
        return []
    data = yaml.safe_load(path.read_text()) or {}
    defaults = data.get('defaults') or {}
    return [Split(e, defaults) for e in data.get('splits') or []]


CONTINUATION_KEYS = {'src', 'range', 'note'}


def group_splits(splits):
    """[[Split, ...], ...]: the entries of one source file are one group, compiled once into one unit. The later entries of a
    group are continuations (only `src`, `range`, `note`)."""
    groups, byfile = [], {}
    for s in splits:
        group = byfile.get(s.src)
        if group is None:
            byfile[s.src] = [s]
            groups.append(byfile[s.src])
            continue
        extra = sorted(set(s.entry) - CONTINUATION_KEYS)
        if extra:
            raise ValueError('%s: the entry at 0x%x continues the file\'s first entry and may only have src, range and note, not %s'
                             % (s.src, s.start, ', '.join(extra)))
        group.append(s)
    return groups


def unit_names(splits):
    """Unique object names for the first entries of the groups (group_splits): the file stem, plus the start address when
    a stem occurs several times (two files of one name in different directories)."""
    names, seen = [], {}
    for s in splits:
        seen[Path(s.src).stem] = seen.get(Path(s.src).stem, 0) + 1
    taken = set()
    for s in splits:
        stem = Path(s.src).stem
        name = stem if seen[stem] == 1 else '%s_%06x' % (stem, s.start)
        n = 1
        while name in taken:
            n += 1
            name = '%s_%06x_%d' % (stem, s.start, n)
        taken.add(name)
        names.append(name)
    return names


# ------------------------------------------------------------------------------------------------------- symbols.txt

class Symbols:
    """Names bound to original addresses (config/<slug>/symbols.txt).

    Rows marked `alias` are readable names only: they are kept apart (`aliases`) and never take part in linking, in
    `by_name` or in `by_addr`, so adding one cannot change what is built."""

    def __init__(self, rows=()):
        self.rows = []
        self.aliases = []                    # (name, address, 'func' or 'data'), in file order
        self.by_name = {}
        self.by_addr = {}
        for name, addr, attrs in rows:
            tokens = attrs.split()
            if 'alias' in tokens:
                self.aliases.append((name, addr, 'data' if 'data' in tokens else 'func'))
                continue
            self.rows.append((name, addr, attrs))
            self.by_name.setdefault(name, []).append(addr)
            if 'func' in tokens:
                self.by_addr.setdefault(addr, []).append(name)

    def function_aliases(self):
        """{address: readable name} of the function aliases (the first one where an address has several)."""
        out = {}
        for name, addr, kind in self.aliases:
            if kind == 'func':
                out.setdefault(addr, name)
        return out

    def data_aliases(self):
        """{address: readable name} of the data aliases (hardware registers and the like)."""
        out = {}
        for name, addr, kind in self.aliases:
            if kind == 'data':
                out.setdefault(addr, name)
        return out

    def address(self, name, override=None):
        """The address of `name`, or None; a name bound to several addresses needs `override` (a split's externs)."""
        if override and name in override:
            return num(override[name])
        addrs = self.by_name.get(name)
        if not addrs:
            return None
        return addrs[0] if len(set(addrs)) == 1 else None

    def function_names(self, addr):
        """Names given to the function at `addr`, in file order."""
        return self.by_addr.get(addr, [])


def parse_symbols(text):
    rows = []
    for number, line in enumerate(text.split('\n'), 1):
        s = line.strip()
        if not s or s.startswith(('#', '//')):
            continue
        m = SYMBOL_LINE.match(line)
        if not m:
            raise ValueError('symbols.txt line %d: expected "name = 0xADDRESS; // type:func"' % number)
        attrs = (m.group(3) or '').replace('type:', '')
        rows.append((m.group(1), int(m.group(2), 0), attrs))
    return rows


def load_symbols(slug=DEFAULT_SLUG, path=None):
    path = Path(path) if path else config_dir(slug) / 'symbols.txt'
    return Symbols(parse_symbols(path.read_text()) if path.exists() else [])


SYMBOLS_HEADER = [
    '# Names bound to original addresses (SLUS_213.76), splat symbol_addrs form. Edit by hand; see docs/build.md.',
    '#   name = 0xADDRESS; // type:func|data',
    '# A compiled function is defined under the name listed for its address (a mangled C++ name) or as func_XXXXXXXX;',
    '# a name the source uses without defining is bound to its address.',
    '# A line ending in `alias` (`// type:func alias`) is a readable name for documentation and tools. It never defines or',
    '# binds a symbol, so it cannot change linking; the function stays func_XXXXXXXX or its mangled name.']


def format_symbols(rows):
    """symbols.txt text for (name, address, kind) rows, sorted by address, then bound names before aliases, then name.
    `kind` is the attribute text after `type:` (`func`, `data`, `func alias`, `data alias`)."""
    out = list(SYMBOLS_HEADER)
    for name, addr, kind in sorted(set(rows), key=lambda r: (r[1], 'alias' in r[2].split(), r[0])):
        out.append('%s = 0x%06X; // type:%s' % (name, addr, kind))
    return '\n'.join(out) + '\n'


# ------------------------------------------------------------------------------------------------------ split writer

def flow(value):
    """Compact one-line YAML for a scalar, list or mapping (hex for ints listed in `HEX`)."""
    return yaml.safe_dump(value, default_flow_style=True, width=1 << 30).strip().removesuffix('\n...').strip()


def format_split(entry):
    """One `- {src: ..., range: [0x.., 0x..], ...}` line; ranges and data addresses in hex."""
    parts = ['src: %s' % entry['src'], 'range: [0x%06x, 0x%06x]' % tuple(num(v) for v in entry['range'])]
    for key in ('compiler', 'flags', 'assembler', 'sections'):
        if key in entry:
            parts.append('%s: %s' % (key, flow(entry[key])))
    for key in ('data_ranges', 'rodata_type_splits', 'shared_exception_tables', 'full_tu_context',
                'unlinked_context_helpers', 'externs'):
        if key in entry:
            parts.append('%s: %s' % (key, flow(entry[key])))
    if 'note' in entry:
        parts.append('note: %s' % flow(entry['note']))
    return '- {%s}' % ', '.join(parts)


def format_splits(entries, defaults, header=''):
    lines = [header.rstrip('\n')] if header else []
    lines.append('variant: %s' % DEFAULT_SLUG)
    lines.append('defaults: %s' % flow(defaults))
    lines.append('splits:')
    lines.extend('  ' + format_split(e) for e in entries)
    return '\n'.join(lines) + '\n'


def check_ownership(splits, read=None, table=None, complete=False):
    """Problems (strings) of the ownership rules; empty when every function has exactly one owner.

    Needs no game files without `table`: no two entries may overlap, even by one byte and even when they belong to the same
    file, and every INCLUDE_ASM marker of a file must name an address inside the file's own ranges (with `read(src)` giving
    the text). With `table` (the function starts of the image) a marker must be a function start, and with `complete` every
    function start must be inside some entry."""
    import bisect
    import include_asm
    problems = []
    read = read or (lambda path: (ROOT / path).read_text())
    ranged = sorted((s.start, s.end, s.src) for s in splits)
    reach = None                                  # the entry with the furthest end so far, so that a long entry is not missed
    for cur in ranged:
        if reach is not None and cur[0] < reach[1]:
            problems.append('ranges overlap: %s [0x%x, 0x%x) and %s [0x%x, 0x%x)' % (
                reach[2], reach[0], reach[1], cur[2], cur[0], cur[1]))
        if reach is None or cur[1] > reach[1]:
            reach = cur
    own_ranges = {}
    for s in splits:
        own_ranges.setdefault(s.src, []).append((s.start, s.end))
    start_set = {a for a, _ in table} if table is not None else None
    for src, rs in sorted(own_ranges.items()):
        text = read(src)
        for defines in (set(), {'NON_MATCHING'}):
            seen = set()
            for marker in include_asm.markers(text, defines):
                addr = include_asm.function_address(marker.name)
                if addr is None:
                    problems.append('%s:%d: INCLUDE_ASM names %s, not func_XXXXXXXX' % (src, marker.line, marker.name))
                    continue
                if not any(lo <= addr < hi for lo, hi in rs):
                    problems.append('%s:%d: func_%08X is not in the file\'s range%s; it belongs to another file' % (
                        src, marker.line, addr, 's' if len(rs) > 1 else ''))
                elif start_set is not None and addr not in start_set:
                    problems.append('%s:%d: func_%08X is not a function start' % (src, marker.line, addr))
                if addr in seen:
                    problems.append('%s:%d: func_%08X is marked twice' % (src, marker.line, addr))
                seen.add(addr)
    if complete and table is not None:
        los = [r[0] for r in ranged]
        his = []
        top = 0
        for r in ranged:
            top = max(top, r[1])
            his.append(top)
        for addr, _ in table:
            k = bisect.bisect_right(los, addr) - 1
            if not (k >= 0 and addr < his[k]):
                problems.append('func_%08X belongs to no file' % addr)
    return list(dict.fromkeys(problems))


# ------------------------------------------------------------------------------------- moving a function between files

def split_entries(text):
    """(head lines, [entry dict, ...], tail lines) of a splits.yaml text; the entries are the one-line `- {src: ...}` items."""
    lines = text.split('\n')
    idx = [i for i, line in enumerate(lines) if line.startswith('  - {')]
    entries = [yaml.safe_load('[' + lines[i].strip()[2:] + ']')[0] for i in idx]
    first, last = (idx[0], idx[-1] + 1) if idx else (len(lines), len(lines))
    return lines[:first], entries, lines[last:]


def join_entries(head, entries, tail):
    """The inverse of split_entries; the entries are written ordered by range."""
    ordered = sorted(entries, key=lambda e: (num(e['range'][0]), num(e['range'][1])))
    return '\n'.join(head + ['  ' + format_split(e) for e in ordered] + tail)


def carve_range(entries, addr, end):
    """Remove [addr, end) from the marker-mode entry that contains it so another file can own the function. Returns
    (entries, options) where `options` are the removed first entry's keys when the file has no entry left, else None.
    The first entry of a file (the lowest range) carries all options, the others only src, range and note."""
    out, options = [], None
    hit = next((e for e in entries if num(e['range'][0]) <= addr < num(e['range'][1])), None)
    if hit is None:
        raise KeyError('no marker-mode entry of the split list contains func_%08X' % addr)
    lo, hi = num(hit['range'][0]), num(hit['range'][1])
    same = sorted((e for e in entries if e['src'] == hit['src']), key=lambda e: num(e['range'][0]))
    carrier = same[0] is hit
    pieces = [(a, b) for a, b in ((lo, addr), (end, hi)) if a < b]
    keys = {k: v for k, v in hit.items() if k not in ('src', 'range')}
    for e in entries:
        if e is not hit:
            out.append(e)
            continue
        for n, (a, b) in enumerate(pieces):
            piece = {'src': hit['src'], 'range': [a, b]}
            if carrier and n == 0:
                piece.update(keys)
            elif not carrier and 'note' in keys:
                piece['note'] = keys['note']
            out.append(piece)
    if carrier and not pieces:
        rest = sorted((e for e in out if e['src'] == hit['src']), key=lambda e: num(e['range'][0]))
        if rest:
            rest[0].update(keys)
        else:
            options = keys
    return out, options


def adopt_range(entries, src, addr, end, options=None):
    """Give [addr, end) to `src`: extend an adjacent entry of that file, or add a continuation (or, for a file with no
    entry, a first entry with `options`); entries of the file that touch afterwards become one. Returns the entries."""
    mine = sorted((e for e in entries if e['src'] == src), key=lambda e: num(e['range'][0]))
    for e in mine:
        if num(e['range'][1]) == addr:
            e['range'] = [num(e['range'][0]), end]
            break
        if num(e['range'][0]) == end:
            e['range'] = [addr, num(e['range'][1])]
            break
    else:
        new = {'src': src, 'range': [addr, end]}
        if not mine:
            new.update(options or {})
        elif addr < num(mine[0]['range'][0]):            # the new lowest entry becomes the one that carries the options
            keys = {k: v for k, v in mine[0].items() if k not in ('src', 'range')}
            for k in keys:
                del mine[0][k]
            new.update(keys)
        entries = entries + [new]
    merged = True
    while merged:
        merged = False
        mine = sorted((e for e in entries if e['src'] == src), key=lambda e: num(e['range'][0]))
        for first, second in zip(mine, mine[1:]):
            if num(first['range'][1]) == num(second['range'][0]) and set(second) <= CONTINUATION_KEYS:
                first['range'] = [num(first['range'][0]), num(second['range'][1])]
                entries = [e for e in entries if e is not second]
                merged = True
                break
    return entries


def check(slug=DEFAULT_SLUG):
    """Static checks of the split list; returns a list of problem strings (no game files needed)."""
    problems = []
    try:
        splits = load_splits(slug)
    except (ValueError, KeyError, TypeError) as e:
        return ['splits.yaml: %s' % e]
    try:
        load_symbols(slug)
    except ValueError as e:
        problems.append(str(e))
    try:
        group_splits(splits)
    except ValueError as e:
        problems.append(str(e))
    table = function_starts(slug)
    problems.extend(check_ownership(splits, table=table, complete=table is not None))
    seen = set()
    for s in splits:
        if (s.src, s.start) in seen:
            problems.append('%s: duplicate split at 0x%x' % (s.src, s.start))
        seen.add((s.src, s.start))
        if not (ROOT / s.src).is_file():
            problems.append('%s: source file is missing' % s.src)
    return problems


def function_starts(slug=DEFAULT_SLUG):
    """[(start, end)] of the functions of the image from the last build (build/<GAME_ID>/functions.json), or None."""
    path = ROOT / 'build' / slug / 'functions.json'
    try:
        import json
        data = json.loads(path.read_text())
        return [(a, b) for a, b in data]
    except (OSError, ValueError):
        return None


def main():
    if sys.argv[1:2] != ['check']:
        raise SystemExit(__doc__)
    slug = sys.argv[2] if len(sys.argv) > 2 else DEFAULT_SLUG
    problems = check(slug)
    print('\n'.join(problems) if problems else 'splits.yaml and symbols.txt are consistent')
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
