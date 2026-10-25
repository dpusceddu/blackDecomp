"""Source layout rules: which library directory and which file name a source unit gets (src/<library>/<name>.c|cpp).

The library comes from the hand-edited address ranges of config/SLUS_213.76/libraries.txt (link-once copies: the owner list the
build computes, build/SLUS_213.76/inline_owners.txt); the name from the translation unit of the generated TU map
(build/SLUS_213.76/tus.yaml, written by `ninja` or on first use) that holds the unit's first function (`tu_<address>`, plus
`_<unit address>` when the unit does not start the TU). A new game file starts in src/game/unsorted/; the directory a file
is in is its subsystem. tools/autodecomp.py and tools/pipeline/tu_files.py use these rules for new files.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import bisect, subprocess, os
import re
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[2]
SLUG = 'SLUS_213.76'
LIBRARIES_FILE = ROOT / 'config' / SLUG / 'libraries.txt'
INLINE_OWNERS_FILE = ROOT / 'build' / SLUG / 'inline_owners.txt'
TUS_FILE = ROOT / 'build' / SLUG / 'tus.yaml'

# TU-map library -> directory under src/. The Sony libraries of the sd-style block share one directory; the C library and
# its helpers another. The TU-map library `linkonce` (the link-once block behind the regular code, which holds instantiated
# inline code) has no directory of its own: build/SLUS_213.76/inline_owners.txt names the library that owns each range.
LIBRARY_DIR = {
    'game': 'game', 'apt': 'apt', 'kynapse': 'kynapse', 'animation': 'animation', 'physics': 'physics',
    'rw_core': 'rw_core', 'rw_audio': 'rw_audio',
    'vibuf': 'sony', 'sony_unidentified': 'sony', 'libipu_libmpeg': 'sony', 'libdbc': 'sony', 'libdma_libpad2': 'sony',
    'libcdvd': 'sony', 'libmc2': 'sony', 'libkernl': 'sony', 'libgs': 'sony',
    'libm': 'libc', 'libc_stdio': 'libc', 'libstdcxx_typeinfo': 'libc',
}
TU_STEM = re.compile(r'^(?:tu_[0-9a-f]{6}|crt0)(?:_[0-9a-f]{6})?$')
_MAP = None
_LIBRARIES = None
_INLINE_OWNERS = None


def _num(v):
    return int(v, 0) if isinstance(v, str) else int(v)


def _ranges(path):
    rows = []
    for line in path.read_text().splitlines():
        if line.strip() and not line.startswith('#'):
            start, end, library = line.split()[:3]
            rows.append((int(start, 0), int(end, 0), library))
    rows.sort()
    return [r[0] for r in rows], rows


def libraries():
    """(starts, rows) of config/SLUS_213.76/libraries.txt: (start, end, library) with `linkonce` for the link-once block."""
    global _LIBRARIES
    if _LIBRARIES is None:
        _LIBRARIES = _ranges(LIBRARIES_FILE)
    return _LIBRARIES


def linkonce_block():
    """(start, end) of the link-once block."""
    rows = [r for r in libraries()[1] if r[2] == 'linkonce']
    return min(r[0] for r in rows), max(r[1] for r in rows)


def library_of_tu(addr):
    """Library directory of the regular code at `addr` from libraries.txt; `linkonce` inside the link-once block."""
    starts, rows = libraries()
    row = rows[max(bisect.bisect_right(starts, addr) - 1, 0)]
    return row[2]


def is_inline(addr):
    """True for code in the link-once block (compiler-emitted inline and template copies)."""
    return library_of_tu(addr) == 'linkonce'


def inline_owners():
    """(starts, rows) of build/SLUS_213.76/inline_owners.txt: owner library of every link-once range (start, end, library).
    The file is generated from the split assembly; it is written on first use if `ninja` has not done it yet."""
    global _INLINE_OWNERS
    if _INLINE_OWNERS is None:
        if not os.environ.get('BLACK_NINJA') and not INLINE_OWNERS_FILE.exists():
            subprocess.run([_sys.executable, str(ROOT / 'tools/build/linkonce_owners.py'), '--write'], check=True, stdout=subprocess.DEVNULL)
        _INLINE_OWNERS = _ranges(INLINE_OWNERS_FILE)
    return _INLINE_OWNERS


def library_of(addr):
    """Directory name of the library that holds the code at `addr`; a link-once copy belongs to its owner library."""
    if is_inline(addr):
        starts, rows = inline_owners()
        row = rows[bisect.bisect_right(starts, addr) - 1]
        if not row[0] <= addr < row[1]:
            raise KeyError('0x%x is in the link-once block but in no range of %s' % (addr, INLINE_OWNERS_FILE.relative_to(ROOT)))
        return row[2]
    return library_of_tu(addr)


def tus_file():
    """Path of the generated TU map, written first if it is missing or older than its inputs (4 s)."""
    inputs = [ROOT / 'build' / SLUG / 'placement.json', ROOT / 'build' / SLUG / 'units.json', ROOT / 'config/tus_overrides.yaml',
              ROOT / 'config' / SLUG / 'libraries.txt', ROOT / 'tools/build/tus.py']
    if not os.environ.get('BLACK_NINJA') and (not TUS_FILE.exists() or any(p.exists() and p.stat().st_mtime > TUS_FILE.stat().st_mtime for p in inputs)):
        subprocess.run([_sys.executable, str(ROOT / 'tools/build/tus.py'), 'map', '--out', str(TUS_FILE)], check=True, stdout=subprocess.DEVNULL)
    return TUS_FILE


def tu_map():
    """(starts, tus) of the generated TU map (build/SLUS_213.76/tus.yaml) sorted by text start."""
    global _MAP
    if _MAP is None:
        tus = yaml.safe_load(tus_file().read_text())['tus']
        tus.sort(key=lambda t: _num(t['text'][0]))
        _MAP = ([_num(t['text'][0]) for t in tus], tus)
    return _MAP


def tu_of(addr):
    starts, tus = tu_map()
    return tus[max(bisect.bisect_right(starts, addr) - 1, 0)]


def source_dir(addr, name=None):
    """Directory under src/ for a new source unit at `addr`: src/<library>, src/<owner>/inline for a link-once copy, and
    src/game/unsorted for game code (move it to the subsystem directory when you learn what it is)."""
    library = library_of(addr)
    if is_inline(addr):
        return 'src/%s/inline' % library
    if library == 'game':
        return 'src/game/unsorted'
    return 'src/' + library


def tu_stem(tu):
    """File stem of a TU: its name without the library prefix of the map ('apt/tu_218370' -> 'tu_218370')."""
    return tu['name'].split('/')[-1].replace('/', '_')


def stem_for(addr):
    """Stem of the file for a unit whose first function is at `addr`."""
    tu = tu_of(addr)
    stem = tu_stem(tu)
    return stem if _num(tu['text'][0]) == addr else '%s_%06x' % (stem, addr)


def source_path(addr, suffix='.c'):
    """Repo-relative path for a source unit that starts at `addr` and has no better name."""
    name = stem_for(addr) + suffix
    return '%s/%s' % (source_dir(addr, name), name)
