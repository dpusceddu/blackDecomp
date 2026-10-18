#!/usr/bin/env python3
"""Automatic decompilation pilot: m2c -> clean -> compile variants -> score -> permuter -> register as source units.

  autodecomp.py run [--max-size N] [--min-size N] [--region R] [--addr A ...] [--limit N] [--no-permute]
                    [--permute-seconds S] [--batch N]
        draft every selected assembly function and record the outcome in build/auto.json
  autodecomp.py register [--group N]     turn exact matches into source units (config/units.yaml) and src/auto/
  autodecomp.py report                   outcome table for build/auto.json
  autodecomp.py show ADDR                print the best draft of a function and its diff

Sizes are the function's code size in bytes. Compilation happens only in the build backend (tools/sandbox.py, one call
per batch of candidates); m2c and scoring run on the host because they only read and write text. Scoring compares the
compiled .text with the original instruction words, masking relocated fields, and compares each relocation's target
(symbol address plus addend) with the symbolic operand of the original assembly. The final authority is the identical
link (tools/settle_units.py). Setup and pinned versions: README.md, "Automatic pipeline".
"""
import argparse, base64, collections, difflib, hashlib, io, json, os, re, struct, subprocess, sys, tarfile, time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfinfo import Elf

ROOT = Path(__file__).resolve().parents[1]
SLUG = 'usa-retail'
BUILD = ROOT / 'build' / SLUG
AUTO = ROOT / 'build' / 'auto'
RESULTS = Path(os.environ.get('AUTODECOMP_RESULTS', ROOT / 'build' / 'auto.json'))
M2C = ROOT / '.venv/bin/m2c'
COMPILER = 'ee-gcc2.95.3-136'
BASE_FLAGS = ['-O2', '-G0', '-snas']
INSN = re.compile(r'^\s+/\* ([0-9A-F]+) ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*?)\s*$')
SYM = re.compile(r'^([A-Za-z_$.][\w$.]*)(?:\s*([+-])\s*(0x[0-9A-Fa-f]+))?$')
ADDRNAME = re.compile(r'^(?:func|D|jtbl|ehtbl)_([0-9A-F]{6,8})$')
# mnemonics m2c cannot handle (EE multimedia, 128-bit, VU0 coprocessor 2); used only to label failures
EE_MNEMONICS = re.compile(r'^(p[a-z0-9]+|lq|sq|q[a-z]+|v[a-z0-9.]+|c[ft]c2|mf(sa|hi1|lo1)|mt(sa|sah|hi1|lo1)|madd1|mult1|div1|divu1|'
                          r'multu1|maddu1|msub1|ei|di|syscall|sync.*|cache|tlb.*|eret|mfc0|mtc0|mfc2|mtc2|bc2.*|lqc2|sqc2|c1|cvt.*|adda.*|suba.*|madda.*)$')


# ---------------------------------------------------------------------------------------------------------- inventory
def parse_operand(expr):
    m = SYM.match(expr.strip())
    if not m:
        return None
    name, sign, off = m.groups()
    add = int(off, 16) * (-1 if sign == '-' else 1) if off else 0
    am = ADDRNAME.match(name)
    return (int(am.group(1), 16) if am else name), add, name


def parse_function(path):
    """Instructions of a split function file up to its endlabel: words, symbolic operands and notes."""
    words, rel, mnem = [], {}, []
    text = path.read_text().split('\n')
    strings, label = {}, None
    for line in text:             # strings the function owns (its migrated .rodata): D_XXXXXXXX -> C literal
        if line.startswith('dlabel '):
            label = line.split()[1]
        elif line.startswith('enddlabel'):
            label = None
        elif label:
            m = re.search(r'\.asciz "(.*)"\s*$', line)
            if m and label not in strings:
                strings[label] = m.group(1)
    for line in text:
        if line.startswith('endlabel'):
            break
        m = INSN.match(line)
        if not m:
            continue
        w = int.from_bytes(bytes.fromhex(m.group(3)), 'little')
        i = len(words)
        words.append(w)
        op, args = m.group(4), m.group(5)
        mnem.append(op)
        g = re.search(r'gp_rel: \(([^)]*)\)', args)
        if g:
            t = parse_operand(g.group(1))
            if t:
                rel[i] = ('gprel',) + t
            continue
        if op in ('jal', 'j'):
            t = parse_operand(args)
            if t:
                rel[i] = ('jal',) + t
            continue
        h = re.search(r'%(hi|lo)\(([^)]*)\)', args)
        if h:
            t = parse_operand(h.group(2))
            if t:
                rel[i] = (h.group(1),) + t
    return words, rel, mnem, strings


def load_inventory():
    """Every function of the image: address, name, true code size, words, relocations. Cached in build/auto/."""
    AUTO.mkdir(parents=True, exist_ok=True)
    cache = AUTO / 'inventory.json'
    stamp = (BUILD / 'placement.json').stat().st_mtime
    if cache.exists():
        d = json.loads(cache.read_text())
        if d['stamp'] == stamp and d.get('version') == 3:
            return d['functions']
    sys.path.insert(0, str(ROOT / 'tools'))
    from progress import regions
    placement = json.loads((BUILD / 'placement.json').read_text())['functions']
    reg, _ = regions([f['addr'] for f in placement])
    out = []
    for f, r in zip(placement, reg):
        p = BUILD / 's/text' / (f['name'] + '.s')
        words, rel, mnem, strings = parse_function(p)
        out.append(dict(addr=f['addr'], name=f['name'], span=f['end'] - f['addr'], size=4 * len(words), words=words,
                        rel={str(k): list(v) for k, v in rel.items()}, mnem=mnem, region=r, owned=sorted(f['owned']), strings=strings,
                        lit4=(BUILD / 's/text' / (f['name'] + '.lit4.s')).exists()))
    cache.write_text(json.dumps(dict(stamp=stamp, version=3, functions=out)))
    return out


def source_functions():
    from units import load_units
    return {f['addr'] for u in load_units(variant=SLUG) for f in u['functions'] if f.get('status') == 'source'}


# ---------------------------------------------------------------------------------------------------------- context
CTYPES = {'int': 's32', 'uint': 'u32', 'void': 'void', 'float': 'f32', 'double': 'f64', 'bool': 'u8', 'char': 's8',
          'uchar': 'u8', 'short': 's16', 'ushort': 'u16', 'long': 's32', 'ulong': 'u32', 'longlong': 's64',
          'ulonglong': 'u64', 'undefined': 'u8', 'undefined1': 'u8', 'undefined2': 'u16', 'undefined4': 'u32',
          'undefined8': 's64', 'byte': 'u8', 'word': 'u16', 'dword': 'u32', 'qword': 'u64'}


def ctype(t):
    t = t.strip().replace('const ', '')
    if '*' in t:
        return 'void *'
    return CTYPES.get(t)


HEADER = ROOT / 'include/types_ghidra.h'


def header_functions():
    """Names of the functions include/types_ghidra.h declares (from the Ghidra signatures)."""
    if not HEADER.exists():
        return set()
    return set(re.findall(r'^extern [^(]*?\b(func_[0-9A-F]{8})\(', HEADER.read_text(), re.M))


WIDE_PRODUCERS = {'lq', 'por', 'qmfc2.ni', 'qmfc2.i'}


def wide_info(f):
    """(return value, [indices of 128-bit arguments]) of a function. The return value is True when the value in $v0 at a
    return comes from lq/por/MMI/qmfc2, False when it does not, or the address of the callee whose result is returned
    unchanged. An argument register is 128-bit when its first use is a 128-bit source (por, sq, MMI)."""
    import rabbitizer
    cat = rabbitizer.InstrCategory.R5900
    ins = [rabbitizer.Instruction(w, f['addr'] + 4 * i, cat) for i, w in enumerate(f['words'])]
    name = lambda x: x.getOpcodeName()
    wide_op = lambda x: name(x) in WIDE_PRODUCERS or (name(x).startswith('p') and name(x) != 'pref')

    def writes_v0(x):
        if x.isBranch() or name(x) in ('sd', 'sq', 'sw', 'sb', 'sh', 'swc1'):
            return False
        return (x.modifiesRd() and int(x.rd.value) == 2) or (x.modifiesRt() and int(x.rt.value) == 2)
    ret = False
    last = None
    for i, x in enumerate(ins):
        if x.isFunctionCall():
            rel = f['rel'].get(str(i))
            last = ('call', rel[1] if rel and rel[0] == 'jal' and isinstance(rel[1], int) else None)
        elif writes_v0(x):
            last = x
        if x.isJrRa():
            lw = last
            d = ins[i + 1] if i + 1 < len(ins) else None
            if d is not None and writes_v0(d):
                lw = d
            if isinstance(lw, tuple):
                if lw[1] is not None and ret is False:
                    ret = lw[1]
            elif lw is not None and wide_op(lw):
                ret = True
    args = []
    written = set()
    for x in ins:
        reads = set()
        if x.readsRs():
            reads.add(int(x.rs.value))
        if x.readsRt():
            reads.add(int(x.rt.value))
        for k in range(4):
            r = 4 + k
            if r in reads and r not in written:
                if (name(x) in ('sq', 'por') or (name(x).startswith('p') and name(x) != 'pref')) and k not in args:
                    args.append(k)
                written.add(r)             # the first use decides
        for reg in (int(x.rd.value) if x.modifiesRd() else None, int(x.rt.value) if x.modifiesRt() else None):
            if reg is not None:
                written.add(reg)
    return ret, sorted(args)


def wide_prototypes(inv, known):
    """Context prototypes of functions that return or take `long long` values (128 bits in SN GCC), as s64 for m2c;
    tools/ee_prep.py turns s64 into the 128-bit type afterwards."""
    arity = compute_arities(inv)
    out = []
    info = {f['addr']: wide_info(f) for f in inv}
    for _ in range(4):                          # a result returned unchanged from a callee takes the callee's width
        for a, (ret, args) in list(info.items()):
            if isinstance(ret, int) and not isinstance(ret, bool):
                callee = info.get(ret)
                info[a] = (callee[0] if callee and not isinstance(callee[0], int) or (callee and isinstance(callee[0], bool)) else False, args)
    for f in inv:
        if f['name'] in known or f['size'] > 600:
            continue
        ret, args = info[f['addr']]
        ret = ret is True
        if not ret and not args:
            continue
        n = max(arity.get(f['addr'], 0), (max(args) + 1) if args else 0)
        out.append('%s %s(%s);' % ('s64' if ret else 's32', f['name'], ', '.join('s64' if k in args else 's32' for k in range(n)) or 'void'))
    return out


def write_context():
    """C context for m2c: the integer typedefs plus include/types_ghidra.h (Ghidra's structures and the signatures of the
    named functions, under the image's func_XXXXXXXX names). Run tools/ghidra_types.py first."""
    out = ['typedef signed char s8; typedef unsigned char u8; typedef short s16; typedef unsigned short u16;',
           'typedef int s32; typedef unsigned int u32; typedef long s64; typedef unsigned long u64;',
           'typedef float f32; typedef double f64;']
    n = 0
    if HEADER.exists():
        for line in HEADER.read_text().split('\n'):
            if line.startswith('#') or line.startswith('typedef char assert_') or line.startswith('/*') or line.startswith(' *'):
                continue
            out.append(line)
            n += line.startswith('extern ')
    known = set(re.findall(r'\b(func_[0-9A-F]{8})\(', '\n'.join(out)))
    wide = wide_prototypes(load_inventory(), known)
    out += wide
    import ee_prep
    out += ee_prep.PLACEHOLDERS
    (AUTO / 'ctx.c').write_text('\n'.join(out) + '\n')
    return n + len(wide)


# ---------------------------------------------------------------------------------------------------------- arity
def _gpr_effects(ins):
    """(registers read, registers written) of one instruction, general-purpose only."""
    w = ins.getRaw()
    rs, rt, rd = w >> 21 & 31, w >> 16 & 31, w >> 11 & 31
    reads, writes = set(), set()
    try:
        if ins.readsRs() or ins.doesLoad() or ins.doesStore():
            reads.add(rs)
        if ins.readsRt():
            reads.add(rt)
        if ins.readsRd():
            reads.add(rd)
        if ins.modifiesRs():
            writes.add(rs)
        if ins.modifiesRt():
            writes.add(rt)
        if ins.modifiesRd():
            writes.add(rd)
    except Exception:
        pass
    return reads, writes


def analyze_arity(f):
    """(registers read before written among $a0..$t3, [(callee address or None, argument registers set for the call)]).
    Straight-line approximation: a call's setup window is the code since the last branch target, branch or call."""
    import rabbitizer
    cat = rabbitizer.InstrCategory.R5900
    ins = [rabbitizer.Instruction(w, f['addr'] + 4 * i, cat) for i, w in enumerate(f['words'])]
    targets = set()
    for i, x in enumerate(ins):
        if x.isBranch() and not x.isJumptableJump():
            targets.add(i + 1 + (x.getBranchOffsetGeneric() >> 2))
    used, defined, window, sites = set(), set(), set(), []
    cut_after = -1
    for i, x in enumerate(ins):
        if i in targets:
            window = set()
        reads, writes = _gpr_effects(x)
        used |= {r for r in reads if 4 <= r <= 11 and r not in defined}
        if x.isFunctionCall():
            delay = _gpr_effects(ins[i + 1])[1] if i + 1 < len(ins) else set()
            rel = f['rel'].get(str(i))
            callee = rel[1] if rel and rel[0] == 'jal' and isinstance(rel[1], int) and not rel[2] else None
            sites.append((callee, sorted(r for r in window | delay if 4 <= r <= 11)))
            window = set()
            cut_after = i + 1
        else:
            window |= {r for r in writes if 4 <= r <= 11}
        defined |= {r for r in writes if 4 <= r <= 11}
        if x.isFunctionCall():
            defined |= set(range(4, 12))        # whatever the callee leaves in them is not an incoming argument
        if (x.isBranch() or x.isJump()) and not x.isFunctionCall():
            cut_after = i + 1
        if i == cut_after:
            window = set()
    return sorted(used), sites


def compute_arities(inv):
    """Argument count per function from its own reads and from every call site (max); cached in build/auto/arity.json."""
    cache = AUTO / 'arity.json'
    stamp = (BUILD / 'placement.json').stat().st_mtime
    if cache.exists():
        d = json.loads(cache.read_text())
        if d['stamp'] == stamp and d.get('version') == 3:
            return {int(k): v for k, v in d['arity'].items()}
    own, seen = {}, collections.defaultdict(collections.Counter)
    for f in inv:
        used, sites = analyze_arity(f)
        if used:
            own[f['addr']] = max(used) - 3
        for callee, regs in sites:
            if callee is not None and regs:
                seen[callee][max(regs) - 3] += 1
    arity = dict(own)
    for callee, c in seen.items():
        mode = max(c.items(), key=lambda t: (t[1], t[0]))[0]      # the usual count; one odd caller does not decide
        arity[callee] = max(own.get(callee, 0), mode)
    cache.write_text(json.dumps(dict(stamp=stamp, version=3, arity={str(k): v for k, v in arity.items()})))
    return arity


def write_context_arity(inv):
    """ctx2.c: ctx.c plus an int-typed prototype with the inferred argument count for every other function."""
    arity = compute_arities(inv)
    base = (AUTO / 'ctx.c').read_text()
    have = set(re.findall(r'\b(func_[0-9A-F]{8})\(', base))
    for name, t in (('ctx2.c', 's32'), ('ctx3.c', 'void *')):
        out = [base.rstrip('\n')]
        for f in inv:
            if f['name'] in have:
                continue
            n = arity.get(f['addr'], 0)
            out.append('%s %s(%s);' % (t, f['name'], ', '.join([t] * n) if n else 'void'))
        (AUTO / name).write_text('\n'.join(out) + '\n')


# ---------------------------------------------------------------------------------------------------------- m2c
def run_m2c(fns, options=(), ctx='ctx.c'):
    """Decompile `fns` in one m2c process. Returns {name: dict(c=..., sig=..., decls={}, error=...)}."""
    import ee_prep
    paths, flags = [], {}
    prep_dir = AUTO / 'prep'
    prep_dir.mkdir(exist_ok=True)
    for f in fns:
        text, flags[f['name']] = ee_prep.prep((BUILD / 's/text' / (f['name'] + '.s')).read_text())
        (prep_dir / (f['name'] + '.s')).write_text(text)
        paths.append(str(prep_dir / (f['name'] + '.s')))
        if f['lit4']:
            paths.append(str(BUILD / 's/text' / (f['name'] + '.lit4.s')))
    cmd = [sys.executable, str(ROOT / 'tools/m2c_wrap.py'), '-t', 'mipsee-gcc-c', '--valid-syntax', '--context', str(AUTO / ctx), '--no-cache'] + list(options) + paths
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT, timeout=3600)
    out = split_m2c(r.stdout + ('\n/* STDERR %s */' % r.stderr if r.returncode else ''), fns)
    for name, fl in flags.items():
        out.setdefault(name, {})['ee'] = fl
    return out


FUNC_START = re.compile(r'^(?!\s)([^\n(;]*?)\b(func_[0-9A-F]{8})\((.*)\) \{$')
FAIL = re.compile(r'/\*\nDecompilation failure in function (\w+):\n(.*?)\n\*/', re.S)


def split_m2c(text, fns):
    res = {f['name']: dict(error=None) for f in fns}
    for m in FAIL.finditer(text):
        res.setdefault(m.group(1), {})['error'] = 'm2c failure: ' + m.group(2).strip().split('\n')[0]
    lines = text.split('\n')
    decls = {}
    i = 0
    while i < len(lines):
        ln = lines[i]
        m = FUNC_START.match(ln)
        if m:
            j = i
            while j < len(lines) and lines[j] != '}':
                j += 1
            name = m.group(2)
            res.setdefault(name, {})
            res[name].update(ret=m.group(1).strip(), params=m.group(3).strip(), body='\n'.join(lines[i + 1:j]))
            i = j
        else:
            d = re.match(r'^(?:extern )?(.*?)\b([A-Za-z_]\w*)\((.*)\);\s*/\* (?:extern|static) \*/$', ln)
            if d:
                decls[d.group(2)] = ('func', d.group(1).strip(), d.group(3).strip())
            else:
                g = re.match(r'^extern (.+?)\b(\w+)((?:\[[^\]]*\])*);$', ln)
                if g:
                    decls[g.group(2)] = ('data', g.group(1).strip(), g.group(3))
        i += 1
    for name, r in res.items():
        r['decls'] = decls
    return res


IDENT = re.compile(r'\b[A-Za-z_]\w*\b')


def tidy_type(t):
    t = re.sub(r'\bM2C_UNK\b(?!\d)', 'M2C_UNK', t)
    return t


def idiom_source(f):
    """Source for functions m2c cannot decompile but that are only a few special instructions: kernel-call and
    interrupt-control stubs (`li $v1, N; syscall; jr $ra`, `ei`, `di`, `sync`). One template, emitted as inline asm.
    Returns (source, idiom name) or None."""
    w = f['words']
    if len(w) < 3 or w[-2] != 0x03E00008 or w[-1] != 0:
        return None
    lines = []
    for x in w[:-2]:
        if x >> 16 & 0xFFE0 == 0x2400 and x >> 21 & 0x1F == 0:       # addiu rt, $0, imm
            lines.append('li $%d, %d' % (x >> 16 & 0x1F, (x & 0xFFFF) - (0x10000 if x & 0x8000 else 0)))
        elif x & 0xFC00003F == 0xC:
            lines.append('syscall' if not (x >> 6 & 0xFFFFF) else 'syscall %d' % (x >> 6 & 0xFFFFF))
        elif x == 0x42000038:
            lines.append('ei')
        elif x == 0x42000039:
            lines.append('di')
        elif x == 0xF:
            lines.append('sync')
        elif x == 0x40F:
            lines.append('sync.p')
        else:
            return None
    kind = 'syscall-stub' if any(l.startswith('syscall') for l in lines) else 'cop0-stub'
    body = '\\n\\t'.join(lines)
    return '#include "auto/prelude.h"\n\nvoid %s(void) {\n    __asm__ volatile("%s");\n}\n' % (f['name'], body), kind


def stack_rewrite(body, size):
    """The frame objects of an m2c body as one local buffer `sp`: bare `sp` is the buffer's address, `&spN` the address at
    byte offset N (hex) and `spN` the value there; the type comes from m2c's own declaration `T spN;` (s32 otherwise)."""
    types = {}
    kept = []
    for line in body.split('\n'):
        m = re.match(r'^\s+([A-Za-z_][\w ]*?\s*\**)\s*sp([0-9A-Fa-f]+);\s*$', line)
        if m and m.group(1).split()[0] not in ('return', 'goto', 'else', 'case'):
            types[m.group(2).upper()] = m.group(1).strip()
        else:
            kept.append(line)
    body = '\n'.join(kept)

    def value(m):
        n = m.group(2).upper()
        n = n if n != '' else '0'
        t = types.get(n, 's32')
        off = int(n, 16)
        return '(sp + %d)' % off if m.group(1) else '*(%s *)(sp + %d)' % (t, off)
    body = re.sub(r'(&?)\bsp([0-9A-Fa-f]+)\b', value, body)
    # a quadword copied out of the frame: m2c converts the narrower variable, the source reads the 16 bytes
    body = re.sub(r'\((s|u)128\) \*\(\w+ \*\)\(sp \+ (\d+)\)', lambda m: '*(%s128 *)(sp + %s)' % (m.group(1), m.group(2)), body)
    return '    u8 sp[%d] __attribute__((aligned(16)));\n' % size + body


def clean_function(name, r, sigs, strings=None, stack=None):
    """Compose a compilable C file for one decompiled function (the mechanical cleaning step). Returns (source, note)."""
    if r.get('error'):
        return None, r['error']
    if 'body' not in r:
        return None, 'm2c failure: no output'
    body, ret, params = r['body'], r['ret'], r['params']
    if r.get('ee') and (r['ee']['q'] or r['ee']['u']):
        import ee_prep
        whole = ee_prep.post('\x00'.join((ret, params, body)), r['ee'])
        if whole is None:
            return None, 'ee-instruction: 128-bit or unaligned access mixed with real 64-bit accesses'
        ret, params, body = whole.split('\x00')
    # a register that is read before it is set is an argument the function receives and passes on (or ignores)
    for reg in re.findall(r'M2C_ERROR\(/\* Read from unset register \$a([0-3]) \*/\)', body):
        body = body.replace('M2C_ERROR(/* Read from unset register $a%s */)' % reg, 'arg%s' % reg)
    errs = re.findall(r'M2C_ERROR\(/\* (.*?) \*/\)', body)
    if re.search(r'\bsp\b|&sp[0-9A-Fa-f]+\b', body):
        if not stack:
            return None, 'stack-object: address of a local aggregate (sp)'
        body = stack_rewrite(body, stack)      # a local buffer; its size is searched so that the frame size matches
    if errs or 'M2C_ERROR' in body or 'M2C_TRAP_IF' in body or 'M2C_BREAK' in body:
        why = errs[0] if errs else 'unsupported construct'
        kind = 'ee-instruction' if 'unknown instruction' in why else ('unset-register' if 'unset register' in why else 'm2c-error')
        return None, '%s: %s' % (kind, why)
    # missing leading parameters: argN used without arg0..argN-1 declared (the caller passes them in registers)
    used = [int(x) for x in re.findall(r'\barg(\d+)\b', params + ' ' + body)]
    plist = [] if params in ('void', '') else [p.strip() for p in params.split(',')]
    have = {}
    for p in plist:
        m = re.search(r'\barg(\d+)$', p)
        if m:
            have[int(m.group(1))] = p
    if used:
        top = max(used) + 1
        extra = [p for p in plist if not re.search(r'\barg\d+$', p)]
        plist = [have.get(k, 's32 arg%d' % k) for k in range(top)] + extra
    params = ', '.join(plist) if plist else 'void'
    for sym, lit in (strings or {}).items():            # the function's own strings go back to being literals
        if re.search(r'\b%s\b' % sym, body):
            body = re.sub(r'&?\b%s\b' % sym, lambda m: '"%s"' % lit, body)
    sig = '%s %s(%s)' % (ret, name, params)
    lines = ['#include "auto/prelude.h"', '#include "types_ghidra.h"', '']
    seen = set()
    known = header_functions()
    for ident in IDENT.findall(sig + ' ' + body):
        if ident in seen or ident == name:
            continue
        seen.add(ident)
        d = r['decls'].get(ident)
        if ident in known or ident.startswith('__ee_'):
            continue
        if d and d[0] == 'func':
            lines.append(decl_function(ident, d))
        elif d and d[0] == 'data' and re.search(r'\b%s\(' % ident, body):
            lines.append('extern s32 (*%s)();' % ident)     # called through a pointer held in a global
        elif d and d[0] == 'data':
            lines.append('extern %s %s%s;' % (d[1], ident, d[2]))
        elif re.match(r'^(func|D)_[0-9A-F]{6,8}$', ident):
            if ident.startswith('D_') and re.search(r'\b%s\(' % ident, body):
                lines.append('extern s32 (*%s)();' % ident)
            else:
                lines.append('extern s32 %s;' % ident if ident.startswith('D_') else 'extern s32 %s();' % ident)
    if r.get('ee') and r['ee']['q'] and not r['ee']['real64']:
        lines = [re.sub(r'\bu64\b', 'u128', re.sub(r'\bs64\b', 's128', l)) for l in lines]
    src = '\n'.join(lines) + '\n\n' + sig + ' {\n' + body + '\n}\n'
    return src, sig


def decl_function(ident, d):
    """K&R declaration (no prototype): any argument count links, ints and pointers pass alike. A prototype is kept only
    when a float or double parameter must not be promoted."""
    _, ret, params = d
    ret = 's32' if ret.replace('M2C_UNK', '').strip() == '' else ret
    if re.search(r'\bf(32|64)\b', params):
        return 'extern %s %s(%s);' % (ret, ident, params)
    return 'extern %s %s();' % (ret, ident)


# ---------------------------------------------------------------------------------------------------------- worker
def is_orphan(words):
    """Pieces of the form `<one non-branch instruction>; nop` (see tools/boundaries.py): not code of any function."""
    if not words:
        return False
    for i, w in enumerate(words):
        if i % 2 == 1 and w != 0:
            return False
        if i % 2 == 0 and (w == 0 or is_control(w)):
            return False
    return True


def is_control(x):
    op = x >> 26
    return (op in (1, 2, 3, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17) or (op == 0 and (x & 0x3F) in (8, 9, 12, 13))
            or (op in (0x10, 0x11, 0x12) and (x >> 21) & 0x1F == 8))


def worker_compile(jobs, tag='auto'):
    """jobs: list of (key, source text, flags). Compiles in one worker call. Returns {key: (rc, message, object bytes)}.
    Results are cached by hash of source and flags in build/auto/cache/."""
    cache = AUTO / 'cache'
    cache.mkdir(parents=True, exist_ok=True)
    out, todo = {}, []
    for key, src, flags in jobs:
        h = hashlib.sha256((src + '\0' + ' '.join(flags) + '\0' + PRELUDE_HASH).encode()).hexdigest()[:24]
        cj = cache / (h + '.json')
        if cj.exists():
            d = json.loads(cj.read_text())
            obj = (cache / (h + '.o')).read_bytes() if d['rc'] == 0 else b''
            out[key] = (d['rc'], d['msg'], obj)
        else:
            todo.append((key, src, flags, h))
    if not todo:
        return out
    t0 = time.time()
    buf = io.BytesIO()
    plan = dict(compile=[], pack='newobjs.tgz')
    with tarfile.open(fileobj=buf, mode='w:gz', compresslevel=1) as tar:
        for rel in ('include/macro.inc', 'tools/elfobj.py', 'include/auto/prelude.h', 'include/types_ghidra.h'):
            tar.add(ROOT / rel, arcname=rel)
        for key, src, flags, h in todo:
            data = src.encode()
            ti = tarfile.TarInfo('src/%s.c' % h)
            ti.size = len(data)
            tar.addfile(ti, io.BytesIO(data))
            plan['compile'].append(dict(src='src/%s.c' % h, obj='obj/%s.o' % h, compiler=COMPILER,
                                        args=list(flags) + ['-I', 'include'], timeout=30))
    d = AUTO / 'job'
    d.mkdir(exist_ok=True)
    (d / 'inputs.tgz').write_bytes(buf.getvalue())
    (d / 'plan.json').write_text(json.dumps(plan))
    for n in ('newobjs.tgz', 'results.json'):
        (d / n).unlink(missing_ok=True)
    r = subprocess.run([sys.executable, str(ROOT / 'tools/sandbox.py'), str(ROOT / 'tools/build_job.py'), '--timeout', '1800',
                        '--file', 'inputs.tgz=' + str(d / 'inputs.tgz'), '--file', 'plan.json=' + str(d / 'plan.json'),
                        '--out', 'newobjs.tgz=' + str(d / 'newobjs.tgz'), '--out', 'results.json=' + str(d / 'results.json')],
                       capture_output=True, text=True)
    if not (d / 'results.json').exists():
        sys.stderr.write(r.stdout[-2000:] + r.stderr[-2000:])
        raise SystemExit('Build backend failed; check the build backend configuration.')
    results = json.loads((d / 'results.json').read_text())
    objs = {}
    if (d / 'newobjs.tgz').exists():
        with tarfile.open(d / 'newobjs.tgz') as tar:
            for m in tar.getmembers():
                if m.isfile():
                    objs[m.name[len('obj/'):-2]] = tar.extractfile(m).read()
    for key, src, flags, h in todo:
        res = results.get('src/%s.c' % h, dict(rc=1, msg='no result'))
        obj = objs.get(h, b'') if res['rc'] == 0 else b''
        msg = ''
        if res['rc']:
            ls = [x.split(': ', 1)[-1] if ': ' in x else x for x in res['msg'].strip().split('\n') if x.strip() and 'In function' not in x and 'warning' not in x]
            msg = (ls[0] if ls else res['msg'][:100])[:200]
            if os.environ.get('AUTODECOMP_VERBOSE'):
                msg = res['msg'][-600:]
        (cache / (h + '.json')).write_text(json.dumps(dict(rc=res['rc'], msg=msg)))
        if obj:
            (cache / (h + '.o')).write_bytes(obj)
        out[key] = (res['rc'], msg, obj)
    STATS['compiles'] += len(todo)
    STATS['compile_calls'] += 1
    STATS['compile_seconds'] += time.time() - t0
    return out


STATS = collections.Counter()
PRELUDE_HASH = hashlib.sha256((ROOT / 'include/auto/prelude.h').read_bytes() + ((ROOT / 'include/types_ghidra.h').read_bytes() if (ROOT / 'include/types_ghidra.h').exists() else b'')).hexdigest()


# ---------------------------------------------------------------------------------------------------------- scoring
HI, LO, GP, J26 = 5, 6, 7, 4
KIND = {HI: 'hi', LO: 'lo', GP: 'gprel', J26: 'jal'}
MASK = {'hi': 0xFFFF0000, 'lo': 0xFFFF0000, 'gprel': 0xFFFF0000, 'jal': 0xFC000000}


def s16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


class Target:
    """The original function as scoring tokens: (masked word, relocation target)."""
    def __init__(self, fn, orig):
        self.fn = fn
        self.tokens = []
        for i, w in enumerate(fn['words']):
            r = fn['rel'].get(str(i))
            if r:
                kind, base, add = r[:3]
                self.tokens.append((w & MASK[kind], self._reloc(kind, base, add)))
            else:
                self.tokens.append((w, None))

    @staticmethod
    def _reloc(kind, base, add):
        if isinstance(base, int):
            return ('hi', (base + add) >> 16) if kind == 'hi' else (kind, base + add)
        return (kind, base, add)


def compiled_tokens(obj_bytes, symbol, consts=None):
    """Tokens of `symbol`'s code in a compiled object, or (None, reason)."""
    e = Elf(obj_bytes)
    text = e.section('.text')
    if text is None:
        return None, 'no .text'
    syms = e.symbols()
    code = e.content(text)
    fs = next((s for s in syms if s['name'] == symbol and s['shndx'] == text['index']), None)
    if fs is None:
        return None, 'function symbol missing'
    start, size = fs['value'], fs['size']
    rels = {}
    for t in e.sections:
        if t['type'] == 9 and t['info'] == text['index']:
            c = e.content(t)
            for o in range(0, len(c), 8):
                off, info = struct.unpack_from('<II', c, o)
                rels[off] = (info & 255, syms[info >> 8])
    toks = []
    for off in range(start, start + size, 4):
        w = struct.unpack_from('<I', code, off)[0]
        r = rels.get(off)
        if r is None:
            toks.append((w, None))
            continue
        kind, y = r
        k = KIND.get(kind)
        if k is None:
            toks.append((w, ('other', kind, y['name'])))
            continue
        if kind == J26:
            add = (w & 0x3FFFFFF) << 2
        elif kind == HI:
            add = s16(w) << 16
        else:
            add = s16(w)
        masked = w & MASK[k]
        name = y['name']
        am = ADDRNAME.match(name) if name else None
        if y['shndx'] not in (0, 0xFFF1, 0xFFF2) and not (name and am):
            # symbol defined in the compiled unit itself (a constant it brought along): compare the bytes it points at
            sec = e.sections[y['shndx']]
            where = y['value'] + add
            data = e.content(sec)
            toks.append((masked, (k, ('const', sec['name'], data[where:where + 4].hex()))))
            continue
        if am:
            base = int(am.group(1), 16)
            toks.append((masked, ('hi', (base + add) >> 16) if k == 'hi' else (k, base + add)))
        else:
            toks.append((masked, (k, name, add)))
    return toks, None


def const_equal(a, b, orig_ro):
    return True


def score(target, toks, orig_const):
    """(exact, differing instruction count, note). A compiled constant token equals an original address token when the
    four bytes the original address holds are equal."""
    def norm(t):
        w, r = t
        return (w, r)

    def same(a, b):
        if a == b:
            return True
        if a[0] != b[0]:
            return False
        ra, rb = a[1], b[1]
        for x, y in ((ra, rb), (rb, ra)):
            if x and y and x[0] == y[0] and isinstance(y[1], tuple) and y[1][0] == 'const' and isinstance(x[1], int):
                return True if x[0] == 'hi' else orig_const(x[1]) == y[1][2]      # the low half checks the bytes
        return False

    want = target.tokens
    if len(want) == len(toks):
        d = sum(0 if same(a, b) else 1 for a, b in zip(want, toks))
        if d == 0:
            return True, 0, ''

        def op(t):
            w = t[0]
            return (w >> 26, w & 0x3F if w >> 26 == 0 else 0)
        if [op(t) for t in want] == [op(t) for t in toks]:
            kind = 'registers'          # same opcodes everywhere: register allocation, operand order or immediates
        elif sorted(op(t) for t in want) == sorted(op(t) for t in toks):
            kind = 'order'              # same instructions in another order: scheduling or branch layout
        else:
            kind = 'code'
        return False, d, kind
    sm = difflib.SequenceMatcher(None, [repr(t) for t in want], [repr(t) for t in toks], autojunk=False)
    d = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != 'equal':
            d += max(i2 - i1, j2 - j1)
    return False, d, 'length'


class OrigImage:
    def __init__(self):
        self.e = Elf((ROOT / 'orig' / SLUG / 'files' / 'SLUS_213.76').read_bytes())
        self.secs = [s for s in self.e.sections if s['addr'] and s['name'] in ('.rodata', '.lit4', '.sdata', '.data', '.text')]

    def word(self, addr):
        for s in self.secs:
            if s['addr'] <= addr < s['addr'] + s['size']:
                o = s['offset'] + addr - s['addr']
                return self.e.data[o:o + 4].hex()
        return None


# ---------------------------------------------------------------------------------------------------------- run
def load_results():
    return json.loads(RESULTS.read_text()) if RESULTS.exists() else {}


def save_results(res):
    RESULTS.write_text(json.dumps(res, indent=1, sort_keys=True))


def variants_for(fn):
    """Flag sets tried in order. -G8 only when the original addresses small data through $gp."""
    uses_gp = any(v[0] == 'gprel' for v in fn['rel'].values())
    first = [BASE_FLAGS] if not uses_gp else [BASE_FLAGS, ['-O2', '-G8', '-snas']]
    return first


EXTRA_FLAG_SETS = [['-O1', '-G0', '-snas'], ['-O3', '-G0', '-snas'], ['-O2', '-G0', '-snas', '-fbyte-bool'],
                   ['-O2', '-G8', '-snas'], ['-O2', '-G0', '-snas', '-fno-peephole'], ['-O2', '-G0', '-snas', '-fno-schedule-insns2'],
                   ['-O2', '-G0', '-snas', '-fno-optimize-sibling-calls']]


def draft(fns, orig, batch, options=(), tag='default', ctx='ctx.c', flag_extra=True):
    """The pipeline for a list of functions. Returns {addr_hex: record}."""
    recs = {}
    names = {}
    targets = {f['name']: Target(f, orig) for f in fns}
    t0 = time.time()
    m2c_out = {}
    for i in range(0, len(fns), batch):
        chunk = fns[i:i + batch]
        m2c_out.update(run_m2c(chunk, options, ctx))
    STATS['m2c_seconds'] += time.time() - t0
    sigs = {}
    srcs = {}
    stack_alts = {}
    for f in fns:
        if is_orphan(f['words']):
            recs['0x%x' % f['addr']] = dict(name=f['name'], size=f['size'], region=f['region'], status='orphan',
                                            reason='orphan piece (instruction + nop between functions): not code of a function')
            continue
        if f['size'] <= 4:
            recs['0x%x' % f['addr']] = dict(name=f['name'], size=f['size'], region=f['region'], status='fragment',
                                            reason='a single instruction: not a function (split artifact)')
            continue
        r = m2c_out.get(f['name'], dict(error='m2c failure: no result'))
        src, note = clean_function(f['name'], r, sigs, f.get('strings'))
        rec = dict(name=f['name'], size=f['size'], region=f['region'])
        recs['0x%x' % f['addr']] = rec
        if src is None and note.startswith('stack-object') and f['words'][0] >> 16 == 0x27BD and f['words'][0] & 0x8000:
            frame = 0x10000 - (f['words'][0] & 0xFFFF)
            for n in sorted({frame - 16 - 8 * j for j in range(9)} | {16, 32}):
                if n > 0:
                    alt, altsig = clean_function(f['name'], r, sigs, f.get('strings'), stack=n)
                    if alt:
                        stack_alts.setdefault(f['name'], []).append(alt)
                        note = altsig
            if stack_alts.get(f['name']):
                src = stack_alts[f['name']][0]
                rec['stack_local'] = True
        if src is None and (idiom := idiom_source(f)):
            src, rec['idiom'] = idiom
            note = 'void %s(void)' % f['name']
        if src is None:
            rec.update(status='m2c-failed', reason=note)
            ee = [m for m in f['mnem'] if EE_MNEMONICS.match(m)]
            if ee and 'ee' not in rec['reason']:
                rec['reason'] += ' [ee: %s]' % ee[0]
            continue
        rec.update(sig=note)
        srcs[f['name']] = src
    # compile the default variants (first try)
    jobs, srcof = [], {}
    for f in fns:
        if f['name'] in srcs:
            for k, flags in enumerate(variants_for(f)):
                jobs.append(((f['name'], k), srcs[f['name']], flags))
                srcof[(f['name'], k)] = srcs[f['name']]
            for j, alt in enumerate(stack_alts.get(f['name'], [])[1:]):
                jobs.append(((f['name'], 200 + j), alt, variants_for(f)[0]))
                srcof[(f['name'], 200 + j)] = alt
    results = {}
    for i in range(0, len(jobs), 400):
        results.update(worker_compile(jobs[i:i + 400]))
    best = {}
    byname = {f['name']: f for f in fns}

    def consider(f, key, flags, res):
        key = (f['name'], key)
        rec = recs['0x%x' % f['addr']]
        rc, msg, obj = res
        if rc != 0:
            if key[1] < 100:
                rec.setdefault('compile_error', msg)
            return None
        toks, why = compiled_tokens(obj, f['name'])
        if toks is None:
            rec.setdefault('compile_error', why)
            return None
        exact, d, note = score(targets[f['name']], toks, orig.word)
        cur = best.get(f['name'])
        if cur is None or d < cur[0]:
            best[f['name']] = (d, flags, exact, note, tag, srcof.get(key, srcs[f['name']]))
        return exact, d

    for (name, k), res in results.items():
        f = byname[name]
        consider(f, k, variants_for(f)[min(k, len(variants_for(f)) - 1)], res)
    # flag variants for the rest
    if flag_extra:
        jobs = []
        for f in fns:
            b = best.get(f['name'])
            if f['name'] in srcs and (b is None or not b[2]) and b is not None:
                for k, flags in enumerate(EXTRA_FLAG_SETS):
                    if flags not in variants_for(f):
                        jobs.append(((f['name'], 100 + k), b[5], flags))
                        srcof[(f['name'], 100 + k)] = b[5]
        res2 = {}
        for i in range(0, len(jobs), 400):
            res2.update(worker_compile(jobs[i:i + 400]))
        for (name, k), res in res2.items():
            consider(byname[name], k, EXTRA_FLAG_SETS[k - 100], res)
    for f in fns:
        rec = recs['0x%x' % f['addr']]
        b = best.get(f['name'])
        if f['name'] not in srcs:
            continue
        rec['source'] = b[5] if b else srcs[f['name']]
        if b is None:
            rec['status'] = 'compile-failed'
            rec['reason'] = rec.get('compile_error', '')
            continue
        d, flags, exact, note, _, _ = b
        rec.update(score=d, flags=flags, note=note, variant=tag)
        if exact:
            rec['status'] = 'matched'
            rec['stage'] = 'template' if rec.get('idiom') else 'stack-local' if rec.get('stack_local') else (
                'flags' if flags not in variants_for(f)[:1] else ('first' if tag in ('ctx.c', 'default') else 'm2c-variant'))
        else:
            rec['status'] = 'near' if d <= 8 else 'mismatch'
    return recs



# ---------------------------------------------------------------------------------------------------------- permuter
PERMUTER = ROOT / '.venv/decomp-permuter'
PERMUTER_COMMIT = '8556c81d80d1c1af98a858c8f4dc951357f29139'    # pinned like requirements.txt


def expand_macros(src):
    """Self-contained C for the permuter's parser: inline the prelude's typedefs and expand its macros."""
    prelude = (ROOT / 'include/auto/prelude.h').read_text()
    types = '\n'.join(l for l in prelude.split('\n') if l.startswith('typedef'))
    body = src.replace('#include "auto/prelude.h"\n', '')
    if '#include "types_ghidra.h"' in body:
        names = re.findall(r'^typedef struct (\w+)', (ROOT / 'include/types_ghidra.h').read_text(), re.M)
        if any(re.search(r'\b%s\b' % n, body) for n in names):
            raise ValueError('uses a Ghidra structure: the permuter\'s parser does not read the header')
        body = body.replace('#include "types_ghidra.h"\n', '')

    def call(text, name, make):
        out, i = [], 0
        while True:
            j = text.find(name + '(', i)
            if j < 0:
                out.append(text[i:])
                return ''.join(out)
            out.append(text[i:j])
            k, depth, args, cur = j + len(name) + 1, 1, [], ''
            while depth:
                c = text[k]
                if c == '(':
                    depth += 1
                elif c == ')':
                    depth -= 1
                    if not depth:
                        break
                if c == ',' and depth == 1:
                    args.append(cur)
                    cur = ''
                else:
                    cur += c
                k += 1
            args.append(cur)
            out.append(make([a.strip() for a in args]))
            i = k + 1
    body = call(body, 'M2C_FIELD', lambda a: '(*(%s)((s8 *)(%s) + (%s)))' % (a[1], a[0], a[2]))
    body = call(body, 'M2C_BITWISE', lambda a: '((%s)(%s))' % (a[0], a[1]))
    return types + '\n' + body.replace('NULL', '((void *)0)')


def hamming(a, b):
    return sum(bin(x[0] ^ y[0]).count('1') for x, y in zip(a, b))


def fine_score(target, toks, orig):
    exact, d, note = score(target, toks, orig.word)
    if exact:
        return 0
    h = hamming(target.tokens, toks) if len(toks) == len(target.tokens) else 64
    return 1000 + 100 * d + h


class Climb:
    """Hill climbing on one function with decomp-permuter's randomizer. Candidates of many functions are compiled
    together (permute_many), so the build backend's per-call latency is shared."""
    def __init__(self, f, src, flags, target, orig, rng=1):
        sys.path.insert(0, str(PERMUTER))
        import random
        from src.perm.parse import perm_parse
        from src.perm.eval import perm_evaluate_one
        from src.helpers import get_default_randomization_weights
        self.f, self.flags, self.target, self.orig = f, flags, target, orig
        self.weights = get_default_randomization_weights('base')
        self.rnd = random.Random(rng ^ f['addr'])
        self.src = perm_evaluate_one(perm_parse(expand_macros(src)))[0]
        self.best = fine_score(target, compiled_tokens(worker_compile([((f['name'], 'b'), self.plain(self.src), flags)])[(f['name'], 'b')][2], f['name'])[0] or [], orig)
        self.tried, self.cands, self.done = 0, {}, False

    @staticmethod
    def plain(text):
        return '\n'.join(l for l in text.split('\n') if not l.startswith('#pragma _permuter'))

    def generate(self, k):
        from src.candidate import Candidate
        from src.perm.perm import EvalState
        self.cands = {}
        for i in range(k):
            try:
                c = Candidate.from_source(self.src, EvalState(), self.f['name'], self.weights, rng_seed=self.rnd.randrange(1, 10 ** 12))
                for _ in range(self.rnd.choice((1, 1, 2, 3))):
                    c.randomize_ast()
                self.cands[i] = c.get_source()
            except Exception:
                continue
        return [((self.f['name'], i), self.plain(t), self.flags) for i, t in self.cands.items()]

    def feed(self, results):
        for (name, i), (rc, msg, obj) in results.items():
            self.tried += 1
            if rc != 0 or not obj:
                continue
            toks, _ = compiled_tokens(obj, self.f['name'])
            if toks is None:
                continue
            sc = fine_score(self.target, toks, self.orig)
            if sc < self.best:
                self.best, self.src = sc, self.cands[i]
        self.done = self.best == 0


def committed_form(text):
    """Source of an exact permuter result in the repository's form: prelude include instead of typedefs, macros back."""
    text = re.sub(r'(typedef struct\s*)?\{\s*s64 v;\s*\}\s*__attribute__\(\(packed\)\)\s*M2C_U64;', '', text)    # the permuter prints it over lines
    lines = text.split('\n')
    i = 0
    while i < len(lines) and (lines[i].startswith('typedef') or not lines[i].strip() or lines[i].startswith('#pragma')):
        i += 1
    body = '\n'.join(l for l in lines[i:] if not l.startswith('#pragma _permuter'))
    body = re.sub(r'\*\(\((\w+ \*)\) \(\(\(s8 \*\) (\w+)\) \+ (0x[0-9A-Fa-f]+|\d+)\)\)', r'M2C_FIELD(\2, \1, \3)', body)
    body = body.replace('((void *) 0)', 'NULL')
    return '#include "auto/prelude.h"\n#include "types_ghidra.h"\n\n' + body.strip() + '\n'


def permute_many(climbs, rounds, per_round, label=''):
    t0 = time.time()
    for r in range(rounds):
        live = [c for c in climbs if not c.done]
        if not live:
            break
        jobs = []
        for c in live:
            jobs += c.generate(per_round)
        res = {}
        for i in range(0, len(jobs), 600):
            res.update(worker_compile(jobs[i:i + 600]))
        for c in live:
            c.feed({k: v for k, v in res.items() if k[0] == c.f['name']})
        STATS['permuter_candidates'] += len(jobs)
        print('  permuter round %d: %d live, %d solved, %.0fs' % (r + 1, len(live), sum(c.done for c in climbs), time.time() - t0), flush=True)
    STATS['permuter_seconds'] += time.time() - t0


def cmd_setup(a):
    """Fetch decomp-permuter at the pinned commit into .venv/ (m2c, pycparser and toml come from requirements.txt)."""
    if not PERMUTER.exists():
        subprocess.run(['git', 'clone', '-q', 'https://github.com/simonlindholm/decomp-permuter', str(PERMUTER)], check=True)
    subprocess.run(['git', '-C', str(PERMUTER), 'checkout', '-q', PERMUTER_COMMIT], check=True)
    print('permuter at', PERMUTER_COMMIT, '; m2c:', M2C, M2C.exists())


def try_source(f, src, flags=None):
    """Compile `src` (a source for function record `f`) with the pipeline's flag variants. Returns (differing, flags, tokens, note)
    of the best variant, or (None, None, None, message) when nothing compiles."""
    sets = [flags] if flags else variants_for(f) + [x for x in EXTRA_FLAG_SETS if x not in variants_for(f)]
    outs = worker_compile([((f['name'], i), src, fl) for i, fl in enumerate(sets)])
    orig = OrigImage()
    target = Target(f, orig)
    best, msg = None, ''
    for (name, i), (rc, m, obj) in sorted(outs.items(), key=lambda kv: kv[0][1]):
        if rc:
            msg = m
            continue
        toks, why = compiled_tokens(obj, f['name'])
        if toks is None:
            msg = why
            continue
        exact, d, note = score(target, toks, orig.word)
        if best is None or d < best[0]:
            best = (d, sets[i], toks, note)
        if exact:
            break
    return best if best else (None, None, None, msg)


def cmd_adopt(a):
    """Record an exact hand-written or templated source for a function (status matched, stage `template`)."""
    f = next(x for x in load_inventory() if x['addr'] == int(a.addr, 16))
    src = Path(a.source).read_text()
    d, flags, toks, note = try_source(f, src)
    if d != 0:
        raise SystemExit('%s is not exact (%s)' % (f['name'], note if d is not None else 'compile failed: ' + note))
    res = load_results()
    rec = res.get('0x%x' % f['addr'], dict(name=f['name'], size=f['size'], region=f['region']))
    rec.update(status='matched', stage='template', source=src, flags=flags, score=0)
    rec.pop('reason', None)
    res['0x%x' % f['addr']] = rec
    save_results(res)
    print('adopted', f['name'])


# ---------------------------------------------------------------------------------------------------------- owned data
def c_bytes(b):
    """C string literal pieces for a byte run: text stays readable, NUL runs become \\000 escapes."""
    out, i = [], 0
    while i < len(b):
        j = i
        if 32 <= b[i] < 127:
            while j < len(b) and 32 <= b[j] < 127:
                j += 1
            out.append('"%s"' % b[i:j].decode().replace('\\', '\\\\').replace('"', '\\"'))
        else:
            while j < len(b) and not (32 <= b[j] < 127):
                j += 1
            out.append('"%s"' % ''.join('\\%03o' % x for x in b[i:j]))
        i = j
    return ' '.join(out)


def owned_rodata(f, orig):
    """Definitions of the .rodata a function owns: [(label, address, bytes, alignment)], one per dlabel of its runs."""
    placement = json.loads((BUILD / 'placement.json').read_text())
    ents = placement['sections']['.rodata']
    sec = next(s for s in orig.e.sections if s['name'] == '.rodata')
    text = (BUILD / 's/text' / (f['name'] + '.s')).read_text().split('\n')
    labels = []
    align = None
    for i, l in enumerate(text):
        if l.startswith('.align ') and align is None:
            align = int(l.split()[1])
        m = re.match(r'dlabel (D_([0-9A-F]{8}))', l)
        if m:
            labels.append((int(m.group(2), 16), m.group(1), 2 ** (align if align is not None else 2) if not labels else None))
            align = None
    out = []
    for i, e in enumerate(ents):
        if e.get('owner') != f['name']:
            continue
        lo, hi = e['key'], ents[i + 1]['key'] if i + 1 < len(ents) else sec['addr'] + sec['size']
        inside = [x for x in labels if lo <= x[0] < hi]
        for k, (addr, name, al) in enumerate(inside):
            end = inside[k + 1][0] if k + 1 < len(inside) else hi
            data = orig.e.data[sec['offset'] + addr - sec['addr']:sec['offset'] + end - sec['addr']]
            out.append((name, addr, data, al or min(8, addr & -addr)))
    return out


def owned_base(f, src, orig):
    """The draft with string literals that sit in the function's owned .rodata replaced by the array's name (declared
    extern), or None when the function owns no .rodata."""
    defs = owned_rodata(f, orig)
    if not defs:
        return None
    replaced = []
    for name, addr, data, al in defs:
        multi = [x for x in data.split(b'\0') if x]
        if multi and all(all(32 <= c < 127 for c in x) and len(x) >= 2 for x in multi) and '"%s"' % multi[0].decode() in src:
            src = src.replace('"%s"' % multi[0].decode(), name, 1)
            replaced.append(name)
    head, body = src.split('\n', 1)
    return head + '\n' + '\n'.join('extern char %s[];' % n for n in replaced) + ('\n' if replaced else '') + body


def add_owned_defs(f, base, orig):
    """`base` plus the definitions of the .rodata the function owns (asm label = the image's D_ name), laid out as the
    original run: strings as text, other data as words."""
    out = []
    for name, addr, data, al in owned_rodata(f, orig):
        ident = 'rodata_%08X' % addr
        multi = [x for x in data.split(b'\0') if x]
        if multi and all(all(32 <= c < 127 for c in x) and len(x) >= 2 for x in multi):
            out.append('const char %s[%d] __asm__("%s") __attribute__((aligned(%d))) = %s;' % (ident, len(data), name, al, c_bytes(data)))
        elif len(data) % 4 == 0:
            words = ', '.join('0x%08X' % int.from_bytes(data[i:i + 4], 'little') for i in range(0, len(data), 4))
            out.append('const u32 %s[%d] __asm__("%s") __attribute__((aligned(%d))) = { %s };' % (ident, len(data) // 4, name, al, words))
        else:
            out.append('const u8 %s[%d] __asm__("%s") __attribute__((aligned(%d))) = { %s };' % (
                ident, len(data), name, al, ', '.join('0x%02X' % c for c in data)))
    head, body = base.split('\n', 1)
    return head + '\n' + '\n'.join(out) + '\n' + body


def cmd_rodata(a):
    """Define the owned .rodata of exact drafts that could not be placed (`size`) and adopt the ones that stay exact."""
    res = load_results()
    inv = {f['addr']: f for f in load_inventory()}
    orig = OrigImage()
    n = 0
    for k, v in sorted(res.items()):
        if not (v['status'] == 'verify-failed' and v.get('reason') == 'size' and 'source' in v):
            continue
        f = inv[int(k, 16)]
        base = owned_base(f, v['source'], orig)
        if base is None:
            continue
        new = add_owned_defs(f, base, orig)
        d, flags, toks, note = try_source(f, new, v.get('flags'))
        if d == 0:
            v.update(status='matched', source=new, base_source=base, flags=flags, stage='rodata', single=True)
            v.pop('reason', None)
            n += 1
        elif a.verbose:
            print(hex(f['addr']), 'not exact after defining the data:', d, note)
    save_results(res)
    print('defined owned rodata for %d functions' % n)


def cmd_show(a):
    import rabbitizer
    f = next(x for x in load_inventory() if x['addr'] == int(a.addr, 16))
    res = load_results()['0x%x' % f['addr']]
    print({k: v for k, v in res.items() if k != 'source'})
    print(res.get('source', ''))
    if 'source' not in res:
        return
    flags = res.get('flags', BASE_FLAGS)
    out = worker_compile([(f['name'], res['source'], flags)])[f['name']]
    if not out[2]:
        print('compile failed:', out[1])
        return
    toks, why = compiled_tokens(out[2], f['name'])
    want = Target(f, None).tokens
    orig = OrigImage()
    sm = difflib.SequenceMatcher(None, [repr(t) for t in want], [repr(t) for t in toks], autojunk=False)

    def text(t, pc):
        w = t[0]
        ins = rabbitizer.Instruction(w, pc)
        return '%-44s %s' % (ins.disassemble(), t[1] if t[1] else '')
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        for k in range(max(i2 - i1, j2 - j1)):
            l = text(want[i1 + k], f['addr'] + 4 * (i1 + k)) if i1 + k < i2 else ''
            r = text(toks[j1 + k], 0) if j1 + k < j2 else ''
            print('%s %-90s | %s' % (' ' if tag == 'equal' else '*', l, r))


def reason_key(rec):
    r = rec.get('reason') or ''
    r = re.sub(r'0x[0-9A-Fa-f]+|\b\d+\b', 'N', r)
    r = re.sub(r"`[^']*'", "`X'", r)
    return r[:90]


def cmd_report(a):
    res = load_results()
    sel = [(k, v) for k, v in res.items() if (a.max_size is None or v['size'] < a.max_size) and v['size'] >= (a.min_size or 0)]
    n = len(sel)
    print('functions: %d, bytes: %d' % (n, sum(v['size'] for _, v in sel)))
    cls = collections.Counter()
    byt = collections.Counter()
    for k, v in sel:
        if v['status'] == 'matched':
            c = 'matched: ' + {'first': 'first try', 'flags': 'after flag variants', 'permuter': 'after permuter', 'm2c-variant': 'after m2c variant (callee arity context)', 'template': 'idiom template (asm stub)', 'family': 'cloned from a family member', 'stack-local': 'after a local buffer for sp'}.get(v.get('stage'), v.get('stage', '?'))
        elif v['status'] == 'fragment':
            c = 'not a function (4-byte split artifact)'
        elif v['status'] == 'verify-failed':
            c = 'exact draft, not placeable: ' + {'size': 'function owns rodata', 'extra': 'unit emits extra code'}.get(v['reason'], v['reason'])
        elif v['status'] == 'near':
            c = 'near miss (1-%d differing)' % 8
        elif v['status'] == 'm2c-failed':
            c = 'm2c failed: ' + v['reason'].split(':')[0]
        elif v['status'] == 'compile-failed':
            c = 'compile failed'
        else:
            c = 'mismatch (>8 differing)'
        cls[c] += 1
        byt[c] += v['size']
    for c, x in sorted(cls.items(), key=lambda t: -t[1]):
        print('  %-36s %6d %5.1f%%  %8d bytes' % (c, x, 100.0 * x / n, byt[c]))
    tot = sum(x for c, x in cls.items() if c.startswith('matched'))
    print('  automatic match rate: %d/%d = %.1f%% (%d bytes = %.1f%%)' % (
        tot, n, 100.0 * tot / n, sum(byt[c] for c in cls if c.startswith('matched')),
        100.0 * sum(byt[c] for c in cls if c.startswith('matched')) / max(1, sum(byt.values()))))
    print('near-miss differing-instruction histogram:', dict(sorted(collections.Counter(
        v['score'] for _, v in sel if v['status'] == 'near').items())))
    for status in ('m2c-failed', 'compile-failed'):
        c = collections.Counter(reason_key(v) for _, v in sel if v['status'] == status)
        print('%s reasons:' % status)
        for r, x in c.most_common(a.top):
            print('  %5d  %s' % (x, r))
    ee = collections.Counter()
    for _, v in sel:
        m = re.search(r'unknown instruction: (\S+)', v.get('reason') or '')
        if m:
            ee[m.group(1)] += 1
    if ee:
        print('unsupported instructions:', ee.most_common(a.top))
    print('by size:')
    for lo, hi in ((0, 12), (12, 24), (24, 48), (48, 100), (100, 200), (200, 300)):
        b = [v for _, v in sel if lo <= v['size'] < hi]
        if b:
            m = sum(v['status'] == 'matched' for v in b)
            print('  %3d-%3d bytes: %5d functions, %5d matched (%.1f%%)' % (lo, hi, len(b), m, 100.0 * m / len(b)))


def split_source(rec):
    """(declaration lines, function text) of a draft source."""
    lines = rec['source'].split('\n')
    at = next(i for i, l in enumerate(lines) if not l.startswith('extern') and re.search(r'\b%s\(' % rec['name'], l))
    decls = [l for l in lines[1:at] if l.strip()]
    return decls, '\n'.join(lines[at:]).strip() + '\n'


def decl_name(line):
    m = re.match(r'^extern .*?\b(\w+)\s*(?:\(.*\)|(?:\[[^\]]*\])*)\s*;$', line)
    return m.group(1) if m else line


def cmd_register(a):
    """Write src/auto/<region>/*.c and add units to config/units.yaml for every exact draft that is not registered yet."""
    sys.path.insert(0, str(ROOT / 'tools'))
    from units import load_units
    import units_verify
    res = load_results()
    inv = {f['addr']: f for f in load_inventory()}
    placement = json.loads((BUILD / 'placement.json').read_text())['functions']
    index = {f['addr']: i for i, f in enumerate(placement)}
    units = load_units(variant=SLUG)
    have = {f['addr'] for u in units for f in u['functions']}
    todo = sorted((int(k, 16), v) for k, v in res.items()
                  if v['status'] == 'matched' and 'registered' not in v and int(k, 16) not in have and 'source' in v)
    if a.limit:
        todo = todo[:a.limit]
    groups, cur, decls = [], [], {}
    for addr, rec in todo:
        d, body = split_source(rec)
        dn = {decl_name(l): l for l in d}
        ok = cur and not rec.get('single') and not cur[-1][1].get('single') and index[addr] == index[cur[-1][0]] + 1 and cur[-1][1]['flags'] == rec['flags'] and \
            cur[-1][1]['region'] == rec['region'] and len(cur) < a.group and \
            all(decls.get(k, v) == v for k, v in dn.items()) and not any(k == rec['name'] for k in decls)
        if not ok:
            if cur:
                groups.append(cur)
            cur, decls = [], {}
        cur.append((addr, rec))
        decls.update(dn)
    if cur:
        groups.append(cur)
    out = []
    for g in groups:
        first = g[0][0]
        region = g[0][1]['region']
        decls, bodies = {}, []
        for addr, rec in g:
            d, body = split_source(rec)
            for l in d:
                decls[decl_name(l)] = l
            bodies.append(body)
        # a function defined in the unit must not also be declared extern
        names = {rec['name'] for _, rec in g}
        lines = [l for k, l in decls.items() if k not in names]
        text = '#include "auto/prelude.h"\n\n' + ('\n'.join(lines) + '\n\n' if lines else '') + '\n'.join(bodies)
        rel = 'src/auto/%s/%06x.c' % (region, first)
        (ROOT / rel).parent.mkdir(parents=True, exist_ok=True)
        (ROOT / rel).write_text(text)
        out.append(dict(name='auto_%s_%06x' % (region, first), source=rel, origin='auto', compiler='ee-gcc2.95.3-136',
                        flags=g[0][1]['flags'], externs={},
                        functions=[dict(addr=addr, symbol=rec['name'], size=rec['size'], status='source') for addr, rec in g]))
        for addr, rec in g:
            rec['registered'] = out[-1]['name']
    units_verify.save(units + out)
    save_results(res)
    print('registered %d functions in %d units' % (len(todo), len(out)))


def cmd_settle(a):
    """Link the registered drafts (tools/settle_units.py), record why any were demoted, retry demoted group members alone."""
    sys.path.insert(0, str(ROOT / 'tools'))
    from units import load_units
    import units_verify
    for rnd in range(3):
        r = subprocess.run([sys.executable, str(ROOT / 'tools/settle_units.py')], cwd=ROOT, capture_output=True, text=True)
        print(r.stdout.strip().split('\n')[-1], '' if r.returncode == 0 else '(settle failed)')
        units = load_units(variant=SLUG)
        res = load_results()
        byunit = {}
        for k, v in res.items():
            if v.get('registered'):
                byunit.setdefault(v['registered'], {})[int(k, 16)] = v
        keep, retry = [], 0
        for u in units:
            if not u['name'].startswith('auto_'):
                keep.append(u)
                continue
            fs = u['functions']
            if all(f['status'] == 'source' for f in fs):
                keep.append(u)
                continue
            for f in fs:
                rec = byunit.get(u['name'], {}).get(f['addr'])
                if rec is None:
                    continue
                rec.pop('registered', None)
                if len(fs) == 1 or rec.get('single'):
                    rec['status'], rec['reason'] = 'verify-failed', f.get('reason') or 'unknown'
                else:
                    rec['single'] = True          # a neighbour's failure took the whole group down: try each alone
                    retry += 1
            if (ROOT / u['source']).exists():
                (ROOT / u['source']).unlink()
        units_verify.save(keep)
        save_results(res)
        if not retry:
            break
        print('retrying %d group members as single units' % retry)
        cmd_register(argparse.Namespace(group=a.group, limit=None))
    r = subprocess.run(['ninja'], cwd=ROOT, capture_output=True, text=True)
    print(r.stdout.strip().split('\n')[-1])


def propagate_families(res, inv, orig):
    """Clone every exact source onto the unmatched members of its family; keep the clones that compile to the same words."""
    by = {f['addr']: f for f in inv}
    rep = {}
    for k, v in sorted(res.items()):
        f = by[int(k, 16)]
        key, ok = family_key(f)
        if ok and v['status'] == 'matched' and 'source' in v and key not in rep and (not f['owned'] or 'base_source' in v):
            rep[key] = (f, v)
    jobs, who = [], {}
    for k, v in res.items():
        if v['status'] in ('matched', 'verify-failed', 'fragment') or v.get('registered'):
            continue
        f = by[int(k, 16)]
        key, ok = family_key(f)
        if ok and key in rep and rep[key][0]['addr'] != f['addr']:
            src = clone_source(rep[key][1].get('base_source') or rep[key][1]['source'], rep[key][0], f)
            if src and f['owned']:
                src = add_owned_defs(f, src, orig)
            if src and bool(f['owned']) == bool(rep[key][0]['owned']):
                jobs.append(((f['name'], 'family'), src, rep[key][1]['flags']))
                who[f['name']] = (k, src, rep[key][1]['flags'], rep[key][0]['name'])
    done = 0
    res2 = {}
    for i in range(0, len(jobs), 600):
        res2.update(worker_compile(jobs[i:i + 600]))
    for (name, _), (rc, msg, obj) in res2.items():
        k, src, flags, parent = who[name]
        if rc != 0 or not obj:
            continue
        toks, _ = compiled_tokens(obj, name)
        if toks is None:
            continue
        f = by[int(k, 16)]
        exact, d, note = score(Target(f, orig), toks, orig.word)
        if exact:
            res[k].update(status='matched', stage='family', source=src, flags=flags, score=0, family_of=parent)
            res[k].pop('reason', None)
            done += 1
    print('families: %d clones tried, %d exact' % (len(jobs), done))
    return done


def cmd_permute(a):
    """Run the permuter over the near misses of build/auto.json."""
    inv = {f['addr']: f for f in load_inventory()}
    res = load_results()
    orig = OrigImage()
    todo = sorted(((v['score'], k) for k, v in res.items() if v['status'] == 'near' and v['score'] <= a.max_score
                   and 's128' not in v['source'] and 'permuter' not in v and (a.max_size is None or v['size'] < a.max_size)))
    seen = set()
    reps = []
    for sc, k in todo:                      # one member per family: the others get the result by cloning
        key, ok = family_key(inv[int(k, 16)])
        if ok and key in seen:
            continue
        seen.add(key)
        reps.append((sc, k))
    print('%d near misses in %d families or singletons' % (len(todo), len(reps)))
    todo = reps
    if a.limit:
        todo = todo[:a.limit]
    print('permuting %d near misses' % len(todo))
    for i in range(0, len(todo), a.group):
        chunk = todo[i:i + a.group]
        climbs = []
        for _, k in chunk:
            f = inv[int(k, 16)]
            try:
                climbs.append(Climb(f, res[k]['source'], res[k]['flags'], Target(f, orig), orig))
            except Exception as e:
                res[k]['permuter'] = dict(error=str(e)[:100])
        permute_many(climbs, a.rounds, a.per_round)
        for c in climbs:
            k = '0x%x' % c.f['addr']
            rec = res[k]
            rec['permuter'] = dict(best=c.best, tries=c.tried)
            if c.done:
                rec.update(status='matched', stage='permuter', source=committed_form(c.src))
        propagate_families(res, list(inv.values()), orig)
        save_results(res)
        print('[%d/%d] solved so far: %d' % (min(i + a.group, len(todo)), len(todo),
                                              sum(1 for v in res.values() if v.get('stage') == 'permuter')), flush=True)


RANK = {'matched': 0, 'verify-failed': 0, 'near': 1, 'mismatch': 2, 'compile-failed': 3, 'm2c-failed': 4, 'fragment': 5}


def better(new, old):
    if old is None:
        return True
    if old.get('registered') or old['status'] == 'verify-failed':
        return False
    a, b = RANK[new['status']], RANK[old['status']]
    if a != b:
        return a < b
    return new.get('score', 0) < old.get('score', 0)


def merge_records(res, recs):
    """Keep the better of an earlier and a new draft; the loser's variant is recorded in `tried`."""
    out = {}
    for k, new in recs.items():
        old = res.get(k)
        if better(new, old):
            if old and old.get('variant'):
                new['tried'] = old.get('tried', []) + [dict(variant=old['variant'], status=old['status'], score=old.get('score'))]
            out[k] = new
        else:
            old.setdefault('tried', []).append(dict(variant=new.get('variant', '?'), status=new['status'], score=new.get('score')))
            out[k] = old
    return out


def family_key(f):
    """Functions with equal keys are the same code over other symbols: identical words once relocated fields are masked,
    identical addends, and the same pattern of which relocations share a symbol."""
    rel = f['rel']
    order, sig, masked = {}, [], []
    for i, w in enumerate(f['words']):
        r = rel.get(str(i))
        if r:
            kind, base, add = r[:3]
            order.setdefault(str(base), len(order))
            sig.append((i, kind, add, order[str(base)], base if not isinstance(base, int) else None))
            masked.append(w & (0xFC000000 if kind == 'jal' else 0xFFFF0000))
        else:
            masked.append(w)
    return json.dumps([masked, sig]), not f['lit4'] and (not f['owned'] or f['owned'] == ['.rodata'])


def symbol_names(f):
    """The function's own name followed by the distinct symbols its relocations refer to, in order of appearance."""
    names, seen = [f['name']], set()
    for i in sorted(f['rel'], key=int):
        n = f['rel'][i][3]
        if n not in seen:
            seen.add(n)
            names.append(n)
    return names


def clone_source(src, a, b):
    """Source of function `b` from the exact source of its family member `a` (rename the symbols in order)."""
    na, nb = symbol_names(a), symbol_names(b)
    if len(na) != len(nb):
        return None
    tmp = {x: '@@%d@@' % i for i, x in enumerate(na)}
    out = re.sub(r'\b(%s)\b' % '|'.join(map(re.escape, sorted(na, key=len, reverse=True))), lambda m: tmp[m.group(1)], src)
    for i, y in enumerate(nb):
        out = out.replace('@@%d@@' % i, y)
    return out


def reconcile(res):
    """Records of functions that are source units now say so (units.yaml is the truth)."""
    from units import load_units
    n = 0
    live = {'0x%x' % f['addr'] for f in load_inventory()}
    for k in [k for k in res if k not in live]:          # a boundary repair removed this start
        res.pop(k)
    for u in load_units(variant=SLUG):
        if not u['name'].startswith('auto_'):
            continue
        for f in u['functions']:
            rec = res.get('0x%x' % f['addr'])
            if f.get('status') == 'source' and rec is not None and rec.get('registered') != u['name']:
                rec['status'], rec['registered'] = 'matched', u['name']
                rec.pop('reason', None)
                n += 1
    return n


def cmd_run(a):
    AUTO.mkdir(parents=True, exist_ok=True)
    inv = load_inventory()
    if not (AUTO / 'ctx.c').exists() or a.refresh_context:
        print('context: %d prototypes' % write_context())
        write_context_arity(inv)
    done = source_functions()
    sel = [f for f in inv if f['addr'] not in done]
    if a.addr:
        want = {int(x, 16) for x in a.addr}
        sel = [f for f in sel if f['addr'] in want]
    if a.max_size is not None:
        sel = [f for f in sel if f['size'] < a.max_size]
    if a.min_size:
        sel = [f for f in sel if f['size'] >= a.min_size]
    if a.region:
        sel = [f for f in sel if f['region'] in a.region]
    sel = [f for f in sel if f['size'] > 0]
    res = load_results()
    reconcile(res)
    if a.status:
        sel = [f for f in sel if res.get('0x%x' % f['addr'], {}).get('status') in a.status]
    if a.sample and len(sel) > a.sample:
        import random
        sel = sorted(random.Random(a.sample).sample(sel, a.sample), key=lambda f: f['addr'])
    if a.limit:
        sel = sel[:a.limit]
    if not a.redo and not a.status:
        sel = [f for f in sel if '0x%x' % f['addr'] not in res]
    if 'verify-failed' in (a.status or []):
        for f in sel:
            if res.get('0x%x' % f['addr'], {}).get('status') == 'verify-failed':
                res.pop('0x%x' % f['addr'])        # the earlier exact draft could not be placed: draft it again
    else:
        sel = [f for f in sel if res.get('0x%x' % f['addr'], {}).get('status') != 'verify-failed']
    print('selected %d functions' % len(sel))
    orig = OrigImage()
    t0 = time.time()
    for i in range(0, len(sel), a.chunk):
        chunk = sel[i:i + a.chunk]
        recs = draft(chunk, orig, a.batch, options=a.m2c_option or (), tag=a.tag or a.ctx, ctx=a.ctx)
        recs = merge_records(res, recs)
        res.update(recs)
        save_results(res)
        c = collections.Counter(r['status'] for r in recs.values())
        print('[%d/%d] %s  (%.0fs)' % (min(i + a.chunk, len(sel)), len(sel), dict(c), time.time() - t0), flush=True)
    print('stats', dict(STATS))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    r = sub.add_parser('run')
    r.add_argument('--max-size', type=int, help='functions smaller than this many bytes')
    r.add_argument('--min-size', type=int)
    r.add_argument('--region', action='append')
    r.add_argument('--addr', action='append')
    r.add_argument('--limit', type=int)
    r.add_argument('--sample', type=int, help='a random sample of this many functions (fixed seed)')
    r.add_argument('--batch', type=int, default=200, help='functions per m2c process')
    r.add_argument('--chunk', type=int, default=600, help='functions per checkpoint of auto.json')
    r.add_argument('--redo', action='store_true')
    r.add_argument('--ctx', default='ctx.c', help='m2c context file in build/auto/ (ctx.c, ctx2.c, ctx3.c)')
    r.add_argument('--tag', help='name of this m2c variant in the records')
    r.add_argument('--m2c-option', action='append', help='extra m2c option (repeatable), e.g. --m2c-option=--no-andor')
    r.add_argument('--status', action='append', help='redo the functions whose earlier outcome was this')
    r.add_argument('--refresh-context', action='store_true')
    r.set_defaults(fn=cmd_run)
    rp = sub.add_parser('report')
    rp.add_argument('--max-size', type=int)
    rp.add_argument('--min-size', type=int)
    rp.add_argument('--top', type=int, default=12)
    rp.set_defaults(fn=cmd_report)
    rg = sub.add_parser('register')
    rg.add_argument('--group', type=int, default=24, help='most adjacent functions per unit')
    rg.add_argument('--limit', type=int)
    rg.set_defaults(fn=cmd_register)
    st = sub.add_parser('settle')
    st.add_argument('--group', type=int, default=24)
    st.set_defaults(fn=cmd_settle)
    pm = sub.add_parser('permute')
    pm.add_argument('--max-score', type=int, default=8)
    pm.add_argument('--max-size', type=int)
    pm.add_argument('--limit', type=int)
    pm.add_argument('--group', type=int, default=60, help='functions climbed together')
    pm.add_argument('--rounds', type=int, default=6)
    pm.add_argument('--per-round', type=int, default=60, help='candidates per function and round')
    pm.set_defaults(fn=cmd_permute)
    fm = sub.add_parser('family')
    fm.set_defaults(fn=lambda a: (lambda res: (reconcile(res), propagate_families(res, load_inventory(), OrigImage()), save_results(res)))(load_results()))
    mg = sub.add_parser('merge')
    mg.add_argument('file')
    mg.set_defaults(fn=lambda a: (lambda res: (res.update(merge_records(res, {k: v for k, v in json.loads(Path(a.file).read_text()).items()})), save_results(res)))(load_results()))
    su = sub.add_parser('setup')
    su.set_defaults(fn=cmd_setup)
    ro = sub.add_parser('rodata')
    ro.add_argument('--verbose', action='store_true')
    ro.set_defaults(fn=cmd_rodata)
    ad = sub.add_parser('adopt')
    ad.add_argument('addr')
    ad.add_argument('source')
    ad.set_defaults(fn=cmd_adopt)
    sh = sub.add_parser('show')
    sh.add_argument('addr')
    sh.set_defaults(fn=cmd_show)
    a = ap.parse_args()
    a.fn(a)


if __name__ == '__main__':
    main()
