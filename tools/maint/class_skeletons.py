#!/usr/bin/env python3
"""Generate conservative GCC 2.95 PS2 class skeletons from RTTI and vtables into build/classes/include/ (ignored).

A skeleton is a starting point, not a source file: the class views the sources include (include/game/classes/ and
include/kynapse/classes/) are hand-edited headers that began as copies of such skeletons. When a source needs another class,
generate the set, copy the skeleton and adapt it. ABI evidence lives in config/SLUS_213.76/class_method_abi.json and
config/SLUS_213.76/rtti_abi.json (edited by hand); the generator also needs the recovered context
(`tools/autodecomp.py context --refresh`).
Object views deliberately make no complete-size or unverified inheritance-layout
claim. RTTI hierarchy and virtual slot order are retained separately from those
partial ABI views. No compiler or target tool executes on the host.
"""
import pathlib as _pl, sys as _sys
_sys.path[:0] = [str(_pl.Path(__file__).resolve().parents[1] / _d) for _d in ('', 'build', 'pipeline', 'maint')]
import argparse
import collections
import hashlib
import json
from pathlib import Path
import re
import struct

from elfinfo import Elf

ROOT = Path(__file__).resolve().parents[2]
SCALARS = {'v': 'void', 'b': 'bool', 'c': 'char', 's': 'short', 'i': 'int',
           'l': 'long', 'x': 'long long', 'f': 'float', 'd': 'double', 'r': 'long double'}
CPP_TYPES = {'s8': 'signed char', 'u8': 'unsigned char', 's16': 'short', 'u16': 'unsigned short',
             's32': 'int', 'u32': 'unsigned int', 's64': 'long', 'u64': 'unsigned long',
             's128': 'S128', 'u128': 'U128', 'f32': 'float', 'f64': 'double',
             'unknown': 'unsigned int', 'void': 'void', '...': '...'}


class NameDecoder:
    """Bounded parser for legacy GCC qualified, template and function types."""
    def __init__(self, text):
        self.text, self.i = text, 0

    def number(self):
        m = re.match(r'\d+', self.text[self.i:])
        if not m:
            raise ValueError('expected length or count')
        self.i += len(m[0])
        return int(m[0])

    def component(self):
        if self.text[self.i:self.i + 1] == 't':
            self.i += 1
            name = self.component()
            count = self.number()
            args = []
            for _ in range(count):
                if self.text[self.i:self.i + 1] == 'Z':
                    self.i += 1
                    args.append(self.type())
                else:
                    typ = self.type()
                    negative = self.text[self.i:self.i + 1] == 'm'
                    self.i += negative
                    value = self.number()
                    args.append(('-' if negative else '') + str(value) + ' /* ' + typ + ' */')
            return name + '<' + ', '.join(args) + '>'
        length = self.number()
        end = self.i + length
        value = self.text[self.i:end]
        if len(value) == length and value.startswith('_GLOBAL_'):
            self.i = end
            return 'Anonymous_' + hashlib.sha256(value.encode()).hexdigest()[:12]
        if len(value) != length or not re.fullmatch(r'[A-Za-z_$][\w$]*', value):
            raise ValueError('invalid identifier')
        self.i = end
        return value

    def type(self):
        if self.i >= len(self.text):
            raise ValueError('truncated type')
        code = self.text[self.i]
        self.i += 1
        if code == 'Q':
            if self.text[self.i:self.i + 1] == '_':
                self.i += 1
                count = self.number()
                if self.text[self.i:self.i + 1] != '_':
                    raise ValueError('qualified count terminator')
                self.i += 1
            else:
                count = int(self.text[self.i])
                self.i += 1
            return '::'.join(self.component() for _ in range(count))
        if code in ('P', 'R', 'C', 'V', 'U', 'S'):
            function = self.text[self.i:self.i + 1] == 'F'
            value = self.type()
            if code in ('P', 'R') and function:
                result, arguments = value.rsplit(' (', 1)
                return result + (' (*)(' if code == 'P' else ' (&)(') + arguments
            return value + ('*' if code == 'P' else '&') if code in ('P', 'R') else {
                'C': 'const ', 'V': 'volatile ', 'U': 'unsigned ', 'S': 'signed '}[code] + value
        if code == 'F':
            args = []
            while self.i < len(self.text) and self.text[self.i] != '_':
                args.append(self.type())
            if self.i == len(self.text):
                raise ValueError('function return separator')
            self.i += 1
            result = self.type()
            return result + ' (' + ', '.join(args) + ')'
        if code == 'A':
            count = self.number()
            if self.text[self.i:self.i + 1] != '_':
                raise ValueError('array separator')
            self.i += 1
            return self.type() + '[' + str(count) + ']'
        if code in SCALARS:
            return SCALARS[code]
        self.i -= 1
        return self.component()


def decode_name(encoded):
    parser = NameDecoder(encoded)
    try:
        name = parser.type()
        if parser.i != len(encoded):
            raise ValueError('unparsed suffix')
        return name, True
    except (ValueError, IndexError):
        return 'UnparsedType_' + hashlib.sha256(encoded.encode()).hexdigest()[:12], False


def identifier(name, encoded=''):
    result = re.sub(r'[^A-Za-z0-9_]+', '_', name).strip('_')
    if not result or result[0].isdigit():
        result = 'Type_' + result
    if len(result) > 110 or '<' in name:
        result = result[:85] + '_' + hashlib.sha256((encoded or name).encode()).hexdigest()[:12]
    return result


def cpp_type(typ):
    typ = typ.strip()
    if '*' in typ or '&' in typ:
        base = typ.replace('const ', '').split('*')[0].split('&')[0].strip()
        if base not in CPP_TYPES and base not in ('void', 'char', 'unsigned short', 'short', 'int', 'float'):
            return 'void *'
        return re.sub(r'\b(?:s8|u8|s16|u16|s32|u32|s64|u64|s128|u128|f32|f64)\b',
                      lambda m: CPP_TYPES[m[0]], typ)
    return CPP_TYPES.get(typ, typ if typ in ('bool', 'char', 'unsigned char', 'short', 'unsigned short',
                                           'int', 'unsigned int', 'long', 'unsigned long', 'float', 'double') else 'unsigned int')


def field_type(typ, size):
    """An unknown semantic type must still retain the PS2 access width."""
    if typ == 'unknown':
        return {1: 'unsigned char', 2: 'unsigned short', 4: 'unsigned int', 8: 'unsigned long', 16: 'U128'}.get(size)
    return cpp_type(typ)


class Image:
    def __init__(self, data):
        self.elf = Elf(data)

    def words(self, section):
        s = self.elf.section(section)
        return s['addr'], list(struct.unpack('<%dI' % (s['size'] // 4), self.elf.content(s)))

    def word(self, address):
        for s in self.elf.sections:
            if s['type'] != 8 and s['addr'] <= address < s['addr'] + s['size'] - 3:
                return struct.unpack_from('<I', self.elf.data, s['offset'] + address - s['addr'])[0]
        return None


def table_inventory(image, inventory, getters):
    """Find legacy eight-byte entries, including short tables absent from context.

    No-RTTI zero headers require a real code reference, avoiding arbitrary zero
    data followed by callbacks. Context runs are retained as unverified candidates.
    """
    functions = {f['addr'] for f in inventory}
    references = collections.defaultdict(set)
    for f in inventory:
        for rel in f['rel'].values():
            if isinstance(rel[1], int) and rel[0] != 'jal':
                references[rel[1] + rel[2]].add(f['addr'])
    tables = {}
    for section in ('.data', '.rodata'):
        base, words = image.words(section)
        i = 0
        while i + 3 < len(words):
            address = base + i * 4
            header = words[i] == 0 and (words[i + 1] in getters or
                      words[i + 1] == 0 and address in references)
            if header and words[i + 3] in functions:
                entries, k = [], i + 2
                while k + 1 < len(words) and words[k + 1] in functions and words[k + 1] not in getters:
                    adjustment = words[k] & 65535
                    adjustment -= 65536 if adjustment & 32768 else 0
                    index = words[k] >> 16
                    if index not in (0, 65535) or abs(adjustment) > 8192:
                        break
                    entries.append(dict(index=len(entries), offset=(k - i) * 4, function=words[k + 1],
                                        adjustment=adjustment, adjustment_word=words[k]))
                    k += 2
                if entries:
                    tables[address] = dict(address=address, vptr=address, context_group=address if words[i + 1] else address + 8,
                                           getter=words[i + 1] or None, slots=entries,
                                           referenced_by=sorted(references[address]), basis='RTTI header' if words[i + 1] else 'referenced zero RTTI header')
                    i = k
                    continue
            i += 1
    # Retain the broad old context scan without treating callback runs as proved
    # vtables. Work from this image, so synthetic inputs need no private files.
    base, words = image.words('.data')
    groups, i = {}, 0
    while i + 1 < len(words):
        entries, k = [], i
        while k + 1 < len(words) and words[k] == 0 and words[k + 1] in functions:
            entries.append(words[k + 1])
            k += 2
        if len(entries) >= 3:
            groups[base + 4 * i] = entries
            i = k
        else:
            i += 1
    for address, functions_in_run in groups.items():
        if any(t['address'] <= address < t['address'] + 8 * (len(t['slots']) + 1) for t in tables.values()):
            continue
        tables[address] = dict(address=address, vptr=None, context_group=address, getter=None,
                               slots=[dict(index=i, offset=8 * i, function=f, adjustment=0, adjustment_word=0)
                                      for i, f in enumerate(functions_in_run)],
                               referenced_by=sorted(references[address]), basis='unverified zero-adjustment function run')
    return sorted(tables.values(), key=lambda t: t['address'])


def vptr_stores(inventory, table_addresses):
    """Conservative direct this-derived stores of materialized vtable addresses."""
    import rabbitizer
    from context_recovery import effects
    output = collections.defaultdict(list)
    for function in inventory:
        if not any(isinstance(r[1], int) and r[1] + r[2] in table_addresses for r in function['rel'].values()):
            continue
        regs = [None] * 32
        regs[0], regs[4] = ('constant', 0), ('this', 0)
        clobber_after = None
        for i, word in enumerate(function['words']):
            x = rabbitizer.Instruction(word, function['addr'] + i * 4, rabbitizer.InstrCategory.R5900)
            op, rs, rt = x.getOpcodeName(), word >> 21 & 31, word >> 16 & 31
            a, b, value = regs[rs], regs[rt], None
            imm = (word & 65535) - (65536 if word & 32768 else 0)
            if op == 'sw' and b and b[0] == 'constant' and b[1] in table_addresses and a and a[0] == 'this':
                offset = a[1] + imm
                if 0 <= offset < 4096:
                    output[b[1]].append(dict(function=function['addr'], instruction=function['addr'] + 4 * i, offset=offset))
            if op == 'lui':
                value = ('constant', (word & 65535) << 16)
            elif op in ('addiu', 'daddiu') and a:
                value = (a[0], (a[1] + imm) & 0xffffffff)
            elif op == 'ori' and a and a[0] == 'constant':
                value = ('constant', a[1] | (word & 65535))
            elif op in ('addu', 'daddu', 'or', 'por'):
                if a and b and b == ('constant', 0):
                    value = a
                elif a == ('constant', 0) and b:
                    value = b
            for reg in effects(x)[1]:
                if 0 < reg < 32:
                    regs[reg] = value
            if clobber_after == i:
                for reg in list(range(1, 16)) + [24, 25, 31]:
                    regs[reg] = None
                clobber_after = None
            if x.isFunctionCall():
                clobber_after = i + 1
            regs[0] = ('constant', 0)
    return output


def signature(address, context, matched, overrides):
    override = overrides.get(hex(address), {})
    if override:
        return dict(ret=override['return'], params=override.get('params', []),
                    verified=address in matched, basis='PS2 exact source probe; full-build status recorded separately')
    row = context.get('signatures', {}).get(str(address), {})
    params = list(row.get('params', []))
    # A vtable target is an instance method, even where the generic context lost this.
    if params:
        params.pop(0)
    return dict(ret=cpp_type(row.get('ret', 'unknown')), params=[cpp_type(p) for p in params],
                verified=False,
                basis=row.get('source') or 'PS2 register/type inference; unverified unused parameters',
                conflicts=row.get('conflicts', []), arity_proven=row.get('source_quality', 0) >= 2)


def load_context(root=ROOT):
    path = root / 'build/auto/context.json'
    if not path.exists():
        raise SystemExit('Recovered context is missing; run tools/autodecomp.py context --refresh before tools/maint/class_skeletons.py')
    return json.loads(path.read_text())


def table_fields(table, context, matched, reserved_offsets=()):
    """Keep exact receiver fields when source naming splits a vtable group.

    Other arguments are separate objects. Named receiver evidence only fills
    missing offsets, preserving existing views and explicit field overrides.
    """
    layouts = context.get('layouts', {})
    primary_name = 'Recovered_Vtable_%08X' % table['context_group']
    primary = layouts.get(primary_name, {})
    occupied = {field['offset'] for field in primary.get('fields', [])} | set(reserved_offsets)
    receivers = {slot['function'] for slot in table['slots']
                 if slot['function'] in matched
                 and slot.get('adjustment', 0) == 0
                 and context.get('signatures', {}).get(str(slot['function']), {}).get('this')
                 and context['signatures'][str(slot['function'])].get('source_quality', 0) >= 4}
    for name, layout in layouts.items():
        proven = {node[0] for node in layout.get('nodes', []) if node[1] == 0 and node[0] in receivers}
        if name != primary_name and not proven:
            continue
        for field in layout.get('fields', []):
            functions = set(field['functions'])
            if name != primary_name and (field['offset'] in occupied or not functions & proven):
                continue
            verified = functions & (set(layout.get('verified_by', [])) | proven)
            basis = ('PS2 receiver offset and exact source probe' if name != primary_name else
                     'PS2 access grouping; class extent and overlapping interpretations unverified')
            yield field, sorted(verified), basis


def collect_model(root=ROOT):
    import autodecomp as auto
    from units import load_units
    from rtti_evidence import collect_evidence, deleting_destructor_pattern
    context = load_context(root)
    evidence = collect_evidence(root=root)
    config_path = root / 'config/SLUS_213.76/class_method_abi.json'
    config = json.loads(config_path.read_text()) if config_path.exists() else {}
    units = load_units()
    matched = {f['addr'] for u in units for f in u['functions'] if f.get('status') == 'source'}
    inv = auto.load_inventory()
    function_by_address = {f['addr']: f for f in inv}
    image = Image((root / 'orig/SLUS_213.76/SLUS_213.76').read_bytes())
    classes, getter_class = {}, {}
    for record in evidence['classes']:
        encoded = record['encoded_name']
        name, decoded = decode_name(encoded)
        row = dict(record, name=name, name_decoded=decoded, cpp_name=identifier(name, encoded),
                   class_identity='RTTI', vtables=[], fields=[], methods=[], constructors=[], destructors=[])
        classes[encoded] = row
        for getter in record['getters']:
            getter_class[getter] = encoded
    tables = table_inventory(image, inv, getter_class)
    stores = vptr_stores(inv, {t['address'] for t in tables})
    method_overrides = config.get('methods', {})
    for table in tables:
        encoded = getter_class.get(table['getter'])
        if encoded is None:
            encoded = 'UnknownVtable_%08X' % table['address']
            classes.setdefault(encoded, dict(encoded_name=encoded, name=encoded, name_decoded=False, cpp_name=encoded,
                                             name_addresses=[], getters=[], storage=[], kind='unknown', bases=[],
                                             class_identity='unverified vtable owner', vtables=[], fields=[], methods=[], constructors=[], destructors=[]))
        row = classes[encoded]
        table['stores'] = stores.get(table['address'], [])
        offsets = {s['offset'] for s in table['stores']}
        table['vptr_offset_candidates'] = sorted(offsets)
        table['vptr_offset'] = config.get('virtual_views', {}).get(row['cpp_name'], {}).get('vptr_offset')
        table['vptr_offset_basis'] = ('exact PS2 virtual-call source probe' if table['vptr_offset'] is not None else
                                      'unknown: this-derived stores may initialize embedded subobjects')
        for slot in table['slots']:
            slot['signature'] = signature(slot['function'], context, matched, method_overrides)
            slot['method_name'] = 'Function_%08X' % slot['function']
            slot['counterpart_leads'] = context.get('counterpart_leads', {}).get(str(slot['function']), [])
        if table['getter'] in getter_class and table['slots']:
            first = table['slots'][0]
            proof = deleting_destructor_pattern(function_by_address[first['function']])
            if proof:
                first['deleting_destructor'] = proof
                first['signature'] = dict(ret='void', params=[], verified=False,
                                          basis='PS2 in-charge flag and conditional release; hidden destructor flag omitted')
                row['destructors'].append(dict(address=first['function'], kind='destructor',
                                                evidence=proof['evidence'], verification='PS2 destructor pattern'))
        row['vtables'].append(table)
        for store in table['stores']:
            row['constructors'].append(dict(address=store['function'], confidence='candidate vptr initializer; may be destructor'))
    for row in classes.values():
        for base in row['bases']:
            target = classes.get(base.get('encoded_name'))
            base['cpp_name'] = target['cpp_name'] if target else None
        rows = {}
        for table in row['vtables']:
            reserved = {f['offset'] for slot in table['slots']
                        for f in method_overrides.get(hex(slot['function']), {}).get('fields', [])}
            for field, verified, basis in table_fields(table, context, matched, reserved):
                typ = field_type(field['type'], field['size'])
                if typ is None:
                    continue
                key = field['offset'], field['size'], typ
                rows[key] = dict(field, type=key[2], verified_by=verified, basis=basis)
            for slot in table['slots']:
                override = method_overrides.get(hex(slot['function']), {})
                for field in override.get('fields', []):
                    key = field['offset'], field['size'], field['type']
                    rows[key] = dict(field, functions=[slot['function']], verified_by=[slot['function']] if slot['function'] in matched else [],
                                     basis='PS2 instruction offset and exact source probe')
                if override.get('destructor'):
                    row['destructors'].append(slot['function'])
        # Accessors can safely expose overlapping interpretations: no data members are synthesized.
        by_offset = collections.defaultdict(list)
        for (offset, _, _), field in rows.items():
            if 0 <= offset < 0x10000:
                by_offset[offset].append(field)
        row['fields'] = [sorted(candidates, key=lambda f: ('exact source probe' not in f['basis'], -len(f.get('verified_by', [])), f['size'], f['type']))[0]
                         for _, candidates in sorted(by_offset.items())]
        methods = {}
        for table in row['vtables']:
            for slot in table['slots']:
                methods[slot['function']] = dict(address=slot['function'], name=slot['method_name'], **slot['signature'])
        row['methods'] = [methods[k] for k in sorted(methods)]
        row['area'] = 'kynapse' if row['name'].startswith('Kaim::') else 'game' if row['vtables'] and min(t['address'] for t in row['vtables']) < 0x3e0000 else 'other'
        row['header'] = CLASS_DIRS[row['area']] + '/' + row['cpp_name'] + '.hpp'
        row['layout_verified'] = False
        row['virtual_view'] = config.get('virtual_views', {}).get(row['cpp_name'])
        row['vptr_initializers'] = row['constructors']
        row['constructors'] = []
        for member in evidence.get('special_members', []):
            if member.get('encoded_name') == row['encoded_name']:
                key = 'destructors' if member['kind'] == 'destructor' else 'constructors'
                row[key].append(member)
    output = sorted(classes.values(), key=lambda r: r['cpp_name'])
    return dict(abi='GCC 2.95 EE: eight-byte virtual entries; RTTI getter/zero header is not a method', records=config.get('records', {}),
                nonclass_types=evidence.get('nonclass_types', []),
                summary=dict(rtti_classes=len(evidence['classes']), nonclass_types=len(evidence.get('nonclass_types', [])),
                             type_info_records=len(evidence['classes']) + len(evidence.get('nonclass_types', [])),
                             named_classes=sum(r['name_decoded'] for r in output if r['class_identity'] == 'RTTI'),
                             class_name_occurrences=sum(len(r['name_addresses']) for r in evidence['classes']),
                             kaim_name_occurrences=sum(len(r['name_addresses']) for r in evidence['classes'] if 'Kaim' in r['encoded_name']),
                             vtable_candidates=len(tables), rtti_vtables=sum(t['getter'] in getter_class for t in tables),
                             referenced_zero_header_vtables=sum(t['basis'] == 'referenced zero RTTI header' for t in tables),
                             unverified_function_runs=sum(t['basis'].startswith('unverified') for t in tables),
                             class_interfaces=len(output), unknown_owner_interfaces=len(output) - len(evidence['classes']),
                             fields=sum(len(r['fields']) for r in output),
                             verified_field_accesses=sum(bool(f.get('verified_by')) for r in output for f in r['fields']),
                             virtual_slots=sum(len(t['slots']) for t in tables),
                             constructor_identities=sum(len(r['constructors']) for r in output),
                             destructor_identities=len({m['address'] if isinstance(m, dict) else m
                                                        for r in output for m in r['destructors']})), classes=output)


def reference_type(typ):
    if '(*)' in typ:
        # Function pointer declarations need a typedef, handled by the header emitter.
        return typ
    return typ + ' &'


def render_header(row):
    guard = 'BLACK_CLASSES_' + row['cpp_name'].upper() + '_HPP'
    lines = ['// Generated by tools/maint/class_skeletons.py; the evidence is config/SLUS_213.76/class_method_abi.json.',
             '#ifndef ' + guard, '#define ' + guard, '#include "game/classes/support.hpp"',
             '#include "game/classes/hierarchy.hpp"', '', 'namespace BlackPS2Classes {', '',
             '// ' + row['name'], '// Identity: ' + row['class_identity'] + '. Complete size and inheritance layout are UNVERIFIED.']
    if row['getters']:
        lines.append('// RTTI getters: ' + ', '.join('0x%08X' % a for a in row['getters']) + '.')
    for base in row['bases']:
        lines.append('// RTTI base: ' + base.get('cpp_name', base.get('encoded_name', 'unknown')) +
                     '; offset ' + str(base.get('offset', 'unknown')) + '; ' + base.get('access', 'unknown') +
                     (' virtual.' if base.get('virtual') else ' nonvirtual.'))
    lines.append('struct ' + row['cpp_name'] + ' {')
    if row['class_identity'] == 'RTTI':
        lines.append('    typedef Hierarchy_' + row['cpp_name'] + ' Hierarchy; // Semantic bases, not an object layout.')
    for member in row.get('constructors', []):
        lines.append('    // Constructor identity: 0x%08X; %s.' % (member['address'], member.get('evidence', 'matched source')))
    for member in row.get('destructors', []):
        address = member['address'] if isinstance(member, dict) else member
        lines.append('    // Destructor identity: 0x%08X.' % address)
    # This is an explicit ABI view, not a declaration of a complete recovered type.
    lines.append('    // Field references address the original object; sizeof(this view) is not the allocation size.')
    for field in row['fields']:
        typ, offset = field['type'], field['offset']
        method = 'Field_%04X' % offset
        status = ('VERIFIED PS2 offset/access; semantic field type UNVERIFIED' if field.get('verified_by') else
                  'UNVERIFIED type; PS2 access offset')
        if '(*)' in typ:
            alias = 'FieldType_%04X' % offset
            lines.append('    typedef ' + typ.replace('(*)', '(*' + alias + ')') + ';')
            typ = alias
        lines += ['    // 0x%X: %s.' % (offset, status),
                  '    inline ' + typ + ' & ' + method + '() { return *(' + typ + ' *)((unsigned char *)this + 0x%X); }' % offset]
    for method in row['methods']:
        params = ', '.join(t if t == '...' else t + ' argument' + str(i) for i, t in enumerate(method['params']))
        label = ('code-compatible exact source signature; original semantic types UNVERIFIED' if method['verified'] else
                 'UNVERIFIED signature')
        lines += ['    // 0x%08X: %s (%s).' % (method['address'], label, method['basis']),
                  '    ' + method['ret'] + ' ' + method['name'] + '(' + params + ');']
    for number, table in enumerate(row['vtables']):
        lines += ['', '    // Vtable 0x%08X; vptr field offset %s; %s.' % (table['address'],
                  'unknown' if table['vptr_offset'] is None else '0x%X' % table['vptr_offset'], table['basis']),
                  '    // Separate interface preserves slot order without claiming this object\'s C++ inheritance layout.',
                  '    struct VirtualInterface' + str(number) + ' {']
        for slot in table['slots']:
            sig = slot['signature']
            params = ', '.join(t if t == '...' else t + ' argument' + str(i) for i, t in enumerate(sig['params']))
            label = ('code-compatible exact source signature; original semantic types UNVERIFIED' if sig['verified'] else
                     'UNVERIFIED signature')
            lines += ['        // slot %d, table+0x%X, this delta %d, function 0x%08X; %s.' %
                      (slot['index'], slot['offset'], slot['adjustment'], slot['function'], label),
                      ('        virtual ~VirtualInterface' + str(number) + '();' if slot.get('deleting_destructor') else
                       '        virtual ' + sig['ret'] + ' Slot%03d(' % slot['index'] + params + ');')]
        lines.append('    };')
    lines += ['};', '', '} // namespace BlackPS2Classes', '', '#endif', '']
    view = row.get('virtual_view')
    if view:
        extra = ['// Separate, source-probed virtual dispatch view; not a complete class layout.',
                 'namespace BlackPS2Classes {', 'struct ABI_' + row['cpp_name'] + ' {']
        if view['vptr_offset']:
            extra.append('    unsigned char unknown_prefix[0x%X];' % view['vptr_offset'])
        params = ', '.join(t + ' argument' + str(i) for i, t in enumerate(view['params']))
        extra += ['    virtual ' + view['return'] + ' Slot%03d(' % i + params + ');' for i in range(view['slot_count'])]
        extra += ['};', '} // namespace BlackPS2Classes', '']
        lines[-2:-2] = extra
    return '\n'.join(lines)


def rendered_files(model):
    output = {}
    for row in model['classes']:
        output[Path(row['header'])] = render_header(row)
    support = ['// Generated by tools/maint/class_skeletons.py; EE widths and PS2-verified argument records.',
               '#ifndef BLACK_CLASSES_SUPPORT_HPP', '#define BLACK_CLASSES_SUPPORT_HPP', 'namespace BlackPS2Classes {',
               'typedef int S128 __attribute__((mode(TI)));', 'typedef unsigned int U128 __attribute__((mode(TI)));']
    for name, fields in sorted(model.get('records', {}).items()):
        support += ['struct ' + name + ' {'] + ['    ' + f + ';' for f in fields] + ['};']
    support += ['}', '#endif', '']
    output[Path('game/classes/support.hpp')] = '\n'.join(support)
    hierarchy = ['// Generated semantic RTTI hierarchy. Never use these empty types as PS2 object layouts.',
                 '#ifndef BLACK_CLASSES_HIERARCHY_HPP', '#define BLACK_CLASSES_HIERARCHY_HPP', 'namespace BlackPS2Classes {']
    pending = {r['cpp_name']: r for r in model['classes'] if r['class_identity'] == 'RTTI'}
    emitted = set()
    while pending:
        ready = [r for r in pending.values() if all(b.get('cpp_name') in emitted for b in r['bases'])]
        if not ready:
            raise ValueError('unresolved or cyclic RTTI base hierarchy')
        for row in sorted(ready, key=lambda r: r['cpp_name']):
            bases = [b.get('access', 'public') + (' virtual' if b.get('virtual') else '') +
                     ' Hierarchy_' + b['cpp_name'] for b in row['bases']]
            hierarchy.append('struct Hierarchy_' + row['cpp_name'] + (' : ' + ', '.join(bases) if bases else '') + ' {};')
            emitted.add(row['cpp_name'])
            del pending[row['cpp_name']]
    hierarchy += ['}', '#endif', '']
    output[Path('game/classes/hierarchy.hpp')] = '\n'.join(hierarchy)
    lines = ['// Generated by tools/maint/class_skeletons.py; all partial class interfaces.', '#ifndef BLACK_CLASSES_ALL_HPP', '#define BLACK_CLASSES_ALL_HPP']
    lines += ['#include "' + row['header'] + '"' for row in model['classes']]
    lines += ['#endif', '']
    output[Path('game/classes/all.hpp')] = '\n'.join(lines)
    return output


CLASS_DIRS = {'game': 'game/classes', 'kynapse': 'kynapse/classes', 'other': 'game/classes/other'}   # under include/


def owned_headers(directory):
    """Headers this generator owns below the include directory."""
    return [p for d in ('game/classes', 'kynapse/classes') for p in (directory / d).rglob('*.hpp')]


def generate(model, directory):
    output = rendered_files(model)
    directory.mkdir(parents=True, exist_ok=True)
    for path, text in output.items():
        path = directory / path
        path.parent.mkdir(parents=True, exist_ok=True)
        if not path.exists() or path.read_text() != text:
            path.write_text(text)
    for path in owned_headers(directory):
        if path.relative_to(directory) not in output:
            path.unlink()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', default='build/classes/catalog.json', help='ignored detailed integration catalog')
    args = parser.parse_args()
    output = ROOT / args.output
    if not output.resolve().is_relative_to((ROOT / 'build').resolve()):
        parser.error('detailed catalog must stay in ignored build/')
    model = collect_model()
    generate(model, ROOT / 'build/classes/include')
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(model, indent=2) + '\n')
    print(json.dumps(model['summary'], indent=2))


if __name__ == '__main__':
    main()
