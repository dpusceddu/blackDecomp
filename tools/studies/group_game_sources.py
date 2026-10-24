#!/usr/bin/env python3
"""Group the translation unit files of src/game/ into subsystem directories, from the evidence the repository already holds.

Files keep their names (`tu_<address>` until the original name is known); only the directory says what they are for.
The directory a file is in is its subsystem: the layout is the record, nothing about it is committed besides the files. This study
only proposes: it writes build/SLUS_213.76/game_subsystems.txt, one line per file name (`file subsystem evidence`); a file that
is already in a subsystem directory counts as `manual` and keeps it. Every file without evidence stays in src/game/unsorted/.

  group_game_sources.py                 compute the proposal into build/ (files already sorted keep their directory) and print the counts
  group_game_sources.py --apply         move the files to the directories the proposal names (git mv; splits.yaml, docs and
                                        generated comments follow, tools/studies/relocate_sources.py); run `ninja` afterwards

Needs the units that `ninja` derives (build/SLUS_213.76/units.json). A file gets the subsystem with the most evidence among:
the classes of the bound and alias names of the functions it compiles (config/SLUS_213.76/symbols.txt: ModWeapons, ModWorld, CameraController, AIMovement, RouteRequest, Frontend...), the headers it
includes (include/game/weapons, camera, effects, frontend, actor), the descriptive prefix of its name (ai_route_*, frontend_*, muzzle_*), and the exact consumers of the native header views
(config/SLUS_213.76/native_header_evidence.json: weapons, camera, effects). Classes that name a general area (CampaignActor) count
half. If two subsystems of one parent tie (ai/movement and ai/navigation) the file gets the parent (ai). A file without evidence of
its own gets the subsystem its two neighbours in address order agree on (`bracketed`: the engine's code is laid out by subsystem,
so a unit between two AI units is AI), or their common parent. Anything else is `unsorted`. Movement, routes and AI actions are
split under ai/ because the engine groups them (0x172000-0x19d000); nothing is guessed from names alone.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import bisect, collections, json, re, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / _d) for _d in ('', 'build', 'pipeline', 'maint')]
import splits as S


ROOT = Path(__file__).resolve().parents[2]
MAP = ROOT / 'build/SLUS_213.76/game_subsystems.txt'
SLUG = 'SLUS_213.76'
SPECIFIC = [
    ('ai/movement', r'AIMovement|MovementMode|FormationMode|DirectMode|MovementCore|^ai_movement|Recovered_Movement'),
    ('ai/navigation', r'AIRoute|RouteRequest|RouteQueue|RouteMode|AINavigation|NodeSearch|^ai_route|GamePathPS2|game_path|'
                      r'Recovered_Route|Recovered_PathCallback|Recovered_PathFile'),
    ('ai', r'AIAction|ActionStack|ActionTimer|ActionWeight|AICover|^ai_action|BlackGame::Action|Recovered_Action'),
    ('weapons', r'ModWeapons|^mod_weapons|game/weapons|Recovered_BkMod(?:Weapon|Inventory|Delayed|Source)|'
                r'Recovered_(?:Inventory|Weapon|MovingShot|MovingPool|Reserves)'),
    ('world', r'ModWorld|GameCollisionQueue|mod_world'),
    ('camera', r'CameraController|game/camera|PadBackend|^actor_camera'),
    ('effects', r'ModEffects|game/effects|^muzzle_|^emitter_|Recovered_Bk(?:Effect|Emitter)|Recovered_ModEffects|'
                r'Recovered_Muzzle|Recovered_Emitter'),
    ('audio', r'SoundEnvelope|sound_envelopes|audio_provider|TimedEnvelope|DestructionEnvelope|LowHealthEnvelope'),
    ('ui', r'game/frontend|^frontend_|Frontend'),
]
GENERAL = [('actor', r'game/actor|CampaignActor|ActorStateMachine|ActorEntries|^actor_|Recovered_Actor|Recovered_BkActor')]
HEADER_DIRS = {'include/game/weapons': 'weapons', 'include/game/camera': 'camera', 'include/game/effects': 'effects'}


def common_parent(subsystems):
    parts = [s.split('/') for s in subsystems]
    out = []
    for column in zip(*parts):
        if len(set(column)) != 1:
            break
        out.append(column[0])
    return '/'.join(out)


def game_files():
    """{file name: dict(path, lo, hi, functions)} for the files of src/game/ (not inline/), from the units `ninja` derives
    (build/SLUS_213.76/units.json): lo and hi span the functions the file really compiles, not its split range."""
    path = ROOT / 'build' / SLUG / 'units.json'
    if not path.exists():
        raise SystemExit('run ninja first: %s lists the functions each file compiles' % path.relative_to(ROOT))
    files = {}
    for u in json.loads(path.read_text())['units']:
        if not u['source'].startswith('src/game/') or '/inline/' in u['source']:
            continue
        compiled = [f for f in u['functions'] if f.get('status') == 'source']
        if not compiled:
            continue
        d = files.setdefault(Path(u['source']).name, dict(path=u['source'], lo=compiled[0]['addr'], hi=0, functions=[]))
        d['lo'] = min(d['lo'], min(f['addr'] for f in compiled))
        d['hi'] = max(d['hi'], max(f['addr'] + f['size'] for f in compiled))
        d['functions'] += [(f['addr'], f.get('symbol', '')) for f in compiled]
    for split in S.load_splits(SLUG):      # files that compile nothing yet (only INCLUDE_ASM lines and drafts)
        name = Path(split.src).name
        if split.src.startswith('src/game/') and '/inline/' not in split.src and name not in files:
            files[name] = dict(path=split.src, lo=split.start, hi=split.end, functions=[])
    return files


def symbols():
    out = []
    for line in (ROOT / 'config' / SLUG / 'symbols.txt').read_text().splitlines():
        m = re.match(r'(\S+) = (0x[0-9a-fA-F]+); //', line)
        if m:
            out.append((int(m.group(2), 16), m.group(1)))
    out.sort()
    return out


def consumers():
    """{address: subsystem} for the exact consumers of the native header views."""
    layers = json.loads((ROOT / 'config' / SLUG / 'native_header_evidence.json').read_text())['layers']
    return {int(a, 16): HEADER_DIRS[l['header'].rsplit('/', 1)[0]] for l in layers
            if l['header'].rsplit('/', 1)[0] in HEADER_DIRS for a in l.get('controls', [])}


def classify(files):
    syms = symbols()
    addrs = [a for a, _ in syms]
    controls = consumers()
    direct = {}
    for stem, d in files.items():
        text = (ROOT / d['path']).read_text(errors='replace')
        tokens = [('name', stem)] + [('include', i) for i in re.findall(r'#include "([^"]+)"', text)]
        tokens += [('view', v) for v in set(re.findall(r'Recovered_\w+', text))]
        tokens += [('symbol', name) for _, name in d['functions']]
        for address, _ in d['functions']:        # readable aliases of the compiled functions
            i = bisect.bisect_left(addrs, address)
            while i < len(addrs) and addrs[i] == address:
                tokens.append(('symbol', syms[i][1]))
                i += 1
        score, kinds = collections.Counter(), collections.defaultdict(set)
        for kind, token in tokens:
            for weight, table in ((2, SPECIFIC), (1, GENERAL)):
                for sub, rx in table:
                    if re.search(rx, token):
                        score[sub] += weight
                        kinds[sub].add(kind)
        for a, sub in controls.items():
            if d['lo'] <= a < d['hi']:
                score[sub] += 4
                kinds[sub].add('consumer')
        if not score:
            continue
        top = max(score.values())
        winners = [s for s, v in score.items() if 2 * v > top]
        sub = winners[0] if len(winners) == 1 else common_parent(winners)
        if sub:
            direct[stem] = (sub, 'direct:' + ','.join(sorted(kinds[sub] if sub in kinds else set().union(*(kinds[w] for w in winners)))))
    anchors = sorted((files[s]['lo'], s) for s in direct)
    starts = [a for a, _ in anchors]
    result = {}
    for stem, d in files.items():
        if stem in direct:
            result[stem] = direct[stem]
            continue
        i = bisect.bisect_left(starts, d['lo'])
        before = direct[anchors[i - 1][1]][0] if i else None
        after = direct[anchors[i][1]][0] if i < len(anchors) else None
        sub = common_parent([before, after]) if before and after else ''
        result[stem] = (sub, 'bracketed') if sub else ('unsorted', 'none')
    return result


def read_mapping(files):
    """{stem: (subsystem, evidence)} of the files that are already in a subsystem directory (the layout is the record)."""
    rows = {}
    for stem, d in files.items():
        sub = Path(d['path']).parent.relative_to('src/game').as_posix()
        if sub != 'unsorted' and sub != '.':
            rows[stem] = (sub, 'manual')
    return rows


def write_mapping(result, files):
    merged = {**result, **read_mapping(files)}
    head = ('# Proposed subsystem directory of every src/game/ file: `file directory evidence`, sorted by address. Written by\n'
            '# tools/studies/group_game_sources.py into build/ (evidence: direct:<what>, bracketed, none, manual = already placed).\n'
            '# Move a file when you learn what it is, rename it when you learn its name (CONTRIBUTING.md).\n')
    lines = ['%s %s %s' % (s, merged[s][0], merged[s][1]) for s in sorted(files, key=lambda s: (files[s]['lo'], s))]
    MAP.parent.mkdir(parents=True, exist_ok=True)
    MAP.write_text(head + '\n'.join(lines) + '\n')
    return merged


def target(path, sub):
    p = Path(path)
    return str(p.parent / sub / p.name)


def main():
    files = game_files()
    if '--apply' in sys.argv:
        sys.path.insert(0, str(Path(__file__).resolve().parent))
        import relocate_sources
        merged = write_mapping(classify(files), files)
        rows = merged
        pairs = [(d['path'], target('src/game/' + Path(d['path']).name, rows.get(stem, ('unsorted', ''))[0]))
                 for stem, d in files.items()]
        print(relocate_sources.relocate(pairs), 'files moved')
        return
    merged = write_mapping(classify(files), files)
    print(len(files), 'files', dict(collections.Counter(v[0] for v in merged.values())))
    print(dict(collections.Counter(v[1].split(':')[0] for v in merged.values())))


if __name__ == '__main__':
    main()
