#!/usr/bin/env python3
"""Write the GNU ld script and the object list for the rebuild.

Every loaded section is placed by alignment only (no hard-coded addresses except the image base), so sizes can change.
The input order of each section is the original order recorded by split_objects.py (build/<slug>/placement.json):
one object per function, shared constant runs, and splat's data files. A function listed with `status: source` in
config/units.yaml is replaced by its unit's compiled object: the object takes the slot of the unit's first function in
every section it occupies, and the unit's other functions are dropped from the order. Their `func_XXXXXXXX` names are
defined as aliases of the compiled symbols, so assembly callers link against the source definition.
Writes build/<slug>/link.ld and build/<slug>/objects.json (name, kind, source, sections).
Usage: make_ld.py VARIANT_SLUG [WORK]
"""
import bisect, json, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from units import load_units

ROOT = Path(__file__).resolve().parents[1]


def main():
    slug = sys.argv[1]
    work = sys.argv[2] if len(sys.argv) > 2 else slug
    boot = json.loads((ROOT / 'config/variants.json').read_text())[slug]['boot']
    layout = json.loads((ROOT / 'config' / ('%s.layout.json' % boot)).read_text())
    build = ROOT / 'build' / work
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
    # Symbol names. A compiled unit defines its functions under the exact mangled name; the image's own names
    # (func_XXXXXXXX, referenced by assembly) become aliases of those. The same mangled name can be defined at several
    # addresses (identical inline copies), and the name a unit leaves undefined is bound to one original address, so a
    # name that would be defined twice or bound to two addresses is made unique per address with a `$XXXXXX` suffix.
    live_units = []
    for u in load_units(variant=slug):
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
    for u, src in live_units:
        uname = 'units/' + u['name']
        objects[uname] = dict(name=uname, kind='cc', src=u['source'], compiler=u['compiler'], flags=u['flags'])
        positions = sorted(index[f['addr']] for f in src if f['addr'] in index)
        if positions != list(range(positions[0], positions[0] + len(positions))):
            problems.append('%s: source functions are not contiguous in the original order' % u['name'])
        for f in src:
            if f['addr'] not in func_by_addr:
                problems.append('%s: %#x is not a function start' % (u['name'], f['addr']))
                continue
            replaced[func_by_addr[f['addr']]['name']] = uname
            aliases.append('%s = %s;' % (func_by_addr[f['addr']]['name'], f['link_name']))
            # labels inside the function (exception handlers, jump targets) that other objects still refer to:
            # the compiled code is byte-identical, so they sit at the same offsets from the function
            i = bisect.bisect_right(label_addrs, f['addr'])
            while i < len(labels) and labels[i][0] < f['addr'] + f['size']:
                aliases.append('%s = %s + 0x%X;' % (labels[i][1], f['link_name'], labels[i][0] - f['addr']))
                i += 1
    if problems:
        raise SystemExit('\n'.join(problems))
    aliases = list(dict.fromkeys(aliases))
    # Input order. ld resolves a script with one statement per object quadratically (hours for 12,000 objects), so
    # the migrated sections are placed by sorted input-section names instead: every input section is called
    # `<section>.<8 hex digits of its original address>` and `*(SORT_BY_NAME(<section>.*))` restores the order.
    # A unit's object takes the key of the first slot it replaces in each section (its sections are renamed at link
    # time); the slots of its other functions simply disappear.
    sorted_secs = ('.text', '.rodata', '.lit4', '.gcc_except_table')
    objs_in_link, rename = [], {}
    sections = {}
    for sec, entries in placement['sections'].items():
        seq = []
        for e in entries:
            obj = e['obj']
            fn = e.get('owner') or (obj[len('text/'):] if obj.startswith('text/') and not obj.endswith('.lit4') else None)
            if fn in replaced:
                uname = replaced[fn]
                if sec in sorted_secs:
                    rename.setdefault(uname, {}).setdefault(sec, '%s.%08X' % (sec, e['key']))
                continue
            seq.append(e)
            objs_in_link.append(obj)
        sections[sec] = seq
    for uname in rename:
        objs_in_link.append(uname)
    out = ['/* Generated by tools/make_ld.py; do not edit. */', 'ENTRY(%s)' % layout['entry_symbol'], '']
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
    (build / 'link.ld').write_text('\n'.join(out))
    listing = []
    for n in dict.fromkeys(objs_in_link):
        o = dict(objects[n])
        if n in rename:
            o['rename'] = rename[n]
            o['redefine'] = redefine.get(n[len('units/'):], {})
        listing.append(o)
    (build / 'objects.json').write_text(json.dumps(listing, indent=1))
    print('link.ld: %d objects (%d replaced by source)' % (len(listing), len(replaced)))


if __name__ == '__main__':
    main()
