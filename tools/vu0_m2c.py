"""Opt-in, conservative semantic VU0 adapter for the local m2c wrapper.

prepare() folds only closed adjacent ACC/Q operations. Partial writes retain an
old destination when any omitted lane is read elsewhere in the function. m2c
then rejects unset old registers instead of inventing W. This global liveness
over-approximation intentionally rejects some valid instruction allocations.
Microcalls, control/flag traffic and unclosed ACC/Q instructions are rejected.
No installed package, assembly output or target bytes are modified.
"""
import re

LINE = re.compile(r'^(\s*(?:/\*.*?\*/\s*)?)([A-Za-z][\w.]*)(?:\s+(.*?))?(\s*(?:#.*)?)$')
VF = re.compile(r'^\$?vf(\d+)([xyzw]?)$')
OPS = {'vadd.xyz': ('add', 'BkVuAddXYZ'), 'vsub.xyz': ('sub', 'BkVuSubXYZ'),
       'vmul.xyz': ('mul', 'BkVuMulXYZ')}
HELPERS = {'add': ('BkVuAddXYZ', 'BkVuLowerAddXYZ'),
           'sub': ('BkVuSubXYZ', 'BkVuLowerSubXYZ'),
           'mul': ('BkVuMulXYZ', 'BkVuLowerMulXYZ'),
           'one': ('BkVuOneX', 'BkVuLowerOneX'),
           'sum': ('BkVuSumXYZ', 'BkVuLowerSumXYZ'),
           'cross': ('BkVuCrossXYZ', 'BkVuLowerCrossXYZ'),
           'normalize': ('BkVuNormalizeXYZ', 'BkVuLowerNormalizeXYZ'),
           'sqrt': ('BkVuSqrtX', 'BkVuLowerSqrtX')}


def _vf(value):
    match = VF.fullmatch(value)
    return '$vf' + match[1] if match else None


def has_vu(text):
    return any(row and (row[1].startswith('v') or row[1].split('.')[0]
                       in {'lqc2', 'sqc2', 'qmtc2', 'qmfc2', 'cfc2', 'ctc2', 'mfc2', 'mtc2'})
               for row in map(_parse, text.splitlines()))


def _parse(line):
    m = LINE.fullmatch(line)
    if not m:
        return None
    operands = tuple(a.strip() for a in (m[3] or '').split(',') if a.strip())
    # splat and Rabbitizer disagree on the dollar prefix of VU specials.
    operands = tuple('$' + a if a in {'ACC', 'Q', 'I', 'R'} else a for a in operands)
    return m[1], m[2].lower(), operands, m[4]


def _base(value):
    return value.rstrip('xyzw') if _vf(value) else value


def _lane_reads(op, args):
    """Conservative register-lane reads for raw VU instructions."""
    reads = []
    if op in {'lqc2', 'qmtc2.ni', 'qmtc2.i'}:
        return reads
    if op in {'sqc2', 'qmfc2.ni', 'qmfc2.i'}:
        reg = args[0] if op == 'sqc2' else args[1]
        return [(reg, set('xyzw'))]
    mask = op.split('.', 1)[1] if '.' in op and set(op.split('.', 1)[1]) <= set('xyzw') else 'xyzw'
    for value in args[1:]:
        m = VF.fullmatch(value)
        if m:
            reads.append(('$vf' + m[1], set(m[2] or mask)))
    return reads


def _prepare(text):
    lines = text.splitlines()
    parsed = [_parse(line) for line in lines]
    # Upstream's scalar stack-variable coalescing cannot represent an overlaid
    # vector and its individual float/word fields. It can print a numeric cast
    # in place of a bit-preserving spill. Leave this as aggregate work.
    stack_quad, stack_scalar = [], []
    for row in parsed:
        if not row or len(row[2]) != 2:
            continue
        memory = re.fullmatch(r'(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$(?:sp|29)\)', row[2][1])
        if not memory:
            continue
        offset = int(memory[1], 0)
        if row[1] in {'lqc2', 'sqc2'}:
            stack_quad.append(offset)
        elif row[1] in {'lw', 'sw', 'lwc1', 'swc1'}:
            stack_scalar.append(offset)
    if any(q <= s < q + 16 for q in stack_quad for s in stack_scalar):
        raise ValueError('VU0 lowering: mixed-width stack overlay needs aggregate modeling')
    reads = {}
    for row in parsed:
        if row:
            if row[1].startswith(('v', 'lqc2')) and row[2] and row[2][0] == '$vf0':
                raise ValueError('VU0 lowering: writes to the constant VF0 register are unsupported')
            if row[1].startswith('qmtc2') and len(row[2]) == 2 and row[2][1] == '$vf0':
                raise ValueError('VU0 lowering: writes to the constant VF0 register are unsupported')
            for reg, lanes in _lane_reads(row[1], row[2]):
                reads.setdefault(reg, set()).update(lanes)
    edits, folded = {}, set()
    wide_gprs = set()
    for row in parsed:
        if row is None:
            continue
        _, op, a, _ = row
        if op in {'qmtc2.ni', 'qmtc2.i'} and len(a) == 2:
            if reads.get(a[1], set()) - {'x'} and a[0] not in wide_gprs:
                raise ValueError('VU0 lowering: full quadword source of qmtc2 is not locally proved')
        if op.startswith('b') or op in {'j', 'jr', 'jal', 'jalr'}:
            wide_gprs.clear()
        elif a and a[0].startswith('$') and not _vf(a[0]):
            if op == 'lq' or op in {'qmfc2.ni', 'qmfc2.i'}:
                wide_gprs.add(a[0])
            elif op == 'por' and len(a) == 3 and '$zero' in a[1:]:
                src = a[2] if a[1] == '$zero' else a[1]
                if src in wide_gprs:
                    wide_gprs.add(a[0])
                else:
                    wide_gprs.discard(a[0])
            elif op not in {'sq', 'sd', 'sw', 'sh', 'sb', 'mtc1', 'sqc2', 'qmtc2.ni', 'qmtc2.i'}:
                wide_gprs.discard(a[0])

    def replace(start, count, family, dest, inputs, written):
        preserve = bool(reads.get(dest, set()) - set(written))
        if '$vf0' in inputs:
            raise ValueError('VU0 lowering: generic vf0 operand is outside the closed operation subset')
        name = 'bkvu_' + family + ('_keep' if preserve else '')
        arguments = [dest] + ([dest] if preserve else []) + list(inputs)
        row = parsed[start]
        edits[start] = row[0] + name + ' ' + ', '.join(arguments) + row[3]
        for j in range(start + 1, start + count):
            old = parsed[j]
            edits[j] = old[0] + 'nop' + old[3] + ' # closed VU operation folded above'
            folded.add(j)
        folded.add(start)

    for n, row in enumerate(parsed):
        if row is None or n in folded:
            continue
        _, op, a, _ = row
        following = parsed[n:n + 7]
        if op in OPS and len(a) == 3 and all(_vf(v) == v for v in a):
            replace(n, 1, OPS[op][0], a[0], a[1:], 'xyz')
        elif op == 'vaddw.x' and len(a) == 3 and a[1:] == ('$vf0', '$vf0w'):
            replace(n, 1, 'one', a[0], (), 'x')
        elif op == 'vopmula.xyz' and len(following) >= 2 and following[1]:
            b = following[1]
            if len(a) == 3 and a[0] == '$ACC' and b[1] == 'vopmsub.xyz' and b[2][1:] == a[:0:-1]:
                replace(n, 2, 'cross', b[2][0], a[1:], 'xyz')
        elif op == 'vadday.x' and len(following) >= 2 and following[1]:
            b = following[1]
            if (len(a) == 3 and a[0] == '$ACC' and a[2] == a[1] + 'y'
                    and b[1] == 'vmaddz.x' and len(b[2]) == 3 and b[2][2] == a[1] + 'z'):
                replace(n, 2, 'sum', b[2][0], (a[1], b[2][1]), 'x')
        elif op == 'vnop' and len(following) >= 6 and all(following[:6]):
            f = following
            if [r[1] for r in f[:3]] != ['vnop'] * 3:
                continue
            if (f[3][1] == 'vrsqrt' and len(f[3][2]) == 3 and f[3][2][:2] == ('$Q', '$vf0w')
                    and f[4][1] == 'vwaitq' and f[5][1] == 'vmulq.xyz' and len(f[5][2]) == 3
                    and f[5][2][2] == '$Q' and f[3][2][2].endswith('x')):
                replace(n, 6, 'normalize', f[5][2][0], (f[5][2][1], _base(f[3][2][2])), 'xyz')
            elif (len(f) >= 7 and f[6] and f[3][1] == 'vsqrt' and len(f[3][2]) == 2
                  and f[3][2][0] == '$Q' and f[3][2][1].endswith('x') and f[4][1] == 'vaddw.x'
                  and len(f[4][2]) == 3 and f[4][2][1:] == ('$vf0', '$vf0w') and f[5][1] == 'vwaitq'
                  and f[6][1] == 'vmulq.x' and f[6][2] == (f[4][2][0], f[4][2][0], '$Q')):
                replace(n, 7, 'sqrt', f[4][2][0], (_base(f[3][2][1]),), 'x')
    for n, row in enumerate(parsed):
        if not row or n in folded:
            continue
        _, op, a, _ = row
        if op in {'lqc2', 'sqc2', 'qmtc2.ni', 'qmfc2.ni', 'qmtc2.i', 'qmfc2.i'}:
            continue
        if op == 'vmove.xyzw' and len(a) == 2:
            edits[n] = row[0] + 'bkvu_move ' + ', '.join(a) + row[3]
            continue
        if op.startswith('v') or op.startswith(('ctc2', 'cfc2', 'bc2', 'mfc2', 'mtc2')):
            raise ValueError('VU0 lowering: unsupported or unclosed operation ' + op)
    return '\n'.join(edits.get(n, line) for n, line in enumerate(lines)) + ('\n' if text.endswith('\n') else '')


def prepare(text, *, strict=False):
    """Return unchanged unsupported inputs so one function cannot kill a batch.

    strict=True is useful for diagnostics/tests; normal m2c emits its existing
    unsupported-instruction failure for an input outside the closed subset.
    """
    try:
        return _prepare(text)
    except ValueError:
        if strict:
            raise
        return text


def install():
    """Install only into this process; idempotent and EE-specific."""
    from m2c.arch_mips import MipseeArch
    if getattr(MipseeArch, '_black_vu0_installed', False):
        return
    from m2c.asm_instruction import Register
    from m2c.evaluate import fn_op
    from m2c.translate import as_type
    from m2c.translate import Cast
    from m2c.types import Type
    old_parse = MipseeArch.parse.__func__
    MipseeArch.all_regs = list(MipseeArch.all_regs) + [Register('vf' + str(n)) for n in range(32)]
    MipseeArch.temp_regs = list(MipseeArch.temp_regs) + [Register('vf' + str(n)) for n in range(32)]
    MipseeArch.instrs_destination_first = dict(MipseeArch.instrs_destination_first)
    old_cast_format = Cast.format

    def cast_format(self, fmt):
        # QMFC2 -> MTC1 is a low-word bit transfer, never a numeric TI->float
        # conversion. Keep the independently controlled integer/FPR recipe.
        if (fmt.valid_syntax and self.reinterpret and self.type.is_float()
                and self.type.get_size_bits() == 32 and not self.expr.type.is_float()
                and self.expr.type.get_size_bits() == 128):
            return '__ee_vu_read_x(%s)' % self.expr.format(fmt)
        return old_cast_format(self, fmt)
    Cast.format = cast_format

    def wide(expr):
        return as_type(expr, Type.reg128(), silent=False)

    for family, names in HELPERS.items():
        for keep, helper in enumerate(names):
            mnemonic = 'bkvu_' + family + ('_keep' if keep else '')

            def evaluate(a, name='__ee_vu_' + family + ('_keep' if keep else '')):
                return fn_op(name, [wide(a.reg(n)) for n in range(1, len(a.raw_args))], Type.reg128())
            MipseeArch.instrs_destination_first[mnemonic] = evaluate
    MipseeArch.instrs_destination_first['bkvu_move'] = lambda a: wide(a.reg(1))

    @classmethod
    def parse(cls, mnemonic, args, meta):
        if mnemonic in {'lqc2', 'sqc2'}:
            return old_parse(cls, 'lq' if mnemonic == 'lqc2' else 'sq', args, meta)
        if mnemonic in {'qmtc2.ni', 'qmtc2.i'}:
            return old_parse(cls, 'bkvu_move', [args[1], args[0]], meta)
        if mnemonic in {'qmfc2.ni', 'qmfc2.i'}:
            return old_parse(cls, 'bkvu_move', args, meta)
        if mnemonic == 'por' and len(args) == 3 and Register('zero') in args[1:]:
            source = args[2] if args[1] == Register('zero') else args[1]
            return old_parse(cls, 'bkvu_move', [args[0], source], meta)
        return old_parse(cls, mnemonic, args, meta)
    MipseeArch.parse = parse
    MipseeArch._black_vu0_installed = True
