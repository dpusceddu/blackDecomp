#!/usr/bin/env python3
"""Place unit input sections in original order and invoke the ordinary GNU link once."""
import argparse
import bisect
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
sys.path[:0] = [str(Path(__file__).resolve().parents[1]), str(Path(__file__).resolve().parent)]
from elfinfo import Elf
from splits import load_symbols
from make_ld import migrated_data_aliases, explicit_data_aliases
from source_data import source_ranges
from object_compile import environment


def plan_objects(objects, placement):
    """Select actual sections; no size gate is imposed on individual object builds."""
    by_function, by_name = {}, {o['name']: o for o in objects}
    for o in objects:
        for f in o.get('unit', {}).get('functions', []):
            if any(lo <= f['addr'] < hi for lo, hi in o['unit'].get('ranges', [o['unit']['range']])):
                by_function[f['addr']] = o
    sections, used = {}, {}
    by_func_name = {f['name']: f for f in placement['functions']}
    by_func_obj = {f['obj']: f for f in placement['functions']}
    explicit_at = {(r['section'], int(r['start'], 0) if isinstance(r['start'], str) else r['start']): (o['name'], r['input'])
                   for o in objects for r in o.get('unit', {}).get('data_ranges', [])}
    for section, entries in placement['sections'].items():
        seq = []
        for entry in entries:
            f = by_func_name.get(entry.get('owner'))
            if section == '.text':
                f = by_func_obj.get(entry['obj'])
            o = by_function.get(f['addr']) if f else None
            if o:
                target = o['name']
                addr = f['addr']
                info = next(x for x in o['unit']['functions'] if x['addr'] == addr)
                if section == '.text':
                    name = o['resolved'][str(addr)]['section']
                elif info['status'] == 'source':
                    name = section
                else:
                    name = entry['sec']
                    if section == '.lit4':
                        target = entry['obj']
            else:
                target = entry['obj']
                if section == '.text':
                    target = 'asm/text'
                name = '.text' if section == '.text' else entry['sec']
                if entry.get('owner') and target not in by_name:
                    target = 'asm/text'
            explicit = explicit_at.get((section, entry.get('key')))
            if explicit:
                target, name = explicit
            key = (target, name)
            if target not in by_name or key in used.get(section, set()):
                continue
            used.setdefault(section, set()).add(key)
            seq.append((target, name, entry.get('key')))
        sections[section] = seq
    return sections


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('version')
    ap.add_argument('--non-matching', action='store_true')
    a = ap.parse_args()
    slug = a.version
    shared = Path('build') / slug
    out = Path(str(shared) + ('-nm' if a.non_matching else ''))
    objects = json.loads((out / 'unit_objects.json').read_text())
    layout = json.loads((shared / 'layout.json').read_text())
    placement = json.loads((shared / 'placement.json').read_text())
    aliases = []
    replaced, facts = {}, {}
    symbols = load_symbols(slug)
    labels = json.loads((shared / 'labels.json').read_text())
    label_addrs = [a for a, _ in labels]
    global_labels = [(a,n) for a,n in labels if not n.startswith(('.', '$'))]
    global_addrs = [a for a,_ in global_labels]
    for o in objects:
        o['path'] = str(out / 'obj' / (o['name'] + '.o'))
        if o['kind'] != 'cc':
            continue
        state = json.loads(Path(o['path'] + '.json').read_text())
        o.update(state)
        import re
        for s in Elf(Path(o['path']).read_bytes()).symbols():
            m = re.fullmatch(r'context_func_([0-9A-F]{8})', s['name'])
            if m and s['shndx'] == 0:
                aliases.append('PROVIDE(%s = func_%s);' % (s['name'], m[1]))
        u = o['unit']
        for f in u['functions']:
            if str(f['addr']) in state['resolved']:
                f['status'] = state['resolved'][str(f['addr'])]['status']
        facts[u['name']] = dict(symbols={k: v['symbol'] for k, v in o['resolved'].items()}, externs=state['externs'])
        for f in u['functions']:
            if str(f['addr']) not in o['resolved']:
                continue
            r = o['resolved'][str(f['addr'])]
            original = 'func_%08X' % f['addr']
            if r['link_name'] != original:
                aliases.append('PROVIDE(%s = %s);' % (original, r['link_name']))
            if f['status'] == 'source':
                replaced[original] = o['name']
            lo = bisect.bisect_right(label_addrs, f['addr'])
            hi = bisect.bisect_left(label_addrs, f['addr']+f['size'])
            for address, label in labels[lo:hi]:
                aliases.append('PROVIDE(%s = %s + 0x%X);' % (label, r['link_name'], address-f['addr']))
        for name, addr in state['externs'].items():
            # Address names for code resolve to functions; data use the nearest retained label.
            index = bisect.bisect_right(global_addrs, addr)-1
            if index < 0:
                aliases.append('PROVIDE(%s$%X = 0x%X);' % (name, addr, addr))
            else:
                address, label = global_labels[index]
                aliases.append('PROVIDE(%s$%X = %s + 0x%X);' % (name, addr, label, addr-address))
    explicit = source_ranges([o['unit'] for o in objects if o['kind'] == 'cc'])
    aliases += migrated_data_aliases(placement, labels, replaced, layout)
    aliases += explicit_data_aliases(explicit, labels, layout)
    sections = plan_objects(objects, placement)
    lines = ['ENTRY(%s)' % layout['entry_symbol'], (shared / 'symbols.ld').read_text(),
             (out / 'asm_aliases.ld').read_text()] + list(dict.fromkeys(aliases))
    lines += ['SECTIONS {', ' . = 0x%X;' % layout['segment']['vaddr']]
    for s in layout['sections']:
        if s['source'] != 'linked':
            continue
        name = s['name']
        lines.append(' %s ALIGN(%d)%s : {' % (name, s['align'], ' (NOLOAD)' if s['type'] == 8 else ''))
        for obj, sec, _ in sections.get(name, []):
            lines.append(' %s/obj/%s.o(%s)' % (out, obj, sec))
        lines.append(' }')
        if name == layout['gp']['section']:
            lines.append(' _gp = ADDR(%s) + 0x%X;' % (name, layout['gp']['offset']))
        if name == '.bss':
            lines.append(' __end_bss = .;')
    lines += [' /DISCARD/ : { *(*) }', '}']
    (out / 'link.ld').write_text('\n'.join(lines) + '\n')
    (out / 'unit_facts.json').write_text(json.dumps(facts))
    if a.non_matching:
        (out/'nm_fallback.json').write_text(json.dumps({o['name']:o['draft_fallback'] for o in objects if o.get('draft_fallback')},indent=2)+'\n')
    (out / 'objects.json').write_text(json.dumps(objects))
    # Compatibility for read-only analysis tools; these are ordinary objects, not a content-hash cache.
    (out / 'objects_cache.json').write_text(json.dumps({o['name']: 'obj/' + o['name'] + '.o' for o in objects}))
    base, env = environment()
    args = [env['BLACK_BINUTILS_PREFIX'] + 'ld', '-m', 'elf32ltsmip', '-nostdlib', '-static', '-z', 'norelro',
            '-z', 'noseparate-code', '--no-warn-rwx-segments', '-T', str(out / 'link.ld'), '-Map', str(out / 'link.map'),
            '-o', str(out / 'linked.elf')]
    response = out / 'objects.rsp'
    used = {obj for entries in sections.values() for obj, _, _ in entries}
    response.write_text('\n'.join(o['path'] for o in objects if o['name'] in used) + '\n')
    p = subprocess.run(args + ['@' + str(response)], env=env, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    (out / 'link.log').write_text(p.stdout)
    print(p.stdout, end='')
    raise SystemExit(p.returncode)


if __name__ == '__main__':
    main()
