#!/usr/bin/env python3
"""Write the GNU ld script and the object list for the rebuild.

Every loaded section is placed by alignment only (no hard-coded addresses except the image base), so sizes can change.
The input order of each section is the original order recorded by split_objects.py (build/<GAME_ID>/placement.json):
one object per function, shared constant runs, and splat's data files. A function listed with `status: source` in
a function that a split of config/<GAME_ID>/splits.yaml compiles is replaced by the split's compiled object: the object takes the slot of the unit's first function in
every section it occupies, and the unit's other functions are dropped from the order. Their `func_XXXXXXXX` names are
defined as aliases of the compiled symbols, so assembly callers link against the source definition.
Writes build/<GAME_ID>/link.ld and build/<GAME_ID>/objects.json (build/<GAME_ID>-nm/ for the NON_MATCHING build) (name, kind, source, sections).
Usage: make_ld.py GAME_ID [WORK]
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import bisect, json, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / d) for d in ('', 'build', 'pipeline', 'maint')]
from units import load_units, out_dir
from source_data import source_ranges

ROOT = Path(__file__).resolve().parents[2]


def migrated_data_aliases(placement, labels, replaced, layout):
    """Keep names referenced by retained objects when source replaces owned constants.

    Compiler-generated tables usually expose different local names. Their original
    labels retain section-relative positions; full-image comparison still verifies
    every byte and relocation. PROVIDE leaves an explicit source definition intact.
    """
    aliases = []
    addresses = [address for address, _ in labels]
    for section in layout['sections']:
        name = section['name']
        if name not in ('.rodata', '.lit4', '.gcc_except_table'):
            continue
        entries = placement['sections'].get(name, [])
        for index, entry in enumerate(entries):
            owner = entry.get('owner')
            if owner not in replaced:
                continue
            start = entry['key']
            end = entries[index + 1]['key'] if index + 1 < len(entries) else section['addr'] + section['orig_size']
            for address, label in labels[bisect.bisect_left(addresses, start):bisect.bisect_left(addresses, end)]:
                if not label.startswith(('.', '$')):
                    aliases.append('PROVIDE(%s = ADDR(%s) + 0x%X);' %
                                   (label, name, address - section['addr']))
    return aliases


def explicit_data_aliases(ranges, labels, layout):
    """Retain all original labels inside explicitly replaced source storage."""
    bases = {s['name']: s['addr'] for s in layout['sections']}
    return ['PROVIDE(%s = ADDR(%s) + 0x%X);' % (label, r['section'], address - bases[r['section']])
            for r in ranges for address, label in labels
            if r['start'] <= address < r['end'] and not label.startswith(('.', '$'))]


def main():
    slug = sys.argv[1]
    work = sys.argv[2] if len(sys.argv) > 2 else slug
    boot = json.loads((ROOT / 'config/versions.json').read_text())[slug]['boot']
    layout = json.loads((ROOT / 'config' / boot / 'layout.json').read_text())
    build = ROOT / 'build' / work
    outdir = out_dir(slug) if work == slug else build
    outdir.mkdir(parents=True, exist_ok=True)
    placement = json.loads((build / 'placement.json').read_text())
    objects = {name: dict(o, name=name) for name, o in placement['objects'].items()}
    func_by_name = {f['name']: f for f in placement['functions']}
    func_by_addr = {f['addr']: f for f in placement['functions']}
    labels = json.loads((build / 'labels.json').read_text())
    label_addrs = [a for a, _ in labels]
    secs = [(r['name'], r['addr'], r['addr'] + r['orig_size']) for r in layout['sections']
            if r['source'] == 'linked' and r['orig_size']]

    def resolve(addr):
        """Express an original address as `label + delta` with the nearest label in the same section."""
        sec = next(s for s in secs if s[1] <= addr < s[2])
        i = bisect.bisect_right(label_addrs, addr) - 1
        while i >= 0 and (label_addrs[i] < sec[1] or labels[i][1].startswith(('.', '$'))):
            i -= 1
        if i < 0:
            raise SystemExit('no label before %#x' % addr)
        a, name = labels[i]
        return name if a == addr else '%s + 0x%X' % (name, addr - a)

    replaced, aliases, problems = {}, [], []
    all_units = load_units(variant=slug)
    explicit_data = source_ranges(all_units)
    trims = {u['name']: u.get('trim') or {} for u in all_units}
    # Symbol names. A compiled unit defines its functions under the exact mangled name; the image's own names
    # (func_XXXXXXXX, referenced by assembly) become aliases of those. The same mangled name can be defined at several
    # addresses (identical inline copies), and the name a unit leaves undefined is bound to one original address, so a
    # name that would be defined twice or bound to two addresses is made unique per address with a `$XXXXXX` suffix.
    live_units = []
    for u in all_units:
        src = [f for f in u['functions'] if f.get('status') == 'source']
        if src:
            live_units.append((u, src))
    defs, binds = {}, {}
    for u, src in live_units:
        for f in src:
            defs.setdefault(f['symbol'], set()).add(f['addr'])
        for name, addr in u['externs'].items():
            binds.setdefault(name, set()).add(addr)
    redefine = {}
    for u, src in live_units:
        r = redefine.setdefault(u['name'], {})
        for f in src:
            f['link_name'] = f['symbol']
            if len(defs[f['symbol']]) > 1 or f['symbol'] in binds:
                f['link_name'] = '%s$%X' % (f['symbol'], f['addr'])
                r[f['symbol']] = f['link_name']
    defined = {f['link_name'] for _, src in live_units for f in src}
    for u, src in live_units:
        r = redefine[u['name']]
        for name, addr in sorted(u['externs'].items()):
            if name in defs or len(binds[name]) > 1:
                r[name] = '%s$%X' % (name, addr)
            if r.get(name, name) not in defined:      # else a unit already defines it, at this very address
                aliases.append('%s = %s;' % (r.get(name, name), resolve(addr)))
    index = {f['addr']: i for i, f in enumerate(placement['functions'])}
    fsym = {}                                         # address -> symbol, for the functions of units compiled with -ffunction-sections
    for u, src in live_units:
        uname = 'units/' + u['name']
        objects[uname] = dict(name=uname, kind='cc', src=u['source'], compiler=u['compiler'], flags=u['flags'])
        positions = sorted(index[f['addr']] for f in src if f['addr'] in index)
        if '-ffunction-sections' in u['flags']:      # one section per function: the unit may have assembly functions between its own
            for f in src:
                fsym[f['addr']] = f['symbol']
        elif positions != list(range(positions[0], positions[0] + len(positions))):
            problems.append('%s: source functions are not contiguous in the original order' % u['name'])
        for f in src:
            if f['addr'] not in func_by_addr:
                problems.append('%s: %#x is not a function start' % (u['name'], f['addr']))
                continue
            replaced[func_by_addr[f['addr']]['name']] = uname
            if func_by_addr[f['addr']]['name'] != f['link_name']:     # a draft keeps the image's own name
                aliases.append('%s = %s;' % (func_by_addr[f['addr']]['name'], f['link_name']))
            # labels inside the function (exception handlers, jump targets) that other objects still refer to:
            # the compiled code is byte-identical, so they sit at the same offsets from the function
            i = bisect.bisect_right(label_addrs, f['addr'])
            while i < len(labels) and labels[i][0] < f['addr'] + f['size']:
                aliases.append('%s = %s + 0x%X;' % (labels[i][1], f['link_name'], labels[i][0] - f['addr']))
                i += 1
    if problems:
        raise SystemExit('\n'.join(problems))
    aliases += migrated_data_aliases(placement, labels, replaced, layout)
    aliases += explicit_data_aliases(explicit_data, labels, layout)
    aliases = list(dict.fromkeys(aliases))
    # Input order. ld resolves a script with one statement per object quadratically (hours for 12,000 objects), so
    # the migrated sections are placed by sorted input-section names instead: every input section is called
    # `<section>.<8 hex digits of its original address>` and `*(SORT_BY_NAME(<section>.*))` restores the order.
    # A unit's object takes the key of the first slot it replaces in each section (its sections are renamed at link
    # time); the slots of its other functions simply disappear.
    sorted_secs = ('.text', '.rodata', '.lit4', '.gcc_except_table')
    objs_in_link, rename = [], {}
    sections = {}
    explicit_at = {(r['section'], r['start']): r for r in explicit_data}
    placed_data = set()
    for sec, entries in placement['sections'].items():
        seq = []
        for e in entries:
            data = explicit_at.get((sec, e.get('key')))
            if data:
                if e.get('end') != data['end']:
                    raise SystemExit('%s: data range is not an exact placement fragment' % data['unit'])
                uname = 'units/' + data['unit']
                output = '%s.%08X' % (sec, data['start'])
                rename.setdefault(uname, {})[data['input']] = output
                seq.append(dict(obj=uname, sec=output, key=data['start'], end=data['end']))
                objs_in_link.append(uname)
                placed_data.add((sec, data['start']))
                continue
            obj = e['obj']
            fn = e.get('owner') or (obj[len('text/'):] if obj.startswith('text/') and not obj.endswith('.lit4') else None)
            if fn in replaced:
                uname = replaced[fn]
                if sec in sorted_secs:
                    addr = func_by_name[fn]['addr']
                    if sec == '.text' and addr in fsym:        # the function's own section takes the function's slot
                        rename.setdefault(uname, {})['.text.' + fsym[addr]] = '%s.%08X' % (sec, e['key'])
                    else:
                        rename.setdefault(uname, {}).setdefault(sec, '%s.%08X' % (sec, e['key']))
                continue
            seq.append(e)
            objs_in_link.append(obj)
        sections[sec] = seq
    if placed_data != set(explicit_at):
        raise SystemExit('source data range absent from placement; rerun split_objects.py')
    for uname in rename:
        objs_in_link.append(uname)
    out = ['/* Generated by tools/build/make_ld.py; do not edit. */', 'ENTRY(%s)' % layout['entry_symbol'], '']
    sym = build / 'symbols.ld'
    if sym.exists():
        out += [sym.read_text(), '']
    out += aliases + ['', 'SECTIONS\n{', '    . = 0x%X;' % layout['segment']['vaddr']]
    for r in layout['sections']:
        if r['source'] != 'linked':
            continue
        n = r['name']
        if n == '.vubss':
            out.append('    .vubss (NOLOAD) : { }')
            continue
        noload = ' (NOLOAD)' if r['type'] == 8 else ''
        out.append('    %s ALIGN(%d)%s :\n    {' % (n, r['align'], noload))
        if n in sorted_secs:
            out.append('        *(SORT_BY_NAME(%s.*));' % n)
        else:
            for e in sections.get(n, []):
                out.append('        obj/%s.o(%s);' % (e['obj'], e['sec']))
        out.append('    }')
        if n == layout['gp']['section']:
            out.append('    _gp = ADDR(%s) + 0x%X;' % (n, layout['gp']['offset']))
        if n == '.bss':
            out.append('    __end_bss = .;')
    out += ['', '    /DISCARD/ : { *(*) }', '}', '']
    (outdir / 'link.ld').write_text('\n'.join(out))
    listing = []
    for n in dict.fromkeys(objs_in_link):
        o = dict(objects[n])
        if n in rename:
            o['rename'] = rename[n]
            o['redefine'] = redefine.get(n[len('units/'):], {})
            o['trim'] = trims.get(n[len('units/'):], {})
        listing.append(o)
    (outdir / 'objects.json').write_text(json.dumps(listing, indent=1))
    print('link.ld: %d objects (%d replaced by source)' % (len(listing), len(replaced)))


if __name__ == '__main__':
    main()
