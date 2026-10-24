#!/usr/bin/env python3
"""Move source files and keep every reference to them consistent: the build inputs, documentation and generated comments.

Usage: relocate_sources.py PAIRS [--dry-run]       PAIRS is a file of `old new` repo-relative paths, one pair per line
                                                   (`-` reads standard input; blank lines and `#` comments are ignored)
For every pair whose old file exists it runs `git mv`, then rewrites the exact old path in `src:` lines of
config/SLUS_213.76/splits.yaml and in any other tracked text file that mentions it (docs, headers with generated comments,
tools). Pairs whose old file is already gone are skipped, so the tool can be run again. It changes only paths: the build
must stay byte-identical, check it with `ninja` afterwards. Used by linkonce_owners.py (--pairs) and group_game_sources.py.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TEXT = ('.py', '.md', '.yaml', '.yml', '.txt', '.json', '.h', '.hpp', '.c', '.cpp', '.inc', '.toml', '.ninja')


def read_pairs(source):
    text = sys.stdin.read() if source == '-' else Path(source).read_text()
    pairs = []
    for line in text.splitlines():
        line = line.split('#')[0].strip()
        if line:
            old, new = line.split()
            pairs.append((old, new))
    return pairs


def relocate(pairs, dry_run=False):
    """Move the files of `pairs` (old, new) and rewrite references; returns the number of files moved."""
    todo = [(old, new) for old, new in pairs if old != new and (ROOT / old).exists()]
    if len(set(new for _, new in todo)) != len(todo):
        raise SystemExit('two files would get the same new path')
    for _, new in todo:
        if (ROOT / new).exists():
            raise SystemExit('%s already exists' % new)
    if dry_run or not todo:
        return len(todo)
    for old, new in todo:
        (ROOT / new).parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(['git', 'mv', old, new], cwd=ROOT, check=True)
    table = dict(todo)
    pattern = re.compile('(?<![\\w/.-])(' + '|'.join(re.escape(old) for old in sorted(table, key=len, reverse=True)) + ')(?![\\w])')
    tracked = subprocess.run(['git', 'ls-files', '-z'], cwd=ROOT, check=True, capture_output=True, text=True).stdout.split('\0')
    for name in tracked:
        path = ROOT / name
        if not name.endswith(TEXT) or not path.is_file() or path.is_symlink():
            continue
        try:
            text = path.read_text()
        except UnicodeDecodeError:
            continue
        new = pattern.sub(lambda m: table[m.group(1)], text)
        if new != text:
            path.write_text(new)
    return len(todo)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    if len(args) != 1:
        raise SystemExit(__doc__.strip())
    n = relocate(read_pairs(args[0]), '--dry-run' in sys.argv)
    print('%d files %s' % (n, 'would move' if '--dry-run' in sys.argv else 'moved'))


if __name__ == '__main__':
    main()
