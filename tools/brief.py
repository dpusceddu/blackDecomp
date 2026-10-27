#!/usr/bin/env python3
"""Everything a work session needs about one source file, in one printout, so that it can start writing C at once.

Usage: brief.py src/<library>/<file>.c|cpp|func_XXXXXXXX [--max-size N] [--top N] [--drafts] [--no-asm] [--no-draft]
Prints, for the file that owns the function (or the file given):
  - its split entries (range, compiler, flags, assembler and notes) and #include lines;
  - its recovered functions (definition lines) and drafts with their `// Unmatched:` notes;
  - for each target (untried assembly functions, with --drafts also the drafted ones, of at most --max-size bytes, default the median size of all remaining
    functions; at most --top of them, in address order): size, callees and callers with their owner file and state, the
    data it references with any names from symbols.txt, an m2c draft with the project's context (as decompile.py), and its
    assembly without the address columns;
  - the other assembly functions of the file, by size.
Needs `python3 tools/setup.py` preparation (the assembly under asm/) and its installed m2c dependency; no image build.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import argparse, collections, json, re, statistics, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
import include_asm
import ownership
import preflight
import splits as S

ROOT = S.ROOT
SLUG = S.DEFAULT_SLUG
ASM = ROOT / 'asm' / SLUG / 'nonmatchings'
CALL = re.compile(r'\b(?:jal|j)\s+([A-Za-z_][\w.$]*)\s*$')
DATA = re.compile(r'%(?:hi|lo|gp_rel)\(([A-Za-z_][\w.$]*)')
COLUMNS = re.compile(r'^\s*/\*.*?\*/\s*')
DEFINITION = re.compile(r'^(?!static\s+inline|#|\s)[A-Za-z_][\w\s*&:<>,]*?\b([A-Za-z_][\w:~]*)\s*\([^;]*\)\s*(?:const\s*)?\{')
UNMATCHED = re.compile(r'//\s*Unmatched:\s*(.*)')
FUNC = re.compile(r'^func_([0-9A-Fa-f]{8})$')


def address(name, by_name):
    m = FUNC.match(name)
    return int(m.group(1), 16) if m else by_name.get(name)


def call_graph(by_name):
    """{caller address: [callee names]} and {callee address: [caller addresses]} from the assembly of every function."""
    calls, callers = {}, collections.defaultdict(list)
    for path in ASM.glob('func_*.s'):
        if not FUNC.match(path.stem):
            continue                                 # func_X.lit4 and the like are data
        caller = int(path.stem[5:], 16)
        names = [m.group(1) for line in path.read_text().splitlines() if (m := CALL.search(line))]
        names = [n for n in dict.fromkeys(names) if not n.startswith('.')]
        calls[caller] = names
        for n in names:
            a = address(n, by_name)
            if a is not None and a != caller:
                callers[a].append(caller)
    return calls, callers


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('target', help='a source file (src/...) or a function (func_XXXXXXXX)')
    ap.add_argument('--max-size', type=int)
    ap.add_argument('--top', type=int, default=12)
    ap.add_argument('--drafts', action='store_true', help='also show the functions that have a draft as targets')
    ap.add_argument('--no-asm', action='store_true', help='leave out the assembly')
    ap.add_argument('--no-draft', action='store_true', help='leave out the m2c drafts (faster)')
    a = ap.parse_args()
    preflight.require(SLUG, build=('placement.json',))
    if not ASM.is_dir():
        raise SystemExit('no assembly under asm/%s/nonmatchings: run `python3 tools/setup.py` first' % SLUG)
    splits, symbols = S.load_splits(SLUG), S.load_symbols(SLUG)
    rows = S.parse_symbols((S.config_dir(SLUG) / 'symbols.txt').read_text())
    by_name = {n: addr for n, addr, _ in rows}
    names = collections.defaultdict(list)
    for n, addr, attrs in rows:
        names[addr].append(n + (' (alias)' if 'alias' in attrs else ''))
    texts = {}

    def read(path):
        if path not in texts:
            texts[path] = Path(path).read_text()
        return texts[path]

    def where(addr):
        split, kind, line, path = ownership.locate(addr, splits, symbols, read=read)
        return ('%s:%s %s' % (split.src, line, kind)) if split else 'no owner'

    target = a.target
    if FUNC.match(target):
        split, _, _, _ = ownership.locate(int(target[5:], 16), splits, symbols, read=read)
        if split is None:
            raise SystemExit('%s: no source file owns it' % target)
        target = split.src
    entries = [s for s in splits if s.src == target]
    if not entries:
        raise SystemExit('%s is not a source file of config/%s/splits.yaml (python3 tools/where.py names the file of a function)' % (target, SLUG))
    text = read(ROOT / target)

    print('# %s' % target)
    recipes = collections.defaultdict(list)
    for s in entries:
        extra = ''.join(' %s=%s' % kv for kv in (('assembler', s.assembler), ('note', s.note)) if kv[1])
        recipes['%s %s%s' % (s.compiler, ' '.join(s.flags), extra)].append('0x%x-0x%x' % (s.start, s.end))
    for recipe, ranges in recipes.items():
        shown = ', '.join(ranges[:4]) + (' and %d more ranges' % (len(ranges) - 4) if len(ranges) > 4 else '')
        print('compile: %s  (%s)' % (recipe, shown))
    for line in text.splitlines():
        if line.startswith('#include'):
            print(line)

    active = include_asm.active_lines(text, set())
    print('\n## recovered functions')
    for _, line in active:
        if (m := DEFINITION.match(line)):
            print('  ' + line.rstrip(' {'))
    left = [include_asm.function_address(m.name) for m in include_asm.markers(text, set())]
    untried = {include_asm.function_address(m.name) for m in include_asm.markers(text, {'NON_MATCHING'})}
    lines = text.splitlines()
    drafts = [x for x in left if x not in untried]
    if drafts:
        print('\n## drafts (tried before; read the note before trying again)')
        for x in drafts:
            name = 'func_%08X' % x
            notes = [m.group(1) for i, l in enumerate(lines) if name in l and '#else' not in l
                     for m in [UNMATCHED.search(lines[i - 1]) if i else None] if m]
            print('  %s  %s' % (name, notes[0] if notes else '(no note)'))

    calls, callers = call_graph(by_name)
    units = json.loads((ROOT / 'build' / SLUG / 'units.json').read_text())['units']
    sizes = {f['addr']: f['size'] for u in units for f in u['functions']}
    done = {f['addr'] for u in units for f in u['functions'] if f['status'] == 'source'}
    limit = a.max_size or statistics.median(s for x, s in sizes.items() if x not in done and s > 8)
    targets = [x for x in sorted(left if a.drafts else untried) if 8 < sizes.get(x, 0) <= limit][:a.top]
    print('\n## targets (%s, at most %d bytes): %d shown' % ('all assembly' if a.drafts else 'untried', limit, len(targets)))
    for x in targets:
        name = 'func_%08X' % x
        print('\n### %s, %d bytes%s' % (name, sizes[x], ('  names: ' + ', '.join(names[x])) if names.get(x) else ''))
        for callee in calls.get(x, []):
            c = address(callee, by_name)
            known = ('  [' + ', '.join(names[c]) + ']') if c in names and FUNC.match(callee) else ''
            print('  calls   %-28s %s%s' % (callee, where(c) if c is not None else 'unknown', known))
        for caller in callers.get(x, [])[:6]:
            print('  called by func_%08X %s' % (caller, where(caller)))
        if len(callers.get(x, [])) > 6:
            print('  ... %d callers in all' % len(callers[x]))
        asm = (ASM / (name + '.s')).read_text()
        for d in dict.fromkeys(DATA.findall(asm)):
            d_addr = address(d, by_name) if not d.startswith('D_') else int(d[2:], 16)
            print('  data    %-28s %s' % (d, ', '.join(names.get(d_addr, [])) if d_addr is not None else ''))
        if not a.no_draft:
            import io, contextlib, decompile
            try:
                with contextlib.redirect_stdout(io.StringIO()):
                    _, result, source, note = decompile.draft(x, 'ctx.c')
                print('  m2c draft%s:' % ('' if source else ' (raw; cleaning gave up: %s)' % note))
                body = source or '%s %s(%s) {\n%s\n}' % (result.get('ret'), name, result.get('params'), result.get('body'))
                body = '\n'.join(l for l in body.splitlines() if not l.startswith('#include')).strip('\n')
                print('\n'.join('    ' + l for l in body.rstrip().splitlines()))
            except SystemExit as e:
                print('  m2c draft: none (%s)' % e)
        if not a.no_asm:
            print('  assembly:')
            for l in asm.splitlines():
                if l.strip() and not l.startswith(('.include', '.set', '.section', '.align', 'glabel', 'endlabel', '.size')):
                    print('    ' + COLUMNS.sub('', l).rstrip())
    rest = [x for x in left if x not in targets]
    if rest:
        print('\n## other assembly functions of the file')
        print('  ' + ', '.join('func_%08X (%d%s)' % (x, sizes.get(x, 0), ', draft' if x not in untried else '') for x in sorted(rest)))
    return 0


if __name__ == '__main__':
    sys.exit(preflight.guard(main))
