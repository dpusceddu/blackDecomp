#!/usr/bin/env python3
"""Automatic decompilation pilot: m2c -> clean -> compile variants -> score -> permuter -> register as source units.

  autodecomp.py run [--max-size N] [--min-size N] [--region R] [--addr A ...] [--limit N] [--no-permute]
                    [--permute-seconds S] [--batch N]
        draft every selected assembly function and record the outcome in build/auto.json
  autodecomp.py register [--group N]     put exact matches into their TU files (replacing the INCLUDE_ASM line; tools/tu_files.py)
  autodecomp.py report                   outcome table for build/auto.json
  autodecomp.py show ADDR                print the best draft of a function and its diff

Sizes are the function's code size in bytes. Compilation happens only with the build toolchain (tools/sandbox.py, one call
per batch of candidates); m2c and scoring run on the host because they only read and write text. Scoring compares the
compiled .text with the original instruction words, masking relocated fields, and compares each relocation's target
(symbol address plus addend) with the symbolic operand of the original assembly. The final authority is the identical
link (`ninja` ends with OK); `settle` puts back the INCLUDE_ASM line of what does not place identically. Setup and pinned versions: docs/pipeline.md.
"""
import argparse, base64, collections, difflib, hashlib, io, json, os, re, struct, subprocess, sys, tarfile, time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfinfo import Elf
from build_telemetry import record as record_build
from layout import view_include

ROOT = Path(__file__).resolve().parents[1]
SLUG = 'SLUS_213.76'
BUILD = ROOT / 'build' / SLUG
FUNCTION_ASM = ROOT / 'asm' / SLUG / 'nonmatchings'      # one assembly file per function (tools/split_objects.py)
AUTO = ROOT / 'build' / 'auto'
RESULTS = Path(os.environ.get('AUTODECOMP_RESULTS', ROOT / 'build' / 'auto.json'))
M2C = ROOT / '.venv/bin/m2c'
COMPILER = 'ee-gcc2.95.3-136'
BASE_FLAGS = ['-O2', '-G0', '-snas']
INSN = re.compile(r'^\s+/\* ([0-9A-F]+) ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+(\S+)\s*(.*?)\s*$')
SYM = re.compile(r'^([A-Za-z_$.][\w$.]*)(?:\s*([+-])\s*(0x[0-9A-Fa-f]+))?$')
ADDRNAME = re.compile(r'^(?:func|D|jtbl|ehtbl)_([0-9A-Fa-f]{1,8})$')
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
    """All text blocks of a split function, excluding final alignment and owned data.

    Switch cases can have secondary function labels and their own endlabels in
    the same input section. The last endlabel bounds the code, not the first.
    """
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
    code, in_text, last_end = [], True, None
    for line in text:
        section = re.match(r'\s*\.section\s+([^,\s]+)', line)
        if section:
            in_text = section.group(1).startswith('.text')
        if in_text:
            code.append(line)
            if line.startswith('endlabel'):
                last_end = len(code)
    for line in code[:last_end]:
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
        if d['stamp'] == stamp and d.get('version') == 5:
            return d['functions']
    sys.path.insert(0, str(ROOT / 'tools'))
    from progress import regions
    placement = json.loads((BUILD / 'placement.json').read_text())['functions']
    reg, _ = regions([f['addr'] for f in placement])
    out = []
    for f, r in zip(placement, reg):
        p = FUNCTION_ASM / (f['name'] + '.s')
        words, rel, mnem, strings = parse_function(p)
        out.append(dict(addr=f['addr'], name=f['name'], span=f['end'] - f['addr'], size=4 * len(words), words=words,
                        rel={str(k): list(v) for k, v in rel.items()}, mnem=mnem, region=r, owned=sorted(f['owned']), strings=strings,
                        lit4=(FUNCTION_ASM / (f['name'] + '.lit4.s')).exists()))
    cache.write_text(json.dumps(dict(stamp=stamp, version=5, functions=out)))
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


HEADER = ROOT / 'include/ps2/prototypes.h'              # recovered signatures (weak declarations, by func_XXXXXXXX name)
TYPES_HEADER = ROOT / 'include/ps2/recovered_types.h'    # the structures those signatures use


def header_functions():
    """Names of the functions include/ps2/prototypes.h declares."""
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


RECOVERED = None


def recovered_context(refresh=False):
    """The same recovery feeds m2c and the build backend; retain diagnostics in ignored JSON."""
    global RECOVERED
    if RECOVERED is None or refresh:
        if os.environ.get('AUTODECOMP_FREEZE_CONTEXT') == '1':
            if refresh:
                raise SystemExit('Frozen context cannot be refreshed; refresh it once, before parallel runs.')
            cache = AUTO / 'context.json'
            if not cache.exists() or not (ROOT / 'include/game/layouts/layouts.h').exists() or not (AUTO / 'ctx.c').exists():
                raise SystemExit('Frozen recovery context is missing; create it first with `autodecomp.py context --refresh`.')
            RECOVERED = json.loads(cache.read_text())
        else:
            import context_recovery
            RECOVERED = context_recovery.recover(refresh=refresh)
            context_recovery.write_build_context(RECOVERED)   # ignored build/auto/ only; never the committed headers
    return RECOVERED


def header_declarations():
    """Keep authored pointee names and parameter spellings available to every consumer."""
    return {m.group(1): line for line in HEADER.read_text().splitlines()
            if line.startswith('extern ') and (m := re.search(r'\b(func_[0-9A-F]{8})\(', line))} if HEADER.exists() else {}


def return_abi(typ):
    """Only the physical return bank and width; low-word pointer evidence stays compatible."""
    if '*' in typ:
        return 'gpr', 4
    if typ == 'f32':
        return 'fpr', 4
    if typ in ('s8', 'u8', 's16', 'u16', 's32', 'u32'):
        return 'gpr', 4
    if typ in ('s64', 'u64', 'f64'):
        return 'gpr', 8
    if typ in ('s128', 'u128'):
        return 'gpr', 16
    return None


def selected_prototype(row, header=None, m2c=False, scalar=None):
    """Merge only proved ABI corrections into weak HEADER declarations.

    A direct producer must agree with the resolved return before replacing its
    width/bank. A void return also needs a real caller consumption in that bank.
    Low-word GPR facts cannot narrow an existing wider header return.
    Keep the header's useful parameter and pointee spellings; caller counts and
    propagated types alone never replace them. Anchored/variadic rows retain
    their existing precedence. Unsupported header syntax is left untouched.
    """
    import context_recovery as cr
    anchored = row.get('source_quality', 0) >= 2 or row.get('variadic')
    if header and not anchored:
        declaration = re.fullmatch(r'extern\s+(.+?)\s+' + re.escape(row['name']) + r'\((.*)\);(.*)', header)
        if not declaration:
            return header
        ret, params, tail = declaration.groups()
        header_ret, _ = cr.normalize_type(ret)
        # Syscalls have implicit operands absent from the stub instructions.
        # Relax their false zero-argument declaration without guessing a return.
        if row.get('syscall') and header_ret == 'void' and params.strip() == 'void':
            return 'extern %s %s();%s' % (ret, row['name'], tail)
        evidence = row.get('return_evidence', {})
        abi = return_abi(row['ret'])
        if abi and not row.get('syscall'):
            direct, conflicts = cr.resolve_type(evidence.get('direct_types', {}).get(abi[0], []))
            incompatible = any(c.get('slot') == 'ret' and c.get('kind') != 'source-hint-disagrees'
                               for c in row.get('conflicts', []))
            produced = not conflicts and return_abi(direct) == abi
            consumed = abi[0] in evidence.get('consumed_banks', [])
            header_abi = return_abi(header_ret)
            contradiction = header_abi and (header_abi[0] != abi[0] or abi[1] > header_abi[1])
            if produced and not incompatible and ((header_ret == 'void' and consumed)
                                                    or contradiction):
                ret = cr.context_type(row['ret'], m2c)
        return 'extern %s %s(%s);%s' % (ret, row['name'], params, tail)
    alternate = row
    if scalar and not anchored:
        simple = {'unknown', 's32', 'u32', 'void *'}
        if scalar == 'void':
            alternate = dict(row, ret='void' if row['ret'] in ('unknown', 's32', 'u32') else row['ret'])
        else:
            params = [scalar if t in simple and str(k) not in row.get('param_views', {}) else t
                      for k, t in enumerate(row['params'])]
            alternate = dict(row, params=params, ret=scalar if row['ret'] in simple else row['ret'])
    return 'extern ' + cr.prototype(alternate, m2c)


def write_context(refresh=False):
    """Whole-callgraph signatures, PS2 aggregate views and the recovered types for m2c."""
    context = recovered_context(refresh)
    if os.environ.get('AUTODECOMP_FREEZE_CONTEXT') == '1':
        return len(context['signatures'])
    out = ['typedef signed char s8; typedef unsigned char u8; typedef short s16; typedef unsigned short u16;',
           'typedef int s32; typedef unsigned int u32; typedef long s64; typedef unsigned long u64;',
           'typedef float f32; typedef double f64;']
    declared = header_declarations()
    for header in (TYPES_HEADER, HEADER):
        if not header.exists():
            continue
        for line in header.read_text().split('\n'):
            if line.startswith('#') or line.startswith('typedef char assert_') or line.startswith('/*') or line.startswith(' *'):
                continue
            match = re.search(r'\bfunc_([0-9A-F]{8})\(', line) if line.startswith('extern ') else None
            row = context['signatures'].get(str(int(match.group(1), 16))) if match else None
            if row:
                continue
            out.append(line)
    known = set(re.findall(r'\b(func_[0-9A-F]{8})\(', '\n'.join(out)))
    out.append((AUTO / 'recovered_layouts.c').read_text())
    for row in context['signatures'].values():
        if row['name'] not in known:
            out.append(selected_prototype(row, declared.get(row['name']), m2c=True))
    import ee_prep
    out += ee_prep.PLACEHOLDERS
    (AUTO / 'ctx.c').write_text('\n'.join(out) + '\n')
    return len(context['signatures'])


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
            targets.add(i + (x.getBranchOffsetGeneric() >> 2))
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
        if d['stamp'] == stamp and d.get('version') == 4:
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
    cache.write_text(json.dumps(dict(stamp=stamp, version=4, arity={str(k): v for k, v in arity.items()})))
    return arity


def write_context_arity(inv):
    """Scalar/pointer alternatives retain all anchored source and EE/float signatures."""
    if os.environ.get('AUTODECOMP_FREEZE_CONTEXT') == '1':
        return
    context = recovered_context()
    declared = header_declarations()
    base = '\n'.join(line for line in (AUTO / 'ctx.c').read_text().splitlines()
                     if not re.match(r'^(?:extern )?[^;{}]*\bfunc_[0-9A-F]{8}\(', line))
    for name, typ in (('ctx2.c', 's32'), ('ctx3.c', 'void *'), ('ctx_void.c', 'void')):
        out = [base]
        for row in context['signatures'].values():
            out.append(selected_prototype(row, declared.get(row['name']), m2c=True, scalar=typ))
        (AUTO / name).write_text('\n'.join(out) + '\n')


# ---------------------------------------------------------------------------------------------------------- m2c
def run_m2c(fns, options=(), ctx='ctx.c'):
    """Decompile `fns` in one m2c process. Returns {name: dict(c=..., sig=..., decls={}, error=...)}."""
    import m2c_input
    paths, flags, rejected = [], {}, {}
    prep_dir = AUTO / 'prep'
    prep_dir.mkdir(exist_ok=True)
    for f in fns:
        try:
            text, flags[f['name']] = m2c_input.prepare((FUNCTION_ASM / (f['name'] + '.s')).read_text())
        except ValueError as error:
            rejected[f['name']] = dict(error='ee-instruction: ' + str(error), decls={})
            continue
        (prep_dir / (f['name'] + '.s')).write_text(text)
        paths.append(str(prep_dir / (f['name'] + '.s')))
        if f['lit4']:
            lit = prep_dir / (f['name'] + '.lit4.s')
            lit.write_text(m2c_input.normalize_sections((FUNCTION_ASM / (f['name'] + '.lit4.s')).read_text()))
            paths.append(str(lit))
    if not paths:
        STATS['m2c_function_failures'] += len(rejected)
        return rejected
    cmd = [sys.executable, str(ROOT / 'tools/m2c_wrap.py'), '-t', 'mipsee-gcc-c', '--valid-syntax', '--context', str(AUTO / ctx), '--no-cache'] + list(options) + paths
    timeout = float(os.environ.get('AUTODECOMP_M2C_TIMEOUT', '180'))
    try:
        r = subprocess.run(cmd, capture_output=True, text=True, cwd=ROOT, timeout=timeout)
    except subprocess.TimeoutExpired:
        if len(fns) > 1:
            # One pathological CFG must not lose the rest of an unrestricted run.
            middle = len(fns) // 2
            print('m2c timeout; bisecting %d functions' % len(fns), file=sys.stderr, flush=True)
            result = run_m2c(fns[:middle], options, ctx)
            result.update(run_m2c(fns[middle:], options, ctx))
            return result
        f = fns[0]
        return {f['name']: dict(error='m2c failure: decompiler timeout after %.0fs' % timeout,
                               decls={}, ee=flags[f['name']])}
    if r.returncode and 'Syntax error when parsing C context' in r.stdout + r.stderr:
        raise SystemExit('m2c context is invalid; stopping instead of recording every function as failed.\n' + (r.stdout + r.stderr)[-2000:])
    if r.returncode and not any(FUNC_START.match(line) for line in r.stdout.splitlines()) and not FAIL.search(r.stdout):
        raise SystemExit('m2c failed before analyzing the batch; stopping instead of hiding an input failure.\n' + (r.stdout + r.stderr)[-2500:])
    out = split_m2c(r.stdout + ('\n/* STDERR %s */' % r.stderr if r.returncode else ''), fns)
    out.update(rejected)
    STATS['m2c_body_functions'] += sum('body' in row for row in out.values())
    STATS['m2c_function_failures'] += sum(bool(row.get('error')) for row in out.values())
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
    return '#include "ps2/prelude.h"\n\nvoid %s(void) {\n    __asm__ volatile("%s");\n}\n' % (f['name'], body), kind


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


def restore_abi_widths(name, ret, params, body):
    """Restore known EE128 ABI values without widening unrelated true64 locals.

    m2c represents both with s64. Explicit incoming slots, direct call results and
    copies of those results can be recovered; arbitrary mixed-width expressions
    remain a limitation rather than a blanket replacement of every s64 token.
    """
    rows = recovered_context()['signatures']
    row = rows.get(str(int(name[5:], 16))) if re.fullmatch(r'func_[0-9A-F]{8}', name) else None
    wide = set()
    if row:
        if row['ret'] in ('s128', 'u128'):
            ret = row['ret']
        for typ, slot in zip(row['params'], row.get('register_slots', [])):
            if typ not in ('s128', 'u128') or slot >= 8:
                continue
            var = 'arg%d' % slot
            params = re.sub(r'\b(?:s64|u64|s128|u128|s32|u32)\s+' + var + r'\b', typ + ' ' + var, params)
            wide.add(var)
    wide_calls = {value['name'] for value in rows.values() if value['ret'] in ('s128', 'u128')}
    declarations = set(re.findall(r'\b(?:s64|u64)\s+(\w+)\s*(?:[;=])', body))
    assignments = re.findall(r'\b(\w+)\s*=\s*([^;]+);', body)
    changed = True
    while changed:
        changed = False
        for target, expression in assignments:
            if target not in declarations or target in wide:
                continue
            expression = expression.strip()
            direct = expression in wide
            call = re.match(r'^(func_[0-9A-F]{8})\(.*\)$', expression, re.S)
            if direct or call and call.group(1) in wide_calls:
                wide.add(target)
                changed = True
    for var in wide & declarations:
        body = re.sub(r'\b(s64|u64)(\s+' + re.escape(var) + r'\b)', lambda match: ('s128' if match.group(1) == 's64' else 'u128') + match.group(2), body)
    return ret, params, body


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
    ret, params, body = restore_abi_widths(name, ret, params, body)
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
    lines = ['#include "ps2/prelude.h"', '#include "ps2/recovered_types.h"', '']
    if '__ee_vu_' in body:
        lines.insert(1, '#include "ps2/vu0_lowering.h"')
    seen = set()
    known = header_declarations()
    for ident in IDENT.findall(sig + ' ' + body):
        if ident in seen or ident == name:
            continue
        seen.add(ident)
        d = r['decls'].get(ident)
        if ident.startswith('__ee_'):
            continue
        row = recovered_context()['signatures'].get(str(int(ident[5:], 16))) if re.fullmatch(r'func_[0-9A-F]{8}', ident) else None
        if row:
            lines.append(selected_prototype(row, known.get(ident)))
        elif ident in known:
            lines.append(known[ident])
        elif d and d[0] == 'func':
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
    body2, changed = byte_addresses(body, lines)
    if changed and not os.environ.get('AUTODECOMP_NO_BYTEADDR'):
        body = body2
    views = sorted(set(re.findall(r'\bRecovered_\w+\b', '\n'.join(lines) + sig + body)))
    lines[2:2] = ['#include "%s"' % view_include(view) for view in views]
    src = '\n'.join(lines) + '\n\n' + sig + ' {\n' + body + '\n}\n'
    return src, sig


ADDR_OF = re.compile(r'&(D_[0-9A-F]{8})\b')


def byte_addresses(body, lines):
    """`&D_x + n` in m2c's C scales n by the size of D_x, but the assembly adds bytes: make the address an integer wherever it is
    an operand of + or - (`(s32) &D_x`) and give the dereferences of such sums the type D_x is declared with."""
    dtype = {}
    for l in lines:
        m = re.match(r'^extern (.+?)\s+(D_[0-9A-F]{8});$', l)
        if m:
            dtype[m.group(2)] = m.group(1)

    def operand(m):
        pre, post = body[:m.start()].rstrip(), body[m.end():].lstrip()
        if re.search(r'[+-]$', pre) and not pre.endswith(('++', '--')) or re.match(r'[+-](?![+-=])', post) and not post.startswith(('+=', '-=')):
            return '((s32) &%s)' % m.group(1)
        return m.group(0)
    out = ADDR_OF.sub(operand, body)
    if '(s32) &D_' not in out:
        return out, False
    # `*(<sum with an integer address>)`: the pointer is gone, so say what is read
    res, i = [], 0
    while i < len(out):
        j = out.find('*(', i)
        if j < 0 or (j > 0 and (out[j - 1].isalnum() or out[j - 1] in '_)]')):      # a multiplication, not a dereference
            if j < 0:
                break
            res.append(out[i:j + 2])
            i = j + 2
            continue
        depth, k = 0, j + 1
        while k < len(out):
            depth += out[k] == '('
            depth -= out[k] == ')'
            if depth == 0:
                break
            k += 1
        inner = out[j + 1:k + 1]
        m = re.search(r'\(s32\) &(D_[0-9A-F]{8})', inner)
        if m:
            res.append(out[i:j] + '*(%s *)%s' % (dtype.get(m.group(1), 's32'), inner))
            i = k + 1
        else:
            res.append(out[i:j + 2])
            i = j + 2
    res.append(out[i:])
    return ''.join(res), True


def decl_function(ident, d):
    """K&R declaration (no prototype): any argument count links, ints and pointers pass alike. A prototype is kept only
    when a float or double parameter must not be promoted."""
    _, ret, params = d
    ret = 's32' if ret.replace('M2C_UNK', '').strip() == '' else ret
    if params.strip() and 'M2C_UNK' not in params:
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


def split_cc(flags):
    """(compiler, flags): a flag set may start with `--cc=NAME` to select another compiler than the SN default."""
    cc, out = COMPILER, []
    for f in flags:
        if f.startswith('--cc='):
            cc = f[5:]
        else:
            out.append(f)
    return cc, out


def compile_dependencies(source):
    """Quoted-header closure for a draft, including custom area and recovered headers."""
    seen, todo = {}, [(source, ROOT / 'src')]
    while todo:
        text, parent = todo.pop()
        for name in re.findall(r'^\s*#\s*include\s+"([^"]+)"', text, re.M):
            for candidate in (parent / name, ROOT / 'include' / name, ROOT / name):
                if candidate.is_file():
                    path = candidate.resolve()
                    try:
                        relative = path.relative_to(ROOT).as_posix()
                    except ValueError:
                        raise ValueError('draft header is outside the repository')
                    if relative not in seen:
                        seen[relative] = path.read_bytes()
                        todo.append((seen[relative].decode(), path.parent))
                    break
    return seen


def worker_compile(jobs, tag='auto'):
    """jobs: list of (key, source text, flags). Compiles in one build call. Returns {key: (rc, message, object bytes)}.
    Results are cached by hash of source and flags in build/auto/cache/."""
    cache = AUTO / 'cache'
    cache.mkdir(parents=True, exist_ok=True)
    out, todo, headers, aliases = {}, [], {}, {}
    for key, src, flags in jobs:
        deps = compile_dependencies(src)
        headers.update(deps)
        digest = hashlib.sha256((src + '\0' + ' '.join(flags) + '\0' + PRELUDE_HASH).encode())
        if any(f.startswith('--assembler=') for f in flags):
            digest.update((ROOT / 'tools/assembler.py').read_bytes())
        if split_cc(flags)[0].startswith('mwcps2-'):
            digest.update(b'\0catalog-mw-joined-include-v1')
        for path, data in sorted(deps.items()):
            digest.update(path.encode() + b'\0' + data)
        h = digest.hexdigest()[:24]
        cj = cache / (h + '.json')
        if cj.exists():
            d = json.loads(cj.read_text())
            obj = (cache / (h + '.o')).read_bytes() if d['rc'] == 0 else b''
            out[key] = (d['rc'], d['msg'], obj)
        elif h in aliases:
            aliases[h].append(key)           # never race compilers on the same object path
        else:
            aliases[h] = [key]
            todo.append((key, src, flags, h))
    if not todo:
        record_build(AUTO, 'candidate', 'cached', requested=len(jobs), cached=len(out), compile_jobs=0, tag=tag)
        return out
    t0 = time.time()
    buf = io.BytesIO()
    plan = dict(compile=[], pack='newobjs.tgz')
    with tarfile.open(fileobj=buf, mode='w:gz', compresslevel=1) as tar:
        for rel in ('include/macro.inc', 'tools/elfobj.py', 'tools/assembler.py'):
            tar.add(ROOT / rel, arcname=rel)
        for rel, data in sorted(headers.items()):
            item = tarfile.TarInfo(rel)
            item.size = len(data)
            tar.addfile(item, io.BytesIO(data))
        for key, src, flags, h in todo:
            data = src.encode()
            ti = tarfile.TarInfo('src/%s.c' % h)
            ti.size = len(data)
            tar.addfile(ti, io.BytesIO(data))
            cc, fl = split_cc(flags)
            plan['compile'].append(dict(src='src/%s.c' % h, obj='obj/%s.o' % h, compiler=cc,
                                        args=fl + (['-Iinclude'] if cc.startswith('mwcps2-') else ['-I', 'include']), timeout=30))
    d = AUTO / ('job-%d' % os.getpid())          # one directory per process: several runs may share the build backend
    d.mkdir(exist_ok=True)
    (d / 'inputs.tgz').write_bytes(buf.getvalue())
    (d / 'plan.json').write_text(json.dumps(plan))
    for n in ('newobjs.tgz', 'results.json'):
        (d / n).unlink(missing_ok=True)
    call_id = record_build(AUTO, 'candidate', 'submitted', requested=len(jobs), cached=len(out), compile_jobs=len(todo), tag=tag)
    r = subprocess.run([sys.executable, str(ROOT / 'tools/sandbox.py'), str(ROOT / 'tools/build_job.py'), '--timeout', '1800',
                        '--file', 'inputs.tgz=' + str(d / 'inputs.tgz'), '--file', 'plan.json=' + str(d / 'plan.json'),
                        '--out', 'newobjs.tgz=' + str(d / 'newobjs.tgz'), '--out', 'results.json=' + str(d / 'results.json')],
                       capture_output=True, text=True)
    record_build(AUTO, 'candidate', 'completed', call_id, worker_rc=r.returncode,
                 elapsed_seconds=time.time() - t0, has_results=(d / 'results.json').exists())
    if not (d / 'results.json').exists():
        sys.stderr.write(r.stdout[-2000:] + r.stderr[-2000:])
        raise SystemExit('Build backend failed; run tools/toolchain.py check (or see the backend plugin named in .local/config.json).')
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
        for alias in aliases[h]:
            out[alias] = (res['rc'], msg, obj)
    STATS['compiles'] += len(todo)
    STATS['compile_calls'] += 1
    STATS['compile_seconds'] += time.time() - t0
    return out


STATS = collections.Counter()
PRELUDE_HASH = hashlib.sha256(b''.join(p.read_bytes() for p in (ROOT / 'include/ps2/prelude.h', TYPES_HEADER, HEADER) if p.exists())).hexdigest()


# ---------------------------------------------------------------------------------------------------------- scoring
HI, LO, GP, LITERAL, J26 = 5, 6, 7, 8, 4
KIND = {HI: 'hi', LO: 'lo', GP: 'gprel', LITERAL: 'gprel', J26: 'jal'}
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

    def literal_match(self, index, token):
        """A compiler may resolve an absolute address without emitting a relocation.

        Compare the complete original instruction, including its encoded immediate;
        do not infer HI16 carry rules or forgive an unresolved symbolic target.
        """
        relocation = self.fn['rel'].get(str(index))
        return bool(relocation and relocation[0] in ('hi', 'lo') and isinstance(relocation[1], int)
                    and token == (self.fn['words'][index], None))


class CompiledTokens(list):
    """Score tokens with optional, strictly resolved HI16/LO16 instruction words."""
    def __init__(self):
        super().__init__()
        self.resolved_words = {}


def source_symbol_address(elf, symbol, kind, bindings, section_bindings):
    """Resolve only named image symbols or explicitly placed source sections.

    Local MIPS GPREL and LITERAL addends include minus the object's GP0. Its
    .reginfo value must be restored for section symbols; external symbol GP
    relocations already use the ordinary named-symbol convention.
    """
    name = symbol.get('name', '')
    image = ADDRNAME.match(name) if name else None
    if image:
        return int(image.group(1), 16)
    if name in bindings:
        return bindings[name]
    index = symbol.get('shndx', 0)
    if symbol.get('type') != 3 or not 0 < index < len(elf.sections):
        return None
    section = elf.sections[index]
    base = section_bindings.get(section['name'])
    if base is None:
        return None
    base += symbol.get('value', 0)
    if kind in (GP, LITERAL):
        reginfo = elf.section('.reginfo')
        if reginfo is None or reginfo['size'] < 24:
            return None
        base += struct.unpack_from('<i', elf.content(reginfo), 20)[0]
    return base


def resolved_address_words(code, relocations, bindings, symbol_address=None):
    """Resolve known address operands for comparison only, following MIPS REL pairing.

    A retail LUI can serve several addresses without its own inferred relocation.
    Its complete encoded word is still a valid comparison when the object's
    symbol address and HI16/LO16 addend are both known. No object bytes change.
    Unknown symbols, unsupported relocations and unpaired HI16s stay unresolved.
    """
    pending, resolved = {}, {}
    for offset, (kind, symbol) in relocations.items():
        if kind not in (HI, LO):
            continue
        name = symbol.get('name', '')
        address_name = ADDRNAME.match(name) if name else None
        address = (symbol_address(symbol, kind) if symbol_address else
                   int(address_name.group(1), 16) if address_name else bindings.get(name))
        if not isinstance(address, int):
            continue
        word = struct.unpack_from('<I', code, offset)[0]
        # Symbols are the same table objects at both relocation sites. Do not
        # pair distinct aliases just because they happen to resolve equally.
        key = id(symbol)
        if kind == HI:
            pending.setdefault(key, []).append((offset, word))
        else:
            low = s16(word)
            resolved[offset] = (word & 0xFFFF0000) | ((address + low) & 0xFFFF)
            for high_offset, high_word in pending.pop(key, []):
                addend = ((high_word & 0xFFFF) << 16) + low
                encoded = ((address + addend + 0x8000) >> 16) & 0xFFFF
                resolved[high_offset] = (high_word & 0xFFFF0000) | encoded
    return resolved


def resolved_address_match(target, index, tokens):
    """Accept exact encoded instructions only; never forgive an unknown target."""
    word = getattr(tokens, 'resolved_words', {}).get(index)
    relocation = target.fn['rel'].get(str(index))
    return (word is not None and (not relocation or
            relocation[0] in ('hi', 'lo') and isinstance(relocation[1], int))
            and word == target.fn['words'][index])


def compiled_tokens(obj_bytes, symbol, consts=None, bindings=None, section_bindings=None):
    """Tokens of `symbol`'s code, or (None, reason).

    section_bindings optionally maps verified source input-section names to
    their final image bases. It never infers placement from zero/constant data.
    """
    e = Elf(obj_bytes)
    syms = e.symbols()
    bindings = bindings or {}
    section_bindings = section_bindings or {}
    def symbol_address(entry, kind):
        return source_symbol_address(e, entry, kind, bindings, section_bindings)
    fs = next((s for s in syms if s['name'] == symbol and 0 < s['shndx'] < len(e.sections)
               and (e.sections[s['shndx']]['name'] == '.text'
                    or e.sections[s['shndx']]['name'].startswith('.text.'))), None)
    if fs is None:
        return None, 'function symbol missing'
    text = e.sections[fs['shndx']]
    code = e.content(text)
    start, size = fs['value'], fs['size']
    rels = {}
    for t in e.sections:
        if t['type'] == 9 and t['info'] == text['index']:
            c = e.content(t)
            for o in range(0, len(c), 8):
                off, info = struct.unpack_from('<II', c, o)
                rels[off] = (info & 255, syms[info >> 8])
    toks = CompiledTokens()
    resolved = resolved_address_words(code, rels, bindings, symbol_address)
    toks.resolved_words = {(offset - start) // 4: word for offset, word in resolved.items()
                           if start <= offset < start + size}
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
        base = symbol_address(y, kind)
        if y['shndx'] not in (0, 0xFFF1, 0xFFF2) and base is None:
            # symbol defined in the compiled unit itself (a constant it brought along): compare the bytes it points at
            sec = e.sections[y['shndx']]
            where = y['value'] + add
            from constant_relocs import constant_word
            image = ADDRNAME.match(symbol)
            word = constant_word(e, syms, sec, where, fs,
                                 int(image.group(1), 16) if image else bindings.get(symbol))
            value = word.hex() if word is not None else 'unresolved-constant-relocation'
            toks.append((masked, (k, ('const', sec['name'], value))))
            continue
        if base is not None:
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
        d = sum(0 if same(a, b) or target.literal_match(i, b)
                or resolved_address_match(target, i, toks) else 1
                for i, (a, b) in enumerate(zip(want, toks)))
        if d == 0:
            return True, 0, ''

        def op(t):
            w = t[0]
            return (w >> 26, w & 0x3F if w >> 26 == 0 else 0)
        if [op(t) for t in want] == [op(t) for t in toks]:
            kind = 'operands'           # identical opcodes do not distinguish registers from wrong immediates/types
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
        self.e = Elf((ROOT / 'orig' / SLUG / 'SLUS_213.76').read_bytes())
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


SONY = 'ee-gcc2.9-991111-01'
_TUMAP = None


def tu_flags(addr):
    """(compiler, flags, basis) the TU map (config/tus.yaml) gives the TU of this function, or None. Used when the environment
    variable AUTODECOMP_TU is set; see tools/tus.py."""
    global _TUMAP
    if not os.environ.get('AUTODECOMP_TU'):
        return None
    if _TUMAP is None:
        import bisect, yaml
        d = yaml.safe_load((ROOT / 'config/tus.yaml').read_text())
        rows = sorted((int(t['text'][0], 16), int(t['text'][1], 16), t['compiler'], t['flags'], t['flags_basis']) for t in d['tus'])
        _TUMAP = (rows, [r[0] for r in rows])
    import bisect
    rows, starts = _TUMAP
    k = bisect.bisect_right(starts, addr) - 1
    if k >= 0 and rows[k][0] <= addr < rows[k][1]:
        return rows[k][2:]
    return None


SNAS_OK = ('ee-gcc2.95.2-273a', 'ee-gcc2.95.3-114', 'ee-gcc2.95.3-136')       # builds whose driver accepts -snas


def force_cc(flag_sets):
    """Experiments (run --cc NAME): the same flag sets with another compiler."""
    cc = os.environ.get('AUTODECOMP_CC')
    if not cc:
        return flag_sets
    return [['--cc=' + cc] + [x for x in fl if x != '-snas' or cc in SNAS_OK] for fl in flag_sets]


def variants_for(fn):
    return vu0_flags(fn, force_cc(variants_for_sn(fn)))


def vu0_flags(fn, sets):
    """Record the VU register option in recipes as well as worker invocations."""
    if not os.environ.get('AUTODECOMP_VU0') or not any(
            mnemonic.startswith(('v', 'lqc2', 'sqc2', 'qmtc2', 'qmfc2'))
            for mnemonic in fn['mnem']):
        return sets
    return [flags if '-mvu0-use-vf0-vf31' in flags else
            flags + ['-mvu0-use-vf0-vf31'] for flags in sets]


def variants_for_sn(fn):
    """Flag sets tried in order. -G8 only when the original addresses small data through $gp."""
    uses_gp = any(v[0] == 'gprel' for v in fn['rel'].values())
    tf = tu_flags(fn['addr'])
    if tf and tf[0] != COMPILER:                      # another compiler: its flags only (no -snas)
        base = ['--cc=' + tf[0]] + [x for x in tf[1] if x != '-snas']
        return [base] + ([['--cc=' + tf[0], '-O2', '-G8']] if uses_gp else [])
    first = [BASE_FLAGS] if not uses_gp else [BASE_FLAGS, ['-O2', '-G8', '-snas']]
    if tf and tf[2].startswith(('matched', 'override')) and tf[1] not in first:
        first = [tf[1]] + first                       # the flags that matched the TU's other functions go first
    return first


EXTRA_FLAG_SETS = [['-O1', '-G0', '-snas'], ['-O3', '-G0', '-snas'], ['-Os', '-G0', '-snas'], ['-O2', '-G0', '-snas', '-fbyte-bool'],
                   ['-O2', '-G8', '-snas'], ['-O2', '-G0', '-snas', '-fno-peephole'], ['-O2', '-G0', '-snas', '-fno-schedule-insns2'],
                   ['-O2', '-G0', '-snas', '-fno-schedule-insns'],
                   ['-O2', '-G0', '-snas', '-fno-optimize-sibling-calls']]
SONY_EXTRA = [['--cc=' + SONY] + f for f in (['-O1', '-G0'], ['-O3', '-G0'], ['-Os', '-G0'], ['-O2', '-G8'], ['-O2', '-G0', '-fno-peephole'],
                                                 ['-O2', '-G0', '-fno-schedule-insns2'], ['-O2', '-G0', '-fno-schedule-insns'], ['-O0', '-G0'])]


def extra_sets(fn):
    from assembler import FALLBACKS
    # A recovered TU recipe may already select an assembler. Each fallback
    # replaces that selection; two --assembler options invalidate the job.
    assembler_base = [flag for flag in variants_for_sn(fn)[0]
                      if not flag.startswith('--assembler=')]
    assembler_sets = [assembler_base + ['--assembler=' + choice] for choice in FALLBACKS]
    tf = tu_flags(fn['addr'])
    if tf and tf[0] != COMPILER:
        return vu0_flags(fn, force_cc(SONY_EXTRA + assembler_sets))
    # The bundled GNU assembler and SN assembler differ on short-loop/hazard
    # padding. Both have full-image-verified matches; try both rather
    # than treating an assembler NOP difference as an unfixable C mismatch.
    sets = EXTRA_FLAG_SETS + [['-O2', '-G0'], ['-O2', '-G0', '-fbyte-bool'], ['-Os', '-G0'],
                              ['-O2', '-G0', '-fno-schedule-insns']]
    sets += assembler_sets
    if any(value[0] == 'gprel' for value in fn['rel'].values()):
        sets += [['-O2', flag] + extra for flag in ('-G1', '-G8')
                 for extra in ([], ['-fbyte-bool'])]
    return vu0_flags(fn, force_cc(sets))


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
        from stack_context import detect_frame_size
        frame = detect_frame_size(f['words']) if src is None and note.startswith('stack-object') else None
        if frame is not None:
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
            if f['name'] in srcs and (b is None or not b[2]):
                for k, flags in enumerate(extra_sets(f)):
                    if b is None and not any(x.startswith('--assembler=') for x in flags):
                        continue
                    if flags not in variants_for(f):
                        candidate = b[5] if b else srcs[f['name']]
                        jobs.append(((f['name'], 100 + k), candidate, flags))
                        srcof[(f['name'], 100 + k)] = candidate
        res2 = {}
        for i in range(0, len(jobs), 400):
            res2.update(worker_compile(jobs[i:i + 400]))
        for (name, k), res in res2.items():
            consider(byname[name], k, extra_sets(byname[name])[k - 100], res)
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


def strip_c_comments(text):
    """Remove parser-unsupported comments while preserving literals and token boundaries."""
    tokens = r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*'
    return re.sub(tokens, lambda m: (' ' + '\n' * m[0].count('\n'))
                  if m[0].startswith(('/*', '//')) else m[0], text, flags=re.S)


def expand_macros(src):
    """Self-contained C for the permuter's parser: inline the prelude's typedefs and expand its macros."""
    prelude = (ROOT / 'include/ps2/prelude.h').read_text()
    types = '\n'.join(l for l in prelude.split('\n') if l.startswith('typedef'))
    body = src.replace('#include "ps2/prelude.h"\n', '')
    for view in re.findall(r'^#include "(\w+/layouts/Recovered_\w+\.h)"$', body, re.M):
        header = (ROOT / 'include' / view).read_text()
        layout = '\n'.join(line for line in header.splitlines() if not line.startswith('#') and not line.startswith('typedef char assert_'))
        body = body.replace('#include "%s"' % view, layout)
    if '#include "ps2/recovered_types.h"' in body or '#include "ps2/prototypes.h"' in body:
        names = re.findall(r'^typedef struct (\w+)', TYPES_HEADER.read_text(), re.M)
        if any(re.search(r'\b%s\b' % n, body) for n in names):
            raise ValueError('uses a recovered structure: the permuter\'s parser does not read the header')
        body = body.replace('#include "ps2/recovered_types.h"\n', '').replace('#include "ps2/prototypes.h"\n', '')

    body = strip_c_comments(types + '\n' + body)

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
            out.append(make([call(a.strip(), name, make) for a in args]))
            i = k + 1
    body = call(body, 'M2C_FIELD', lambda a: '(*(%s)((s8 *)(%s) + (%s)))' % (a[1], a[0], a[2]))
    body = call(body, 'M2C_BITWISE', lambda a: '((%s)(%s))' % (a[0], a[1]))
    return body.replace('NULL', '((void *)0)')


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
    together (permute_many), so the backend's per-call latency is shared."""
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
        first_error = None
        for i in range(k):
            try:
                c = Candidate.from_source(self.src, EvalState(), self.f['name'], self.weights, rng_seed=self.rnd.randrange(1, 10 ** 12))
                for _ in range(self.rnd.choice((1, 1, 2, 3))):
                    c.randomize_ast()
                self.cands[i] = c.get_source()
            except Exception as error:
                if first_error is None:
                    first_error = error
                continue
        if k and not self.cands:
            raise RuntimeError('Permuter generated no candidates for %s: %s' %
                               (self.f['name'], first_error)) from first_error
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
    text = re.sub(r'(?m)^\s*typedef\s+struct\s*\{\s*s64\s+v;\s*\}\s*__attribute__\(\(packed\)\)\s*M2C_U64;', '', text)
    # Only complete declarations of the shared prelude's aliases may disappear.
    # A user typedef can span many lines; dropping just its first line corrupts
    # recovered structs. Restoring the prelude also restores SN's mode(TI) widths
    # if the C parser printed its s128/u128 placeholders as ordinary int types.
    aliases = 's8|u8|s16|u16|s32|u32|s64|u64|s128|u128|f32|f64|M2C_UNK|M2C_UNK8|M2C_UNK16|M2C_UNK32|M2C_UNK64'
    shared = re.compile(r'\s*typedef\s+[^;{}]+\b(?:' + aliases + r')\s*(?:__attribute__\(\(.*\)\))?\s*;\s*$')
    lines = text.split('\n')
    i = 0
    while i < len(lines) and (shared.fullmatch(lines[i]) or not lines[i].strip() or lines[i].startswith('#pragma _permuter')):
        i += 1
    body = '\n'.join(l for l in lines[i:] if not l.startswith('#pragma _permuter'))
    body = re.sub(r'\*\(\((\w+ \*)\) \(\(\(s8 \*\) (\w+)\) \+ (0x[0-9A-Fa-f]+|\d+)\)\)', r'M2C_FIELD(\2, \1, \3)', body)
    body = body.replace('((void *) 0)', 'NULL')
    return '#include "ps2/prelude.h"\n#include "ps2/prototypes.h"\n\n' + body.strip() + '\n'


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
    sets = [flags] if flags else variants_for(f) + [x for x in extra_sets(f) if x not in variants_for(f)]
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
    text = (FUNCTION_ASM / (f['name'] + '.s')).read_text().split('\n')
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
    for lo, hi in ((0, 12), (12, 24), (24, 48), (48, 100), (100, 200), (200, 300), (300, 1000), (1000, 1000000)):
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
    """Put every exact draft that is not registered yet into its translation unit file, replacing the function's INCLUDE_ASM
    line (tools/tu_files.py); a function whose compiler flags differ from its file's, or that failed in a group, gets a small
    file of its own with an entry in config/SLUS_213.76/splits.yaml."""
    sys.path.insert(0, str(ROOT / 'tools'))
    from units import load_units
    import tu_files
    res = load_results()
    units = load_units(variant=SLUG)
    have = {f['addr'] for u in units for f in u['functions'] if f.get('status') == 'source'}
    todo = sorted((int(k, 16), v) for k, v in res.items()
                  if v['status'] == 'matched' and 'registered' not in v and int(k, 16) not in have and 'source' in v)
    if a.limit:
        todo = todo[:a.limit]
    done = 0
    for addr, rec in todo:
        decls, body = split_source(rec)
        names = {rec['name']}
        decls = [l for l in decls if decl_name(l) not in names]
        cc, fl = split_cc(rec['flags'])
        try:
            record = tu_files.add_function(addr, body, decls, cc, fl, symbol=rec['name'], single=bool(rec.get('single')))
        except (KeyError, StopIteration) as error:
            rec['status'], rec['reason'] = 'verify-failed', 'no INCLUDE_ASM line (%s)' % error
            continue
        rec['registered'] = record['path']
        rec['registration'] = {k: v for k, v in record.items() if k != 'code'} | dict(code=record['code'])
        done += 1
    save_results(res)
    print('registered %d functions' % done)


def cmd_settle(a):
    """Compile and link what `register` wrote (the build backend), put the INCLUDE_ASM line back for every function that does not
    place identically (a file that fails to compile takes its new functions back out, to be retried one per file), and end
    with a build that says OK."""
    sys.path.insert(0, str(ROOT / 'tools'))
    import tu_files
    for rnd in range(3):
        res = load_results()
        fresh = {k: v for k, v in res.items() if v.get('registration') and not v.get('settled')}
        if not fresh:
            break
        problems = verify_build()
        bad = {}
        for unit, addr, reason in problems:
            bad.setdefault(addr, reason)
        by_file = {}
        for k, v in fresh.items():
            by_file.setdefault(v['registration']['path'], []).append(k)
        retry = 0
        for path, keys in by_file.items():
            file_bad = [k for k in keys if int(k, 16) in bad or None in bad]
            whole_file = None in bad and not file_bad
            if not file_bad and not whole_file:
                for k in keys:
                    res[k]['settled'] = True
                continue
            for k in keys:                              # a failure in one function takes the whole object down: back out all
                rec = res[k]
                tu_files.revert_function(rec['registration'])
                rec.pop('registered', None)
                rec.pop('registration', None)
                if len(keys) == 1 or rec.get('single'):
                    rec['status'], rec['reason'] = 'verify-failed', bad.get(int(k, 16), 'compile')
                else:
                    rec['single'] = True               # try each alone, in a file of its own
                    retry += 1
        save_results(res)
        if not retry:
            break
        print('retrying %d functions in files of their own' % retry)
        cmd_register(argparse.Namespace(group=a.group, limit=None))
    r = subprocess.run(['ninja'], cwd=ROOT, capture_output=True, text=True)
    if r.returncode:
        sys.stderr.write(r.stdout + r.stderr)
        raise SystemExit('Final identical build failed.')
    print(r.stdout.strip().split('\n')[-1])


def verify_build():
    """[(unit name, address or None, reason)] of what the current sources do not place identically (never raises on those)."""
    def run(*args):
        r = subprocess.run([sys.executable] + [str(x) for x in args], cwd=ROOT, capture_output=True, text=True)
        if any(m in r.stdout + r.stderr for m in ('Build backend failed', 'Connection refused')):
            raise SystemExit(r.stdout + r.stderr)
        return r
    run('tools/units.py', SLUG)
    run('tools/split_objects.py', SLUG)
    run('tools/make_ld.py', SLUG)
    c = run('tools/build_objects.py', SLUG, '--compile-only')
    if c.returncode and not (BUILD / 'results.json').exists():
        raise SystemExit(c.stdout + c.stderr)
    run('tools/units_verify.py', 'prepare')
    problems = json.loads((BUILD / 'unit_problems.json').read_text())
    if problems:
        return problems
    run('tools/make_ld.py', SLUG)
    link = run('tools/build_objects.py', SLUG)
    if link.returncode:
        run('tools/units_verify.py', 'link')
        return json.loads((BUILD / 'unit_problems.json').read_text()) or [[None, None, 'link']]
    run('tools/pack_elf.py', BUILD / 'linked.elf', ROOT / 'config' / SLUG / 'layout.json', ROOT / 'data' / SLUG / 'elf',
        BUILD / (json.loads((ROOT / 'config/variants.json').read_text())[SLUG]['boot'] + '.elf'))
    run('tools/units_verify.py', 'compare')
    return json.loads((BUILD / 'unit_problems.json').read_text())


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
                   and 's128' not in v['source'] and 'permuter' not in v and (a.max_size is None or v['size'] < a.max_size)
                   and (not a.cc or ('--cc=' + a.cc) in v.get('flags', []))))
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


RANK = {'matched': 0, 'verify-failed': 0, 'near': 1, 'mismatch': 2, 'compile-failed': 3, 'm2c-failed': 4, 'fragment': 5, 'orphan': 6}


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
    """Records of functions that are compiled from source now say so (the TU files and the split list are the truth)."""
    from units import load_units
    n = 0
    live = {'0x%x' % f['addr'] for f in load_inventory()}
    for k in [k for k in res if k not in live]:          # a boundary repair removed this start
        res.pop(k)
    for u in load_units(variant=SLUG):
        for f in u['functions']:
            rec = res.get('0x%x' % f['addr'])
            if f.get('status') == 'source' and rec is not None and rec.get('registered') != u['source']:
                rec['status'], rec['registered'] = 'matched', u['source']
                rec.pop('reason', None)
                n += 1
    return n


def cmd_context(a):
    AUTO.mkdir(parents=True, exist_ok=True)
    print('context: %d prototypes' % write_context(refresh=a.refresh))
    write_context_arity(load_inventory())
    print(json.dumps(recovered_context()['summary'], indent=2))


def rescore_saved_record(record, result, function, original):
    """A saved score is valid only with the headers used by this compilation."""
    record = dict(record)
    rc, message, obj = result
    tokens, why = compiled_tokens(obj, function['name']) if rc == 0 and obj else (None, message)
    if tokens is None:
        record.update(status='compile-failed', reason=why or 'saved draft did not compile')
        record.pop('score', None)
        record.pop('note', None)
        return record
    exact, difference, note = score(Target(function, original), tokens, original.word)
    record.update(score=difference, note=note)
    if not (exact and record.get('status') == 'verify-failed'):
        record['status'] = 'matched' if exact else 'near' if difference <= 8 else 'mismatch'
        record.pop('reason', None)
    return record


def cmd_rescore(a):
    """Recompile saved best drafts before comparing them with newly generated candidates."""
    records, original = load_results(), OrigImage()
    inventory, sourced = {f['addr']: f for f in load_inventory()}, source_functions()
    todo = sorted(k for k, r in records.items()
                  if int(k, 16) in inventory and int(k, 16) not in sourced and r.get('source'))
    counts = collections.Counter()
    for offset in range(0, len(todo), a.chunk):
        keys = todo[offset:offset + a.chunk]
        jobs = [(k, records[k]['source'], records[k].get('flags', BASE_FLAGS)) for k in keys]
        results = worker_compile(jobs, tag='saved-context-rescore')
        for key in keys:
            records[key] = rescore_saved_record(records[key], results[key], inventory[int(key, 16)], original)
            counts[records[key]['status']] += 1
        save_results(records)
        print('rescored %d/%d saved drafts: %s' %
              (min(offset + a.chunk, len(todo)), len(todo), dict(counts)), flush=True)


def cmd_run(a):
    AUTO.mkdir(parents=True, exist_ok=True)
    inv = load_inventory()
    print('context: %d prototypes' % write_context(refresh=a.refresh_context))
    write_context_arity(inv)
    done = source_functions()
    sel = [f for f in inv if f['addr'] not in done]
    if a.addr:
        want = {int(x, 16) for x in a.addr}
        sel = [f for f in sel if f['addr'] in want]
    if a.cc:
        os.environ['AUTODECOMP_CC'] = a.cc
    if a.tu:                                                # the TU map's compiler and flags go first (tools/tus.py)
        os.environ['AUTODECOMP_TU'] = '1'
        if a.tu != 'all':
            sel = [f for f in sel if (tu_flags(f['addr']) or (COMPILER,))[0] == a.tu]
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
    if a.redo or 'verify-failed' in (a.status or []):
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
    context = sub.add_parser('context', help='refresh the shared m2c and compile contexts')
    context.add_argument('--refresh', action='store_true')
    context.set_defaults(fn=cmd_context)
    saved = sub.add_parser('rescore', help='revalidate saved scores after shared-header changes')
    saved.add_argument('--chunk', type=int, default=400)
    saved.set_defaults(fn=cmd_rescore)
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
    r.add_argument('--ctx', default='ctx.c', help='m2c context file in build/auto/ (ctx.c, ctx2.c, ctx3.c, ctx_void.c)')
    r.add_argument('--tag', help='name of this m2c variant in the records')
    r.add_argument('--m2c-option', action='append', help='extra m2c option (repeatable), e.g. --m2c-option=--no-andor')
    r.add_argument('--status', action='append', help='redo the functions whose earlier outcome was this')
    r.add_argument('--refresh-context', action='store_true')
    r.add_argument('--cc', help='experiment: compile every flag set with this compiler (use AUTODECOMP_RESULTS to keep the records apart)')
    r.add_argument('--tu', help='use the TU map flags (config/tus.yaml): `all`, or a compiler name to select only the functions of those TUs')
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
    pm.add_argument('--cc', help='only near misses compiled with this compiler (a --cc= flag set)')
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
