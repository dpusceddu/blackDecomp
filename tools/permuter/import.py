#!/usr/bin/env python3
"""Import a permuter seed while preserving PS2 scalar typedef attributes and checking 128-bit widths.

Usage: python3 tools/permuter/import.py --no-prune --settings build/permuter/FUNCTION.toml DRAFT.c TARGET.s
Uses the pinned upstream importer in .venv/decomp-permuter. Preserved typedefs and
compile-time size checks survive every candidate's parser round trip; an invalid
ABI fails import before searching. Other arguments are upstream import.py arguments.
Seeds are saved under build/permuter/nonmatchings/ (the importer prints the path).
"""
import importlib.util
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools/permuter'))
from abi import preserve_typedefs


def load_importer():
    path = ROOT / '.venv/decomp-permuter/import.py'
    if not path.is_file():
        raise SystemExit('run python3 tools/autodecomp.py setup first')
    sys.path.insert(0, str(path.parent))
    spec = importlib.util.spec_from_file_location('upstream_permuter_import', path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def main(argv=None):
    args = sys.argv[1:] if argv is None else argv
    if args[:1] in (['-h'], ['--help']):
        print(__doc__.strip())
        return 0
    upstream = load_importer()
    upstream.STUB_FN_MACROS = [f for f in upstream.STUB_FN_MACROS if not f.startswith('-D__attribute__')]
    original = upstream.import_c_file
    upstream.import_c_file = lambda *a, **kw: preserve_typedefs(original(*a, **kw))
    # Upstream can continue on a parser failure without compiling base.c. A
    # successful project import must have parsed and compiled its guarded seed.
    prune = upstream.prune_source
    def checked_prune(*a, **kw):
        source, compilable = prune(*a, **kw)
        if compilable is None:
            raise SystemExit('permuter import: seed could not be parsed; refusing an unchecked import')
        return source, compilable
    upstream.prune_source = checked_prune
    compile_base = upstream.compile_base
    def checked_compile(script, source, c_file, out_file):
        compile_base(script, source, c_file, out_file)
        # Upstream prints a warning and continues after compiler failure (and
        # skips PERM macro seeds). Neither establishes the guarded type sizes.
        if not Path(out_file).is_file():
            raise SystemExit('permuter import: seed did not compile; refusing an unchecked import')
    upstream.compile_base = checked_compile
    def create_directory(name):
        base = ROOT / 'build/permuter/nonmatchings'
        base.mkdir(parents=True, exist_ok=True)
        n = 1
        while True:
            path = base / (name if n == 1 else '%s-%d' % (name, n))
            try:
                path.mkdir()
                return str(path)
            except FileExistsError:
                n += 1
    upstream.create_directory = create_directory
    upstream.main(['--no-prune'] + list(args))
    return 0


if __name__ == '__main__':
    sys.exit(main())
