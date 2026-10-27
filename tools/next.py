#!/usr/bin/env python3
"""Best next work: the source files to claim next, and analyses from the automatic pipeline's results (build/auto.json).

  next.py [files|claims|near|types|identical|data|ee|all] [--top N] [--max-size N] [--library L] [--repo OWNER/NAME] [--pick]

  files     (default) source files to work on next, skipping claimed ones: game first, then kynapse, animation and physics,
            then the other libraries; within a library, the files with the most untried functions of tractable size
            (at most the median size of all remaining functions, or --max-size). A file is claimed when an open pull
            request of --repo (default: the GitHub repository of the `upstream` or `origin` remote; read with `gh`)
            changes it or names it on a `Claims:` line of its description, unless it is a draft without updates for
            48 hours, or when another local worktree changes it. --pick prints one file instead, drawn at random from the
            first --top files (weighted by their tractable bytes), so sessions starting together rarely take the same one.
            When both kinds are available, one pick in five revisits existing drafts, preferring saved near misses and
            smaller drafts. The listing shows both kinds; saved scores are hints, not current matching evidence.
  claims    files claimed by more than one open pull request; the lowest pull request number keeps the claim.
  near      near misses by differing-instruction count, with what differs (registers, order, code, length)
  types     functions the pipeline could not compile or decompile for want of a type, grouped by what they need
  identical groups of assembly functions with identical bodies (candidates for one template or one shared source)
  data      exact drafts that could not be placed because the function owns rodata (strings, tables)
  ee        functions m2c cannot read (EE instructions), grouped by instruction
Functions already provided by source units are left out everywhere.
"""
import argparse, collections, datetime, json, random, re, statistics, struct, subprocess, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
from units import load_units, ROOT
import include_asm
import preflight

RESULTS = ROOT / 'build' / 'auto.json'
GLOBAL = re.compile(r'\bD_[0-9A-F]{6,8}\b')
CALLEE = re.compile(r'\bfunc_[0-9A-F]{6,8}\b')


def load():
    res = json.loads(RESULTS.read_text()) if RESULTS.exists() else {}
    done = {f['addr'] for u in load_units(variant='SLUS_213.76') for f in u['functions'] if f.get('status') == 'source'}
    return {k: v for k, v in res.items() if int(k, 16) not in done}


def near(res, top, max_size):
    rows = [(v['score'], v['size'], k, v) for k, v in res.items() if v['status'] == 'near' and (max_size is None or v['size'] < max_size)]
    rows.sort(key=lambda r: (r[0], r[1]))
    by = collections.Counter((r[0], r[3].get('note', '')) for r in rows)
    print('near misses: %d functions' % len(rows))
    print('  differing instructions x kind of difference:')
    for n in sorted({s for s, _ in by}):
        print('   %2d: %s' % (n, ', '.join('%s %d' % (kind or '?', c) for (s, kind), c in sorted(by.items()) if s == n)))
    print('  closest (address, size, differing, kind, permuter):')
    for score, size, k, v in rows[:top]:
        p = v.get('permuter')
        print('   %s  %4d bytes  %d  %-10s %s' % (k, size, score, v.get('note', ''), ('tried %d, best %s' % (p.get('tries', 0), p.get('best'))) if p else ''))


def needs(v):
    """What a failed draft is missing, as (kind, subject)."""
    src = v.get('source', '')
    reason = v.get('reason', '')
    if v['status'] == 'm2c-failed':
        if reason.startswith('stack-object'):
            return 'local aggregate type (address of a stack object is passed on)', ''
        if reason.startswith('unset-register'):
            return 'calling convention (register read before it is set)', ''
        return None
    callee = CALLEE.findall(src.split('{', 1)[-1])
    glob = GLOBAL.findall(src)
    if 'too few arguments' in reason or 'too many' in reason:
        return 'callee signature', callee[0] if callee else ''
    if 'invalid type argument' in reason or 'invalid operands' in reason or 'void' in reason or 'wide integer' in reason \
            or 'cannot convert' in reason or 'pointer value' in reason:
        return 'type of a global or pointer (deref or arithmetic on an untyped value)', glob[0] if glob else 'argument/pointer'
    if 'undeclared' in reason:
        return 'declaration', reason.split('`')[1] if '`' in reason else ''
    return 'other compile error: ' + reason[:50], ''


def types(res, top, max_size):
    groups = collections.defaultdict(list)
    for k, v in res.items():
        if v['status'] in ('compile-failed', 'm2c-failed') and (max_size is None or v['size'] < max_size):
            n = needs(v)
            if n:
                groups[n].append(k)
    total = sum(len(g) for g in groups.values())
    print('missing types: %d functions' % total)
    kinds = collections.Counter()
    for (kind, _), g in groups.items():
        kinds[kind] += len(g)
    for kind, c in kinds.most_common():
        print('  %5d  %s' % (c, kind))
    print('  most needed subjects (one type or signature fixes all of a row):')
    for (kind, subject), g in sorted(groups.items(), key=lambda t: -len(t[1]))[:top]:
        if subject:
            print('   %3d  %-14s %s' % (len(g), subject, kind[:60]))


def families(res, top, max_size):
    sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
    import autodecomp
    inv = autodecomp.load_inventory()
    done = {f['addr'] for u in load_units(variant='SLUS_213.76') for f in u['functions'] if f.get('status') == 'source'}
    groups = collections.defaultdict(list)
    for f in inv:
        if f['addr'] in done or f['size'] <= 4 or (max_size is not None and f['size'] >= max_size):
            continue
        masked = []
        for i, w in enumerate(f['words']):
            r = f['rel'].get(str(i))
            masked.append(w & (0xFC000000 if r and r[0] == 'jal' else 0xFFFF0000) if r else w)
        groups[tuple(masked)].append(f)
    fams = [g for g in groups.values() if len(g) > 1]
    fams.sort(key=lambda g: -len(g) * g[0]['size'])
    print('groups of identical bodies (relocations masked): %d groups, %d functions' % (len(fams), sum(len(g) for g in fams)))
    for g in fams[:top]:
        st = collections.Counter(res.get('0x%x' % f['addr'], {}).get('status', 'untried') for f in g)
        print('  %4d x %3d bytes  e.g. 0x%x  %s' % (len(g), g[0]['size'], g[0]['addr'], dict(st)))


def data(res, top, max_size):
    rows = [(k, v) for k, v in res.items() if v['status'] == 'verify-failed' and v['reason'] == 'size']
    print('exact drafts blocked by owned rodata: %d functions, %d bytes' % (len(rows), sum(v['size'] for _, v in rows)))
    for k, v in rows[:top]:
        print('  %s %4d bytes %s' % (k, v['size'], v['name']))


def ee(res, top, max_size):
    c = collections.Counter()
    for k, v in res.items():
        if v['status'] == 'm2c-failed' and 'unknown instruction' in v.get('reason', ''):
            m = re.search(r'unknown instruction: (\S+)', v['reason'])
            c[m.group(1)] += 1
    print('functions m2c cannot read: %d' % sum(c.values()))
    for m, n in c.most_common(top):
        print('  %4d  %s' % (n, m))


TIERS = {'game': 0, 'kynapse': 1, 'animation': 1, 'physics': 1}
LAPSE = datetime.timedelta(hours=48)


def git(*args, cwd=ROOT):
    r = subprocess.run(['git', *args], cwd=cwd, capture_output=True, text=True)
    return r.stdout if r.returncode == 0 else ''


def github_repo():
    for remote in ('upstream', 'origin'):
        m = re.search(r'github\.com[:/]([^/]+/[^/]+?)(?:\.git)?$', git('remote', 'get-url', remote).strip())
        if m:
            return m.group(1)
    return None


def pr_claims(repo):
    """{path: [pull request numbers]} for the files that open pull requests change or name on a `Claims:` line; None with a reason when they cannot be read."""
    if not repo:
        return None, 'no GitHub remote (pass --repo OWNER/NAME)'
    try:
        r = subprocess.run(['gh', 'pr', 'list', '--repo', repo, '--state', 'open', '--limit', '500',
                            '--json', 'number,isDraft,updatedAt,files,body'], capture_output=True, text=True, timeout=60)
    except (OSError, subprocess.TimeoutExpired) as e:
        return None, 'gh failed (%s)' % e
    if r.returncode:
        return None, 'gh failed (%s)' % (r.stderr.strip().splitlines() or ['?'])[-1]
    now = datetime.datetime.now(datetime.timezone.utc)
    claims = {}
    for pr in json.loads(r.stdout):
        updated = datetime.datetime.fromisoformat(pr['updatedAt'].replace('Z', '+00:00'))
        if pr['isDraft'] and now - updated > LAPSE:
            continue
        paths = [f['path'] for f in pr.get('files') or []]
        for line in (pr.get('body') or '').splitlines():
            if line.strip().lower().startswith('claims:'):
                paths += re.findall(r'src/\S+?\.(?:c|cpp)\b', line)
        for path in set(paths):
            claims.setdefault(path, []).append(pr['number'])
    return claims, None


def worktree_claims():
    """{path: worktree} for the files that other worktrees of this repository change against main."""
    here, claims, tree = ROOT.resolve(), {}, None
    for line in git('worktree', 'list', '--porcelain').splitlines() + ['']:
        if line.startswith('worktree '):
            tree = Path(line[9:]).resolve()
        elif not line and tree and tree != here:
            base = next((b for b in ('main', 'origin/main', 'upstream/main') if git('rev-parse', '--verify', '-q', b, cwd=tree)), None)
            changed = git('diff', '--name-only', base + '...HEAD', cwd=tree).split() if base else []
            changed += [l[3:] for l in git('status', '--porcelain', cwd=tree).splitlines()]
            for path in changed:
                claims[path] = tree.parent.name + '/' + tree.name
            tree = None
    return claims


def files(top, max_size, library, repo, pick=False):
    units = load_units(variant='SLUS_213.76')
    size = {f['addr']: f['size'] for u in units for f in u['functions']}
    rows = []
    for source, lib in sorted({(u['source'], u['library']) for u in units}):
        if library and lib != library:
            continue
        text = (ROOT / source).read_text()
        left = [include_asm.function_address(m.name) for m in include_asm.markers(text, set())]
        untried = {include_asm.function_address(m.name) for m in include_asm.markers(text, {'NON_MATCHING'})}
        left = [(a, size[a]) for a in left if a in size and size[a] > 8]  # 8-byte orphan pieces are not code
        if left:
            rows.append((source, lib, left, untried))
    if not rows:
        print('no remaining functions')
        return
    limit = max_size or statistics.median(s for _, _, left, _ in rows for _, s in left)
    claims, problem = pr_claims(repo or github_repo())
    if problem:
        print('note: claims of open pull requests unknown: %s; only local worktrees are checked' % problem, file=sys.stderr)
    claims = dict(claims or {}, **worktree_claims())
    results = {int(k, 16): v for k, v in json.loads(RESULTS.read_text()).items()} if RESULTS.exists() else {}
    ranked, revisits, taken = [], [], 0
    for source, lib, left, untried in rows:
        if source in claims:
            taken += 1
            continue
        easy = [(a, s) for a, s in left if s <= limit and a in untried]
        drafts = [(a, s) for a, s in left if s <= limit and a not in untried]
        if easy or drafts:
            row = (TIERS.get(lib, 2), -len(easy), -sum(s for _, s in easy), source, lib, len(left), easy, drafts)
            ranked.append(row)
            if drafts:
                near_scores = [v['score'] for a, _ in drafts
                               if (v := results.get(a, {})).get('status') == 'near'
                               and isinstance(v.get('score'), (int, float))]
                revisits.append((row, min(near_scores, default=float('inf')), min(s for _, s in drafts)))
    ranked.sort()
    revisits.sort(key=lambda r: (r[0][0], r[1], r[2], r[0][3]))
    if pick:
        fresh = [r for r in ranked if r[6]][:top]
        if revisits and (not fresh or random.random() < 0.2):
            print(random.choice(revisits[:top])[0][3])
        elif fresh:
            print(random.choices(fresh, weights=[-r[2] for r in fresh])[0][3])
        return
    print('files to work on next (tractable: at most %d bytes; %d claimed files skipped; --pick revisits drafts 20%% of the time):' % (limit, taken))
    print('  %-48s %-9s %5s %8s %7s %7s' % ('file', 'library', 'left', 'untried', 'drafts', 'bytes'))
    for _, _, _, source, lib, n, easy, drafts in ranked[:top]:
        print('  %-48s %-9s %5d %8d %7d %7d' % (source, lib, n, len(easy), len(drafts), sum(s for _, s in easy + drafts)))


def contested(repo):
    claims, problem = pr_claims(repo or github_repo())
    if problem:
        raise SystemExit('claims of open pull requests unknown: %s' % problem)
    both = {path: sorted(prs) for path, prs in claims.items() if len(prs) > 1 and path.startswith('src/')}
    print('files claimed by more than one open pull request: %d (the first number keeps the claim)' % len(both))
    for path, prs in sorted(both.items()):
        print('  %-48s %s' % (path, ' '.join('#%d' % n for n in prs)))


EE_VECTOR = re.compile(r'^(p(add|sub|cpy|ext|pac|mul|div|and|or|nor|xor|abs|min|max|lzc|sll|srl|sra|rot|ack|mfh|mth|mfl|mtl|ceq|cgt|inc|sat)[a-z0-9]*|lqc2|sqc2|qm[ft]c2.*|c[ft]c2|v[a-z0-9.]+|mf(sa|hi1|lo1)|mt(sa|sah|hi1|lo1)|madd1|mult1|multu1|div1|divu1|adda.*|suba.*|madda.*)$')


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('what', nargs='?', default='files', choices=['files', 'claims', 'near', 'types', 'identical', 'families', 'data', 'ee', 'all'])
    ap.add_argument('--top', type=int, default=15)
    ap.add_argument('--max-size', type=int)
    ap.add_argument('--library', help='files: only this library (game, kynapse, animation, physics, ...)')
    ap.add_argument('--repo', help='files, claims: GitHub repository whose open pull requests claim files (OWNER/NAME)')
    ap.add_argument('--pick', action='store_true', help='files: print one file, drawn at random from the first --top')
    a = ap.parse_args()
    preflight.require()
    if a.what == 'files':
        return files(a.top, a.max_size, a.library, a.repo, a.pick)
    if a.what == 'claims':
        return contested(a.repo)
    if a.what == 'families':
        a.what = 'identical'
    res = load()
    if not res:
        raise SystemExit('no results: run tools/autodecomp.py run first')
    for name, fn in (('near', near), ('types', types), ('identical', families), ('data', data), ('ee', ee)):
        if a.what in (name, 'all'):
            fn(res, a.top, a.max_size)
            print()


if __name__ == '__main__':
    preflight.guard(main)
