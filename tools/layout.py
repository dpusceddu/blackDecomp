"""Source layout rules: which library directory and which file name a source unit gets (src/<library>/<name>.c|cpp).

The library comes from the address ranges of config/tus.yaml; the name from the translation unit that holds the unit's
first function (`tu_<address>`, plus `_<unit address>` when the unit does not start the TU). tools/autodecomp.py and
tools/tu_files.py use them for new files.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import bisect, json
import re
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[1]

# TU-map library -> directory under src/. The Sony libraries of the sd-style block share one directory; the C library and
# its helpers another. The TU-map library `linkonce` (the link-once block behind the regular code, which holds instantiated
# inline code) has no directory of its own: config/SLUS_213.76/inline_owners.txt names the library that owns each range.
LIBRARY_DIR = {
    'game': 'game', 'apt': 'apt', 'kynapse': 'kynapse', 'animation': 'animation', 'physics': 'physics',
    'renderware_core': 'rw_core', 'rwa_ee': 'rw_audio',
    'vibuf': 'sony', 'sony_unidentified': 'sony', 'libipu_libmpeg': 'sony', 'libdbc': 'sony', 'libdma_libpad2': 'sony',
    'libcdvd': 'sony', 'libmc2': 'sony', 'libkernl': 'sony', 'libgs': 'sony',
    'libm': 'libc', 'libc_stdio': 'libc', 'libstdcxx_typeinfo': 'libc',
}
LIBRARIES = sorted(set(LIBRARY_DIR.values()))
TU_STEM = re.compile(r'^(?:tu_[0-9a-f]{6}|crt0)(?:_[0-9a-f]{6})?$')
_MAP = None
_VIEW_LIBRARIES = None
_INLINE_OWNERS = None
_GAME_SUBSYSTEMS = None


def _num(v):
    return int(v, 0) if isinstance(v, str) else int(v)


def tu_map():
    """(starts, tus) of config/tus.yaml sorted by text start."""
    global _MAP
    if _MAP is None:
        tus = yaml.safe_load((ROOT / 'config/tus.yaml').read_text())['tus']
        tus.sort(key=lambda t: _num(t['text'][0]))
        _MAP = ([_num(t['text'][0]) for t in tus], tus)
    return _MAP


def tu_of(addr):
    starts, tus = tu_map()
    return tus[max(bisect.bisect_right(starts, addr) - 1, 0)]


def layout_library(name):
    """Library whose include/<library>/partial/ directory holds the partial view `name` (default: game)."""
    global _VIEW_LIBRARIES
    if _VIEW_LIBRARIES is None:
        _VIEW_LIBRARIES = {p.stem: p.parent.parent.name for p in (ROOT / 'include').glob('*/partial/Recovered_*.h')}
    return _VIEW_LIBRARIES.get(name, 'game')


def view_include(name):
    """Quoted include of a partial view, e.g. 'game/partial/Recovered_Action.h'."""
    return '%s/partial/%s.h' % (layout_library(name), name)


def inline_owners():
    """(starts, rows) of config/SLUS_213.76/inline_owners.txt: owner library of every link-once range (start, end, library)."""
    global _INLINE_OWNERS
    if _INLINE_OWNERS is None:
        rows = []
        for line in (ROOT / 'config/SLUS_213.76/inline_owners.txt').read_text().splitlines():
            if line.strip() and not line.startswith('#'):
                start, end, library = line.split()[:3]
                rows.append((int(start, 0), int(end, 0), library))
        rows.sort()
        _INLINE_OWNERS = ([r[0] for r in rows], rows)
    return _INLINE_OWNERS


def is_inline(addr):
    """True for code in the link-once block (compiler-emitted inline and template copies)."""
    return tu_of(addr)['library'] == 'linkonce'


def library_of_tu(addr):
    """Library directory by the TU map alone (not for the link-once block, whose owners come from inline_owners)."""
    return LIBRARY_DIR[tu_of(addr)['library']]


def library_of(addr):
    """Directory name of the library that holds the code at `addr`; a link-once copy belongs to its owner library."""
    if is_inline(addr):
        starts, rows = inline_owners()
        row = rows[bisect.bisect_right(starts, addr) - 1]
        if not row[0] <= addr < row[1]:
            raise KeyError('0x%x is in the link-once block but in no range of config/SLUS_213.76/inline_owners.txt' % addr)
        return row[2]
    return library_of_tu(addr)


def game_subsystem(name):
    """Subdirectory of src/game/ for the file `name` (with extension) from config/SLUS_213.76/game_subsystems.txt; 'unsorted' if unlisted."""
    global _GAME_SUBSYSTEMS
    if _GAME_SUBSYSTEMS is None:
        _GAME_SUBSYSTEMS = {}
        path = ROOT / 'config/SLUS_213.76/game_subsystems.txt'
        for line in path.read_text().splitlines() if path.exists() else ():
            if line.strip() and not line.startswith('#'):
                file, subsystem = line.split()[:2]
                _GAME_SUBSYSTEMS[file] = subsystem
    return _GAME_SUBSYSTEMS.get(name, 'unsorted')


def source_dir(addr, name=None):
    """Directory under src/ for a new source unit at `addr`: src/<library>, src/<owner>/inline for a link-once copy, and
    src/game/<subsystem> for game code (a file that the subsystem list does not name goes to src/game/unsorted)."""
    library = library_of(addr)
    if is_inline(addr):
        return 'src/%s/inline' % library
    if library == 'game':
        return 'src/game/' + game_subsystem(name)
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
