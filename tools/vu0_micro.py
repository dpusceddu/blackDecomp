#!/usr/bin/env python3
"""Static, conservative VU0 microcall contracts for the retail upload images.

This reads the input ELF; it never executes a toolchain or emits microcode.
Reports belong under ignored build/. An entry is (uploaded image, byte offset),
not just the VCALLMS operand: physics, animation and RenderWare upload different
programs at micro address zero. ISA field decoding follows the VU instruction
format; the PCSX2 disassembler/interpreter is a useful independent reference:
https://github.com/PCSX2/pcsx2/blob/master/pcsx2/DebugTools/DisVUops.h
https://github.com/PCSX2/pcsx2/blob/master/pcsx2/VUops.cpp

Read masks are may-read-before-definition; write masks are may-write. A join
intersects defined lanes, so branches cannot falsely prove a preserved input.
Both halves read the incoming state before either half writes. Branch and E-bit
delay pairs execute. Unknown instructions or indirect branches invalidate a
contract. Pipeline flag latency is deliberately not treated as scalar dataflow.
"""
import argparse
import bisect
import collections
import json
from pathlib import Path
import re
import struct

import rabbitizer

from elfinfo import Elf


ROOT = Path(__file__).resolve().parents[1]
LANES = 'xyzw'
# Loader instructions independently identify these upload packets. Source
# addresses name existing input bytes, not a reconstruction of the programs.
UPLOADS = (
    dict(name='physics', packet=0x3ba100, loader=0x26cd3c,
         payloads=((0x3ba110, 0, 0x800), (0x3ba918, 0x800, 0x620)),
         callers=(0x26cd28, 0x26f0b0)),
    dict(name='animation', packet=0x3bb6e0, loader=0x3528e8,
         payloads=((0x3bb6e8, 0, 0x530),), callers=(0x344178, 0x3528e0)),
    dict(name='renderware', packet=0x3bbc20, loader=0x37c544,
         payloads=((0x3bbc30, 0, 0x700),), callers=(0x37d2a0, 0x37e678)),
)


def mask(word):
    return sum(1 << i for i in range(4) if word & (1 << (24-i)))


def signed(value, width):
    return value - (1 << width) if value & (1 << (width-1)) else value


def add(target, register, lanes=15):
    if register not in ('vf0', 'vi0') and lanes:
        target[register] = target.get(register, 0) | lanes


def upper(word):
    """Use the shared macro/micro arithmetic encoding, excluding micro flags."""
    text = rabbitizer.Instruction(0x4a000000 | (word & 0x1ffffff), 0,
                                  rabbitizer.InstrCategory.R5900).disassemble()
    # Rabbitizer deliberately marks macro CLIP unsupported; the micro encoding
    # is nevertheless valid. Decode its architectural operands directly.
    if word & 0x7ff == 0x1ff:
        fs, ft = (word >> 11) & 31, (word >> 16) & 31
        reads = {}
        add(reads, 'vf%d' % fs, 7)
        add(reads, 'vf%d' % ft, 8)
        add(reads, 'clip-history')
        return 'CLIP', reads, {'clip-history': 15}, set()
    match = re.match(r'(\w+)(?:\.([xyzw]+))?\s*(.*)', text)
    reads, writes, hazards = {}, {}, set()
    if not match or text.startswith('.word'):
        return text, reads, writes, {'unknown-upper'}
    opcode, suffix, rest = match.groups()
    if opcode == 'vnop':
        return text, reads, writes, hazards
    lanes = sum(1 << LANES.index(c) for c in suffix or 'xyzw')
    operands = [part.strip().replace('$', '') for part in rest.split(',')]
    if opcode == 'vclipw':
        add(reads, operands[0], 7)
        add(reads, re.sub('[xyzw]$', '', operands[1]), 8)
        add(reads, 'clip-history')
        add(writes, 'clip-history')
        return text, reads, writes, hazards
    if len(operands) < 2:
        return text, reads, writes, {'unknown-upper'}
    dest, sources = operands[0], operands[1:]
    add(writes, dest, lanes)
    if opcode.startswith(('vmadd', 'vmsub', 'vopmsub')):
        add(reads, 'ACC', lanes)
    for source in sources:
        match = re.fullmatch(r'(vf\d+)([xyzw])?', source)
        if match:
            register, lane = match.groups()
            source_lanes = 1 << LANES.index(lane) if lane else lanes
            if opcode.startswith(('vopmula', 'vopmsub')):
                source_lanes = 7
            add(reads, register, source_lanes)
        elif source in ('Q', 'I'):
            add(reads, source)
        else:
            hazards.add('unknown-upper-operand')
    # ABS, conversion and min/max instructions do not update arithmetic flags.
    if opcode.startswith(('vadd', 'vsub', 'vmul', 'vmadd', 'vmsub', 'vop')):
        add(writes, 'MAC')
        add(writes, 'status-current')
        add(reads, 'status-sticky')
        add(writes, 'status-sticky')
        hazards.add('arithmetic-flags-pipelined')
    return text, reads, writes, hazards


def lower(word, immediate=False):
    reads, writes, hazards = {}, {}, set()
    fs, ft, fd = (word >> 11) & 31, (word >> 16) & 31, (word >> 6) & 31
    vf_s, vf_t = 'vf%d' % fs, 'vf%d' % ft
    vi_s, vi_t, vi_d = 'vi%d' % (fs & 15), 'vi%d' % (ft & 15), 'vi%d' % (fd & 15)
    lanes = mask(word)
    branch = None
    if immediate:
        add(writes, 'I')
        return 'LOI', reads, writes, hazards, branch
    op = word >> 25
    direct = {0: 'LQ', 1: 'SQ', 4: 'ILW', 5: 'ISW', 8: 'IADDIU', 9: 'ISUBIU',
              0x10: 'FCEQ', 0x11: 'FCSET', 0x12: 'FCAND', 0x13: 'FCOR',
              0x14: 'FSEQ', 0x15: 'FSSET', 0x16: 'FSAND', 0x17: 'FSOR',
              0x18: 'FMEQ', 0x1a: 'FMAND', 0x1b: 'FMOR', 0x1c: 'FCGET',
              0x20: 'B', 0x21: 'BAL', 0x24: 'JR', 0x25: 'JALR',
              0x28: 'IBEQ', 0x29: 'IBNE', 0x2c: 'IBLTZ', 0x2d: 'IBGTZ',
              0x2e: 'IBLEZ', 0x2f: 'IBGEZ'}
    name = direct.get(op)
    if op == 0x40:
        special = word & 63
        name = {0x30: 'IADD', 0x31: 'ISUB', 0x32: 'IADDI',
                0x34: 'IAND', 0x35: 'IOR'}.get(special)
        if special >= 60:
            group = {12: ('MOVE', 'MR32', None, None),
                     13: ('LQI', 'SQI', 'LQD', 'SQD'),
                     14: ('DIV', 'SQRT', 'RSQRT', 'WAITQ'),
                     15: ('MTIR', 'MFIR', 'ILWR', 'ISWR'),
                     16: ('RNEXT', 'RGET', 'RINIT', 'RXOR')}.get(fd)
            name = group[special-60] if group else None
    if not name:
        return '?', reads, writes, {'unknown-lower'}, branch
    if name in ('MOVE', 'MR32'):
        source_lanes = lanes if name == 'MOVE' else sum(
            1 << ((i+1) % 4) for i in range(4) if lanes & (1 << i))
        add(reads, vf_s, source_lanes)
        add(writes, vf_t, lanes)
    elif name in ('LQ', 'LQI', 'LQD', 'SQ', 'SQI', 'SQD'):
        load = name.startswith('LQ')
        add(reads, vi_s if load else vi_t)
        add(writes if load else reads, vf_t if load else vf_s, lanes)
        add(reads if load else writes, 'vu-memory')
        if name[-1] in 'ID':
            add(writes, vi_s if load else vi_t)
    elif name in ('ILW', 'ISW', 'ILWR', 'ISWR'):
        add(reads, vi_s)
        add(writes if name.startswith('IL') else reads, vi_t)
        add(reads if name.startswith('IL') else writes, 'vu-memory')
    elif name in ('IADDIU', 'ISUBIU', 'IADDI'):
        add(reads, vi_s)
        add(writes, vi_t)
    elif name in ('IADD', 'ISUB', 'IAND', 'IOR'):
        add(reads, vi_s)
        add(reads, vi_t)
        add(writes, vi_d)
    elif name == 'MTIR':
        add(reads, vf_s, 1 << ((word >> 21) & 3))
        add(writes, vi_t)
    elif name == 'MFIR':
        add(reads, vi_s)
        add(writes, vf_t, lanes)
    elif name in ('DIV', 'SQRT', 'RSQRT'):
        if name != 'SQRT':
            add(reads, vf_s, 1 << ((word >> 21) & 3))
        add(reads, vf_t, 1 << ((word >> 23) & 3))
        add(writes, 'Q')
        add(writes, 'status-div')
        hazards.add('Q-pending-until-interlock')
    elif name == 'WAITQ':
        hazards.add('Q-interlock')
    elif name in ('RNEXT', 'RGET', 'RINIT', 'RXOR'):
        if name != 'RINIT':
            add(reads, 'R')
        if name in ('RINIT', 'RXOR'):
            add(reads, vf_s, 1 << ((word >> 21) & 3))
        else:
            add(writes, vf_t, lanes)
        if name != 'RGET':
            add(writes, 'R')
    elif name.startswith('FC'):
        if name != 'FCSET':
            add(reads, 'clip-history')
        add(writes, 'clip-history' if name == 'FCSET' else vi_t if name == 'FCGET' else 'vi1')
    elif name.startswith(('FS', 'FM')):
        if name.startswith('FM'):
            add(reads, 'MAC')
            add(reads, vi_s)
        elif name != 'FSSET':
            add(reads, 'status-current')
            add(reads, 'status-sticky')
            add(reads, 'status-div')
        add(writes, 'status-sticky' if name == 'FSSET' else vi_t)
        hazards.add('flag-read-pipelined')
    elif name in ('B', 'BAL', 'IBEQ', 'IBNE', 'IBLTZ', 'IBGTZ', 'IBLEZ', 'IBGEZ'):
        branch = dict(relative=(signed(word & 2047, 11)+1)*8,
                      conditional=name not in ('B', 'BAL'))
        if name.startswith('IB'):
            add(reads, vi_s)
            if name in ('IBEQ', 'IBNE'):
                add(reads, vi_t)
        if name == 'BAL':
            add(writes, vi_t)
    elif name in ('JR', 'JALR'):
        add(reads, vi_s)
        if name == 'JALR':
            add(writes, vi_t)
        hazards.add('indirect-branch')
    return name, reads, writes, hazards, branch


def pair(lo, hi):
    text, ur, uw, uh = upper(hi)
    name, lr, lw, lh, branch = lower(lo, bool(hi >> 31))
    reads, writes = dict(ur), dict(uw)
    for register, lanes in lr.items():
        add(reads, register, lanes)
    for register, lanes in lw.items():
        add(writes, register, lanes)
    return dict(upper=text, lower=name, reads=reads, writes=writes,
                hazards=sorted(uh | lh), branch=branch, end=bool(hi & 0x40000000),
                flags=''.join(c for c, bit in zip('IEMDT', (31, 30, 29, 28, 27)) if hi & (1 << bit)))


def contract(code, entry):
    """Explore (PC, delayed destination/end) states to account for delay pairs."""
    queue = collections.deque([(entry, None, False, {})])
    incoming, external, written, hazards, visited, exits = {}, {}, {}, set(), set(), set()
    while queue:
        pc, pending, ending, defined = queue.popleft()
        state = (pc, pending, ending)
        if state in incoming:
            old = incoming[state]
            joined = {r: old.get(r, 0) & defined.get(r, 0) for r in old}
            joined = {r: m for r, m in joined.items() if m}
            if joined == old:
                continue
            defined = joined
        incoming[state] = dict(defined)
        if pc not in code:
            hazards.add('out-of-image-control-flow')
            continue
        instruction = code[pc]
        visited.add(pc)
        hazards.update(instruction['hazards'])
        for r, m in instruction['reads'].items():
            add(external, r, m & ~defined.get(r, 0))
        # Sticky and arithmetic flag reads have non-scalar pipeline semantics.
        for r, m in instruction['writes'].items():
            add(written, r, m)
            add(defined, r, m)
        if ending:
            exits.add(pc)
            continue
        if pending is not None:
            if instruction['branch'] or instruction['end']:
                hazards.add('control-in-delay-pair')
            queue.append((pending, None, False, defined))
            continue
        if instruction['end']:
            queue.append((pc+8, None, True, defined))
        elif instruction['branch']:
            branch = instruction['branch']
            queue.append((pc+8, pc+branch['relative'], False, dict(defined)))
            if branch['conditional']:
                queue.append((pc+8, pc+16, False, dict(defined)))
        else:
            queue.append((pc+8, None, False, defined))
    invalid = hazards & {'unknown-upper', 'unknown-upper-operand', 'unknown-lower',
                         'indirect-branch', 'out-of-image-control-flow', 'control-in-delay-pair'}
    def display(registers):
        return {r: ''.join(c for i, c in enumerate(LANES) if m & (1 << i))
                if r.startswith('vf') or r == 'ACC' else True
                for r, m in sorted(registers.items())}
    return dict(entry=entry, valid=bool(exits) and not invalid,
                read_before_definition=display(external), may_write=display(written),
                hazards=sorted(hazards), pairs=len(visited), exits=sorted(exits),
                flag_contract='arithmetic flag effects are pipelined; sticky input retained',
                q_completion='inspect Q producer and interlocks on every exit path',
                offsets=sorted(visited))


def analyze(elf_path, placement_path):
    elf = Elf(elf_path.read_bytes())
    text, micro = elf.section('.text'), elf.section('.vutext')
    bytes_text, bytes_micro = elf.content(text), elf.content(micro)
    functions = json.loads(placement_path.read_text())['functions']
    starts = [f['addr'] for f in functions]
    calls, programs, unmapped = [], {}, []
    for off in range(0, len(bytes_text), 4):
        word = struct.unpack_from('<I', bytes_text, off)[0]
        # VCALLMS immediate and VCALLMSR are the two COP2 special encodings.
        if word & 0xfe00003f != 0x4a000038 and word & 0xfe00003f != 0x4a000039:
            continue
        address = text['addr']+off
        function = functions[bisect.bisect_right(starts, address)-1]
        source = next((u for u in UPLOADS if u['callers'][0] <= address < u['callers'][1]), None)
        call = dict(address=address, function=function['addr'], size=function['end']-function['addr'],
                    dynamic=bool(word & 1), entry=((word >> 6) & 0x7fff)*8,
                    upload=source['name'] if source else None)
        calls.append(call)
        if not source:
            unmapped.append(address)
    for upload in UPLOADS:
        code = {}
        for address, destination, size in upload['payloads']:
            for off in range(0, size, 8):
                lo, hi = struct.unpack_from('<II', bytes_micro, address-micro['addr']+off)
                code[destination+off] = pair(lo, hi)
        entries = sorted({c['entry'] for c in calls if c['upload'] == upload['name'] and not c['dynamic']})
        programs[upload['name']] = dict(packet=upload['packet'], loader=upload['loader'],
            entry_contracts={hex(e): contract(code, e) for e in entries})
    return dict(schema=1, immediate_unit='byte offset; encoded index multiplied by eight',
                calls=calls, programs=programs, unmapped=unmapped,
                scope='known retail VU0 uploads; VU1 overlay contracts are not inferred')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--elf', type=Path, default=ROOT/'orig/usa-retail/files/SLUS_213.76')
    parser.add_argument('--placement', type=Path, default=ROOT/'build/usa-retail/placement.json')
    parser.add_argument('--output', type=Path, default=ROOT/'build/math-study/micro-contracts.json')
    args = parser.parse_args()
    result = analyze(args.elf, args.placement)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2)+'\n')
    print('%d call sites, %d functions, %d uploaded domains, %d unmapped' % (
        len(result['calls']), len({c['function'] for c in result['calls']}),
        len(result['programs']), len(result['unmapped'])))
    for name, program in result['programs'].items():
        contracts = program['entry_contracts']
        print('%s: %d entries, %d complete conservative contracts' % (
            name, len(contracts), sum(c['valid'] for c in contracts.values())))


if __name__ == '__main__':
    main()
