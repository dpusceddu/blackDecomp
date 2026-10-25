#!/usr/bin/env python3
"""Which source file owns a function, and where in the file it is: the answer of `python3 tools/where.py`.

Every function belongs to exactly one entry of config/SLUS_213.76/splits.yaml (tools/build/splits.py, `check_ownership`), so the
owner is the entry whose range contains the address. Inside the file a function is one of
  assembly   an INCLUDE_ASM marker names it,
  draft      the marker is the `#else` branch of an `#ifdef NON_MATCHING` block that holds a readable version,
  source     no marker: the file defines it (found by its symbol, `func_XXXXXXXX` or the C++ spelling of a mangled name).
Needs only the committed configuration and sources; no game files, no build.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import re
from pathlib import Path

import include_asm
import splits as S


def owner_entry(addr, splits):
    """The split that owns the function at `addr`, or None when no entry claims it."""
    for s in splits:
        if s.start <= addr < s.end:
            return s
    return None


def _identifier(text, pos):
    """(name, new position) of a length-prefixed identifier of a GCC 2.x mangled name, or None."""
    m = re.compile(r'\d+').match(text, pos)
    if not m:
        return None
    n = int(m.group())
    end = m.end() + n
    return (text[m.end():end], end) if end <= len(text) else None


def _class_of(text, pos):
    """The (possibly nested) class name that starts at `pos` of a mangled name, as a list of identifiers."""
    if text.startswith('Q', pos) and pos + 1 < len(text) and text[pos + 1].isdigit():
        count, pos = int(text[pos + 1]), pos + 2
        names = []
        for _ in range(count):
            part = _identifier(text, pos)
            if not part:
                return []
            names.append(part[0])
            pos = part[1]
        return names
    part = _identifier(text, pos)
    return [part[0]] if part else []


def source_names(symbol):
    """Spellings a definition of the bound symbol may have in source: the symbol itself and, for a GCC 2.x mangled C++ name,
    `Class::method` (`Reset__4Game` -> `Game::Reset`, `__4Game` -> `Game::Game`, `_$_4Game` -> `Game::~Game`)."""
    names = [symbol]
    m = re.match(r'^(_\$_|__)(?=\d|Q\d)', symbol)
    if m:
        cls = _class_of(symbol, m.end())
        if cls:
            leaf = cls[-1]
            names.append('%s::%s%s' % (leaf, '~' if m.group(1) == '_$_' else '', leaf))
        return names
    for m in re.finditer(r'__(?=C?(?:\d|Q\d))', symbol):
        pos = m.end() + (1 if symbol.startswith('C', m.end()) else 0)
        cls = _class_of(symbol, pos)
        if cls:
            names.append('%s::%s' % (cls[-1], symbol[:m.start()]))
            break
    return names


def locate_in_text(text, addr, names, defines=()):
    """(kind, line) of the function in a source file: ('assembly'|'draft', marker line) or ('source', definition line), or
    (None, None) when the file mentions it nowhere."""
    wanted = 'func_%08X' % addr
    blocks, stack = [], []
    lines = include_asm.blank_comments(text).split('\n')
    for number, line in enumerate(lines, 1):
        m = include_asm.DIRECTIVE.match(line)
        if m:
            kind, args = m.groups()
            if kind in ('ifdef', 'ifndef', 'if'):
                stack.append([kind, args.strip(), number, None])
            elif kind in ('else', 'elif') and stack:
                stack[-1][3] = number
            elif kind == 'endif' and stack:
                stack.pop()
            continue
        marker = include_asm.MARKER.search(line)
        if marker and marker.group(2) == wanted:
            draft = any(k == 'ifdef' and a == 'NON_MATCHING' and els is not None for k, a, _, els in stack)
            return ('draft' if draft else 'assembly'), number
    spellings = [n for n in dict.fromkeys(names + [wanted])]
    for spelling in spellings:
        pattern = re.compile(r'(?<![\w:~])' + re.escape(spelling) + r'\s*\(')
        for number, line in enumerate(lines, 1):
            if pattern.search(line) and not line.lstrip().startswith('#') and not line.rstrip().endswith(';'):
                return 'source', number
    return None, None


def locate(addr, splits=None, symbols=None, read=None):
    """(split, kind, line, path) for the function at `addr`; the split is None when no entry owns it."""
    splits = S.load_splits() if splits is None else splits
    split = owner_entry(addr, splits)
    if split is None:
        return None, None, None, None
    symbols = S.load_symbols() if symbols is None else symbols
    names = []
    for symbol in symbols.function_names(addr):
        names += source_names(symbol)
    path = S.ROOT / split.src
    text = read(split.src) if read else path.read_text()
    kind, line = locate_in_text(text, addr, names)
    return split, kind, line, path
