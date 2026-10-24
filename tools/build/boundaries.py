#!/usr/bin/env python3
"""Function boundaries splat cannot see: write build/<GAME_ID>/boundaries.txt (splat's symbol_addrs format), derived from the image.

Usage: boundaries.py GAME_ID [--check]      (--check: report counts, do not write)

Found from the instructions of the boot executable alone:

orphan pairs   After the end of a function (`jr $ra` and its delay slot, plus an optional padding nop) the image holds
               runs of 8-byte pieces `<one non-branch instruction>; nop` at 8-byte alignment, for example
               `addiu $sp, $sp, 0x60; nop` or `sw $0, 0x7C($4); nop`. No call, jump, address built by lui/addiu or data
               pointer reaches them, the instruction has nothing to do with the neighbouring frames (the pairing with the
               previous function's frame size is no better than chance), and a function compiled from C does not emit
               them (functions that match with the pair left outside prove it). They are not code of the function that
               follows: when that function is referenced, the reference points behind the run (for example
               `%lo(func_00103928 + 0x8)`). Splat sees no boundary there when the real function start is unreferenced and
               fuses the run with the function. This tool puts a function start behind every run that begins at a
               function end and is itself unreferenced; the run stays a function of its own (assembly only). A real
               function may begin with such a pair too (`mtc1 $0, $f1; nop`) and then looks like the last orphan of a run.
               Such starts are listed by hand in config/<GAME_ID>/explicit_boundaries.txt, each behind a `// explicit: <reason>` line
               (four on USA retail, none on the others); the scan treats them as known function starts, ends the run there,
               and the generated file contains them too.

ctor list      The linker's __CTOR_LIST__ in .data (a count word, that many pointers into .text, a zero) holds the address of every
               `_GLOBAL__I_*` stub, which is a function start whether or not anything calls it. In USA retail one of the 116 entries,
               0x339c28, lies behind five orphan pieces that splat fused with it; the entry is added as a function start.

Everything else that was suspected is not a boundary error and is not listed here (see docs/build.md, "Function boundaries"):
"falls through" over-splits (the words after the function are its jump table) and functions that end in a computed jump.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, re, struct, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / d) for d in ('', 'build', 'pipeline', 'maint')]
from elfinfo import Elf

ROOT = Path(__file__).resolve().parents[2]
JR_RA = 0x03E00008


def control(x):
    """Branches, jumps, syscall/break, and the COP branches: instructions with a delay slot or a trap."""
    op = x >> 26
    if op in (1, 2, 3, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17):
        return True
    if op == 0 and (x & 0x3F) in (8, 9, 12, 13):
        return True
    return op in (0x10, 0x11, 0x12) and (x >> 21) & 0x1F == 8


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


def reference_targets(elf, text_addr, words):
    """Addresses reached by jal/j, by lui+addiu/ori pairs and by 32-bit data words."""
    out = set()
    last_lui = {}
    for i, x in enumerate(words):
        op = x >> 26
        a = text_addr + 4 * i
        if op in (2, 3):
            out.add(((a & 0xF0000000) | ((x & 0x3FFFFFF) << 2)))
        elif op == 0x0F:                                   # lui
            last_lui[(x >> 16) & 31] = (i, (x & 0xFFFF) << 16)
        elif op in (9, 13):                                # addiu / ori
            rs = (x >> 21) & 31
            if rs in last_lui and i - last_lui[rs][0] <= 12:
                hi = last_lui[rs][1]
                out.add((hi + (sext16(x & 0xFFFF) if op == 9 else (x & 0xFFFF))) & 0xFFFFFFFF)
    for s in elf.sections:
        if s['index'] and s['type'] == 1 and s['flags'] & 2 and not s['flags'] & 4 and s['size'] >= 4:
            c = elf.content(s)
            out.update(struct.unpack_from('<%dI' % (len(c) // 4), c))
    return out


def branch_spans(base, words):
    """(low, high) address of every pc-relative branch: a function boundary cannot lie inside one."""
    out = []
    for i, x in enumerate(words):
        op = x >> 26
        if op in (4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17) or (op == 1 and (x >> 16) & 0x1F in (0, 1, 2, 3, 0x10, 0x11, 0x12, 0x13)) \
                or (op in (0x10, 0x11, 0x12) and (x >> 21) & 0x1F == 8):
            a = base + 4 * i
            t = a + 4 + 4 * sext16(x & 0xFFFF)
            out.append((min(a, t), max(a, t)))
    return out


ENTRY = re.compile(r'^\s*\w+\s*=\s*(0[xX][0-9a-fA-F]+)\s*;')
EXPLICIT = '// explicit:'
HEADER = ['// Function starts splat cannot see, in splat symbol_addrs format. Generated by tools/build/boundaries.py from the image (ninja);',
          '// an entry behind a `// explicit: <reason>` line comes from config/<GAME_ID>/explicit_boundaries.txt, which is edited by hand.']


def parse_boundaries(text):
    """({address: reason} of the explicit entries, [every address]) of a boundaries.txt. A `// explicit:` line applies to the
    entry that follows it."""
    explicit, starts, reason = {}, [], None
    for line in text.split('\n'):
        s = line.strip()
        if s.startswith(EXPLICIT):
            reason = s[len(EXPLICIT):].strip()
            continue
        m = ENTRY.match(s)
        if m:
            starts.append(int(m.group(1), 16))
            if reason:
                explicit[starts[-1]] = reason
        if m or not s.startswith('//'):
            reason = None
    return explicit, starts


def explicit_starts(slug):
    """{address: reason} of the hand-listed function starts in config/<GAME_ID>/explicit_boundaries.txt."""
    path = ROOT / 'config' / slug / 'explicit_boundaries.txt'
    return parse_boundaries(path.read_text())[0] if path.exists() else {}


def format_boundaries(starts, explicit):
    out = list(HEADER)
    for a in sorted(set(starts) | set(explicit)):
        if a in explicit:
            out.append('%s %s' % (EXPLICIT, explicit[a]))
        out.append('func_%08X = 0x%08X; // type:func' % (a, a))
    return '\n'.join(out) + '\n'


def orphan_splits(elf, known=frozenset()):
    """(function starts behind the orphan runs, number of orphan pieces); `known` are function starts that end a run."""
    t = elf.section('.text')
    data = elf.content(t)
    words = struct.unpack('<%dI' % (len(data) // 4), data)
    base = t['addr']
    refs = reference_targets(elf, base, words)
    import bisect
    spans = sorted(branch_spans(base, words))
    los = [lo for lo, _ in spans]
    # prefix maximum of the high ends: a position p is crossed when some span has lo < p <= hi
    pmax, m = [], 0
    for lo, hi in spans:
        m = max(m, hi)
        pmax.append(m)

    def crossed(p):
        i = bisect.bisect_left(los, p) - 1          # spans with lo < p
        return i >= 0 and pmax[i] >= p
    w = lambda a: words[(a - base) // 4]
    splits, orphans = [], 0
    a = base + 16
    end = base + len(data)
    while a < end - 8:
        # a function end: jr $ra with its delay slot just before a, optionally followed by one padding nop
        prev_end = w(a - 8) == JR_RA or (w(a - 4) == 0 and w(a - 12) == JR_RA and w(a - 8) != JR_RA)
        if not (a % 8 == 0 and prev_end and a not in refs and a not in known and not crossed(a)):
            a += 4
            continue
        r = a
        while r + 8 <= end and w(r + 4) == 0 and w(r) != 0 and not control(w(r)):
            r += 8
        # a real function can itself begin with `<instruction>; nop` (an FPU hazard nop, say): when a known start
        # (an explicit entry of explicit_boundaries.txt) lies inside the run, the orphans end there
        inner = [x for x in range(a + 8, r, 8) if x in known]
        if inner:
            r = inner[0]
        if r > a:
            orphans += (r - a) // 8
            if r < end and w(r) != 0 and not crossed(r):
                splits.append(r)
            a = r
        else:
            a += 4
    return splits, orphans


def ctor_list_starts(elf):
    """Pointers of the longest [count][count pointers into .text][0] array in .data."""
    d = elf.section('.data')
    t = elf.section('.text')
    dc = elf.content(d)
    lo, hi = t['addr'], t['addr'] + t['size']
    best = []
    for o in range(0, len(dc) - 12, 4):
        n = struct.unpack_from('<I', dc, o)[0]
        if 20 <= n <= 1000 and o + 8 + 4 * n <= len(dc):
            ptrs = struct.unpack_from('<%dI' % n, dc, o + 4)
            if all(lo <= p < hi and p % 4 == 0 for p in ptrs) and struct.unpack_from('<I', dc, o + 4 + 4 * n)[0] == 0 and n > len(best):
                best = list(ptrs)
    return best


def main():
    args = [x for x in sys.argv[1:] if not x.startswith('--')]
    slug = args[0]
    boot = json.loads((ROOT / 'config/versions.json').read_text())[slug]['boot']
    elf = Elf((ROOT / 'orig' / slug / boot).read_bytes())
    explicit = explicit_starts(slug)
    splits, orphans = orphan_splits(elf, frozenset(explicit))
    print('%s: %d orphan pieces, %d function starts added behind them (%d explicit)' % (slug, orphans, len(splits), len(explicit)))
    ctors = ctor_list_starts(elf)
    extra = sorted(set(ctors) - set(splits))
    print('%s: %d entries in __CTOR_LIST__' % (slug, len(ctors)))
    splits = sorted(set(splits) | set(ctors) | set(explicit))
    if '--check' in sys.argv:
        return
    out = ROOT / 'build' / slug / 'boundaries.txt'
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(format_boundaries(splits, explicit))


if __name__ == '__main__':
    main()
