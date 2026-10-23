#!/usr/bin/env python3
"""Read the private, versioned harness entry stream and make typed fuzz inputs."""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import collections
import json
from pathlib import Path
import struct

MAGIC = b'EECAP001'


def words(stream, count):
    data = stream.read(count*8)
    if len(data) != count*8:
        raise ValueError('truncated capture stream')
    return struct.unpack('<'+'Q'*count, data)


def entries(path, memory=None):
    """Yield metadata after applying each ordered memory delta to optional RAM.

    Registers include pending VU and external events. Address zero is a terminal
    checkpoint and must never contribute to per-function coverage.
    """
    with Path(path).open('rb') as stream:
        if stream.read(8) != MAGIC:
            raise ValueError('unsupported capture format')
        index = 0
        while stream.peek(1):
            offset = stream.tell()
            address, ordinal = words(stream, 2)
            fixed = words(stream, 593)
            pending = fixed[-1]
            if pending > 1024:
                raise ValueError('invalid pending VU writes')
            words(stream, pending*11)
            tail = words(stream, 249)  # TLB, EE control, external clock and queue size
            if tail[-1] > 1024:
                raise ValueError('invalid pending interrupts')
            words(stream, tail[-1]*3)
            count, = words(stream, 1)
            if count > 32*1024*1024+24576:
                raise ValueError('invalid memory delta')
            for _ in range(count):
                a, b = words(stream, 2)
                if b > 255:
                    raise ValueError('invalid captured byte')
                if memory is not None and a < len(memory):
                    memory[a] = b
            count, = words(stream, 1)
            if count > 1000000:
                raise ValueError('invalid hardware delta')
            words(stream, count*3)
            yield dict(index=index, offset=offset, function=address, ordinal=ordinal,
                       pc=fixed[397], receiver=fixed[16], instructions=tail[245],
                       gpr=tuple(fixed[:128]), fpr=tuple(fixed[168:200]))
            index += 1


def object_candidates(ram, catalog):
    tables = {t['vptr']:(c,t) for c in catalog['classes'] for t in c['vtables']}
    hits = collections.defaultdict(list)
    # Exclude code/vtables/constants. A remaining hit is still a candidate until
    # linked to a recorded receiver; freed heap objects can retain their vptr.
    for i, (value,) in enumerate(struct.iter_unpack('<I', ram)):
        if i*4 >= 0x480000 and value in tables:
            hits[value].append(i*4)
    return [dict(class_name=tables[v][0]['cpp_name'], identity=tables[v][0]['class_identity'],
                 vtable=v, vptr_offset=tables[v][1]['vptr_offset'],
                 pointer_locations=locations) for v,locations in sorted(hits.items())]


def field_variants(value, typ, size):
    """Small scalar changes only; pointers, unknown storage and enums are kept."""
    if size not in (1,2,4) or any(token in typ for token in ('*','&','unknown')):
        return []
    if typ == 'bool':
        return [1-value] if value in (0,1) else []
    if typ == 'float' and size == 4:
        exponent = value>>23&255
        if exponent == 255:  # input formats with arbitrary exponent-255 data need a field contract
            return []
        return [value^1] if exponent else [0x3c23d70a]  # adjacent bits, or 0.01f
    if typ not in ('char','signed char','unsigned char','short','unsigned short','int','unsigned int','long','unsigned long'):
        return []
    maximum = (1<<(size*8))-1
    return [x for x in (max(0,value-1),min(maximum,value+1)) if x != value]


def make_fuzz(corpus, ram, catalog, output, limit=256):
    tables = collections.defaultdict(list)
    for cls in catalog['classes']:
        for table in cls['vtables']:
            offsets = [table['vptr_offset']] if table['vptr_offset'] is not None else table['vptr_offset_candidates']
            for off in offsets:
                if 0 <= off < 4096:
                    tables[off].append((table['vptr'],cls))
    types = {off:dict(rows) for off,rows in tables.items()}
    memory = bytearray(ram)
    rows, used, observed = [],set(),collections.Counter()
    for entry in entries(corpus, memory):
        function, receiver = entry['function'],entry['receiver']
        if not function or not (0x480000 <= receiver < len(memory)-4096):
            continue
        for off, lookup in types.items():
            vptr = struct.unpack_from('<I',memory,receiver+off)[0]
            cls = lookup.get(vptr)
            if cls is None:
                continue
            observed[cls['cpp_name']] += 1
            # A recovered receiver layout also permits perturbing fields read by
            # other methods of the same view. Keep that distinction in evidence;
            # mutations still do not count as naturally recorded entry states.
            fields = sorted(cls['fields'],key=lambda f:function not in f.get('functions',[]))
            for field in fields:
                if not field.get('verified_by'):
                    continue
                key = (function,receiver,field['offset'])
                if key in used:
                    continue
                a, size = receiver+field['offset'],field['size']
                if not (receiver <= a <= len(memory)-size):
                    continue
                before = int.from_bytes(memory[a:a+size],'little')
                variants = field_variants(before,field['type'],size)
                if not variants:
                    continue
                used.add(key)
                for after in variants:
                    rows.append(dict(index=entry['index'],function=function,receiver=receiver,
                                     class_name=cls['cpp_name'],field_offset=field['offset'],
                                     current_method_access=function in field.get('functions',[]),
                                     type=field['type'],size=size,address=a,before=before,after=after,
                                     evidence=field['basis']))
                    if len(rows) >= limit:
                        break
                if len(rows) >= limit:
                    break
            if len(rows) >= limit:
                break
        if len(rows) >= limit:
            break
    output = Path(output)
    Path(str(output)+'.json').write_text(json.dumps(dict(cases=rows,observed_receivers=observed),indent=2)+'\n')
    Path(str(output)+'.txt').write_text(''.join(
        f"{r['index']} {r['address']:x} {r['before']:x} {r['after']:x} {r['size']}\n" for r in rows))
    return rows
