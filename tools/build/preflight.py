#!/usr/bin/env python3
"""One-line answers instead of tracebacks when the game's executable or the first build is missing.

`python3 tools/build/preflight.py exe GAME_ID` is the check that `ninja` runs first.
Most tools read `orig/<GAME_ID>/<GAME_ID>` (your own copy of the boot executable, never committed) or the output of `ninja`
under build/<GAME_ID>/. `require()` checks for them at the start of a tool and ends it with a single sentence that says what
to do; `guard(main)` turns a FileNotFoundError for one of those paths, raised anywhere deeper, into the same sentence.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h', '--help'], ['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_SLUG = 'SLUS_213.76'


def boot_name(slug):
    try:
        return json.loads((ROOT / 'config' / 'versions.json').read_text())[slug]['boot']
    except (OSError, ValueError, KeyError):
        return slug


def executable_problem(slug=DEFAULT_SLUG, then='run ninja first'):
    path = ROOT / 'orig' / slug / boot_name(slug)
    if path.is_file():
        return None
    return 'orig/%s/%s is missing: put the executable of your copy of the game in orig/%s/ (see README.md); %s.' % (
        slug, path.name, slug, then)


def build_problem(slug=DEFAULT_SLUG, names=('placement.json',)):
    for name in names:
        if not (ROOT / 'build' / slug / name).is_file():
            return 'the build has not run (build/%s/%s is missing): run ninja first.' % (slug, name)
    return None


def require(slug=DEFAULT_SLUG, build=('placement.json',), executable=True):
    """Stop with one line when the executable (unless executable=False) or a file of the first build is missing."""
    problem = (executable and executable_problem(slug)) or build_problem(slug, build)
    if problem:
        raise SystemExit(problem)


def guard(main, slug=DEFAULT_SLUG):
    """Run main(); a FileNotFoundError for a path under orig/, build/, asm/ or data/ becomes the one-line message."""
    try:
        return main()
    except FileNotFoundError as error:
        name = Path(error.filename).as_posix() if error.filename else ''
        root = ROOT.as_posix() + '/'
        rel = name[len(root):] if name.startswith(root) else name
        if rel.startswith('orig/'):
            raise SystemExit(executable_problem(slug) or '%s is missing: put the executable in orig/; run ninja first.' % rel)
        if rel.startswith(('build/', 'asm/', 'data/')):
            raise SystemExit('the build has not run (%s is missing): run ninja first.' % rel)
        raise


def main(argv):
    """`preflight.py exe GAME_ID`: exit 1 with the one-line message when the executable is missing (the ninja rule uses it)."""
    if len(argv) == 3 and argv[1] == 'exe':
        problem = executable_problem(argv[2], then='then run ninja again')
        if problem:
            print(problem, file=_sys.stderr)
            return 1
        return 0
    print(__doc__.strip())
    return 0


if __name__ == '__main__':
    raise SystemExit(main(_sys.argv))
