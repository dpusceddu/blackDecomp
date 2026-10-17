"""Loader for config/units.yaml: the provisional translation units that replace assembly functions.

Format (see README.md):
  units:
    - name: kynapse_children          # object name; also build/<slug>/units/<name>.o
      source: src/kynapse/children.cpp
      compiler: ee-gcc2.95.3-136      # optional, this is the default
      flags: [-O2, -G0, -snas]        # optional, these are the defaults
      externs: {gIdA: 0x2b3a3c}       # symbols the source refers to but does not define: name -> original address
      functions:
        - {addr: 0x2e3100, symbol: FindChild__12ChildBuffersPCcT1, status: source}
        - {addr: 0x2e7ac0, symbol: __15ParameterTables, status: asm, reason: layout}
Only `status: source` functions are provided by the unit's object; the others stay assembly.
"""
import os, re
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_COMPILER = 'ee-gcc2.95.3-136'
DEFAULT_FLAGS = ['-O2', '-G0', '-snas']


def _num(v):
    return int(v, 0) if isinstance(v, str) else int(v)


def load_units(path=None):
    path = Path(path or ROOT / 'config/units.yaml')
    data = yaml.safe_load(path.read_text()) if path.exists() else None
    units = (data or {}).get('units') or []
    for u in units:
        if os.environ.get('BLACK_UNITS_ALL'):      # diagnostics: pretend every listed function is provided by source
            for f in u.get('functions', []):
                f['status'] = 'source'
        u.setdefault('compiler', DEFAULT_COMPILER)
        u.setdefault('flags', list(DEFAULT_FLAGS))
        u['functions'] = [dict(f, addr=_num(f['addr'])) for f in u.get('functions', [])]
        u['externs'] = {k: _num(v) for k, v in (u.get('externs') or {}).items()}
    return units


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
