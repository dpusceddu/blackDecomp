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
# its helpers another. `linkonce` is the link-once area behind the regular code: it holds instantiated inline code.
LIBRARY_DIR = {
    'game': 'game', 'apt': 'apt', 'kynapse': 'kynapse', 'animation': 'animation', 'physics': 'physics',
    'renderware_core': 'rw_core', 'rwa_ee': 'rw_audio', 'linkonce': 'linkonce',
    'vibuf': 'sony', 'sony_unidentified': 'sony', 'libipu_libmpeg': 'sony', 'libdbc': 'sony', 'libdma_libpad2': 'sony',
    'libcdvd': 'sony', 'libmc2': 'sony', 'libkernl': 'sony', 'libgs': 'sony',
    'libm': 'libc', 'libc_stdio': 'libc', 'libstdcxx_typeinfo': 'libc',
}
LIBRARIES = sorted(set(LIBRARY_DIR.values()))
TU_STEM = re.compile(r'^(?:tu_[0-9a-f]{6}|crt0)(?:_[0-9a-f]{6})?$')
_MAP = None
_VIEW_LIBRARIES = None


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
    """Library whose include/<library>/layouts/ directory holds the generated access view `name` (default: game)."""
    global _VIEW_LIBRARIES
    if _VIEW_LIBRARIES is None:
        path = ROOT / 'config/layout_libraries.json'
        _VIEW_LIBRARIES = json.loads(path.read_text()) if path.exists() else {}
    return _VIEW_LIBRARIES.get(name, 'game')


def view_include(name):
    """Quoted include of a generated access view, e.g. 'game/layouts/Recovered_Action.h'."""
    return '%s/layouts/%s.h' % (layout_library(name), name)


def library_of(addr):
    """Directory name of the library that holds the code at `addr`."""
    return LIBRARY_DIR[tu_of(addr)['library']]


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
    return 'src/%s/%s%s' % (library_of(addr), stem_for(addr), suffix)
