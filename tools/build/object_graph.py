#!/usr/bin/env python3
"""Generate real assembler includes and ordinary per-object Ninja edges from the split image."""
import argparse
import json
import re
from pathlib import Path
import sys
sys.path[:0] = [str(Path(__file__).resolve().parents[1]), str(Path(__file__).resolve().parent)]
from asm_syntax import translate
from splits import group_splits, load_splits
from units import load_units
from split_objects import write_if_changed

ROOT = Path(__file__).resolve().parents[2]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('version')
    ap.add_argument('--non-matching', action='store_true')
    a = ap.parse_args()
    slug = a.version
    build = Path('build') / slug
    out = Path(str(build) + ('-nm' if a.non_matching else ''))
    out.mkdir(parents=True, exist_ok=True)
    placement = json.loads((build / 'placement.json').read_text())
    units = load_units(variant=slug, refresh=True, facts=False)
    ownership = {f['addr']: u for u in units for f in u['functions']
                 if any(lo <= f['addr'] < hi for lo,hi in u.get('ranges', [u['range']]))}
    funcs = {f['addr']: f for f in placement['functions']}
    aliases, objects, edges = {}, [], []
    includes = {}
    for addr, u in ownership.items():
        f = funcs[addr]
        original = Path(placement['objects'][f['obj']]['src'])
        directory = Path('asm') / slug / 'nonmatchings' / Path(u['source']).relative_to('src').with_suffix('')
        path = directory / (f['name'] + '.s')
        sn = '-snas' in u['flags'] or any(x.startswith('--assembler=sn-') for x in u['flags'])
        text, extra = translate(original.read_text(), sn=sn)
        write_if_changed(path, text)
        aliases.update(extra)
        includes.setdefault(u['name'], []).append(path.as_posix())
    (out / 'asm_aliases.ld').write_text('\n'.join('%s = %s;' % x for x in sorted(aliases.items())) + '\n')
    layout = json.loads((build / 'layout.json').read_text())
    limits = {s['name']: s['addr']+s.get('orig_size', 0) for s in layout['sections']}
    all_slots = {}
    for sec, entries in placement['sections'].items():
        if sec == '.text':
            continue
        for i, e in enumerate(entries):
            if e.get('owner'):
                stop = entries[i+1].get('key') if i+1 < len(entries) else None
                all_slots.setdefault(e['owner'], []).append((sec, e['key'], stop or limits[sec]))
    for u in units:
        flags = list(u['flags'])
        if a.non_matching:
            flags.append('-DNON_MATCHING')
        u['functions'] = [f for f in u['functions'] if any(lo <= f['addr'] < hi for lo, hi in u.get('ranges', [u['range']]))]
        slots = {}
        for f in u['functions']:
            for sec, low, high in all_slots.get('func_%08X' % f['addr'], []):
                slots.setdefault(sec, []).append([low, high, f['addr']])
        objects.append(dict(name='units/' + u['name'], kind='cc', src=u['source'], compiler=u['compiler'],
                            flags=flags, slots=slots, includes=includes.get(u['name'], []), unit=u))
    # Functions without source belong to one assembly segment, never one object per function.
    remaining = [f for f in placement['functions'] if f['addr'] not in ownership]
    if remaining:
        source = Path('asm') / slug / 'text_units.s'
        lines = [re.sub(r'^\.section \.text\.[^\n]+', '.text', Path(placement['objects'][f['obj']]['src']).read_text(), flags=re.M) for f in remaining]
        write_if_changed(source, '\n'.join(lines) + '\n')
        objects.append(dict(name='asm/text', kind='asm', src=str(source), includes=[placement['objects'][f['obj']]['src'] for f in remaining]))
    text_objects = {f['obj'] for f in placement['functions']}
    for name, spec in placement['objects'].items():
        if name not in text_objects:
            objects.append(dict(spec, name=name))
    for o in objects:
        spec = out / 'spec' / (o['name'] + '.json')
        obj = out / 'obj' / (o['name'] + '.o')
        write_if_changed(spec, json.dumps(o, sort_keys=True) + '\n')
        edges += ['build %s: object %s | %s tools/build/object_compile.py tools/build/assembler.py tools/build/elfobj.py' %
                  (obj, o['src'], spec), '  spec = ' + str(spec)]
        if o.get('includes'):
            # Assembly includes are not reported by compiler -M.
            edges[-2] += ' ' + ' '.join(o['includes'])
        if o['kind'] == 'cc':
            base = out / 'objdiff/base' / (o['unit']['name'] + '.o')
            target = out / 'objdiff/target' / (o['unit']['name'] + '.o')
            edges += ['build %s | %s: objdiff_unit %s | %s tools/objdiff.py' % (base, target, obj, spec), '  spec = ' + str(spec), '  base = ' + str(base)]
    edges += ['build objdiff_objects: phony ' + ' '.join(str(out/'objdiff/base'/(o['unit']['name']+'.o')) for o in objects if o['kind']=='cc')]
    listing = out / 'unit_objects.json'
    write_if_changed(listing, json.dumps(objects, indent=1) + '\n')
    edges += ['build %s/linked.elf: unit_link %s | %s tools/build/unit_link.py %s/asm_aliases.ld' %
              (out, ' '.join(str(out / 'obj' / (o['name'] + '.o')) for o in objects), listing, out)]
    write_if_changed(out / 'objects.ninja', '\n'.join(edges) + '\n')
    print('%d source objects, %d assembly objects' % (len(units), len(objects)-len(units)))


if __name__ == '__main__':
    main()
