#!/usr/bin/env python3
"""EE instructions that m2c cannot read, rewritten before m2c sees them, and the matching clean-up of its C afterwards.

SN GCC 2.95 for the EE has `long` = 64 bits and `long long` = 128 bits, so (verified by compiling, see README):
  lq / sq / por rd, rs, $0     128-bit load, store and register move: a `long long` (here s128/u128) value
  ldl+ldr / sdl+sdr pairs      one 8-byte access at byte alignment: a copy of a `struct { char c[8]; }`, or a member of a
                               packed struct; written here as M2C_UNALIGNED64 (include/auto/prelude.h)
m2c is shown `ld` / `sd` / `daddu` instead and its 64-bit types are turned into the 128-bit type (or the unaligned accessor)
afterwards, but only when the function has no real 64-bit access of its own (`ld` / `sd` off $sp are the frame saves).
Other multimedia and VU0 instructions are left alone (the function then fails in m2c and is reported by instruction).
"""
import re

LINE = re.compile(r'^(\s*/\*.*?\*/\s+)(\w[\w.]*)(\s+)(.*?)\s*$')
MEM = re.compile(r'^\$(\w+),\s*(-?0x[0-9A-Fa-f]+|-?\d+)\(\$(\w+)\)$')


def _num(s):
    return int(s, 0)


def frame_transfers(parsed):
    """Callee-save sq/lq pairs carry ABI state, not 128-bit source expressions."""
    aliases = {'sp': '29', 'fp': '30', 's8': '30', 'ra': '31'}
    aliases.update({'s%d' % n: str(16 + n) for n in range(8)})
    canonical = lambda reg: aliases.get(reg, reg)
    written, saves, restores = set(), {}, []
    stores = {'sw', 'sd', 'sb', 'sh', 'sq', 'sdl', 'sdr', 'swc1', 'sqc2'}
    branches = {'beq', 'bne', 'beqz', 'bnez', 'b', 'jr', 'jal', 'j', 'jalr'}
    for i, (_, op, _, args) in sorted(parsed.items()):
        mem = MEM.match(args)
        if mem and canonical(mem.group(3)) == '29':
            reg = canonical(mem.group(1))
            key = (reg, _num(mem.group(2)))
            if op == 'sq' and reg in {str(n) for n in range(16, 24)} | {'30', '31'} and reg not in written:
                saves.setdefault(key, i)
            elif op == 'lq':
                restores.append((i, key))
        regs = re.findall(r'\$(\w+)', args)
        if regs and op not in stores | branches and not op.startswith('b'):
            written.add(canonical(regs[0]))
    paired = {key for _, key in restores if key in saves}
    return {saves[key] for key in paired} | {i for i, key in restores if key in paired}


def prep(text):
    """(new assembly text, {'q': 128-bit ops seen, 'u': unaligned pairs seen, 'real64': ld/sd away from $sp})."""
    lines = text.split('\n')
    out = list(lines)
    flags = dict(q=False, u=False, real64=False, qargs=[], ph=False)
    parsed = {}
    for i, l in enumerate(lines):
        m = LINE.match(l)
        if m:
            parsed[i] = (m.group(1), m.group(2), m.group(3), m.group(4))
    frame_q = frame_transfers(parsed)
    # m2c drops the delay-slot instruction of a `j func` tail call (an argument set there is lost): put it before the jump
    for i, (pre, op, sp, args) in sorted(parsed.items()):
        if op == 'j' and args.startswith('func_') and i + 1 in parsed and parsed[i + 1][1] not in ('nop', 'j', 'jr', 'jal', 'jalr') \
                and not parsed[i + 1][1].startswith(('b', 'c1')):
            dpre, dop, dsp, dargs = parsed[i + 1]
            out[i] = '%s%s%s%s' % (dpre.replace('*/ ', '*/', 1) if dpre.endswith('*/  ') else dpre, dop, dsp, dargs)
            out[i + 1] = '%s%s%s%s\n%snop' % (pre, op, sp, args, pre)
            parsed[i], parsed[i + 1] = (dpre, dop, dsp, dargs), (pre, op, sp, args)
    written = set()
    argreg = {str(n + 4): n for n in range(8)}
    argreg.update({'a%d' % n: n for n in range(8)})
    argreg.update({'t%d' % n: n + 4 for n in range(4)})
    for i, (pre, op, sp, args) in sorted(parsed.items()):
        regs = re.findall(r'\$(\w+)', args)
        if op == 'por':
            a = [x.strip() for x in args.split(',')]
            src = a[2] if a[1] in ('$0', '$zero') else a[1]
            if len(a) == 3 and src.lstrip('$') in argreg and src.lstrip('$') not in written:
                k = argreg[src.lstrip('$')]
                if k not in flags['qargs']:
                    flags['qargs'].append(k)
        if regs and op not in ('sw', 'sd', 'sb', 'sh', 'sq', 'sdl', 'sdr', 'swc1', 'beq', 'bne', 'beqz', 'bnez'):
            written.add(regs[0])
        if op in ('ld', 'sd'):
            mm = MEM.match(args)
            if mm and mm.group(3) not in ('sp', '29'):
                flags['real64'] = True
        elif placeholder(pre, op, sp, args) and not (i - 1 in parsed and parsed[i - 1][1] in ('jr', 'jal', 'j', 'jalr', 'beq', 'bne', 'beqz', 'bnez')):
            out[i] = '\n'.join(placeholder(pre, op, sp, args))
            flags['ph'] = True
        elif op in ('lq', 'sq'):
            if i not in frame_q:
                flags['q'] = True
            out[i] = '%s%s%s%s' % (pre, 'ld' if op == 'lq' else 'sd', sp, args)
        elif op == 'por':
            a = [x.strip() for x in args.split(',')]
            if len(a) == 3 and a[2] in ('$0', '$zero'):
                out[i] = '%sdaddu%s%s, %s, $0' % (pre, sp, a[0], a[1])
                flags['q'] = True
            elif len(a) == 3 and a[1] in ('$0', '$zero'):
                out[i] = '%sdaddu%s%s, %s, $0' % (pre, sp, a[0], a[2])
                flags['q'] = True
    # unaligned pairs: ldl rt, off+7(rs) with ldr rt, off(rs) (and the same for stores), in either order, adjacent
    idx = sorted(parsed)
    for a, b in zip(idx, idx[1:]):
        (p1, o1, s1, g1), (p2, o2, s2, g2) = parsed[a], parsed[b]
        for left, right, plain in (('ldl', 'ldr', 'ld'), ('sdl', 'sdr', 'sd')):
            pair = {o1, o2} == {left, right}
            if not pair:
                continue
            m1, m2 = MEM.match(g1), MEM.match(g2)
            if not (m1 and m2 and m1.group(1) == m2.group(1) and m1.group(3) == m2.group(3)):
                continue
            lo = min(_num(m1.group(2)), _num(m2.group(2)))
            hi = max(_num(m1.group(2)), _num(m2.group(2)))
            if hi - lo != 7:
                continue
            first, second = (a, b) if o1 == left else (b, a)       # the left half carries off+7, the right half off
            keep = a if a < b else b
            pre = parsed[keep][0]
            out[a] = '%s%s%s$%s, %d($%s)' % (pre, plain, parsed[keep][2], m1.group(1), lo, m1.group(3))
            out[b] = '%snop' % parsed[b][0]
            flags['u'] = True
    return '\n'.join(out), flags


# Instructions m2c has no model for that are plain statements or expressions in the source: shown to m2c as calls of
# placeholder functions, which include/auto/prelude.h defines as inline assembly (SN accepts the instructions as text).
PLACEHOLDERS = ['void __ee_ei(void);', 'void __ee_di(void);', 'f32 __ee_max_s(f32, f32);', 'f32 __ee_min_s(f32, f32);', 'f32 __ee_sqrt_s(f32);'] + \
    ['s32 __ee_mfc0_%d(void);' % n for n in range(32)] + ['void __ee_mtc0_%d(s32);' % n for n in range(32)]


def placeholder(pre, op, sp, args):
    """Replacement lines for one instruction, or None."""
    a = [x.strip() for x in args.split(',')]
    nop = '%snop' % pre
    if op in ('ei', 'di'):
        return ['%sjal%s__ee_%s' % (pre, sp, op), nop]
    if op in ('max.s', 'min.s') and len(a) == 3 and all(x.startswith('$f') for x in a):
        return ['%smov.s%s$f12, %s' % (pre, sp, a[1]), '%smov.s%s$f14, %s' % (pre, sp, a[2]),
                '%sjal%s__ee_%s' % (pre, sp, op.replace('.', '_')), nop, '%smov.s%s%s, $f0' % (pre, sp, a[0])]
    if op == 'mfc0' and len(a) == 2 and a[1].startswith('$') and a[1][1:].isdigit():
        return ['%sjal%s__ee_mfc0_%s' % (pre, sp, a[1][1:]), nop, '%sdaddu%s%s, $2, $0' % (pre, sp, a[0])]
    if op == 'mtc0' and len(a) == 2 and a[1].startswith('$') and a[1][1:].isdigit():
        return ['%sdaddu%s$4, %s, $0' % (pre, sp, a[0]), '%sjal%s__ee_mtc0_%s' % (pre, sp, a[1][1:]), nop]
    return None


def post(src, flags):
    """The C of an m2c run on prep()'s assembly, with the 128-bit or unaligned accesses restored. Returns the new C, or
    None when the function mixes real 64-bit accesses with the rewritten ones (not decided mechanically)."""
    if not (flags['q'] or flags['u']):
        return src
    if flags['real64']:
        return None
    if flags['q'] and flags['u']:
        return None
    if flags['q']:
        src = re.sub(r'\bu64\b', 'u128', re.sub(r'\bs64\b', 's128', src))
        for k in flags['qargs']:
            src = re.sub(r'\b(?:s32|u32|M2C_UNK|s64|void \*) arg%d\b' % k, 's128 arg%d' % k, src)
        return src
    ret, params, body = src.split('\x00')
    body = re.sub(r'M2C_FIELD\((.*?), (?:s64|u64) \*, ([^()]+?)\)', lambda m: 'M2C_UNALIGNED64(%s, %s)' % (m.group(1), m.group(2)), body)
    # variables that point at the 8 bytes: the dereference goes through the packed type
    for name in set(re.findall(r'\b(?:s64|u64) \*(\w+)', params + ' ' + body)):
        body = re.sub(r'(?<![\w)])\*%s\b' % name, '(((M2C_U64 *) %s)->v)' % name, body)
    params = re.sub(r'\b(?:s64|u64) \*(\w+)', r'void *\1', params)
    body = re.sub(r'\b(?:s64|u64) \*(\w+)', r'void *\1', body)
    return '\x00'.join((ret, params, body))
