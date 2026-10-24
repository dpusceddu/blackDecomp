"""The source units of the build (python3 tools/build/units.py [GAME_ID] derives and caches them), derived from the split list, the source files and the symbol table.

A *unit* is one split of config/<GAME_ID>/splits.yaml: a source file that replaces the functions of an address range.
Nothing here is stored in Git as a unit list: `load_units()` builds it from

  config/<GAME_ID>/splits.yaml     source file, address range, compiler, flags (tools/build/splits.py)
  the source file itself           its INCLUDE_ASM markers (tools/build/include_asm.py): marked functions stay assembly, every
                                   other function of the range is provided by the source
  config/<GAME_ID>/symbols.txt     the names a compiled function may carry, and the addresses of names it refers to
  config/<GAME_ID>/equivalent.yaml evidence of the `equivalent` tier
  build/<GAME_ID>/functions.json   function starts of the image (written by tools/build/split_objects.py --functions)
  build/<GAME_ID>/unit_facts.json  what compiling taught (extern bindings, trimmed constants; tools/build/units_verify.py)

and caches the result in build/<GAME_ID>/units.json. Each unit is a dict:
  name, source, library, compiler, flags (as handed to the compiler), range [start, end), externs {name: address},
  functions [{addr, symbol, size, status: 'source' | 'asm'}], and the optional keys of a split (data_ranges, owner, ...).
`size` is the distance to the next function. With BLACK_NON_MATCHING=1 the markers of `#ifdef NON_MATCHING` blocks are
read as if NON_MATCHING were defined, and -DNON_MATCHING is added to the flags (configure.py --non-matching).
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import bisect, json, os, re
from pathlib import Path

sys_path = _sys.path
sys_path.insert(0, str(Path(__file__).resolve().parent))
import include_asm
import splits as S
from splits import DEFAULT_COMPILER, DEFAULT_FLAGS, DEFAULT_SLUG, num as _num

ROOT = Path(__file__).resolve().parents[2]
CACHE_VERSION = 3


def non_matching():
    """True when the environment asks for the NON_MATCHING build (configure.py --non-matching)."""
    return bool(os.environ.get('BLACK_NON_MATCHING'))


def build_dir(slug):
    """Shared build outputs (placement, split assembly, object cache) of a version."""
    return ROOT / 'build' / slug


def out_dir(slug):
    """Directory of the outputs that differ in the NON_MATCHING build (units, link script, ELF)."""
    return ROOT / 'build' / (slug + '-nm' if non_matching() else slug)


# ----------------------------------------------------------------------------------------------------- function table

def function_table(slug=DEFAULT_SLUG):
    """[(address, end)] of every function start of the image, from build/<slug>/functions.json (or placement.json)."""
    build = build_dir(slug)
    path = build / 'functions.json'
    if path.exists():
        return [(a, e) for a, e in json.loads(path.read_text())]
    path = build / 'placement.json'
    if path.exists():
        return [(f['addr'], f['end']) for f in json.loads(path.read_text())['functions']]
    raise SystemExit('no function table: run ninja (or tools/build/split_objects.py %s --functions) first' % slug)


def write_function_table(slug, functions):
    """Write build/<slug>/functions.json from [(address, end)]."""
    (build_dir(slug) / 'functions.json').write_text(json.dumps([[a, e] for a, e in functions]) + '\n')


# ------------------------------------------------------------------------------------------------------------ derive

def derive_units(splits, table, symbols, equivalent=None, read=None, is_non_matching=False, fallback=()):
    """Units for the splits (see the module docstring). `read(path)` returns the text of a source file."""
    read = read or (lambda p: (ROOT / p).read_text())
    equivalent = equivalent or {}
    starts = [a for a, _ in table]
    ends = dict(table)
    names = S.unit_names(splits)
    units = []
    for split, name in zip(splits, names):
        nm = is_non_matching and name not in fallback      # a unit whose drafts do not compile stays as in the matching build
        text = read(split.src)
        if split.functions is not None:         # a file compiled several times with -D selectors: no markers
            marked = {a for a in starts[bisect.bisect_left(starts, split.start):bisect.bisect_left(starts, split.end)]
                      if a not in set(split.functions)}
        else:
            marked = set(include_asm.marker_addresses(text, split.defines(nm)))
        lo, hi = bisect.bisect_left(starts, split.start), bisect.bisect_left(starts, split.end)
        inside = starts[lo:hi]
        unknown = marked - set(inside)
        if unknown:
            raise ValueError('%s: INCLUDE_ASM names functions outside its range [%#x, %#x): %s' % (
                split.src, split.start, split.end, ', '.join('func_%08X' % a for a in sorted(unknown))))
        functions = []
        for addr in inside:
            names_at = symbols.function_names(addr)
            default = 'func_%08X' % addr
            f = dict(addr=addr, symbol=names_at[0] if names_at else default, size=ends[addr] - addr,
                     status='asm' if addr in marked else 'source')
            if names_at:
                f['candidates'] = names_at + [default]
            if addr in equivalent and f['status'] == 'asm':
                f['evidence'] = equivalent[addr].get('evidence', {})
                f['nonmatching'] = {k: equivalent[addr][k] for k in ('source', 'symbol', 'returns') if k in equivalent[addr]}
            functions.append(f)
        unit = dict(name=name, source=split.src, library=split.library, origin=split.library, compiler=split.compiler,
                    flags=split.compile_flags(nm), range=[split.start, split.end], functions=functions,
                    externs={k: _num(v) for k, v in (split.entry.get('externs') or {}).items()})
        unit.update({k: v for k, v in split.extra.items() if k != 'externs'})
        if split.owner:
            unit['owner'] = split.owner
        if split.note:
            unit['note'] = split.note
        if split.assembler or (split.compiler.startswith('ee-gcc2.95') and '-snas' not in split.flags):
            unit['assembler_evidence'] = dict(strength='weak', basis='individually verified output',
                                              historical_provenance='unresolved')
        units.append(unit)
    return units


def apply_facts(units, facts):
    """Merge what compiling taught (build/<slug>/unit_facts.json): resolved symbols, extern bindings, trimmed constants."""
    for u in units:
        f = facts.get(u['name'])
        if not f:
            continue
        resolved = {int(a): s for a, s in (f.get('symbols') or {}).items()}
        for fn in u['functions']:
            if fn['addr'] in resolved:
                fn['symbol'] = resolved[fn['addr']]
        u['externs'] = {k: _num(v) for k, v in (f.get('externs') or {}).items()}
        if f.get('trim'):
            u['trim'] = f['trim']
        if f.get('unbound'):
            u['unbound'] = f['unbound']
        gone = set(f.get('assembly') or ())          # functions the NON_MATCHING build could not take from a draft
        for fn in u['functions']:
            if fn['addr'] in gone:
                fn['status'] = 'asm'
    return units


def _inputs(slug, units=None):
    cfg = S.config_dir(slug)
    out = [out_dir(slug) / 'nm_fallback.json', cfg / 'splits.yaml', cfg / 'symbols.txt', cfg / 'equivalent.yaml', build_dir(slug) / 'functions.json',
           ROOT / 'tools/build/units.py', ROOT / 'tools/build/include_asm.py', ROOT / 'tools/build/splits.py']
    return out


def load_units(path=None, variant=None, refresh=False, facts=True):
    """Units of the version (default SLUS_213.76), cached in build/<slug>/units.json. The addresses are those of the USA
    retail image: another `variant` has no split list and no units."""
    slug = variant or DEFAULT_SLUG
    split_list = S.config_dir(slug) / 'splits.yaml'
    if not split_list.exists():
        return []
    cache = out_dir(slug) / ('units-nm.json' if non_matching() else 'units.json')
    units = None
    if cache.exists() and not refresh:
        try:
            data = json.loads(cache.read_text())
        except ValueError:
            data = None
        if data and data.get('version') == CACHE_VERSION:
            newest = max([p.stat().st_mtime for p in _inputs(slug) if p.exists()] +
                         [(ROOT / u['source']).stat().st_mtime for u in data['units'] if (ROOT / u['source']).exists()])
            if cache.stat().st_mtime >= newest:
                units = data['units']
    if units is None:
        units = write_units(slug)
    facts_path = out_dir(slug) / 'unit_facts.json'
    if facts and facts_path.exists():
        apply_facts(units, json.loads(facts_path.read_text()))
    if os.environ.get('BLACK_UNITS_ALL'):      # diagnostics: pretend every listed function is provided by source
        for u in units:
            for f in u['functions']:
                f['status'] = 'source'
    return units


def write_units(slug=DEFAULT_SLUG):
    """Derive the units from the split list and its sources, write the cache, and return them."""
    nm = non_matching()
    out = out_dir(slug)
    out.mkdir(parents=True, exist_ok=True)
    fallback = set(json.loads((out / 'nm_fallback.json').read_text())) if nm and (out / 'nm_fallback.json').exists() else set()
    units = derive_units(S.load_splits(slug), function_table(slug), S.load_symbols(slug), S.load_equivalent(slug),
                         is_non_matching=nm, fallback=fallback)
    (out / ('units-nm.json' if nm else 'units.json')).write_text(json.dumps(dict(version=CACHE_VERSION, units=units)))
    return units


def committed_source_addresses(slug=DEFAULT_SLUG):
    """Addresses compiled from source at HEAD (derived from the committed split list and sources), to protect them."""
    import subprocess
    def show(path):
        r = subprocess.run(['git', 'show', 'HEAD:' + path], cwd=ROOT, capture_output=True, text=True)
        return r.stdout if r.returncode == 0 else None
    import tempfile, yaml
    text = show('config/%s/splits.yaml' % slug)
    if text is None:
        return set()
    with tempfile.TemporaryDirectory() as d:
        (Path(d) / 'splits.yaml').write_text(text)
        splits = S.load_splits(slug, path=Path(d) / 'splits.yaml')
    sym = show('config/%s/symbols.txt' % slug)
    symbols = S.Symbols(S.parse_symbols(sym)) if sym else S.Symbols()
    units = derive_units(splits, function_table(slug), symbols, read=lambda p: show(p) or '')
    return {f['addr'] for u in units for f in u['functions'] if f['status'] == 'source'}


INCLUDE = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)


def dependencies(source):
    """Repo-relative paths of a source file and the quoted includes it needs (relative to the file, then include/)."""
    seen, todo = [], [Path(source)]
    while todo:
        p = todo.pop()
        if p in seen:
            continue
        seen.append(p)
        for name in INCLUDE.findall((ROOT / p).read_text()):
            for base in (p.parent, Path('include')):
                q = (base / name)
                if (ROOT / q).is_file():
                    todo.append(Path(*q.parts) if '..' not in q.parts else Path(str((ROOT / q).resolve().relative_to(ROOT))))
                    break
    return seen


def main():
    slug = _sys.argv[1] if len(_sys.argv) > 1 else DEFAULT_SLUG
    units = write_units(slug)
    # ninja re-derives the units when a source file changes (its INCLUDE_ASM markers may have changed)
    sources = sorted({u['source'] for u in units})
    (out_dir(slug) / 'units.d').write_text('build/%s/%s: %s\n' % (
        out_dir(slug).name, 'units-nm.json' if non_matching() else 'units.json', ' '.join(sources)))
    live = [u for u in units if any(f['status'] == 'source' for f in u['functions'])]
    print('%d units (%d with source), %d source functions, %d INCLUDE_ASM functions' % (
        len(units), len(live), sum(f['status'] == 'source' for u in units for f in u['functions']),
        sum(f['status'] == 'asm' for u in units for f in u['functions'])))


if __name__ == '__main__':
    main()
