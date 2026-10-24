#!/usr/bin/env python3
"""Recover legacy GCC RTTI initialization evidence without executing target code.

Calls construct type-info records lazily in zero-initialized storage, so scanning
only data misses them. Track constant GPR values through each getter's control
flow, including delay slots, branch joins and caller clobbers. Getter-return
constants propagate between functions. Names and initializer sites remain in
ignored build/classes/rtti.json; verified ABI seeds are config/rtti_evidence.json.
Class-name demangling and generated headers belong to class_skeletons.py.
"""
import argparse
import collections
import json
from pathlib import Path
import re
import struct

from elfinfo import Elf

ROOT = Path(__file__).resolve().parents[1]


def signed16(word):
    return (word & 65535) - (65536 if word & 32768 else 0)


def call_target(word, pc):
    return ((pc + 4) & 0xf0000000) | ((word & 0x3ffffff) << 2)


def constant_flow(words, start, gp, known_returns, store_sink=None):
    """Conservative GPR constant flow; missing values mean unknown, never zero."""
    import rabbitizer
    from context_recovery import effects
    ins = [rabbitizer.Instruction(w, start + 4*i, rabbitizer.InstrCategory.R5900)
           for i, w in enumerate(words)]
    initial = [None] * 32
    initial[0], initial[28] = 0, gp
    incoming, queue = {0: tuple(initial)}, collections.deque([0])
    calls, returns = {}, set()

    def join(a, b):
        return tuple(x if x == y else None for x, y in zip(a, b))

    def push(index, state):
        if not 0 <= index < len(ins):
            return
        old = incoming.get(index)
        merged = state if old is None else join(old, state)
        if old != merged:
            incoming[index] = merged
            queue.append(index)

    def step(index, state):
        x, w = ins[index], words[index]
        rs, rt = (w >> 21) & 31, (w >> 16) & 31
        a, b, value = state[rs], state[rt], None
        op = x.getOpcodeName()
        if op == 'lui':
            value = (w & 65535) << 16
        elif op in ('addiu', 'daddiu') and a is not None:
            value = a + signed16(w)
        elif op in ('ori', 'andi', 'xori') and a is not None:
            imm = w & 65535
            value = a | imm if op == 'ori' else a & imm if op == 'andi' else a ^ imm
        elif op in ('addu', 'daddu', 'add', 'dadd') and a is not None and b is not None:
            value = a + b
        elif op in ('subu', 'dsubu') and a is not None and b is not None:
            value = a - b
        elif op in ('or', 'por') and a is not None and b is not None:
            value = a | b
        elif op in ('sll', 'srl') and b is not None:
            shift = (w >> 6) & 31
            value = b << shift if op == 'sll' else (b & 0xffffffff) >> shift
        if op == 'sw' and a is not None and store_sink is not None:
            store_sink.append((start + index*4, (a + signed16(w)) & 0xffffffff, b))
        out = list(state)
        for reg in effects(x)[1]:
            if 0 < reg < 32:
                out[reg] = value & 0xffffffff if value is not None else None
        out[0] = 0
        return tuple(out)

    def emit_call(index, state):
        word = words[index]
        target = call_target(word, start + index*4) if word >> 26 in (2, 3) else None
        args = tuple(state[4:8])
        key = (index, target)
        calls[key] = args if key not in calls else join(calls[key], args)
        out = list(state)
        for reg in list(range(1, 16)) + [24, 25, 31]:
            out[reg] = None
        out[2] = known_returns.get(target)
        return tuple(out)

    while queue:
        i = queue.popleft()
        x, state = ins[i], incoming[i]
        if not (x.isBranch() or x.isJump() or x.isFunctionCall()):
            push(i + 1, step(i, state))
            continue
        before = step(i, state)
        delayed = step(i + 1, before) if i + 1 < len(ins) else before
        if x.isFunctionCall():
            push(i + 2, emit_call(i, delayed))
        elif x.isJrRa():
            returns.add(delayed[2])
        elif x.isBranch():
            push(i + 1 + signed16(words[i]), delayed)
            if not x.isUnconditionalBranch():
                push(i + 2, before if x.isBranchLikely() else delayed)
        elif words[i] >> 26 == 2:
            target = call_target(words[i], start + i*4)
            if start <= target < start + 4*len(ins):
                push((target - start) // 4, delayed)
            else:
                emit_call(i, delayed)
    return calls, next(iter(returns)) if len(returns) == 1 else None


def literal_offsets(data, literal):
    """Find string occurrences without mistaking template-name suffixes for names."""
    start = 0
    while (offset := data.find(literal, start)) >= 0:
        # A string can follow binary data (not necessarily a NUL), while an
        # encoded template argument can end with another class's complete name.
        if offset == 0 or not 32 <= data[offset - 1] < 127:
            yield offset
        start = offset + 1


def inline_type_record(words, start, gp, runtime_vtables, cstring):
    """Recognize an inlined non-class type constructor from its actual stores."""
    stores = []
    _, storage = constant_flow(words, start, gp, {}, stores)
    if storage is None:
        return None
    vtables = {value for _, address, value in stores
               if address == storage + 4 and value in runtime_vtables}
    names = {value for _, address, value in stores if address == storage and value is not None}
    if len(vtables) != 1 or len(names) != 1:
        return None
    name_address, vtable = next(iter(names)), next(iter(vtables))
    encoded = cstring(name_address)
    if encoded is None:
        return None
    return dict(encoded_name=encoded, kind=runtime_vtables[vtable], storage=[storage],
                name_addresses=[name_address], getters=[start], runtime_vtable=vtable,
                evidence='PS2 inline type-info constructor stores')


def deleting_destructor_pattern(function):
    """Proof for a first virtual slot: in-charge bit skips a release of this.

    This is deliberately narrower than recognizing any writer of a vptr. Callers
    must also establish that the function occupies the first real virtual slot.
    Track argument aliases, the conditional skip and the free-hook target. A
    generic flags mask or an unconditional free does not satisfy the predicate.
    """
    import rabbitizer
    from context_recovery import effects
    registers = [None] * 32
    registers[0], registers[4], registers[5] = ('constant', 0), ('this', 0), ('incharge', 0)
    pending, guards = None, []
    for index, word in enumerate(function['words']):
        pc = function['addr'] + 4*index
        x = rabbitizer.Instruction(word, pc, rabbitizer.InstrCategory.R5900)
        op, rs, rt = x.getOpcodeName(), word >> 21 & 31, word >> 16 & 31
        a, b, value = registers[rs], registers[rt], None
        if op == 'lui':
            value = ('constant', (word & 65535) << 16)
        elif op in ('addiu', 'daddiu') and a:
            value = (a[0], (a[1] + signed16(word)) & 0xffffffff)
        elif op in ('addu', 'daddu', 'or', 'por'):
            value = a if b == ('constant', 0) else b if a == ('constant', 0) else None
        elif op == 'ori' and a and a[0] == 'constant':
            value = ('constant', a[1] | (word & 65535))
        elif op == 'andi' and word & 65535 == 1 and a == ('incharge', 0):
            value = ('incharge_bit', pc)
        elif op == 'lw':
            relocation = function.get('rel', {}).get(str(index))
            address = a[1] + signed16(word) if a and a[0] == 'constant' else None
            if relocation and isinstance(relocation[1], int):
                address = relocation[1] + relocation[2]
            if address == 0x3c87e0:
                value = ('release', 0)
        if op in ('beq', 'beqz') and a and a[0] == 'incharge_bit' and b == ('constant', 0):
            guards.append((a[1], pc, pc + 4 + signed16(word)*4))
        call = None
        if x.isFunctionCall():
            target = call_target(word, pc) if word >> 26 == 3 else None
            call = (index + 1, pc, target == 0x107d48 or a == ('release', 0))
        for reg in effects(x)[1]:
            if 0 < reg < 32:
                registers[reg] = value
        if pending and pending[0] == index:
            _, call_pc, release = pending
            if release and registers[4] == ('this', 0):
                for mask_pc, branch_pc, target in guards:
                    if branch_pc < call_pc < target:
                        return dict(mask=mask_pc, branch=branch_pc, release=call_pc,
                                    evidence='first virtual slot; in-charge bit zero skips release(this)')
            for reg in list(range(1, 16)) + [24, 25, 31]:
                registers[reg] = None
            pending = None
        if call:
            pending = call
        registers[0] = ('constant', 0)
    return None


def matched_special_members(root, records, elf):
    """Identify constructors/destructors through source-exact C++ symbols."""
    from units import load_units
    by_getter = {getter: row['encoded_name'] for row in records for getter in row['getters']}
    data = elf.section('.data')
    contents, found = elf.content(data), {}
    for unit in load_units():
        if Path(unit['source']).suffix not in ('.cpp', '.cc', '.cxx'):
            continue
        for symbol, vtable in unit.get('externs', {}).items():
            if not symbol.startswith('_vt$') or not data['addr'] <= vtable < data['addr'] + data['size'] - 8:
                continue
            source_class = symbol[4:]
            getter = struct.unpack_from('<I', contents, vtable - data['addr'] + 4)[0]
            encoded = by_getter.get(getter, 'UnknownVtable_%08X' % vtable)
            for function in unit['functions']:
                if function.get('status') != 'source':
                    continue
                compiled = function['symbol']
                kind = ('constructor' if compiled.startswith('__' + source_class) else
                        'destructor' if compiled.startswith('_$_' + source_class) else None)
                if kind is None:
                    continue
                row = dict(address=function['addr'], kind=kind, encoded_name=encoded, vtable=vtable,
                           symbol=compiled, source=unit['source'],
                           evidence='source-exact C++ special-member symbol and bound class vtable')
                found[(row['address'], row['kind'], encoded)] = row
    return sorted(found.values(), key=lambda row: (row['address'], row['kind'], row['encoded_name']))


def collect_evidence(root=ROOT):
    """Return class records with numeric addresses; no private paths in output."""
    from autodecomp import load_inventory
    root = Path(root)
    seeds = json.loads((root / 'config/rtti_evidence.json').read_text())
    helpers = {row['address']: row for row in seeds['helpers']}
    elf = Elf((root / 'orig/SLUS_213.76/SLUS_213.76').read_bytes())
    text = elf.section('.text')
    code = elf.content(text)
    gp = struct.unpack_from('<I', elf.content(elf.section('.reginfo')), 20)[0]
    functions, all_functions = {}, {}
    for fn in load_inventory():
        offset = fn['addr'] - text['addr']
        words = list(struct.unpack_from('<%dI' % len(fn['words']), code, offset))
        all_functions[fn['addr']] = words
        if any(w >> 26 in (2, 3) and call_target(w, fn['addr'] + 4*i) in helpers
               for i, w in enumerate(words)):
            functions[fn['addr']] = words

    def cstring(addr):
        if addr is None:
            return None
        for sec in elf.sections:
            if sec['type'] != 8 and sec['addr'] <= addr < sec['addr'] + sec['size']:
                data = elf.content(sec)[addr - sec['addr']:]
                end = data.find(b'\0', 0, 1024)
                if end > 0:
                    value = data[:end].decode('ascii', errors='replace')
                    if re.fullmatch(r'[A-Za-z0-9_$.,:<>*& ]+', value):
                        return value
        return None

    known_returns = {}
    for _ in range(len(functions) + 1):
        new = dict(known_returns)
        for addr, words in functions.items():
            _, value = constant_flow(words, addr, gp, known_returns)
            if value is not None:
                new[addr] = value
        if new == known_returns:
            break
        known_returns = new

    classes, unresolved = {}, []
    for addr, words in functions.items():
        calls, _ = constant_flow(words, addr, gp, known_returns)
        for (index, target), args in sorted(calls.items()):
            if target not in helpers:
                continue
            storage, name = args[:2]
            encoded = cstring(name)
            if storage is None or encoded is None:
                unresolved.append(dict(function=addr, call=addr + index*4, helper=target, args=args))
                continue
            row = classes.setdefault(encoded, dict(encoded_name=encoded, name_addresses=[], getters=[],
                                                  storage=[], kind=helpers[target]['kind'], bases=[], initializers=[]))
            row['name_addresses'].append(name)
            row['storage'].append(storage)
            row['initializers'].append(dict(function=addr, call=addr + index*4, helper=target))
            if known_returns.get(addr) == storage:
                row['getters'].append(addr)
            if helpers[target]['kind'] == 'si':
                row['bases'].append(dict(storage=args[2], offset=0, virtual=False, access='public',
                                         evidence='PS2 __rtti_si argument'))
            elif helpers[target]['kind'] == 'class':
                row['base_list'], row['base_count'] = args[2:4]
    by_storage = {storage: row for row in classes.values() for storage in row['storage']}
    for row in classes.values():
        for key in ('name_addresses', 'storage', 'getters'):
            row[key] = sorted(set(row[key]))
        bases = {}
        for base in row['bases']:
            parent = by_storage.get(base['storage'])
            if parent:
                base['encoded_name'] = parent['encoded_name']
                base['getters'] = sorted(set(parent['getters']))
            bases[json.dumps(base, sort_keys=True)] = base
        row['bases'] = list(bases.values())
        # Count every duplicate encoded RTTI name, not only the copy passed at a call.
        literal = row['encoded_name'].encode() + b'\0'
        for sec in elf.sections:
            if sec['type'] == 8 or not sec['addr'] or sec['flags'] & 4:
                continue
            for offset in literal_offsets(elf.content(sec), literal):
                row['name_addresses'].append(sec['addr'] + offset)
        row['name_addresses'] = sorted(set(row['name_addresses']))
    records = sorted(classes.values(), key=lambda r: r['encoded_name'])
    runtime_vtables = {row['runtime_vtable']: row['kind'] for row in seeds['nonclass_helpers']}
    runtime_vtables[seeds['builtin_runtime_vtable']] = 'builtin'
    immediate = {value & 65535 for value in runtime_vtables}
    nonclass = []
    for addr, words in all_functions.items():
        if not any(w >> 26 in (8, 9) and w & 65535 in immediate for w in words):
            continue
        row = inline_type_record(words, addr, gp, runtime_vtables, cstring)
        if row is not None:
            nonclass.append(row)
    nonclass_helpers = {row['address']: dict(row, observed_direct_calls=0)
                        for row in seeds['nonclass_helpers']}
    for addr, words in all_functions.items():
        for i, word in enumerate(words):
            target = call_target(word, addr + 4*i) if word >> 26 in (2, 3) else None
            if target in nonclass_helpers:
                nonclass_helpers[target]['observed_direct_calls'] += 1
    special = matched_special_members(root, records, elf)
    for row in seeds.get('special_members', []):
        if not any(x['address'] == row['address'] and x['kind'] == row['kind'] for x in special):
            special.append(dict(row))
    return dict(abi=seeds['abi'], helpers=seeds['helpers'], classes=records,
                nonclass_types=nonclass, nonclass_helpers=list(nonclass_helpers.values()),
                special_members=sorted(special, key=lambda row: (row['address'], row['kind'])),
                summary=dict(classes=len(records), getters=len(known_returns),
                             initializer_calls=sum(len(r['initializers']) for r in records),
                             encoded_name_occurrences=sum(len(r['name_addresses']) for r in records),
                             kaim_classes=sum('Kaim' in r['encoded_name'] for r in records),
                             kaim_name_occurrences=sum(len(r['name_addresses']) for r in records if 'Kaim' in r['encoded_name']),
                             nonclass_records=len(nonclass),
                             builtin_records=sum(r['kind'] == 'builtin' for r in nonclass),
                             total_type_records=len(records) + len(nonclass),
                             source_special_members=sum('source' in row for row in special),
                             verified_special_members=len(special),
                             unresolved_calls=len(unresolved)), unresolved=unresolved)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/classes/rtti.json')
    args = parser.parse_args()
    result = collect_evidence()
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result['summary'], sort_keys=True))


if __name__ == '__main__':
    main()
