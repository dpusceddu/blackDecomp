#!/usr/bin/env python3
"""Check the compiled source units against the original image; report what cannot be placed identically.

  units_verify.py prepare   after the compile step: read each unit's compiled object, resolve the names of its functions
                            (symbols.txt, else func_XXXXXXXX), bind the symbols it refers to (symbols.txt, split `externs`), and
                            report functions whose object does not fit (name, size, extra code, constants, unbound symbols).
                            Writes build/<GAME_ID>/unit_facts.json (read by tools/make_ld.py through tools/units.py) and
                            build/<GAME_ID>/unit_problems.json; exits 1 when there are problems
  units_verify.py link      after a failed link: read build/<GAME_ID>/link.log and name the units it complains about
  units_verify.py compare   after a link: compare the linked image with the target section by section and name the
                            functions (and source files) that own the differing words
Nothing under config/ or src/ is written. Reasons: compile, name, size, extra, extern, section, shared, layout, link, bytes.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, re, struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfinfo import Elf
from units import load_units, out_dir, non_matching, ROOT
import splits as SPL
from source_data import source_ranges, validate_inputs, validate_input_symbols, range_owner

SLUG = 'SLUS_213.76'
BUILD = ROOT / 'build' / SLUG
OUT = out_dir(SLUG)       # compile results, link log and image (build/<GAME_ID>-nm for the NON_MATCHING build)
PROBLEMS = []          # (unit name, address or None, reason), filled by demote()


def save(units):
    """Write the facts compilation taught (never the configuration): resolved symbols, extern bindings, trimmed constants,
    and the problems found."""
    facts = {}
    for u in units:
        if not u.get('assembly') and not any(f.get('status') == 'source' or f.get('reason') for f in u['functions']):
            continue
        entry = dict(symbols={str(f['addr']): f['symbol'] for f in u['functions'] if f.get('status') == 'source' and f.get('symbol')},
                     externs={k: hex(v) for k, v in sorted((u.get('externs') or {}).items())})
        if u.get('trim'):
            entry['trim'] = u['trim']
        if u.get('unbound'):
            entry['unbound'] = u['unbound']
        if u.get('assembly'):
            entry['assembly'] = u['assembly']
        facts[u['name']] = entry
    out = out_dir(SLUG)
    out.mkdir(parents=True, exist_ok=True)
    for name, text in (('unit_facts.json', json.dumps(facts, indent=1)), ('unit_problems.json', json.dumps(PROBLEMS, indent=1))):
        if not (out / name).exists() or (out / name).read_text() != text:       # keep the timestamp for ninja when nothing changed
            (out / name).write_text(text)


WHY = {'compile': 'does not compile', 'name': 'defines none of the names expected for the function',
       'size': 'size differs', 'extra': 'emits code the original does not have there (or INCLUDE_ASM and a definition for one function)',
       'extern': 'refers to symbols without an address (add them to symbols.txt)',
       'section': 'brings data or bss that is not placed', 'shared': 'uses constants the original shares between functions',
       'layout': 'constants of the assembly functions in between interleave with its own',
       'labels': 'a label inside it is still referenced', 'link': 'link error', 'bytes': 'differs from the original'}


def report(units, problems):
    """Readable lines for the problems: source file, function, reason."""
    by_name = {u['name']: u for u in units}
    lines = []
    for name, addr, reason in problems:
        u = by_name.get(name, {})
        where = 'func_%08X' % addr if addr is not None else 'whole file'
        lines.append('%s: %s: %s' % (u.get('source', name), where, WHY.get(reason, reason)))
    return lines


def demote(unit, funcs, reason):
    """Mark functions as assembly in memory (so the checks go on) and record the problem."""
    n = 0
    for f in unit['functions']:
        if f.get('status') == 'source' and (funcs is None or f['addr'] in funcs):
            f['status'], f['reason'] = 'asm', reason
            PROBLEMS.append((unit['name'], f['addr'], reason))
            n += 1
    return n


def cached_object(name):
    m = json.loads((OUT / 'objects_cache.json').read_text())
    p = BUILD / m.get('units/' + name, 'missing')
    return Elf(p.read_bytes()) if p.exists() else None


def bindings():
    """Legacy hook kept for callers: bindings now come from symbols.txt and the splits (see known_symbols)."""
    return {}


_SYMBOLS = None


def known_symbols():
    global _SYMBOLS
    if _SYMBOLS is None:
        _SYMBOLS = SPL.load_symbols(SLUG)
    return _SYMBOLS


def is_text(name):
    """`.text`, or a per-function section (-ffunction-sections)."""
    return name == '.text' or name.startswith('.text.')


def owned_data_gap_fits(size, start, stop, section, input_alignment):
    """A shorter data input may leave only real, naturally aligned zero fill."""
    from text_placement import InputAlignments, natural_text_span
    if size <= 0:
        return False
    original = Elf((ROOT / 'orig' / SLUG / 'SLUS_213.76').read_bytes())
    record = original.section(section)
    if record is None:
        return False
    data = original.content(record)
    low, high = start + size - record['addr'], stop - record['addr']
    if not 0 <= low <= high <= len(data):
        return False
    return natural_text_span(size, start, stop, InputAlignments(BUILD).data_at(section, stop),
                             data[low:high], input_alignment)


def kept_text_names(elf, symbols, live):
    """Only enabled function inputs participate in relocation/data validation."""
    wanted = {f['symbol'] for f in live}
    return {elf.sections[s['shndx']]['name'] for s in symbols
            if s['type'] == 2 and s['name'] in wanted and 0 < s['shndx'] < len(elf.sections)
            and is_text(elf.sections[s['shndx']]['name'])}


def valid_context_sections(elf, symbols, unit):
    """Opt-in context consists of declared real functions and named helpers.

    Helpers carry no original-address or evidence claim. References to a dropped
    helper from kept code still require a real original binding and may fail.
    """
    allowed = {f['symbol'] for f in unit['functions'] if f.get('symbol')}
    allowed.update(unit.get('unlinked_context_helpers', []))
    for section in elf.sections:
        if not is_text(section['name']) or not section['size']:
            continue
        if section['name'] == '.text':
            return False
        functions = [s for s in symbols if s['type'] == 2 and s['shndx'] == section['index']]
        if not functions or any(s['name'] not in allowed for s in functions):
            return False
    return True


def owned_constant_names(live, placement):
    """Unplaced context constants do not introduce bindings into kept code."""
    live_addresses = {f['addr'] for f in live}
    addresses = {f['name']: f['addr'] for f in placement['functions']}
    return {name for name in ('.rodata', '.lit4', '.gcc_except_table')
            if any(addresses.get(entry.get('owner')) in live_addresses
                   for entry in placement['sections'].get(name, []))}


def data_sections(e, syms, u, live, placement):
    """Constants and data the compiled unit brings along. Returns a reason when they cannot take the place of what the
    assembly objects carried: code refers to a section no original slot exists for, the slots are not adjacent, or the
    sizes differ."""
    by_name = {f['name']: f for f in placement['functions']}
    addrs = {f['addr'] for f in live}
    referenced = set()
    explicit_inputs = {r['input'] for r in u.get('data_ranges', [])}
    linked_text = kept_text_names(e, syms, live)
    for t in e.sections:
        if t['type'] == 9 and e.sections[t['info']]['name'] in linked_text:
            c = e.content(t)
            for o in range(0, len(c), 8):
                off, info = struct.unpack_from('<II', c, o)
                y = syms[info >> 8]
                if y['shndx'] not in (0, 0xfff1, 0xfff2):
                    name = e.sections[y['shndx']]['name']
                    # a global defined in a dropped section (a vtable emitted here) is bound to the original instead
                    if y['bind'] in (1, 2) and y['name'] and not is_text(name) and name not in ('.rodata', '.lit4', '.gcc_except_table'):
                        continue
                    referenced.add(name)
    for sec in sorted(x for x in referenced if not is_text(x)
                      and x not in ('.rodata', '.lit4', '.gcc_except_table') and x not in explicit_inputs):
        return 'section'              # own data or bss: not placed
    for sec in ('.rodata', '.lit4', '.gcc_except_table'):
        if sec in explicit_inputs:
            continue                 # strict complete-input validation owns this section
        ents = placement['sections'][sec]
        slots = [i for i, ent in enumerate(ents) if ent.get('owner') and by_name[ent['owner']]['addr'] in addrs]
        so = e.section(sec)
        size = so['size'] if so else 0
        if not slots:
            if sec in referenced:
                return 'shared'       # the original constants are not migrated to these functions
            continue
        if slots != list(range(slots[0], slots[0] + len(slots))):
            return 'layout'           # other objects sit between the slots
        end = ents[slots[-1] + 1]['key'] if slots[-1] + 1 < len(ents) and 'key' in ents[slots[-1] + 1] else None
        if end is not None:
            span = end - ents[slots[0]]['key']
            if span < size and so and all(b == 0 for b in e.content(so)[span:]) and \
                    not any(y['shndx'] == so['index'] and y['value'] + y['size'] > span for y in syms) and \
                    not any(struct.unpack_from('<I', e.content(t), o)[0] >= span
                            for t in e.sections if t['type'] == 9 and t['info'] == so['index']
                            for o in range(0, t['size'], 8)):
                u.setdefault('trim', {})[sec] = span     # trailing alignment pad the original does not have
            elif size != span and not (so and owned_data_gap_fits(
                    size, ents[slots[0]]['key'], end, sec, so['align'])):
                return 'size'
    return None


_IMAGE_NAMES = None


def image_names():
    """Names the split assembly defines (functions, data labels, jump tables, linker-script constants)."""
    global _IMAGE_NAMES
    if _IMAGE_NAMES is None:
        names = {n for _, n in json.loads((BUILD / 'labels.json').read_text())}
        sym = BUILD / 'symbols.ld'
        if sym.exists():
            names |= set(re.findall(r'^(\w+)\s*=', sym.read_text(), re.M))
        _IMAGE_NAMES = names
    return _IMAGE_NAMES


def prepare():
    from text_placement import InputAlignments, natural_text_span
    units = load_units(facts=False)       # earlier facts must not hide functions from the checks
    explicit_data = source_ranges(units)
    original_labels = {name: address for address, name in json.loads((BUILD / 'labels.json').read_text())}
    symbols = known_symbols()
    PROBLEMS.clear()
    lenient = non_matching()      # drafts differ in size: only names and bindings are checked there
    results = json.loads((OUT / 'results.json').read_text()) if (OUT / 'results.json').exists() else {}
    stats = {}
    placement = json.loads((BUILD / 'placement.json').read_text())
    ends = {f['addr']: f['end'] for f in placement['functions']}
    alignments, original_text, text_base = None, None, 0

    def following_data_input(section, address):
        nonlocal alignments
        if alignments is None:
            alignments = InputAlignments(BUILD)
        return alignments.data_section(section, address)

    def fits_text(section, start, stop):
        nonlocal alignments, original_text, text_base
        if section is None:
            return False
        if section['size'] == stop - start:
            return True
        if not 0 < stop - start - section['size'] < 16:
            return False
        if alignments is None:
            alignments = InputAlignments(BUILD)
        if original_text is None:
            original = Elf((ROOT / 'orig' / SLUG / 'SLUS_213.76').read_bytes())
            text = original.section('.text')
            original_text, text_base = original.content(text), text['addr']
        padding_start = start + section['size'] - text_base
        padding_end = stop - text_base
        if not 0 <= padding_start <= padding_end <= len(original_text):
            return False
        return natural_text_span(section['size'], start, stop, alignments.at(stop),
                                 original_text[padding_start:padding_end], section['align'])

    for u in units:
        if not any(f.get('status') == 'source' for f in u['functions']):
            continue
        # a cached object means the compile worked
        e = cached_object(u['name'])
        if e is None:
            stats['compile'] = stats.get('compile', 0) + demote(u, None, 'compile')
            continue
        syms = e.symbols()
        text = e.section('.text')
        fsecs = {t['index'] for t in e.sections if t['name'].startswith('.text.')}
        tidx = text['index'] if text else -1
        defined = {s['name']: s for s in syms if s['type'] == 2 and (s['shndx'] == tidx or s['shndx'] in fsecs)}
        for f in u['functions']:
            if f.get('status') != 'source':
                continue
            # the name the source gives the function: the one symbols.txt lists for the address, else func_XXXXXXXX
            name = next((c for c in f.get('candidates', [f['symbol']]) if c in defined), None)
            if name is None and lenient:
                f['status'] = 'asm'
                u.setdefault('assembly', []).append(f['addr'])
            elif name is None:
                stats['name'] = stats.get('name', 0) + demote(u, {f['addr']}, 'name')
            else:
                f['symbol'] = name
        # the object's code must fill exactly the original span (first function to the next one behind the unit)
        live = [f for f in u['functions'] if f.get('status') == 'source']
        if lenient:
            pass
        elif live and u.get('full_tu_context') and not fsecs:
            stats['context'] = stats.get('context', 0) + demote(u, None, 'context')
            live = []
        if live and fsecs and not lenient:
            # One section per function. The next actual input's alignment may fill
            # a verified zero tail; no extra code or invented padding is accepted.
            bad = set()
            for f in live:
                s = defined.get(f['symbol'])
                sec = e.sections[s['shndx']] if s else None
                nxt = ends[f['addr']]
                if sec is None or not sec['name'].startswith('.text.') or not fits_text(sec, f['addr'], nxt):
                    bad.add(f['addr'])
            if bad:
                stats['extra'] = stats.get('extra', 0) + demote(u, bad, 'extra')
            elif u.get('full_tu_context'):
                if not valid_context_sections(e, syms, u):
                    stats['context'] = stats.get('context', 0) + demote(u, None, 'context')
            elif (text and text['size']) or sum(e.sections[i]['size'] for i in fsecs) != sum(
                    e.sections[defined[f['symbol']]['shndx']]['size'] for f in live):
                mine = {e.sections[defined[f['symbol']]['shndx']]['name'] for f in live}
                print('%s: also defines %s (INCLUDE_ASM and a definition for one function, or a helper that emits code)' % (
                    u['source'], ', '.join(sorted(e.sections[i]['name'] for i in fsecs if e.sections[i]['name'] not in mine)[:6])))
                stats['extra'] = stats.get('extra', 0) + demote(u, None, 'extra')
        elif live and not lenient:
            first, last = min(f['addr'] for f in live), max(f['addr'] for f in live)
            nxt = ends[last]
            if not fits_text(text, first, nxt):
                stats['extra'] = stats.get('extra', 0) + demote(u, None, 'extra')
        live = [f for f in u['functions'] if f.get('status') == 'source']
        if live and not lenient:
            why = validate_inputs(e, [r for r in explicit_data if r['unit'] == u['name']], placement,
                                  following_data_input)
            why = why or validate_input_symbols(e, [r for r in explicit_data if r['unit'] == u['name']], original_labels)
            why = why or data_sections(e, syms, u, live, placement)
            if why:
                stats[why] = stats.get(why, 0) + demote(u, None, why)
        # bind what the object leaves undefined
        used = set()     # only what the linked sections refer to; the dropped ones (unwind data, linkonce copies) do not count
        kept_names = kept_text_names(e, syms, live) | owned_constant_names(live, placement) | {r['input'] for r in u.get('data_ranges', [])}
        for t in e.sections:
            if t['type'] == 9 and e.sections[t['info']]['name'] in kept_names:
                c = e.content(t)
                for o in range(0, len(c), 8):
                    used.add(struct.unpack_from('<I', c, o + 4)[0] >> 8)
        want = sorted({syms[i]['name'] for i in used if syms[i]['name'] and syms[i]['bind'] in (1, 2) and
                       (syms[i]['shndx'] == 0 or (syms[i]['shndx'] < 0xff00 and e.sections[syms[i]['shndx']]['name'] not in kept_names
                                                  and i not in [j for j, y in enumerate(syms) if y['type'] == 2 and y['shndx'] == tidx]))})
        ex, missing = {}, []
        known = dict(u.get('externs') or {})
        for name in want:
            address = symbols.address(name, known)
            if address is not None:
                ex[name] = address
            elif name in image_names():
                continue                  # a label the image's own assembly defines (func_XXXXXXXX, D_XXXXXXXX): ld resolves it
            else:
                missing.append(name)
        u['externs'] = ex
        if missing and any(f.get('status') == 'source' for f in u['functions']):
            u['unbound'] = missing
            stats['extern'] = stats.get('extern', 0) + demote(u, None, 'extern')
        else:
            u.pop('unbound', None)
    save(units)
    lines = report(units, PROBLEMS)
    print('\n'.join(lines[:60]) + ('\n... %d more' % (len(lines) - 60) if len(lines) > 60 else ''))
    print('problems:', stats)
    return 1 if PROBLEMS else 0


def link_errors():
    """Demote the units a failed link names: their object is the one that is wrong, or the label another object needs
    (an exception handler or jump target inside the replaced function) no longer exists."""
    import bisect
    log = (OUT / 'link.log').read_text()
    placement = json.loads((BUILD / 'placement.json').read_text())
    funcs = placement['functions']
    starts = [f['addr'] for f in funcs]
    by_name = {f['name']: f['addr'] for f in funcs}
    owned = sorted((e['key'], by_name[e['owner']]) for sec in ('.rodata', '.lit4', '.gcc_except_table')
                   for e in placement['sections'][sec] if e.get('owner'))
    okeys = [k for k, _ in owned]
    units = load_units()
    explicit_data = source_ranges(units)
    owner = {f['addr']: u['name'] for u in units for f in u['functions'] if f.get('status') == 'source'}
    bad = {}
    for line in log.split('\n'):
        m = re.search(r'obj/units/(\w+)\.o', line)
        if m and ('undefined reference' in line or 'discarded section' in line or 'multiple definition' in line
                  or 'relocation' in line):
            bad.setdefault(m.group(1), (line, 'link'))
        m = re.search(r"undefined reference to `[^`']*?([0-9A-F]{8})'", line)
        if m:
            a = int(m.group(1), 16)
            data_unit = range_owner(explicit_data, None, a)
            if data_unit is not None:
                bad.setdefault(data_unit, (line, 'labels'))
                continue
            fa = starts[bisect.bisect_right(starts, a) - 1]
            if fa in owner:
                bad.setdefault(owner[fa], (line, 'labels'))
            elif 'ehtbl_' in line or 'D_' in line or 'jtbl_' in line:    # a constant that moved with a replaced function
                i = bisect.bisect_right(okeys, a) - 1
                if i >= 0 and owned[i][1] in owner:
                    bad.setdefault(owner[owned[i][1]], (line, 'labels'))
    PROBLEMS.clear()
    for u in units:
        if u['name'] in bad:
            demote(u, None, bad[u['name']][1])
    save(units)
    print('\n'.join(report(units, PROBLEMS)[:40]))
    for k, (line, why) in list(bad.items())[:12]:
        print('  %s (%s): %s' % (k, why, line[:150]))
    if not bad:
        print(log[-2000:])
    return 1 if bad else 0


def compare():
    """Attribute every differing word of the linked image to the unit (or assembly function) that owns it."""
    import bisect
    ref = Elf((ROOT / 'orig' / SLUG / 'SLUS_213.76').read_bytes())
    got = Elf((OUT / 'linked.elf').read_bytes())
    placement = json.loads((BUILD / 'placement.json').read_text())
    funcs = placement['functions']
    starts = [f['addr'] for f in funcs]
    units = load_units()
    explicit_data = source_ranges(units)
    units_by_name = {u['name']: u for u in units}
    owner = {f['addr']: u for u in units for f in u['functions'] if f.get('status') == 'source'}
    ents = {sec: [(e['key'], e) for e in placement['sections'][sec] if 'key' in e]
            for sec in ('.rodata', '.lit4', '.gcc_except_table')}
    bad = {}
    bad_functions = {}
    other = []
    for sec in ('.text', '.rodata', '.lit4', '.gcc_except_table', '.data', '.sdata'):
        a, b = ref.section(sec), got.section(sec)
        ca, cb = ref.content(a), got.content(b)
        for i in range(0, min(len(ca), len(cb)), 4):
            if ca[i:i + 4] == cb[i:i + 4]:
                continue
            addr = a['addr'] + i
            who = None
            data_unit = range_owner(explicit_data, sec, addr)
            if data_unit is not None:
                who = units_by_name[data_unit]
                where = data_unit
            elif sec == '.text':
                fa = starts[bisect.bisect_right(starts, addr) - 1]
                who = owner.get(fa)
                where = 'func_%08X' % fa
            elif sec in ents:
                keys = [k for k, _ in ents[sec]]
                k = bisect.bisect_right(keys, addr) - 1
                e = ents[sec][k][1] if k >= 0 else None
                fa = next((f['addr'] for f in funcs if e and f['name'] == e.get('owner')), None)
                who = owner.get(fa)
                where = e['obj'] if e else '?'
            else:
                where = sec
            if who is not None:
                bad.setdefault(who['name'], []).append((sec, addr))
                if sec == '.text':
                    bad_functions.setdefault((who['name'], fa), (sec, addr))
            else:
                other.append((sec, addr, where))
    PROBLEMS.clear()
    for (name, fa), _ in sorted(bad_functions.items(), key=lambda kv: kv[0][1]):
        PROBLEMS.append((name, fa, 'bytes'))
    for name, v in bad.items():
        if not any(p[0] == name for p in PROBLEMS):
            PROBLEMS.append((name, None, 'bytes'))
    for line in report(units, PROBLEMS)[:40]:
        print('MISMATCH ' + line)
    print('differences outside source units: %d' % len(other))
    for sec, addr, where in other[:25]:
        print('  %s %#x in %s' % (sec, addr, where))
    return 1 if PROBLEMS else 0


if __name__ == '__main__':
    cmd = sys.argv[1] if len(sys.argv) > 1 else ''
    run = {'prepare': prepare, 'link': link_errors, 'compare': compare}.get(cmd)
    sys.exit(run() if run else print(__doc__) or 2)
