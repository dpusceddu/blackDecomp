#!/usr/bin/env python3
"""Cut splat's output into one assembly file (and later one object) per function, migrating constants with them.

Reads  asm/<slug>/text.s and asm/<slug>/data/*.s (splat), build/<slug>/extra_labels.txt (link_support.py),
       config/<boot>.layout.json.
Writes build/<slug>/s/text/<function>.s       one function: its `.extern` block, code, and the constants only it uses
       build/<slug>/s/<section>/<section>.<address>.s   the shared remainder of .rodata, .lit4 and .gcc_except_table
       build/<slug>/placement.json            objects, their sources, and the original order of every output section

Constant migration (the equivalent of splat's rodata migration, for .rodata, .lit4 and .gcc_except_table):
a splat data object (dlabel .. enddlabel) belongs to a function when exactly one function refers to its address
and no data refers to it; an exception table belongs to the function that contains all its handler labels. Owned
objects are appended to the function's file in their own section. A function keeps one contiguous run of objects
per section (the linker places an input section as a whole, so a run must be adjacent in the original); other
objects stay shared. `.align` directives are checked so that every object's start address satisfies its own
alignments: objects are cut at an inner `.align` that the start does not guarantee, and shared runs are cut
where the alignment of the run's start would be violated.
Usage: split_objects.py VARIANT_SLUG [WORK]
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import bisect, json, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(Path(__file__).resolve().parent))
from fixasm import process, load_labels  # noqa: E402

MIGRATED = ('.rodata', '.lit4', '.gcc_except_table')
REF = re.compile(r'\b(?:D|jtbl|ehtbl|STR)_([0-9A-F]{8})\b(?:\s*\+\s*(0x[0-9A-Fa-f]+))?')
CODE_REF = re.compile(r'(?:\$LEH_|\.L)([0-9A-F]{8})\b')
ITEM = re.compile(r'/\* [0-9A-F]+ ([0-9A-F]{8})')
GPREL = re.compile(r'gp_rel: \((\w+)')
ALIGN = re.compile(r'^\.(?:align|balign)\s+(\d+)')
HEADER = ['.include "macro.inc"', '', '.set noat', '.set noreorder', '.set nomacro', '']
SECTION_FLAGS = {'.rodata': '"a"', '.lit4': '"wa"', '.gcc_except_table': '"aw"'}


def ctz(v):
    return (v & -v).bit_length() - 1


def write_if_changed(path, text):
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


# ---------------------------------------------------------------- text

def split_functions(lines):
    """Return [(name, addr, lines)] with each function's header block (`.extern`, `.align`) attached."""
    starts = [i for i, l in enumerate(lines) if l.startswith(('glabel func_', 'dlabel func_'))]
    prefix_ok = lambda l: l == '' or l == '.align 3' or l.startswith(('/* Handwritten', '.extern', '/* Symbols accessed'))
    begins = []
    for i in starts:
        j = i
        while j > 0 and prefix_ok(lines[j - 1]):
            j -= 1
        begins.append(j)
    funcs = []
    for k, i in enumerate(starts):
        end = begins[k + 1] if k + 1 < len(starts) else len(lines)
        name = lines[i].split()[1]
        funcs.append((name, int(name[-8:], 16), lines[begins[k]:end]))
    return funcs


def trim(lines):
    while lines and lines[-1] == '':
        lines = lines[:-1]
    return lines


# ---------------------------------------------------------------- constants

def parse_objects(path):
    """Split a splat data file into dlabel..enddlabel objects: [{name, addr, lines}]."""
    objs, pending, cur = [], [], None
    for l in path.read_text().split('\n'):
        if cur is None:
            if l.startswith('dlabel '):
                cur = dict(name=l.split()[1], lines=pending + [l])
                cur['addr'] = int(cur['name'][-8:], 16)
                pending = []
            elif l == '' or ALIGN.match(l) or l.startswith('/* Automatically'):
                pending.append(l)
        else:
            assert not l.startswith('dlabel '), 'nested dlabel in %s: %s' % (path.name, l)
            cur['lines'].append(l)
            if l.startswith('enddlabel '):
                objs.append(cur)
                cur = None
    assert cur is None
    return objs


def split_scalar_type_tails(objects, literal_at):
    """Separate a four-byte scalar from a following GCC type-name literal.

    Splat sometimes interprets a scalar-plus-type-name run as floats or words.
    Only a complete legacy encoded class name or a standard runtime exception
    name at the second four-byte item establishes this boundary. References and
    ownership are recomputed for both objects after splitting.
    """
    from class_skeletons import decode_name
    out = []
    for obj in objects:
        items = [(i, ITEM.match(line.strip())) for i, line in enumerate(obj['lines'])]
        items = [(i, int(m.group(1), 16)) for i, m in items if m]
        if len(items) < 2 or items[0][1] != obj['addr'] or items[1][1] != obj['addr'] + 4:
            out.append(obj)
            continue
        first, boundary = items[0][0], items[1][0]
        if not re.search(r'\*/\s+\.(?:word|float)\s', obj['lines'][first]):
            out.append(obj)
            continue
        name = literal_at(obj['addr'] + 4)
        valid = name in ('bad_alloc', 'bad_cast', 'bad_typeid')
        if name and (name.startswith('Q') or name[0].isdigit()):
            _, decoded = decode_name(name)
            valid = valid or decoded
        if not valid:
            out.append(obj)
            continue
        label = 'D_%08X' % (obj['addr'] + 4)
        out.append(dict(name=obj['name'], addr=obj['addr'],
                        lines=obj['lines'][:boundary] + ['enddlabel ' + obj['name']]))
        tail = ['dlabel ' + label] + obj['lines'][boundary:]
        tail[-1] = 'enddlabel ' + label
        out.append(dict(name=label, addr=obj['addr'] + 4, lines=tail))
    return out


DIRECTIVE = re.compile(r'\*/\s+(\.\w+)')
IMPLIED = {'.short': 1, '.half': 1, '.word': 2, '.float': 2, '.dword': 3, '.double': 3, '.quad': 3}   # log2; gas aligns these


def need(line):
    """log2 of the alignment a line demands: an explicit `.align`, or the implicit alignment of a data directive."""
    a = ALIGN.match(line)
    if a:
        return int(a.group(1))
    m = DIRECTIVE.search(line)
    return IMPLIED.get(m.group(1), 0) if m else 0


def pieces(obj):
    """Cut an object where an alignment is not guaranteed by the alignment of its start address (an inner `.align`, or
    a `.short`/`.word`/... after a byte string: the assembler aligns those, so the piece would have to start earlier)."""
    lines = obj['lines']
    last_item = max([i for i, l in enumerate(lines) if ITEM.match(l.strip())] or [0])
    out, cur, head = [], [], None
    for i, l in enumerate(lines):
        m = ITEM.match(l.strip())
        if head is not None and i < last_item and need(l) > ctz(head) and cur:
            out.append((head, cur))
            cur, head = [], None
        if m and head is None:
            head = int(m.group(1), 16)
        cur.append(l)
    out.append((head if head is not None else obj['addr'], cur))
    res = []
    for n, (h, ls) in enumerate(out):
        res.append(dict(name=obj['name'] if n == 0 else '%s_p%d' % (obj['name'], n), obj=obj['name'], addr=h,
                        align=max([need(x) for x in ls] or [0]), lines=ls))
    return res


def build_runs(units, owners):
    """Group consecutive units with the same owner. A run must start at an address that satisfies the largest
    `.align` inside it; a run that does not is merged into its predecessor (and becomes shared if the owners differ)."""
    runs = []
    for u in units:
        o = owners.get(u['name'])
        r = runs[-1] if runs else None
        if r and r['owner'] == o and r['head'] % (1 << max(r['align'], u['align'])) == 0:
            r['units'].append(u)
            r['align'] = max(r['align'], u['align'])
        else:
            runs.append(dict(owner=o, head=u['addr'], align=u['align'], units=[u]))
        while len(runs) > 1 and runs[-1]['head'] % (1 << runs[-1]['align']):
            b = runs.pop()
            a = runs[-1]
            a['units'] += b['units']
            a['align'] = max(a['align'], b['align'])
            if a['owner'] != b['owner']:
                a['owner'] = None
    return runs


def main():
    slug = sys.argv[1]
    work = sys.argv[2] if len(sys.argv) > 2 else slug   # the asm/ and build/ directory names
    boot = json.loads((ROOT / 'config/variants.json').read_text())[slug]['boot']
    layout = json.loads((ROOT / 'config' / ('%s.layout.json' % boot)).read_text())
    build = ROOT / 'build' / work
    src = build / 's'
    asm = ROOT / 'asm' / work
    secinfo = {s['name']: s for s in layout['sections'] if s['source'] == 'linked'}

    # ---- functions
    raw = (asm / 'text.s').read_text().split('\n')
    funcs = split_functions(raw)
    labels = load_labels(build / 'extra_labels.txt')
    starts = [f[1] for f in funcs]
    assert starts == sorted(starts)

    # ---- constant objects
    units_by_sec, owners = {}, {}
    all_objs = {}
    for sec in MIGRATED:
        p = asm / 'data' / ('%s.%s.s' % (sec[1:], sec[1:]))
        objs = parse_objects(p)
        if sec == '.rodata':
            from elfinfo import Elf
            image = Elf((ROOT / 'orig' / slug / 'files' / boot).read_bytes())
            rodata = image.section(sec)
            data = image.content(rodata)

            def literal_at(address):
                offset = address - rodata['addr']
                if not 0 <= offset < len(data):
                    return None
                window = data[offset:offset + 1024]
                stop = window.find(b'\0')
                if stop < 0:
                    return None
                raw = window[:stop]
                try:
                    return raw.decode('ascii') if raw else None
                except UnicodeDecodeError:
                    return None

            objs = split_scalar_type_tails(objs, literal_at)
        units_by_sec[sec] = [u for o in objs for u in pieces(o)]
        all_objs[sec] = objs
    obj_starts = {sec: [o['addr'] for o in objs] for sec, objs in all_objs.items()}
    sec_range = {sec: (secinfo[sec]['addr'], secinfo[sec]['addr'] + secinfo[sec]['orig_size']) for sec in MIGRATED}

    def find_obj(addr):
        for sec in MIGRATED:
            lo, hi = sec_range[sec]
            if lo <= addr < hi:
                i = bisect.bisect_right(obj_starts[sec], addr) - 1
                return (sec, i) if i >= 0 else None
        return None

    refs = {}     # (sec, index) -> set of referring function addresses
    dataref = set()
    for name, addr, lines in funcs:
        for l in lines:
            if '*/' not in l:
                continue
            for m in REF.finditer(l.split('*/', 1)[1]):
                a = int(m.group(1), 16) + (int(m.group(2), 16) if m.group(2) else 0)
                k = find_obj(a)
                if k:
                    refs.setdefault(k, set()).add(addr)
    # references from data: every data file, except an object's own label lines
    for p in sorted((asm / 'data').glob('*.s')):
        sec = '.' + p.name.split('.')[0]
        own = None
        for l in p.read_text().split('\n'):
            if l.startswith('dlabel '):
                own = find_obj(int(l.split()[1][-8:], 16)) if sec in MIGRATED else None
                continue
            if l.startswith('enddlabel '):
                own = None
                continue
            if 'D_' not in l and 'jtbl_' not in l and 'ehtbl_' not in l and 'STR_' not in l:
                continue
            for m in REF.finditer(l):
                a = int(m.group(1), 16) + (int(m.group(2), 16) if m.group(2) else 0)
                k = find_obj(a)
                if k and k != own:
                    dataref.add(k)
    # ownership
    stats, owner_of_obj, reasons = {}, {}, {}
    for sec in MIGRATED:
        for idx, o in enumerate(all_objs[sec]):
            k = (sec, idx)
            owner = None
            if sec == '.gcc_except_table':
                targets = {int(m.group(1), 16) for l in o['lines'] for m in CODE_REF.finditer(l)}
                fs = {starts[bisect.bisect_right(starts, t) - 1] for t in targets}
                if len(fs) == 1:
                    owner = fs.pop()
            elif k in refs and len(refs[k]) == 1 and k not in dataref:
                owner = next(iter(refs[k]))
            reason = 'owned' if owner is not None else 'data' if k in dataref else 'multi' if len(refs.get(k, ())) > 1 \
                else 'unreferenced' if k not in refs else 'other'
            reasons[(sec, o['name'])] = reason
            owner_of_obj[(sec, o['name'])] = owner
    for sec in MIGRATED:
        for u in units_by_sec[sec]:
            owners[u['name']] = owner_of_obj[(sec, u['obj'])]

    # ---- runs; a function keeps one run per section, the largest
    final = {}
    for sec in MIGRATED:
        units = units_by_sec[sec]
        for _ in range(8):
            runs = build_runs(units, owners)
            for r in runs:
                for u in r['units']:
                    owners[u['name']] = r['owner']
            best = {}
            for r in runs:
                if r['owner'] is not None and (r['owner'] not in best or len(r['units']) > len(best[r['owner']]['units'])):
                    best[r['owner']] = r
            keep = {id(r) for r in best.values()}
            changed = False
            for r in runs:
                if r['owner'] is not None and id(r) not in keep:
                    for u in r['units']:
                        owners[u['name']] = None
                    changed = True
            if not changed:
                break
        final[sec] = runs

    # ---- write objects
    placement = dict(objects={}, sections={s: [] for s in ('.text', '.vutext', '.data', '.vudata', '.rodata',
                                                             '.gcc_except_table', '.lit4', '.sdata', '.sbss', '.bss')},
                     functions=[])
    func_runs = {}
    for sec in MIGRATED:
        for r in final[sec]:
            if r['owner'] is not None:
                func_runs.setdefault(r['owner'], {})[sec] = r
    for sec in MIGRATED:
        for r in final[sec]:
            if r['owner'] is None:
                oname = '%s/%s.%08X' % (sec[1:], sec[1:], r['head'])
                body = ['.include "macro.inc"', '', '.section %s.%08X, %s' % (sec, r['head'], SECTION_FLAGS[sec]), '']
                for u in r['units']:
                    body += u['lines']
                write_if_changed(src / (oname + '.s'), '\n'.join(body) + '\n')
                placement['objects'][oname] = dict(src='build/%s/s/%s.s' % (work, oname), kind='asm')
                placement['sections'][sec].append(dict(obj=oname, sec='%s.%08X' % (sec, r['head']), key=r['head']))
            else:
                fname = next(f[0] for f in funcs if f[1] == r['owner'])
                placement['sections'][sec].append(dict(obj='text/' + fname + ('.lit4' if sec == '.lit4' else ''),
                                                       sec='%s.%08X' % (sec, r['head']), key=r['head'], owner=fname))
    nraw = 0
    for name, addr, lines in funcs:
        body, n = process(trim(lines), labels)
        nraw += n
        # splat declares a $gp-relative symbol once per file; every function file needs its own declarations
        declared = {l.split()[1].rstrip(',') for l in body if l.startswith('.extern ')}
        used = sorted({m.group(1) for l in body for m in GPREL.finditer(l)} - declared)
        text = list(HEADER) + ['.section .text.%08X, "ax"' % addr, ''] + ['.extern %s, 1' % x for x in used] + [''] + body
        owned = {}
        runs = func_runs.get(addr, {})
        for sec, r in sorted(runs.items()):
            if sec == '.lit4':   # a symbol defined next to the code that addresses it off $gp trips the assembler
                continue
            text += ['', '.section %s.%08X, %s' % (sec, r['head'], SECTION_FLAGS[sec]), '']
            for u in r['units']:
                text += u['lines']
            owned[sec] = len(r['units'])
        if '.lit4' in runs:
            owned['.lit4'] = len(runs['.lit4']['units'])
            lit = ['.include "macro.inc"', '', '.section .lit4.%08X, "wa"' % runs['.lit4']['head'], '']
            for u in runs['.lit4']['units']:
                lit += u['lines']
            write_if_changed(src / 'text' / (name + '.lit4.s'), '\n'.join(lit) + '\n')
            placement['objects']['text/%s.lit4' % name] = dict(src='build/%s/s/text/%s.lit4.s' % (work, name), kind='asm')
        oname = 'text/' + name
        write_if_changed(src / (oname + '.s'), '\n'.join(text) + '\n')
        placement['objects'][oname] = dict(src='build/%s/s/%s.s' % (work, oname), kind='asm')
        placement['sections']['.text'].append(dict(obj=oname, sec='.text.%08X' % addr, key=addr))
        last = [int(m.group(1), 16) for l in lines for m in [ITEM.match(l.strip())] if m]
        placement['functions'].append(dict(name=name, addr=addr, end=(max(last) + 4 if last else addr), obj=oname,
                                           owned=owned))
    # other sections: one splat file each
    for p in sorted((asm / 'data').glob('*.s')):
        sec = '.' + p.name.split('.')[0]
        if sec in MIGRATED or sec not in placement['sections']:
            continue
        oname = 'data/' + p.stem
        text = p.read_text()
        m = re.search(r'^\.section (\.[\w.]+)', text, re.M)
        placement['objects'][oname] = dict(src=p.relative_to(ROOT).as_posix(), kind='asm')
        placement['sections'][sec].append(dict(obj=oname, sec=m.group(1)))
    # statistics: constant bytes migrated per section
    for sec in MIGRATED:
        lo, hi = sec_range[sec]
        objs = all_objs[sec]
        total = hi - lo
        moved = 0
        for r in final[sec]:
            if r['owner'] is None:
                continue
            a0 = r['units'][0]['addr']
            last = r['units'][-1]
            nxt = min([o['addr'] for o in objs if o['addr'] > last['addr']] or [hi])
            moved += nxt - a0
        why = {}
        for i, o in enumerate(objs):
            size = (objs[i + 1]['addr'] if i + 1 < len(objs) else hi) - o['addr']
            r = reasons[(sec, o['name'])]
            if r == 'owned' and owners.get(o['name']) is None:
                r = 'owner run lost'
            why[r] = why.get(r, 0) + size
        stats[sec] = dict(why=why, total=total, migrated=moved, functions=sum(1 for o in func_runs.values() if sec in o),
                          shared_runs=sum(1 for r in final[sec] if r['owner'] is None))
    placement['stats'] = stats
    # every global label with its address, for resolving external references of compiled code
    lab = re.compile(r'^\s*(?:glabel|jlabel|alabel|dlabel|ehlabel)\s+(\S+)')
    labels_out = {}
    sources = [p for p in raw] + [l for p in sorted((asm / 'data').glob('*.s')) for l in p.read_text().split('\n')]
    for l in sources:
        m = lab.match(l)
        if m and re.search(r'[0-9A-F]{8}$', m.group(1)):
            labels_out[int(m.group(1)[-8:], 16)] = m.group(1)
    for ln in (build / 'extra_labels.txt').read_text().split('\n'):
        if ln.strip():
            n, a = ln.split()
            labels_out.setdefault(int(a, 16), n)
    (build / 'labels.json').write_text(json.dumps(sorted(labels_out.items())))
    (build / 'placement.json').write_text(json.dumps(placement, indent=1))
    for sec, v in stats.items():
        print(sec, 'by reason (bytes):', v['why'])
    print('%d functions, %d branches as raw words; migrated: %s' % (
        len(funcs), nraw, ', '.join('%s %d/%d bytes (%d functions, %d shared runs)' % (
            s, v['migrated'], v['total'], v['functions'], v['shared_runs']) for s, v in stats.items())))


if __name__ == '__main__':
    main()
