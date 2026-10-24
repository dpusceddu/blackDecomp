#!/usr/bin/env python3
"""Validate opt-in source-owned data ranges at labels or complete unwind groups.

A live unit may list data_ranges entries with section, input, start and end.
The ranges are exact half-open spans. Read-only .rodata inputs must fill complete
labeled intervals with PROGBITS/A storage; partial function-owned runs are rejected.
NOBITS inputs may leave only the natural
tail required by the verified immediately following NOBITS input's alignment.
All other sections keep the ordinary function/constant migration behavior.
Use --help for the manifest schema; this module never executes SDK tools.
"""
import argparse
import re
import struct

SECTIONS = {'.data': 1, '.sdata': 1, '.rodata': 1, '.bss': 8, '.sbss': 8}
LABEL = re.compile(r'^dlabel\s+\S*?([0-9A-Fa-f]{8})\s*$')
ITEM = re.compile(r'/\* [0-9A-F]+ ([0-9A-F]{8})')


def number(value):
    return int(value, 0) if isinstance(value, str) else int(value)


def source_ranges(units):
    """Return checked ranges of live source units, rejecting overlap or ambiguity."""
    out = []
    for unit in units:
        if not any(f.get('status') == 'source' for f in unit.get('functions', [])):
            continue
        inputs = set()
        for item in unit.get('data_ranges', []):
            section, input_name = item['section'], item['input']
            start, end = number(item['start']), number(item['end'])
            kind = item.get('kind', 'data')
            if kind not in ('data', 'unwind') or kind == 'unwind' and section != '.data':
                raise ValueError('%s: invalid source data kind %s' % (unit['name'], kind))
            if section not in SECTIONS or not (input_name == section or input_name.startswith(section + '.')):
                raise ValueError('%s: invalid source data section %s/%s' % (unit['name'], section, input_name))
            if not 0 <= start < end or input_name in inputs:
                raise ValueError('%s: empty/reversed range or duplicate input %s' % (unit['name'], input_name))
            inputs.add(input_name)
            out.append(dict(unit=unit['name'], section=section, input=input_name, start=start, end=end, kind=kind))
    out.sort(key=lambda r: (r['section'], r['start']))
    for left, right in zip(out, out[1:]):
        if left['section'] == right['section'] and left['end'] > right['start']:
            raise ValueError('overlapping source data ranges: %s and %s' % (left['unit'], right['unit']))
    return out


def range_owner(ranges, section, address):
    """A failed byte/relocation belongs to its explicit data owner, if any."""
    return next((r['unit'] for r in ranges if (section is None or r['section'] == section)
                 and r['start'] <= address < r['end']), None)


def partition_constant_runs(runs, section, start, end, ranges, labels):
    """Replace complete labeled read-only intervals without splitting owned runs.

    Explicit ranges override inferred constant migration only at existing object
    boundaries. A function-owned run must be wholly retained or wholly replaced;
    splitting it would silently leave two inputs for one source constant section.
    Shared runs may retain both sides, with all original items and alignments.
    """
    selected = sorted((r for r in ranges if r['section'] == section), key=lambda r: r['start'])
    if not selected:
        return runs
    if section != '.rodata':
        raise ValueError('explicit constant runs require read-only .rodata')
    boundaries = set(labels) | {end}
    for i, item in enumerate(selected):
        if not start <= item['start'] < item['end'] <= end:
            raise ValueError('%s: source constant range outside original section' % item['unit'])
        if item['start'] not in boundaries or item['end'] not in boundaries:
            raise ValueError('%s: source constant boundary is not an existing object label' % item['unit'])
        if i and selected[i - 1]['end'] > item['start']:
            raise ValueError('overlapping source constant ranges')
    groups = []
    for i, run in enumerate(runs):
        stop = runs[i + 1]['head'] if i + 1 < len(runs) else end
        if run['owner'] is not None:
            for item in selected:
                if run['head'] < item['end'] and item['start'] < stop and not (
                        item['start'] <= run['head'] and stop <= item['end']):
                    raise ValueError('%s: partial cut of a function-owned constant run' % item['unit'])
        for unit in run['units']:
            item = next((r for r in selected if r['start'] <= unit['addr'] < r['end']), None)
            key = ('explicit', item['unit'], item['start']) if item else ('retained', i)
            if groups and groups[-1][0] == key:
                groups[-1][1]['units'].append(unit)
                groups[-1][1]['align'] = max(groups[-1][1]['align'], unit['align'])
            else:
                new = dict(owner=None if item else run['owner'], head=unit['addr'],
                           align=unit['align'], units=[unit])
                if item:
                    new['explicit_range'] = item
                groups.append((key, new))
    result = [run for _, run in groups]
    for run in result:
        if run['head'] % (1 << run['align']):
            raise ValueError('source constant cut changes retained input alignment')
    for item in selected:
        found = [r for r in result if r.get('explicit_range') == item]
        if len(found) != 1 or found[0]['head'] != item['start']:
            raise ValueError('%s: source constant range has no complete item interval' % item['unit'])
    return result


def unwind_groups(data, base, text_start, text_end):
    """Recognize complete legacy CIE/FDE groups with checked relative backlinks.

    This supplies semantic cut boundaries when splat grouped several unwind
    objects under one label. It does not infer arbitrary record or byte cuts.
    """
    groups = {}
    for offset in range(0, len(data) - 19, 4):
        length, cie_id = struct.unpack_from('<II', data, offset)
        if cie_id != 0 or not 8 <= length <= 0x40 or length % 4 or offset + 4 + length > len(data):
            continue
        if data[offset + 8] != 1:
            continue
        terminator = data.find(b'\0', offset + 9, offset + 4 + length)
        if terminator < 0 or data[offset + 9:terminator] not in (b'', b'eh'):
            continue
        cursor, functions = offset + 4 + length, []
        while cursor + 4 <= len(data):
            size = struct.unpack_from('<I', data, cursor)[0]
            if size == 0:
                if functions:
                    groups[(base + offset, base + cursor + 4)] = functions
                break
            if size < 12 or size > 0x100 or size % 4 or cursor + 4 + size > len(data):
                break
            backlink, pc, span = struct.unpack_from('<III', data, cursor + 4)
            if backlink != cursor + 4 - offset or not text_start <= pc < pc + span <= text_end:
                break
            if functions and pc <= functions[-1][0]:
                break
            functions.append((pc, span))
            cursor += 4 + size
    return groups


def add_unwind_labels(lines, edges):
    """Split existing data-label scopes at checked complete unwind boundaries."""
    out, current = [], None
    for line in lines:
        if line.startswith('dlabel '):
            current = line.split()[1]
        item = ITEM.match(line.strip())
        if item and int(item[1], 16) in edges:
            if current is None:
                raise ValueError('unwind boundary has no enclosing splat data label')
            out += ['enddlabel ' + current, '', 'dlabel D_' + item[1]]
            current = 'D_' + item[1]
        if line.startswith('enddlabel '):
            line = 'enddlabel ' + current
            current = None
        out.append(line)
    return out


def carve_ranges(text, section, start, end, ranges, unwind=None):
    """Cut at existing labels or checked complete unwind edges; never split items.

    Return address spans and assembly text. The original header is retained only
    on the first fragment; later fragments keep the include/section declarations.
    Existing alignment statements stay where the original assembler put them.
    """
    selected = [r for r in ranges if r['section'] == section]
    if not selected:
        return None
    lines = text.splitlines()
    labels = {int(m[1], 16): i for i, line in enumerate(lines) if (m := LABEL.match(line))}
    extra_edges = set()
    for r in selected:
        if r.get('kind') == 'unwind':
            if (r['start'], r['end']) not in (unwind or {}):
                raise ValueError('%s: range is not a complete validated CIE/FDE group' % r['unit'])
            extra_edges.update(edge for edge in (r['start'], r['end']) if edge not in labels and edge != end)
    if extra_edges:
        lines = add_unwind_labels(lines, extra_edges)
        labels = {int(m[1], 16): i for i, line in enumerate(lines) if (m := LABEL.match(line))}
    if start not in labels:
        raise ValueError('%s: section start has no splat label' % section)
    cuts = {start, end}
    for r in selected:
        if not start <= r['start'] < r['end'] <= end:
            raise ValueError('%s: source data range outside original section' % r['unit'])
        for edge in (r['start'], r['end']):
            if edge != end and edge not in labels:
                raise ValueError('%s: source data boundary %#x is not an existing splat label' % (r['unit'], edge))
            cuts.add(edge)
    # A retained fragment beginning at 4 mod 8 cannot include a later .align 3:
    # its ELF input would acquire alignment 8, and its internal padding phase
    # would also change. Cut again at the existing aligned label, attaching the
    # directive to that later fragment. Never change the alignment or bytes.
    align = re.compile(r'^\.(align|balign)\s+(\d+)\s*$')
    directive = re.compile(r'\*/\s+(\.\w+)')
    implicit = {'.short': 2, '.half': 2, '.word': 4, '.float': 4,
                '.dword': 8, '.double': 8, '.quad': 8}
    indices = dict(labels)
    for address, index in labels.items():
        while index > 0 and (not lines[index - 1].strip() or align.match(lines[index - 1].strip())):
            index -= 1
        indices[address] = index
    initial_cuts = sorted(cuts)
    owned_spans = {(r['start'], r['end']) for r in selected}
    for lo, hi in zip(initial_cuts, initial_cuts[1:]):
        if (lo, hi) in owned_spans:
            continue
        head = lo
        first = indices[lo]
        stop = len(lines) if hi == end else indices[hi]
        for index in range(first, stop):
            match = align.match(lines[index].strip())
            item_directive = directive.search(lines[index])
            if match:
                alignment = (1 << int(match[2])) if match[1] == 'align' else int(match[2])
            else:
                alignment = implicit.get(item_directive[1], 1) if item_directive else 1
            if alignment <= 1 or head % alignment == 0:
                continue
            item = ITEM.match(lines[index].strip())
            if not match and item and int(item[1], 16) in labels and int(item[1], 16) % alignment == 0:
                address = int(item[1], 16)
                cuts.add(address)
                head = address
                continue
            following = index + 1
            while following < stop and not lines[following].strip():
                following += 1
            label = LABEL.match(lines[following]) if following < stop else None
            address = int(label[1], 16) if label else None
            if address is None or address % alignment:
                raise ValueError('%s: retained alignment needs an existing aligned label' % section)
            cuts.add(address)
            head = address
    header = [line for line in lines[:labels[start]] if line.startswith(('.include ', '.section '))]
    out = []
    ordered = sorted(cuts)
    for lo, hi in zip(ordered, ordered[1:]):
        first = 0 if lo == start else indices[lo]
        stop = len(lines) if hi == end else indices[hi]
        body = lines[first:stop]
        if lo != start:
            body = header + [''] + body
        out.append(dict(start=lo, end=hi, text='\n'.join(body) + '\n'))
    return out


def nobits_tail_fits(section, item, entries, following_input):
    """Accept only an adjacent actual NOBITS input's small natural alignment gap.

    NOBITS contributes zeroed memory rather than file bytes. Its type establishes
    the zero fill; an address label alone never establishes the next alignment.
    The existing text policy's alignment limit also excludes larger unknown gaps.
    """
    from text_placement import natural_text_span
    gap = item['end'] - item['start'] - section['size']
    if section['type'] != 8 or section['size'] <= 0 or not 0 < gap < 16 or not following_input:
        return False
    indices = [i for i, entry in enumerate(entries)
               if entry.get('key') == item['start'] and entry.get('end') == item['end']]
    if len(indices) != 1 or indices[0] + 1 >= len(entries):
        return False
    if entries[indices[0] + 1].get('key') != item['end']:
        return False
    following = following_input(item['section'], item['end'])
    if not following or following.get('type') != 8 or following.get('size', 0) <= 0 \
            or following.get('flags', 0) & 7 != 3:
        return False
    return natural_text_span(section['size'], item['start'], item['end'],
                             following.get('align'), bytes(gap), section['align'])


def validate_input_symbols(elf, ranges, expected):
    """Check defined original labels at their actual source-input offsets.

    Relocation scoring can bind a known name directly to its retail address and
    conceal compiler-reordered BSS definitions. A kept definition overrides the
    linker's PROVIDE alias, so its real section offset must agree independently.
    Undefined labels continue to use the original section-relative aliases.
    """
    inputs = {r['input']: r for r in ranges}
    for symbol in elf.symbols():
        if symbol['bind'] not in (1, 2) or symbol['name'] not in expected:
            continue
        index = symbol['shndx']
        if not 0 < index < len(elf.sections):
            continue
        owner = inputs.get(elf.sections[index]['name'])
        if owner and owner['start'] + symbol['value'] != expected[symbol['name']]:
            return 'data-symbol'
    return None


def validate_inputs(elf, ranges, placement, following_input=None):
    """Require correctly typed complete inputs, or proven adjacent NOBITS tails.

    ``following_input(section, address)`` must return the actual next linked ELF
    section record, never an alignment guessed from a label or manifest value.
    Omitting this evidence preserves strict complete-input validation.
    """
    for r in ranges:
        entries = placement['sections'].get(r['section'], [])
        matches = [e for e in entries if e.get('key') == r['start'] and e.get('end') == r['end']]
        if len(matches) != 1:
            return 'data-layout'
        section = elf.section(r['input'])
        if section is None or section['type'] != SECTIONS[r['section']]:
            return 'data-section'
        if section['size'] != r['end'] - r['start'] and not nobits_tail_fits(
                section, r, entries, following_input):
            return 'data-size'
        alignment = section['align']
        if alignment < 1 or alignment & (alignment - 1) or r['start'] % alignment:
            return 'data-align'
        # A const initialized object can be read-only in its input while the
        # explicit placement supplies the retail writable output section. The
        # final ELF check verifies output flags as well as bytes. NOBITS remains AW.
        flags = section.get('flags', 3) & 7
        allowed_flags = (2,) if r['section'] == '.rodata' else (2, 3) if section['type'] == 1 else (3,)
        if flags not in allowed_flags:
            return 'data-flags'
    return None


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__, epilog=(
        'data_ranges: [{section: .data, input: .data.my_tu, start: 0x1000, end: 0x1040}, '
        '{section: .rodata, input: .rodata, start: 0x2000, end: 0x2040}]'))
    parser.parse_args()
    parser.print_help()
