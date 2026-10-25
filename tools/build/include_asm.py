#!/usr/bin/env python3
"""Read and edit the INCLUDE_ASM markers of a translation unit source file.

A source file lists every function of its address range in address order. A function that is still assembly is a line

    INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100628);

(include/include_asm.h makes it a harmless declaration for the compiler); a recovered function is ordinary C or C++.
Drafts that do not match yet sit in `#ifdef NON_MATCHING` blocks whose `#else` branch holds the marker:

    #ifdef NON_MATCHING
    int func_001B78D8(BkEffectPoolPS2* pool) { ... }
    #else
    INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B78D8);
    #endif

`markers(text, defines)` evaluates only `#ifdef`, `#ifndef`, `#if 0/1`, `#if [!]defined(X)`, `#else` and `#endif`
(other conditions count as true) against `defines`, so the normal build sees the markers outside NON_MATCHING blocks
and `configure.py --non-matching` sees the ones inside. `replace(text, name, code)` swaps a marker (and the draft
block around it) for code. Usage:  include_asm.py FILE [--non-matching]    prints the markers of a file.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import re
import sys
from collections import namedtuple
from pathlib import Path

Marker = namedtuple('Marker', 'directory name line')

MARKER = re.compile(r'\bINCLUDE_ASM\s*\(\s*"([^"\n]*)"\s*,\s*([A-Za-z_$][\w$]*)\s*\)')
FUNC_NAME = re.compile(r'^func_([0-9A-Fa-f]{8})$')
DIRECTIVE = re.compile(r'^\s*#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)$')
DEFINED = re.compile(r'^\s*(!?)\s*defined\s*(?:\(\s*(\w+)\s*\)|\s+(\w+))\s*$')


def blank_comments(text):
    """The text with comments replaced by spaces (newlines stay, so line numbers survive); string literals are kept."""
    out, i, n = [], 0, len(text)
    while i < n:
        c = text[i]
        if c == '"' or c == "'":
            j = i + 1
            while j < n and text[j] != c and text[j] != '\n':
                j += 2 if text[j] == '\\' else 1
            out.append(text[i:j + 1])
            i = j + 1
        elif text.startswith('/*', i):
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
            out.append(''.join(ch if ch == '\n' else ' ' for ch in text[i:j]))
            i = j
        elif text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
            out.append(' ' * (j - i))
            i = j
        else:
            out.append(c)
            i += 1
    return ''.join(out)


def condition(args, defines):
    """True/False for the conditions this module understands, None for the others."""
    args = args.strip()
    if args in ('0', '1'):
        return args == '1'
    m = DEFINED.match(args)
    if m:
        return ((m.group(2) or m.group(3)) in defines) != bool(m.group(1))
    return None


def active_lines(text, defines=()):
    """(line number, line) of the lines that survive the conditionals; defines is the set of names that are defined."""
    defines = set(defines)
    lines = blank_comments(text).split('\n')
    stack = []                                   # (parent active, branch taken so far, this branch active)
    out = []
    for number, line in enumerate(lines, 1):
        m = DIRECTIVE.match(line)
        active = all(s[2] for s in stack)
        if m:
            kind, args = m.groups()
            if kind in ('ifdef', 'ifndef', 'if'):
                if kind == 'if':
                    value = condition(args, defines)
                    value = True if value is None else value
                else:
                    value = (args.split()[0] if args.split() else '') in defines
                    value = value if kind == 'ifdef' else not value
                stack.append((active, value, value))
            elif kind == 'elif' and stack:
                parent, taken, _ = stack[-1]
                value = condition(args, defines)
                value = True if value is None else value
                stack[-1] = (parent, taken or value, value and not taken)
            elif kind == 'else' and stack:
                parent, taken, _ = stack[-1]
                stack[-1] = (parent, True, not taken)
            elif kind == 'endif' and stack:
                stack.pop()
            continue
        if active:
            out.append((number, line))
    return out


def markers(text, defines=()):
    """The INCLUDE_ASM markers that are active under `defines`, in file order."""
    found = []
    for number, line in active_lines(text, defines):
        for m in MARKER.finditer(line):
            found.append(Marker(m.group(1), m.group(2), number))
    return found


def function_address(name):
    """Original address of a marker name (`func_00100628`), or None for any other name."""
    m = FUNC_NAME.match(name)
    return int(m.group(1), 16) if m else None


def marker_addresses(text, defines=()):
    """Addresses of the active markers; raises ValueError for a marker that is not named func_XXXXXXXX."""
    out = []
    for mk in markers(text, defines):
        address = function_address(mk.name)
        if address is None:
            raise ValueError('INCLUDE_ASM names must be func_XXXXXXXX, not %s (line %d)' % (mk.name, mk.line))
        out.append(address)
    return out


def marker_line(name, directory):
    return 'INCLUDE_ASM("%s", %s);' % (directory, name)


def replace(text, name, code):
    """Replace the INCLUDE_ASM line of function `name` by `code` (C/C++ text, without trailing newline).

    When the marker is the only line of the `#else` branch of an `#ifdef NON_MATCHING` block, the whole block is replaced.
    Raises KeyError when there is no marker for the function."""
    lines = text.split('\n')
    hit = None
    for i, line in enumerate(lines):
        for m in MARKER.finditer(blank_comments(line)):
            if m.group(2) == name:
                hit = i
    if hit is None:
        raise KeyError(name)
    start = end = hit
    # is the marker the whole #else branch of an #ifdef NON_MATCHING block?
    if hit + 1 < len(lines) and lines[hit + 1].strip().startswith('#endif'):
        depth, j = 0, hit - 1
        while j >= 0:
            s = lines[j].strip()
            if s.startswith('#endif'):
                depth += 1
            elif s.startswith(('#if', '#ifdef', '#ifndef')):
                if depth == 0:
                    break
                depth -= 1
            elif s.startswith('#else') and depth == 0 and j == hit - 1:
                k = j - 1
                d2 = 0
                while k >= 0:
                    t = lines[k].strip()
                    if t.startswith('#endif'):
                        d2 += 1
                    elif t.startswith(('#if', '#ifdef', '#ifndef')):
                        if d2 == 0:
                            break
                        d2 -= 1
                    k -= 1
                if k >= 0 and re.match(r'#\s*ifdef\s+NON_MATCHING\b', lines[k].strip()):
                    start, end = k, hit + 1
                break
            j -= 1
    lines[start:end + 1] = code.split('\n')
    return '\n'.join(lines)


def nm_blocks(text):
    """The `#ifdef NON_MATCHING ... #else ... #endif` blocks of a file, as dicts with the 0-based line indexes `start`, `els`,
    `end`, the addresses of the markers in the `#else` branch (`marks`) and the number of function bodies in the draft
    branch (`defs`; a block with none only carries includes and comments)."""
    lines = blank_comments(text).split('\n')
    out, stack = [], []
    for n, line in enumerate(lines):
        m = DIRECTIVE.match(line)
        if not m:
            continue
        kind, args = m.groups()
        if kind in ('ifdef', 'ifndef', 'if'):
            stack.append(dict(kind=kind, args=args.strip(), start=n, els=None))
        elif kind in ('else', 'elif') and stack:
            stack[-1]['els'] = n
        elif kind == 'endif' and stack:
            b = stack.pop()
            if b['kind'] == 'ifdef' and b['args'] == 'NON_MATCHING' and b['els'] is not None:
                b['end'] = n
                b['marks'] = [function_address(m2.group(2)) for k in range(b['els'], n) for m2 in [MARKER.search(lines[k])] if m2]
                b['defs'] = len(re.findall(r'\)\s*(?:const\s*)?\{', '\n'.join(lines[b['start'] + 1:b['els']])))
                out.append(b)
    return out


def remove(text, name):
    """Delete the INCLUDE_ASM line of function `name` (the whole `#ifdef NON_MATCHING` block when the marker is all of its
    `#else` branch, as `replace` does). Raises KeyError when there is no marker."""
    return '\n'.join(l for l in replace(text, name, '\0').split('\n') if l != '\0')


def insert(text, name, directory):
    """Add the INCLUDE_ASM line of function `name` in address order among the markers of the file (before the first marker of
    a higher address, or before the draft block that holds it; at the end when there is none)."""
    address = function_address(name)
    lines = text.split('\n')
    blocks = nm_blocks(text)
    at = None
    for number, line in enumerate(blank_comments(text).split('\n')):
        m = MARKER.search(line)
        other = function_address(m.group(2)) if m else None
        if other is not None and other > address:
            at = number
            block = next((b for b in blocks if b['els'] < number < b['end']), None)
            if block:
                at = block['start']
            break
    new = marker_line(name, directory)
    if at is None:
        while lines and not lines[-1].strip():
            lines.pop()
        lines += [new, '']
    else:
        lines.insert(at, new)
    return '\n'.join(lines)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('-')]
    if len(args) != 1:
        raise SystemExit(__doc__)
    defines = {'NON_MATCHING'} if '--non-matching' in sys.argv else set()
    for mk in markers(Path(args[0]).read_text(), defines):
        print('%d: %s %s' % (mk.line, mk.directory, mk.name))


if __name__ == '__main__':
    main()
