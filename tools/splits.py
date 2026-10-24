#!/usr/bin/env python3
"""Readers and writers for the committed, human-edited build inputs of one version (config/<GAME_ID>/).

  splits.yaml      the split list: one entry per source file that replaces assembly, with the address range it covers and
                   how to compile it. Example:
                     - {src: src/game/tu_100518.c, range: [0x100518, 0x103858]}
                     - {src: src/kynapse/behaviors_hide.cpp, range: [0x2d4148, 0x2d4a20], flags: [-O2, -G0, -snas, -fbyte-bool]}
                   Keys: src, range (start inclusive, end exclusive), compiler, flags, assembler (a variant such as sn-min6),
                   sections (false: no -ffunction-sections), owner, note; rare ones: externs, data_ranges,
                   rodata_type_splits, shared_exception_tables, full_tu_context, unlinked_context_helpers.
                   `defaults:` at the top holds compiler, flags and sections for entries that omit them.
  symbols.txt      names and addresses, one per line in splat's symbol_addrs form:  name = 0xADDRESS; // type:func
                   A compiled function may be defined under the name given for its address (a mangled C++ name); names
                   the source uses without defining are bound to their original address.
  equivalent.yaml  functions of the `equivalent` evidence tier with their evidence summary.

Which functions of a range are compiled is not listed here: every function of the range whose INCLUDE_ASM marker is
absent from the source file is (tools/include_asm.py, tools/units.py). `python3 tools/splits.py check` validates the files.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import re
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_SLUG = 'SLUS_213.76'
DEFAULT_COMPILER = 'ee-gcc2.95.3-136'
DEFAULT_FLAGS = ['-O2', '-G0', '-snas']

SPLIT_KEYS = {'src', 'range', 'compiler', 'flags', 'assembler', 'sections', 'owner', 'note', 'externs', 'data_ranges',
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
        self.owner = entry.get('owner')
        self.note = entry.get('note')
        self.extra = {k: entry[k] for k in SPLIT_KEYS - {'src', 'range', 'compiler', 'flags', 'assembler', 'sections', 'owner', 'note'}
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
        if self.sections:
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


def unit_names(splits):
    """Unique object names for the splits: the file stem, plus the start address when a file is split several times."""
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
    """Names bound to original addresses (config/<slug>/symbols.txt)."""

    def __init__(self, rows=()):
        self.rows = [(name, addr, attrs) for name, addr, attrs in rows]
        self.by_name = {}
        self.by_addr = {}
        for name, addr, attrs in self.rows:
            self.by_name.setdefault(name, []).append(addr)
            if 'func' in attrs.split():
                self.by_addr.setdefault(addr, []).append(name)

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


def format_symbols(rows):
    """symbols.txt text for (name, address, kind) rows, sorted by address then name."""
    out = ['# Names bound to original addresses (SLUS_213.76), splat symbol_addrs form. Edit by hand; see docs/build.md.',
           '#   name = 0xADDRESS; // type:func|data',
           '# A compiled function is defined under the name listed for its address (a mangled C++ name) or as func_XXXXXXXX;',
           '# a name the source uses without defining is bound to its address.']
    for name, addr, kind in sorted(set(rows), key=lambda r: (r[1], r[0])):
        out.append('%s = 0x%06X; // type:%s' % (name, addr, kind))
    return '\n'.join(out) + '\n'


# ----------------------------------------------------------------------------------------------------- equivalent.yaml

def load_equivalent(slug=DEFAULT_SLUG, path=None):
    """{address: record} of config/<slug>/equivalent.yaml (source, symbol, returns, evidence)."""
    path = Path(path) if path else config_dir(slug) / 'equivalent.yaml'
    if not path.exists():
        return {}
    data = yaml.safe_load(path.read_text()) or {}
    return {num(f['addr']): f for f in data.get('functions') or []}


# ------------------------------------------------------------------------------------------------------ split writer

def flow(value):
    """Compact one-line YAML for a scalar, list or mapping (hex for ints listed in `HEX`)."""
    return yaml.safe_dump(value, default_flow_style=True, width=1 << 30).strip().removesuffix('\n...').strip()


def format_split(entry):
    """One `- {src: ..., range: [0x.., 0x..], ...}` line; ranges and data addresses in hex."""
    parts = ['src: %s' % entry['src'], 'range: [0x%06x, 0x%06x]' % tuple(num(v) for v in entry['range'])]
    for key in ('compiler', 'flags', 'assembler', 'sections', 'owner'):
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
    seen = set()
    for s in splits:
        if (s.src, s.start) in seen:
            problems.append('%s: duplicate split at 0x%x' % (s.src, s.start))
        seen.add((s.src, s.start))
        if not (ROOT / s.src).is_file():
            problems.append('%s: source file is missing' % s.src)
    return problems


def main():
    if sys.argv[1:2] != ['check']:
        raise SystemExit(__doc__)
    slug = sys.argv[2] if len(sys.argv) > 2 else DEFAULT_SLUG
    problems = check(slug)
    print('\n'.join(problems) if problems else 'splits.yaml and symbols.txt are consistent')
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
