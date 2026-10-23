#!/usr/bin/env python3
"""Read-only VU0 shape census; generated instruction/site reports stay in build/.

Raw shapes preserve destination masks, broadcasts, constants, memory offsets and
register equality while alpha-renaming allocatable registers. A projected block
omits CPU instructions, but never crosses a CPU branch/call or its delay slot.
Projection is a search aid, not proof that the omitted CPU instructions commute.
Semantic recognizers require instruction order and register/lane dataflow. They
deliberately leave quaternion/library identity and microprogram contracts open.
"""
import sys as _sys
from pathlib import Path as _Path
_sys.path.insert(0, str(_Path(__file__).resolve().parents[1]))  # the core tools
import argparse
import bisect
import collections
import dataclasses
import hashlib
import json
from pathlib import Path
import re
import time


ROOT = Path(__file__).resolve().parents[2]
REGISTER = re.compile(r'\$(vf\d+|vi\d+|f\d+|[A-Za-z][A-Za-z0-9]*)([xyzw]?)\b')
VECTOR = re.compile(r'^\$vf(\d+)([xyzw]?)$')
LANES = 'xyzw'
TRANSPORT = {'lqc2', 'sqc2', 'qmtc2', 'qmfc2', 'mfc2', 'mtc2', 'cfc2', 'ctc2'}
SPECIAL = {'ACC', 'Q', 'I', 'R', 'STATUS', 'MAC', 'CLIP'}
KEEP_REGS = {'vf0', 'vi0', 'zero', 'sp', 'gp', 'ra'} | SPECIAL


@dataclasses.dataclass(frozen=True)
class Instruction:
    address: int
    opcode: str
    operands: tuple
    text: str
    control: bool = False
    target: int | None = None

    @property
    def root(self):
        return self.opcode.split('.')[0]

    @property
    def mask(self):
        suffix = self.opcode.split('.', 1)[1] if '.' in self.opcode else ''
        return suffix if suffix and set(suffix) <= set(LANES) else ''

    @property
    def vu(self):
        return self.root.startswith('v') or self.root in TRANSPORT


def parse_instruction(text, address=0, control=None, target=None):
    """Parse authored disassembly too, allowing byte-free unit tests."""
    text = text.split('#', 1)[0].strip()
    pieces = text.split(None, 1)
    opcode = pieces[0].lower()
    operands = tuple(x.strip() for x in pieces[1].split(',')) if len(pieces) > 1 else ()
    if control is None:
        control = (opcode.startswith('b') or opcode in {'j', 'jal', 'jr', 'jalr', 'eret'})
    return Instruction(address, opcode, operands, text, control, target)


def vector(operand):
    m = VECTOR.fullmatch(operand)
    return (int(m[1]), m[2]) if m else None


def register_effects(ins):
    """Conservative lane reads/writes, including implicit VU architectural state.

    STATUS/MAC are conservatively marked as potentially produced by arithmetic,
    not as proven live clobbers. Unknown microprogram state remains unknown.
    """
    reads, writes = set(), set()
    root = ins.root
    if root.startswith('vcallms'):
        return {'microprogram inputs: unknown'}, {'microprogram clobbers: unknown'}
    operands = ins.operands
    dest = None
    if operands and root not in {'sqc2', 'vwaitq', 'vnop', 'vclipw'}:
        dest = 1 if root in {'qmtc2', 'mtc2', 'ctc2'} else 0
    for index, operand in enumerate(operands):
        v = vector(operand)
        values = set()
        if v:
            number, broadcast = v
            lanes = broadcast or ins.mask or LANES
            values = {f'vf{number}.{lane}' for lane in lanes if lane in LANES}
        elif operand.startswith('$') and operand[1:] in SPECIAL:
            values = {operand[1:]}
        else:
            values = {m[1] for m in REGISTER.finditer(operand)}
        # The address base is always read, including a load destination operand.
        if index == dest and '(' not in operand:
            writes.update(values)
        else:
            reads.update(values)
    if root.startswith(('vmadd', 'vmsub', 'vopmsub')):
        reads.add('ACC')
    if root.endswith('a') or root in {'vopmula'} or re.match(r'^v(?:madd|msub|mul|add|sub)a[xyzw]$', root):
        writes.add('ACC')
    if root in {'vdiv', 'vsqrt', 'vrsqrt'}:
        writes.update({'Q', 'STATUS'})
    elif root == 'vwaitq':
        reads.add('Q')
    elif root.startswith('v') and root not in {'vnop', 'vmove', 'vmr32'}:
        writes.update({'STATUS', 'MAC'})
    if root == 'vclipw':
        reads.add('CLIP')
        writes.add('CLIP')
    if root in {'vrnext', 'vrxor'}:
        reads.add('R')
        writes.add('R')
    # Partial writes preserve the other destination lanes, an important source
    # convention for xyz operations on a stored four-lane value.
    if operands and dest is not None and vector(operands[dest]) and ins.mask:
        number, _ = vector(operands[dest])
        reads.update(f'vf{number}.{lane}' for lane in LANES if lane not in ins.mask)
    return reads, writes


def normalize(instructions):
    names = {}
    counts = collections.Counter()

    def rename(match):
        register, suffix = match.groups()
        if register in KEEP_REGS or (register.startswith('vi') and register[2:].isdigit() and int(register[2:]) >= 16):
            return '$' + register + suffix
        kind = 'vf' if register.startswith('vf') else 'vi' if register.startswith('vi') else 'f' if re.fullmatch(r'f\d+', register) else 'g'
        if register not in names:
            names[register] = f'{kind}n{counts[kind]}'
            counts[kind] += 1
        return '$' + names[register] + suffix

    return tuple(ins.opcode + (' ' + ','.join(REGISTER.sub(rename, op) for op in ins.operands) if ins.operands else '')
                 for ins in instructions)


def blocks(instructions, projected=False):
    """Separate basic straight-line regions, including branch targets/delay slots.

    A VU instruction in a CPU delay slot is emitted as its own block, never
    attached to the before/after path. Local branch targets also split blocks.
    """
    targets = {i.target for i in instructions if i.target is not None}
    result, current = [], []
    delay = False

    def flush():
        nonlocal current
        if current:
            result.append(current)
            current = []

    for ins in instructions:
        if ins.address in targets:
            flush()
        if delay:
            flush()
            if ins.vu:
                result.append([ins])
            delay = False
            continue
        if ins.control:
            flush()
            delay = True
        elif ins.vu:
            current.append(ins)
        elif not projected:
            flush()
    flush()
    return result


def nonoverlapping(occurrences):
    """Greedy interval scheduling per function; adjacent repetitions are distinct."""
    chosen, last = [], {}
    for row in sorted(occurrences, key=lambda r: (r['function'], r['end'], r['start'])):
        if row['start'] >= last.get(row['function'], -1):
            chosen.append(row)
            last[row['function']] = row['end']
    return chosen


def architectural_state(instructions):
    """Potential architectural-state dependencies; never guessed liveness/ABI."""
    inputs, produced = set(), set()
    for ins in instructions:
        reads, writes = register_effects(ins)
        relevant = SPECIAL | {f'vi{n}' for n in range(16, 32)}
        inputs.update((reads & relevant) - produced)
        produced.update(writes & relevant)
    return dict(inputs=sorted(inputs), possible_writes=sorted(produced),
                unknown_microprogram_state=any(i.root.startswith('vcallms') for i in instructions),
                qualification='conservative state effects; fixed control-register numbers retained')


def _reg(op):
    v = vector(op)
    return v[0] if v else None


def _lane(op, lane):
    v = vector(op)
    return v is not None and v[1] == lane


def semantic_operations(block):
    """Return operation evidence; strict names require confirmed local dataflow.

    Pair/triple recognizers can skip only transport/vnop, and a skipped load to
    a participating register rejects the sequence. Other arithmetic is retained.
    Dot3 recognition requires the multiply-add coefficient's x lane to be one.
    """
    arithmetic = [i for i in block if i.root not in TRANSPORT and i.root not in {'vnop', 'vwaitq'}]
    constants = {(0, 'x'): 0, (0, 'y'): 0, (0, 'z'): 0, (0, 'w'): 1}
    known = {}
    for ins in block:
        known[ins.address] = dict(constants)
        _, writes = register_effects(ins)
        for value in writes:
            m = re.fullmatch(r'vf(\d+)\.([xyzw])', value)
            if m:
                constants.pop((int(m[1]), m[2]), None)
        if ins.operands and vector(ins.operands[0]) and ins.root not in {'sqc2', 'vclipw'}:
            dest = _reg(ins.operands[0])
            if ins.root == 'vaddw' and ins.operands[1:] == ('$vf0', '$vf0w'):
                for lane in ins.mask:
                    constants[dest, lane] = 1 if lane != 'w' else 2
    operations = []

    def emit(family, seq, proof, verified=True):
        begin, end = seq[0].address, seq[-1].address + 4
        used = {m[1] for i in seq for op in i.operands for m in REGISTER.finditer(op) if m[1].startswith('vf')}
        selected = {i.address for i in seq}
        for gap in block:
            if begin < gap.address < end and gap.address not in selected:
                _, writes = register_effects(gap)
                if any(value.split('.')[0] in used for value in writes):
                    return
        operations.append(dict(family=family, start=begin, end=end, instruction_addresses=[i.address for i in seq],
                               proof=proof, verified_dataflow=verified))

    for n, ins in enumerate(arithmetic):
        seq = arithmetic[n:n + 4]
        root, ops = ins.root, ins.operands
        quat = arithmetic[n:n + 9]
        if root == 'vmul' and ins.mask == 'xyzw' and len(quat) == 9:
            product, suby, subz, subx, crossa, crossb, aw, bw, finish = quat
            temporary, a, b = ops
            output = subx.operands[0] if subx.operands else None
            if (suby.opcode == 'vsubay.w' and suby.operands == ('$ACC', temporary, temporary + 'y')
                    and subz.opcode == 'vmsubaz.w' and subz.operands == ('$ACC', '$vf0', temporary + 'z')
                    and subx.opcode == 'vmsubx.w' and subx.operands == (output, '$vf0', temporary + 'x')
                    and crossa.opcode == 'vopmula.xyz' and crossa.operands == ('$ACC', a, b)
                    and crossb.opcode == 'vopmsub.xyz' and crossb.operands == (output, b, a)
                    and aw.opcode == 'vmulaw.xyz' and aw.operands == ('$ACC', b, a + 'w')
                    and bw.opcode == 'vmaddaw.xyz' and bw.operands == ('$ACC', a, b + 'w')
                    and finish.opcode == 'vmaddw.xyz' and finish.operands == (output, output, '$vf0w')):
                emit('quaternion-product', quat,
                     'w=aw*bw-dot(a.xyz,b.xyz); xyz=cross(a,b)+aw*b.xyz+bw*a.xyz; output w preserved')
        if root in {'vadd', 'vsub', 'vmul'} and len(ops) == 3:
            emit({'vadd': 'vector-add', 'vsub': 'vector-subtract', 'vmul': 'lane-multiply'}[root], [ins], 'lane-wise arithmetic')
        elif re.fullmatch(r'vmul[xyzwq]', root):
            emit('vector-scale', [ins], 'broadcast scalar or Q multiply')
        if root == 'vopmula' and len(seq) >= 2:
            other = seq[1]
            if other.root == 'vopmsub' and ins.mask == other.mask == 'xyz' and ops[1:] == other.operands[:0:-1]:
                emit('cross3', seq[:2], 'outer-product ACC then reversed-product subtraction')
        if root == 'vmul' and ins.mask == 'xyz' and len(seq) >= 3:
            add, madd = seq[1:3]
            product = _reg(ops[0])
            if (add.root == 'vadday' and add.mask == 'x' and len(add.operands) == 3
                    and add.operands[0] == '$ACC' and _reg(add.operands[1]) == product
                    and _reg(add.operands[2]) == product and _lane(add.operands[2], 'y')
                    and madd.root == 'vmaddz' and madd.mask == 'x' and len(madd.operands) == 3
                    and _reg(madd.operands[2]) == product and _lane(madd.operands[2], 'z')):
                one = known[madd.address].get((_reg(madd.operands[1]), 'x')) == 1
                square = ops[1] == ops[2]
                family = ('squared-length3' if square else 'dot3') if one else 'dot3-reduction-candidate'
                emit(family, seq[:3], 'products; x+y into ACC; z times locally proved one' if one else 'multiply-add coefficient not locally proved one', one)
        if root == 'vmulax' and len(seq) == 4:
            a, b, c, d = seq
            masks = {i.mask for i in seq}
            if (b.root == 'vmadday' and c.root == 'vmaddaz' and d.root == 'vmaddw'
                    and len(masks) == 1 and a.operands[0] == b.operands[0] == c.operands[0] == '$ACC'
                    and len({ _reg(i.operands[2]) for i in seq[:3]}) == 1
                    and all(_lane(i.operands[2], lane) for i, lane in zip(seq[:3], 'xyz'))):
                last = d.operands[2]
                affine = last == '$vf0w'
                if affine or (_reg(last) == _reg(a.operands[2]) and _lane(last, 'w')):
                    emit('affine-transform' if affine else 'homogeneous-transform', seq,
                         'four ordered ACC products share input x/y/z, then translation or input w')
        if root in {'vrsqrt', 'vsqrt', 'vdiv'}:
            emit({'vrsqrt': 'reciprocal-square-root', 'vsqrt': 'square-root', 'vdiv': 'division'}[root], [ins], 'Q producer; input lanes retained')
        if root == 'vmr32':
            emit('lane-rotate', [ins], 'one-lane cyclic permutation, not alone a matrix transpose')
    # A quaternion uses the same instruction vocabulary as generic vectors. No
    # name is assigned without external type/call evidence.
    for op in list(operations):
        if op['family'] != 'squared-length3':
            continue
        dot = [i for i in arithmetic if i.address in op['instruction_addresses']]
        input_register = _reg(dot[0].operands[1])
        reduced_register = _reg(dot[-1].operands[0])
        later = [i for i in arithmetic if op['end'] <= i.address <= op['end'] + 80]
        qproducer = next((i for i in later if i.root in {'vrsqrt', 'vsqrt', 'vdiv'}), None)
        if qproducer is None:
            continue
        if (qproducer.root == 'vrsqrt' and len(qproducer.operands) == 3
                and qproducer.operands[1] == '$vf0w' and _reg(qproducer.operands[2]) == reduced_register
                and _lane(qproducer.operands[2], 'x')):
            scale = next((i for i in later if i.address > qproducer.address and i.root == 'vmulq'), None)
            overwritten_q = scale and any(qproducer.address < i.address < scale.address and i.root in {'vdiv', 'vsqrt', 'vrsqrt', 'vcallms', 'vcallmsr'} for i in later)
            if scale and not overwritten_q and scale.mask == 'xyz' and _reg(scale.operands[1]) == input_register:
                emit('normalize3', dot + [qproducer, scale], 'squared xyz norm feeds reciprocal sqrt Q, Q scales original xyz')
        elif (qproducer.root == 'vsqrt' and len(qproducer.operands) == 2
              and _reg(qproducer.operands[1]) == reduced_register and _lane(qproducer.operands[1], 'x')):
            emit('length3', dot + [qproducer], 'squared xyz norm feeds square-root Q')
    return operations


def shape_id(mode, normalized):
    return hashlib.sha256((mode + '\n' + '\n'.join(normalized)).encode()).hexdigest()[:16]


def analyze_function(instructions, metadata, min_length=2, max_length=12):
    shapes, operations = [], []
    cpu = [i for i in instructions if not i.vu]
    cpu_addresses = [i.address for i in cpu]
    for mode in ('contiguous', 'projected'):
        for block in blocks(instructions, projected=mode == 'projected'):
            if mode == 'projected':
                for op in semantic_operations(block):
                    operations.append(dict(op, function=metadata['address']))
            for length in range(min_length, min(max_length, len(block)) + 1):
                for n in range(len(block) - length + 1):
                    seq = block[n:n + length]
                    normalized = normalize(seq)
                    left = bisect.bisect_right(cpu_addresses, seq[0].address)
                    right = bisect.bisect_left(cpu_addresses, seq[-1].address)
                    cpu_gap = cpu[left:right]
                    shapes.append(dict(id=shape_id(mode, normalized), mode=mode, instructions=list(normalized),
                                       start=seq[0].address, end=seq[-1].address + 4,
                                       function=metadata['address'], length=length,
                                       cpu_gaps=[dict(address=i.address, instruction=i.text) for i in cpu_gap]))
    return shapes, operations


def _decode(function):
    import rabbitizer
    from loop_padding import branch_offset
    result = []
    for n, word in enumerate(function['words']):
        address = function['addr'] + 4 * n
        obj = rabbitizer.Instruction(word, address, rabbitizer.InstrCategory.R5900)
        offset = branch_offset(word)
        target = address + 4 + 4 * offset if offset is not None else None
        if word >> 26 in (2, 3):
            target = ((address + 4) & 0xf0000000) | ((word & 0x3ffffff) << 2)
        control = (obj.isFunctionCall() or obj.isBranch() or obj.isJump() or obj.getOpcodeName() == 'eret')
        result.append(parse_instruction(obj.disassemble(), address, control, target))
    return result


def _band(size):
    return '0-100' if size <= 100 else '101-300' if size <= 300 else '301-1024' if size <= 1024 else 'over-1024'


def build_report(functions, tus, source, automatic, min_length=2, max_length=12, min_occurrences=3):
    from loop_padding import sn_compiler
    starts = [int(t['text'][0], 0) for t in tus]
    clusters, users, operations, microcalls = {}, [], [], []
    instruction_counts = collections.Counter()
    for function in functions:
        k = bisect.bisect_right(starts, function['addr']) - 1
        tu = tus[k] if k >= 0 and function['addr'] < int(tus[k]['text'][1], 0) else {}
        if not sn_compiler(tu.get('compiler', '')):
            continue
        instructions = _decode(function)
        if not any(i.vu for i in instructions):
            continue
        instruction_counts.update(i.opcode for i in instructions if i.vu)
        result = automatic.get(hex(function['addr']), {})
        score = result.get('score')
        if score is None:
            scores = [t['score'] for t in result.get('tried', []) if isinstance(t.get('score'), (int, float))]
            score = min(scores) if scores else None
        meta = dict(address=function['addr'], name=function['name'], size=function['size'], span=function['span'],
                    band=_band(function['size']), region=function.get('region'), library=tu.get('library'),
                    tu=tu.get('name'), tu_confidence=tu.get('confidence'), tu_compiler=tu.get('compiler'),
                    source=function['addr'] in source, auto_status=result.get('status'), best_diff=score,
                    vu_instructions=sum(i.vu for i in instructions), families=[])
        meta['vu_span'] = [next(i.address for i in instructions if i.vu), next(i.address + 4 for i in reversed(instructions) if i.vu)]
        shapes, recognized = analyze_function(instructions, meta, min_length, max_length)
        for row in shapes:
            cluster = clusters.get(row['id'])
            if cluster is None:
                cluster = dict(id=row['id'], mode=row['mode'], instructions=row['instructions'], length=row['length'],
                               architectural_state=architectural_state([parse_instruction(line) for line in row['instructions']]), occurrences=[])
                clusters[row['id']] = cluster
            cluster['occurrences'].append({key: value for key, value in row.items() if key not in {'id', 'mode', 'instructions', 'length'}})
        operations.extend(recognized)
        meta['families'] = sorted({op['family'] for op in recognized})
        identified = {a for op in recognized if op['verified_dataflow'] for a in op['instruction_addresses']}
        meta['unclassified_arithmetic'] = sum(i.vu and i.root not in TRANSPORT | {'vnop', 'vwaitq'} and i.address not in identified for i in instructions)
        users.append(meta)
        for n, ins in enumerate(instructions):
            if ins.root.startswith('vcallms'):
                # Observation is intentionally not a proven ABI/clobber contract.
                context = instructions[max(0, n - 12):n + 13]
                microcalls.append(dict(address=ins.address, function=function['addr'], opcode=ins.opcode,
                                       operand=list(ins.operands), observed_context=[dict(address=i.address, instruction=i.text) for i in context],
                                       observed_vf=sorted({int(m[1]) for i in context for m in re.finditer(r'\$vf(\d+)', i.text)}),
                                       contract='unverified; surrounding traffic cannot establish all microprogram clobbers'))
    by_address = {u['address']: u for u in users}
    summaries = {}
    for label, subset in [('all-sn', users), ('tu-library-game', [u for u in users if u['library'] == 'game']),
                          ('mapped-region-game', [u for u in users if u['region'] == 'game']),
                          ('tu-library-renderware', [u for u in users if u['library'] in {'renderware_core', 'rwa_ee'}])]:
        bands = {}
        for band in ('0-100', '101-300', '301-1024', 'over-1024'):
            selected = [u for u in subset if u['band'] == band]
            bands[band] = dict(functions=len(selected), source=sum(u['source'] for u in selected),
                               code_bytes=sum(u['size'] for u in selected))
        summaries[label] = dict(functions=len(subset), source=sum(u['source'] for u in subset),
                                vu_instructions=sum(u['vu_instructions'] for u in subset), bands=bands)
    family_summary = []
    for family in sorted({op['family'] for op in operations}):
        selected = nonoverlapping([op for op in operations if op['family'] == family])
        addresses = {op['function'] for op in selected}
        family_summary.append(dict(family=family, occurrences=len(selected), functions=len(addresses),
                                   tu_game_functions=sum(by_address[a]['library'] == 'game' for a in addresses),
                                   mapped_game_functions=sum(by_address[a]['region'] == 'game' for a in addresses),
                                   source_functions=sum(by_address[a]['source'] for a in addresses),
                                   verified_dataflow=all(op['verified_dataflow'] for op in selected)))
    recurring = []
    for cluster in clusters.values():
        chosen = nonoverlapping(cluster['occurrences'])
        if len(chosen) < min_occurrences:
            continue
        cluster['raw_windows'] = len(cluster['occurrences'])
        cluster['occurrences'] = chosen
        cluster['count'] = len(chosen)
        addresses = {row['function'] for row in chosen}
        cluster['functions'] = len(addresses)
        cluster['game_functions'] = sum(by_address[a]['library'] == 'game' for a in addresses)
        cluster['mapped_game_functions'] = sum(by_address[a]['region'] == 'game' for a in addresses)
        recurring.append(cluster)
    recurring.sort(key=lambda s: (-s['count'], -s['length'], s['id']))
    return dict(schema=1, summaries=summaries, families=family_summary, users=users,
                shapes=recurring, operations=operations, microcalls=microcalls,
                instruction_counts=dict(instruction_counts.most_common()),
                unclassified=dict(functions=sum(u['unclassified_arithmetic'] > 0 for u in users),
                                  arithmetic_instructions=sum(u['unclassified_arithmetic'] for u in users)),
                caveats=['SN scope comes from the TU compiler map, with confidence preserved; it is not compiler provenance proof.',
                         'Per-shape/family occurrences are non-overlapping; counts across shapes or families are not additive.',
                         'Projected shapes retain CPU-gap metadata; intervening CPU instructions are not assumed independent.',
                         'Branch targets and every CPU branch/call/delay slot split projected blocks.',
                         'A recurring instruction shape alone does not identify RenderWare, Criterion or a game class.',
                         'Quaternion/matrix-transpose/normalization names require further type or semantic evidence.',
                         'Microcall context lists preserve fixed VF IDs, but do not prove hidden clobbers or flags.'])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/math-study/vu0-patterns.json')
    parser.add_argument('--min-length', type=int, default=2)
    parser.add_argument('--max-length', type=int, default=12)
    parser.add_argument('--min-occurrences', type=int, default=3)
    args = parser.parse_args()
    if not 1 <= args.min_length <= args.max_length <= 32:
        parser.error('require 1 <= min-length <= max-length <= 32')
    import autodecomp
    import yaml
    started = time.time()
    tus = yaml.safe_load((ROOT / 'config/tus.yaml').read_text())['tus']
    automatic_path = ROOT / 'build/auto.json'
    automatic = json.loads(automatic_path.read_text()) if automatic_path.exists() else {}
    report = build_report(autodecomp.load_inventory(), tus, autodecomp.source_functions(), automatic,
                          args.min_length, args.max_length, args.min_occurrences)
    report['timing'] = dict(start=started, end=time.time())
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=1) + '\n')
    print(json.dumps(dict(summary=report['summaries'], families=report['families'],
                          recurring_shapes=len(report['shapes']), microcall_sites=len(report['microcalls'])), indent=1))


if __name__ == '__main__':
    main()
