#!/usr/bin/env python3
"""One-time move of include/ from origin-based directories to one directory per library, updating every #include.

Usage: reorganize_includes.py [--apply]       (default: dry run that prints the plan and any problem)

Before: include/{auto,campaign,context,mod,recovered,classes}/ next to the library directories.
After:  include/<library>/ for game, kynapse, animation, physics, rw_core, rw_audio, apt, ps2 (shared EE/VU0 helpers)
        include/game/classes, include/kynapse/classes   generated class interfaces (tools/maint/class_skeletons.py)
        include/<library>/layouts/                      generated access views (tools/pipeline/context_recovery.py); the library
                                                        of every view is recorded in config/layout_libraries.json
A header that only forwards to another header is removed and its includers point at the real one. Every quoted include
is resolved the way the compiler does (the includer's directory, then include/) and rewritten to the new location.
Paths of moved headers in config/*.json and docs are rewritten too. Namespaces, include guards and file contents are
untouched, so the rebuilt image stays identical. Sources that include a moved header are recompiled by the next build.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import collections, json, posixpath, re, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
INCLUDE = re.compile(r'^(\s*#\s*include\s+")([^"]+)(")', re.M)

DIR_RULES = [
    ('include/campaign/actor/', 'include/game/actor/'),
    ('include/campaign/behaviors/', 'include/kynapse/behaviors/'),
    ('include/campaign/graph/', 'include/kynapse/graph/'),
    ('include/campaign/graphics/', 'include/game/graphics/'),
    ('include/campaign/weapons/', 'include/game/weapons/'),
    ('include/context/behaviors/', 'include/kynapse/agents/'),
    ('include/mod/animation/', 'include/animation/'),
    ('include/mod/arms/', 'include/animation/arms/'),
    ('include/mod/camera/', 'include/game/camera/'),
    ('include/mod/effects/', 'include/game/effects/'),
    ('include/mod/math/', 'include/game/math/'),
    ('include/mod/weapons/', 'include/game/weapons/'),
    ('include/classes/game/', 'include/game/classes/'),
    ('include/classes/kynapse/', 'include/kynapse/classes/'),
    ('include/classes/other/', 'include/game/classes/other/'),
    ('include/ps2/kynapse/', 'include/kynapse/'),
]
FILE_RULES = {
    'include/auto/prelude.h': 'include/ps2/prelude.h',
    'include/classes/README.md': 'include/game/classes/README.md',
    'include/classes/all.hpp': 'include/game/classes/all.hpp',
    'include/classes/hierarchy.hpp': 'include/game/classes/hierarchy.hpp',
    'include/classes/support.hpp': 'include/game/classes/support.hpp',
    'include/recovered/layouts.h': 'include/game/layouts/layouts.h',
    'include/recovered/signatures.h': 'include/game/layouts/signatures.h',
    'include/mod/README.md': 'docs/native-headers.md',
    'include/mod/effects/random.h': 'include/game/effects/random_state.h',
    'include/animation/pose_campaign.hpp': 'include/animation/pose_operations.hpp',
    'include/rw_core/im3d_campaign.h': 'include/rw_core/im3d_operations.h',
    'include/rw_core/image_campaign.h': 'include/rw_core/image_operations.h',
}
LIBRARIES = ('game', 'kynapse', 'animation', 'physics', 'rw_core', 'rw_audio', 'apt', 'sony', 'libc', 'ps2')
AGGREGATORS = {'include/recovered/layouts.h', 'include/recovered/signatures.h', 'include/classes/all.hpp',
               'include/classes/hierarchy.hpp', 'include/classes/support.hpp'}
NAME_HINTS = [   # first match wins; a view without code evidence is filed by its name, else under game
    ('kynapse', re.compile(r'Kaim|Kynapse|Nav(Edge|Node)|PathFinder|PathObject|PathWay|PathManager|Spatial|Grid|Avoidance|'
                           r'Steering|Query|Visitor|Allocator|Agent|Perception|PointMapper|Tracker|Constraint|Graph|CBrain|'
                           r'CTeam|Route')),
    ('animation', re.compile(r'Animation|Skeleton|Pose|Sampl|Playback|Track|Rig')),
    ('physics', re.compile(r'Physics|Collision|Contact|Hit(Collector)?$|ClosestHit|ComponentSweep')),
    ('rw_audio', re.compile(r'^Rwa|Sound')),
    ('rw_core', re.compile(r'^Rw(?!a)')),
]


def tracked_files():
    out = subprocess.run(['git', 'ls-files', 'include', 'src', 'config', 'docs', 'tools', 'tests', 'README.md', 'AGENTS.md',
                          'PLAN.md'], cwd=ROOT, capture_output=True, text=True, check=True).stdout.split('\n')
    return [f for f in out if f]


def is_text(path):
    return path.suffix in {'.h', '.hpp', '.c', '.cpp', '.inc', '.md', '.py', '.json', '.yaml', '.txt'}


def resolve(includer, text, files):
    """File the compiler finds for `text` (includer's directory first, then include/); also says which rule found it."""
    near = posixpath.normpath(posixpath.join(posixpath.dirname(includer), text))
    if near in files:
        return near, 'near'
    root = posixpath.normpath('include/' + text)
    if root in files:
        return root, 'root'
    return None, None


def forwards_to(path, files):
    """The single header this file only forwards to, or None."""
    lines = [l for l in (ROOT / path).read_text(errors='replace').split('\n')
             if l.strip() and not l.strip().startswith(('//', '/*', '*'))
             and not re.match(r'\s*#\s*(ifndef|define|endif|pragma once)', l)]
    if len(lines) == 1 and path.startswith('include/'):
        m = INCLUDE.match(lines[0])
        if m:
            return resolve(path, m.group(2), files)[0]
    return None


def library_of_source(path):
    parts = path.split('/')
    if parts[0] == 'src' and len(parts) > 2:
        return parts[1]
    return None


def layout_libraries(files, users):
    """Library for every generated access view: code that uses it, then the verified-by addresses, then its name."""
    import layout
    views = [f for f in files if f.startswith('include/recovered/Recovered_')]
    libs = {}
    for view in views:
        name = Path(view).stem
        found = collections.Counter()
        todo, seen = [view], set()
        while todo:
            f = todo.pop()
            if f in seen:
                continue
            seen.add(f)
            for user in users.get(f, ()):
                if user in AGGREGATORS:
                    continue
                lib = library_of_source(user)
                if lib and lib != 'linkonce':
                    found[lib] += 1
                elif user.startswith('include/'):
                    todo.append(user)
        if not found:
            text = (ROOT / view).read_text(errors='replace').split('\n')[0]
            for address in re.findall(r'0x([0-9A-Fa-f]+)', text):
                try:
                    lib = layout.library_of(int(address, 16))
                except Exception:
                    continue
                if lib != 'linkonce':
                    found[lib] += 1
        if not found:
            for lib, pattern in NAME_HINTS:
                if pattern.search(name.replace('Recovered_', '')):
                    found[lib] += 1
                    break
        libs[name] = 'game' if not found or 'game' in found else found.most_common(1)[0][0]
    return libs


def plan(files):
    fileset = set(files)
    users = collections.defaultdict(set)
    for f in files:
        if f.startswith(('src/', 'include/')) and is_text(Path(f)):
            for m in INCLUDE.finditer((ROOT / f).read_text(errors='replace')):
                target, _ = resolve(f, m.group(2), fileset)
                if target:
                    users[target].add(f)
    wrappers = {}
    for f in files:
        if f.startswith('include/') and f.endswith(('.h', '.hpp')):
            target = forwards_to(f, fileset)
            if target and target != f:
                wrappers[f] = target
    libs = layout_libraries(files, users)
    move = {}
    for f in files:
        if not f.startswith('include/') or f in wrappers:
            continue
        new = FILE_RULES.get(f)
        if new is None and f.startswith('include/recovered/Recovered_'):
            new = 'include/%s/layouts/%s' % (libs[Path(f).stem], Path(f).name)
        if new is None and f.startswith('include/campaign/graphics/'):
            direct = {library_of_source(u) for u in users[f]} - {None, 'linkonce'}
            new = ('include/apt/' + Path(f).name) if direct == {'apt'} else 'include/game/graphics/' + Path(f).name
        if new is None:
            for old, dest in DIR_RULES:
                if f.startswith(old):
                    new = dest + f[len(old):]
                    break
        move[f] = new or f
    # forwarding headers: follow chains to the header that holds the content
    def final(f):
        seen = set()
        while f in wrappers and f not in seen:
            seen.add(f)
            f = wrappers[f]
        return move.get(f, f)
    return move, wrappers, final, libs


def rewrite_includes(files, move, wrappers, final):
    fileset = set(files)
    changes, unresolved = {}, []
    for f in files:
        if not f.startswith(('src/', 'include/')) or not is_text(Path(f)) or f in wrappers:
            continue
        text = (ROOT / f).read_text(errors='replace')
        here = move.get(f, f)

        def swap(m):
            target, how = resolve(f, m.group(2), fileset)
            if target is None:
                unresolved.append((f, m.group(2)))
                return m.group(0)
            new_target = final(target)
            if how == 'near' and posixpath.dirname(new_target) == posixpath.dirname(here):
                new_text = posixpath.basename(new_target)
            else:
                new_text = new_target[len('include/'):]
            return m.group(1) + new_text + m.group(3)
        out = INCLUDE.sub(swap, text)
        if out != text:
            changes[f] = out
    return changes, unresolved


def main():
    apply = '--apply' in sys.argv
    files = tracked_files()
    move, wrappers, final, libs = plan(files)
    dest = collections.Counter(v for v in move.values())
    clash = [(v, [k for k, x in move.items() if x == v]) for v, n in dest.items() if n > 1]
    existing = [(new, old) for old, new in move.items() if new != old and new in set(files) and new not in
                {o for o, n in move.items() if n != o} and new not in wrappers]
    changes, unresolved = rewrite_includes(files, move, wrappers, final)
    moved = {o: n for o, n in move.items() if o != n}
    print('%d headers move, %d forwarding headers are removed, %d files change their includes' % (
        len(moved), len(wrappers), len(changes)))
    for name, items in (('destination clash', clash), ('destination exists', existing), ('unresolved include', unresolved)):
        for item in items:
            print('PROBLEM', name, item)
    if clash or existing or any(not u[1].startswith('<') for u in unresolved):
        if not apply:
            return 1
        raise SystemExit('refusing to apply with problems')
    if not apply:
        by = collections.Counter(posixpath.dirname(n) for n in moved.values())
        for d, n in sorted(by.items()):
            print('%5d  %s' % (n, d))
        return 0
    for old in sorted(wrappers):
        subprocess.run(['git', 'rm', '-q', old], cwd=ROOT, check=True)
    for old, new in sorted(moved.items()):
        (ROOT / new).parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(['git', 'mv', old, new], cwd=ROOT, check=True)
    for f, out in changes.items():
        (ROOT / move.get(f, f)).write_text(out)
    # paths of moved headers mentioned in configuration and documentation
    paths = {o: n for o, n in moved.items()}
    for f in files:
        if f.startswith(('config/', 'docs/', 'tools/', 'tests/')) or f in ('README.md', 'AGENTS.md', 'PLAN.md'):
            p = ROOT / f
            if not p.is_file() or not is_text(p):
                continue
            text = out = p.read_text(errors='replace')
            pairs = [(o, n) for o, n in paths.items()] + [(o, final(o)) for o in wrappers]
            for old, new in sorted(pairs, key=lambda kv: -len(kv[0])):
                for a, b in ((old, new), (old[len('include/'):], new[len('include/'):])):
                    if a.startswith('include/') or b.startswith('docs/'):
                        out = out.replace(a, b)
                    else:
                        out = re.sub(r'(?<![\w/.-])' + re.escape(a) + r'(?![\w.])', b, out)
            if out != text:
                p.write_text(out)
    (ROOT / 'config/layout_libraries.json').write_text(json.dumps(libs, indent=1, sort_keys=True) + '\n')
    print('applied')
    return 0


if __name__ == '__main__':
    sys.exit(main())
