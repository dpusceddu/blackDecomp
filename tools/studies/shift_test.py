#!/usr/bin/env python3
"""Shiftability test: insert NOPs into one function of a scratch copy, rebuild and check that references moved.

Usage: shift_test.py GAME_ID [--func func_001DD838] [--nops 1] [--work shift] [--analyze-only]
Copies asm/<GAME_ID> and data/<GAME_ID> to the scratch name (default `shift`), inserts the NOPs right after the function's
label, runs the normal post-process/link/pack stages on the copy (never touching the main build) and compares the
result with the reference image in orig/ using a symbol-derived address map. All symbols carry their original
address in their name, so the old->new address map is exact at every label. Reports, for code and data separately,
how many address-bearing words were relocated, how many stayed stale and how many are inconsistent.
"""
import sys as _sys
from pathlib import Path as _Path
_sys.path.insert(0, str(_Path(__file__).resolve().parents[1]))  # the core tools
import argparse, json, re, shutil, struct, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from elfinfo import Elf

PY = sys.executable


def run(*args):
    r = subprocess.run([PY] + [str(a) for a in args], cwd=ROOT, capture_output=True, text=True)
    sys.stdout.write(r.stdout[-1500:])
    if r.returncode:
        sys.stderr.write(r.stderr[-3000:])
        raise SystemExit('step failed: %s' % ' '.join(map(str, args[:2])))


def prepare(slug, work, func, nops):
    for d in ('asm', 'data', 'build'):
        if (ROOT / d / work).exists():
            shutil.rmtree(ROOT / d / work)
    shutil.copytree(ROOT / 'asm' / slug, ROOT / 'asm' / work)
    shutil.copytree(ROOT / 'data' / slug, ROOT / 'data' / work)
    (ROOT / 'build' / work).mkdir(parents=True)
    for f in ('undefined_syms_auto.txt', 'undefined_funcs_auto.txt'):
        shutil.copy(ROOT / 'build' / slug / f, ROOT / 'build' / work / f)
    for src in sorted((ROOT / 'asm' / work / 'data').glob('vu*.s')):   # blob wrappers name the blob path
        src.write_text(src.read_text().replace('data/%s/' % slug, 'data/%s/' % work))
    text = ROOT / 'asm' / work / 'text.s'
    lines = text.read_text().split('\n')
    i = lines.index('glabel ' + func)
    lines[i + 1:i + 1] = ['    nop'] * nops
    text.write_text('\n'.join(lines))
    print('inserted %d nop(s) after glabel %s' % (nops, func))


def build(slug, work):
    boot = json.loads((ROOT / 'config/variants.json').read_text())[slug]['boot']
    b = ROOT / 'build' / work
    run('tools/link_support.py', slug, work)
    run('tools/split_objects.py', slug, work)
    run('tools/make_ld.py', slug, work)
    run('tools/build_objects.py', work)
    run('tools/pack_elf.py', b / 'linked.elf', 'config/%s.layout.json' % boot, 'data/%s/elf' % slug,
        b / (boot + '.elf'))
    return b / (boot + '.elf'), b / 'linked.elf'


class Map:
    """old -> new address from label names that embed the original address."""
    def __init__(self, linked):
        pairs = {}
        for s in Elf(linked.read_bytes()).symbols():
            m = re.match(r'(?:func|D|ehtbl|\.L|\$LEH_|)_?([0-9A-F]{8})$', s['name'].replace('$LEH_', '_').replace('.L', '_'))
            if m and s['shndx'] not in (0, 0xfff1) and s['name'][0] in 'fDe.$':
                pairs.setdefault(int(m.group(1), 16), s['value'])
        self.old = sorted(pairs)
        self.new = [pairs[o] for o in self.old]

    def __call__(self, a):
        import bisect
        i = bisect.bisect_right(self.old, a) - 1
        return a if i < 0 or not 0x100000 <= a < 0x49bfbd else self.new[i] + a - self.old[i]


def sext(v):
    return v - 0x10000 if v & 0x8000 else v


def analyze(slug, ref, shifted, linked, func, nops):
    f = Map(linked)
    O, S = Elf(ref.read_bytes()), Elf(shifted.read_bytes())
    so = {s['name']: s for s in S.sections}
    gp_old = struct.unpack_from('<I', O.content(O.section('.reginfo')), 20)[0]
    gp_new = struct.unpack_from('<I', S.content(S.section('.reginfo')), 20)[0]
    lo_addr, hi_addr = 0x100000, O.section('.bss')['addr'] + O.section('.bss')['size'] + 1
    isaddr = lambda v: lo_addr <= v < hi_addr
    fstart = int(func[-8:], 16)
    print('text size %#x -> %#x (%+d); .data %#x -> %#x; gp %#x -> %#x' % (
        O.section('.text')['size'], S.section('.text')['size'], S.section('.text')['size'] - O.section('.text')['size'],
        O.section('.data')['addr'], S.section('.data')['addr'], gp_old, gp_new))
    moved = sum(1 for a in range(lo_addr, hi_addr, 0x1000) if f(a) != a)
    print('address pages that moved: %d of %d' % (moved, (hi_addr - lo_addr) // 0x1000))

    def pos(a):  # position of original address a in the shifted image
        if fstart <= a < f_end:  # inside the edited function
            return f(fstart) + 4 * nops + (a - fstart)
        return f(a)
    # function end = next function label
    nxt = [o for o in f.old if o > fstart]
    f_end = nxt[0] if nxt else fstart
    res = {}

    def tally(kind, cls, example=None):
        d = res.setdefault(kind, {})
        d.setdefault(cls, [0, None])
        d[cls][0] += 1
        if example and d[cls][1] is None:
            d[cls][1] = example

    def sym_addr(expr):
        """(original address, new address) of `NAME` or `NAME + 0xN` (names embed the original address)."""
        m = re.match(r'(\S+?)(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?$', expr.strip())
        mm = re.search(r'_([0-9A-Fa-f]+)$', m.group(1)) if m else None
        if not mm:
            raise ValueError(expr)
        base = int(mm.group(1), 16)
        off = int(m.group(2), 0) if m.group(2) else 0
        return base + off, f(base) + off
    # ---- code: every instruction whose assembly names a symbol (%hi, %lo, gp-relative) or a jump target
    t_new = S.section('.text')
    cs = S.content(t_new)
    word = lambda a: struct.unpack_from('<I', cs, a - t_new['addr'])[0]
    ins = re.compile(r'^\s+/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\S+)\s+(.*)$')
    sym = re.compile(r'%(hi|lo)\(([^)]*)\)')
    gprel = re.compile(r'\((D_[0-9A-F]+(?:\s*\+\s*(?:0x[0-9A-F]+|\d+))?)\) /\* gp_rel')
    for line in (ROOT / 'asm' / slug / 'text.s').read_text().split('\n'):
        m = ins.match(line)
        if not m:
            continue
        p = int(m.group(1), 16)
        q = pos(p)
        if q + 4 > t_new['addr'] + len(cs):
            tally('code', 'outside', hex(p))
            continue
        got = word(q) & 0xFFFF
        for kind, expr in sym.findall(m.group(3)):
            try:
                a, b = sym_addr(expr)
            except ValueError:
                tally('%%%s(sym)' % kind, 'unparsed', expr)
                continue
            if False:
                pass
            want = ((b + 0x8000) >> 16) & 0xFFFF if kind == 'hi' else b & 0xFFFF
            moved_ = a != b
            tally('%%%s(sym)' % kind, ('relocated' if moved_ else 'unmoved-target') if got == want else 'MISMATCH',
                  '%#x %s -> imm %#x want %#x' % (p, expr, got, want))
        g = gprel.search(m.group(3))
        if g:
            a, b = sym_addr(g.group(1))
            want = (b - gp_new) & 0xFFFF
            tally('gp-relative', ('relocated' if a != b else 'unmoved-target') if got == want else 'MISMATCH',
                  '%#x %s -> imm %#x want %#x' % (p, g.group(1), got, want))
        if m.group(2) in ('jal', 'j'):
            tgt = int(m.group(3).strip().split('_')[-1], 16) if '_' in m.group(3) else None
            if tgt is not None:
                gt = (word(q) & 0x3FFFFFF) << 2
                tally('jal/j', ('relocated' if f(tgt) != tgt else 'unmoved-target') if gt == f(tgt) else 'MISMATCH',
                      '%#x -> %#x want %#x' % (p, gt, f(tgt)))
    # ---- data: `.word SYMBOL` words must follow their symbol; raw numbers in the address range are listed
    dline = re.compile(r'^\s+/\* \w+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+\.word\s+(\S.*)$')
    for name, fn in (('.data', 'data.data.s'), ('.rodata', 'rodata.rodata.s'), ('.sdata', 'sdata.sdata.s'),
                     ('.gcc_except_table', 'gcc_except_table.gcc_except_table.s'), ('.lit4', 'lit4.lit4.s')):
        b0 = S.section(name)
        cs2 = S.content(b0)
        for line in (ROOT / 'asm' / slug / 'data' / fn).read_text().split('\n'):
            m = dline.match(line)
            if not m:
                continue
            p = int(m.group(1), 16)
            q = pos(p) - b0['addr']
            expr = m.group(2).split('/*')[0].strip()
            if not 0 <= q < len(cs2):
                tally(name, 'outside', hex(p))
                continue
            s, = struct.unpack_from('<I', cs2, q)
            if re.match(r'0x[0-9A-Fa-f]+$', expr):
                v = int(expr, 16)
                if isaddr(v):
                    tally(name + ' raw number in address range', 'not-relocated (%s)' % (
                        'aligned' if v % 4 == 0 else 'odd'), '%#x %#x' % (p, v))
                continue
            a, b = sym_addr(expr.replace('.L', 'L_').replace('$LEH_', 'L_'))
            tally(name + ' .word SYMBOL', ('relocated' if a != b else 'unmoved-target') if s == b else 'MISMATCH',
                  '%#x %s -> %#x want %#x' % (p, expr, s, b))
    print('\n%-18s %s' % ('kind', 'results (count, first example)'))
    for kind, d in res.items():
        print('%-18s ' % kind + '; '.join('%s %d%s' % (c, n, (' [%s]' % ex) if c in ('MISMATCH', 'outside') else '')
                                           for c, (n, ex) in sorted(d.items())))
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('slug')
    ap.add_argument('--func', default='func_001DD838')
    ap.add_argument('--nops', type=int, default=1)
    ap.add_argument('--work', default='shift')
    ap.add_argument('--analyze-only', action='store_true')
    a = ap.parse_args()
    boot = json.loads((ROOT / 'config/variants.json').read_text())[a.slug]['boot']
    if not a.analyze_only:
        prepare(a.slug, a.work, a.func, a.nops)
        shifted, linked = build(a.slug, a.work)
    else:
        shifted = ROOT / 'build' / a.work / (boot + '.elf')
        linked = ROOT / 'build' / a.work / 'linked.elf'
    analyze(a.slug, ROOT / 'orig' / a.slug / boot, shifted, linked, a.func, a.nops)


if __name__ == '__main__':
    main()
