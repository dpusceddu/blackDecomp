#!/usr/bin/env python3
"""One-time migration to one source file per translation unit with INCLUDE_ASM markers (stage 1 of docs/build.md history).

  migrate_include_asm.py plan            print what would be written, change nothing
  migrate_include_asm.py write           regroup src/ into TU files, rewrite config/units.yaml for them (still the old format)
  migrate_include_asm.py verify          settle the units with the build backend and report parts that did not place
                                         identically; `write --demoted FILE` rewrites those parts conservatively

The old layout has one source file per unit (about 2,900 files); every file holds only recovered functions and the other
functions of the translation unit are implicit. The new layout (tools/build/include_asm.py, include/include_asm.h) has one file per
translation unit of build/SLUS_213.76/tus.yaml that lists every function of its address range in address order: recovered functions
as C/C++, the others as `INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_XXXXXXXX);` lines, and drafts that do not match
yet (src/*/nonmatching/ and the sources of all-assembly units) as `#ifdef NON_MATCHING` blocks whose `#else` branch is the marker.

Units of one TU are merged only when they are plain automatic drafts (origin auto, C) with the same compiler and flags, no special
options, and when the constants of the assembly functions between them do not interleave (units_verify.py's slot rule). Hand-written
sources keep their file and their text. A TU that cannot be one file is split at the places where flags, language, constants or
declarations disagree, and each part is a file of its own. Sources compiled several times with -D selectors are left alone.
`write` is re-runnable from a checkout of the old layout (commit f972a63e: src/ and config/units.yaml) and reproduces the committed
files (the fallback levels it found were kept in a state file that is no longer committed); `run` (settlement loop) needs the old tools of that commit.
Stage 2 is tools/studies/migrate_split_list.py.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import argparse, bisect, collections, glob, json, re, subprocess, sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import layout
import include_asm

SLUG = 'SLUS_213.76'
BUILD = ROOT / 'build' / SLUG
ASM_DIR = 'asm/SLUS_213.76/nonmatchings'
SPECIAL_KEYS = ('data_ranges', 'rodata_type_splits', 'shared_exception_tables', 'full_tu_context',
                'unlinked_context_helpers', 'trim')
CONSTANT_SECTIONS = ('.rodata', '.lit4', '.gcc_except_table')
GAP = re.compile(r'/\* Assembly between the functions: (.*?) \*/\n\n?', re.S)
TU_NOTE = re.compile(r'/\* Translation unit .*?\*/\n', re.S)
DEFAULT_FLAGS = ['-O2', '-G0', '-snas']
DEFAULT_COMPILER = 'ee-gcc2.95.3-136'


def num(v):
    return int(v, 0) if isinstance(v, str) else int(v)


# ----------------------------------------------------------------------------------------------------------- inputs

class World:
    """Everything the planner reads: units, function table, constants ownership, TU map."""

    def __init__(self):
        self.doc = yaml.safe_load((ROOT / 'config/units.yaml').read_text())
        self.units = self.doc['units']
        for u in self.units:
            for f in u['functions']:
                f['addr'] = num(f['addr'])
        placement = json.loads((BUILD / 'placement.json').read_text())
        self.funcs = [(f['addr'], f['end']) for f in placement['functions']]
        self.starts = [a for a, _ in self.funcs]
        self.ends = dict(self.funcs)
        by_name = {f['name']: f['addr'] for f in placement['functions']}
        self.slots = {sec: [by_name[e['owner']] if e.get('owner') else None for e in placement['sections'][sec]]
                      for sec in CONSTANT_SECTIONS}
        tus = yaml.safe_load(__import__('layout').tus_file().read_text())['tus']
        tus.sort(key=lambda t: num(t['text'][0]))
        self.tus = tus
        self.tu_starts = [num(t['text'][0]) for t in tus]
        self.tu_ends = [num(t['text'][1]) for t in tus]

    def tu_index(self, addr):
        k = bisect.bisect_right(self.tu_starts, addr) - 1
        return k if k >= 0 and addr < self.tu_ends[k] else None

    def functions_in(self, lo, hi):
        return self.starts[bisect.bisect_left(self.starts, lo):bisect.bisect_left(self.starts, hi)]

    def layout_ok(self, compiled):
        """The constants owned by the compiled functions must be adjacent entries of each constant section."""
        for lst in self.slots.values():
            idx = [i for i, o in enumerate(lst) if o in compiled]
            if idx and idx != list(range(idx[0], idx[0] + len(idx))):
                return False
        return True


# ----------------------------------------------------------------------------------------------------------- pieces

class Piece:
    """A source file as the old layout had it: the text of one unit, or a draft."""

    def __init__(self, uid, src, text, srcs, funcs, unit=None, draft=False):
        self.id, self.src, self.text, self.unit, self.draft = uid, src, text, unit, draft
        self.srcs = sorted(srcs)          # compiled functions
        self.funcs = sorted(funcs)        # functions the piece relates to (compiled or not)
        self.suffix = Path(src).suffix
        u = unit or {}
        self.compiler = u.get('compiler', DEFAULT_COMPILER)
        self.flags = list(u.get('flags', DEFAULT_FLAGS))
        self.base_flags = tuple(f for f in self.flags if f != '-ffunction-sections')
        self.special = any(u.get(k) for k in SPECIAL_KEYS)
        self.frozen = False
        self.anchor = None
        self.level = 0
        self.had_sections = '-ffunction-sections' in self.flags
        self.plain = bool(unit) and not draft and u.get('origin') == 'auto' and self.suffix == '.c' and not self.special \
            and not any(f.startswith('-D') for f in self.flags) \
            and not re.search(r'^\s*#\s*(if|ifdef|ifndef|else|elif|endif)\b', text, re.M)

    @property
    def key(self):
        u = self.unit or {}
        return (self.compiler, self.base_flags, self.suffix, u.get('owner'), u.get('language'))


def draft_functions(text, filename, starts, by_symbol=None):
    """Addresses a draft file defines or documents: func_XXXXXXXX definitions, methods bound by __asm__, the header comment,
    the file name. The first source of evidence that names a function start wins."""
    def valid(items):
        return sorted({a for a in items if a in starts})

    comment = '\n'.join(l for l in text.split('\n')[:8] if l.lstrip().startswith(('//', '/*', '*')))
    defs = [int(x, 16) for x in re.findall(
        r'^[A-Za-z_][\w \*:<>~&,"]*?\bfunc_([0-9A-F]{8})\s*\([^;{]*\)\s*(?:const\s*)?\{', text, re.M)]
    bound = []
    for name, addr in re.findall(r'(\w+)\s*\([^;{}]*\)\s*(?:const\s*)?__asm__\s*\(\s*"func_([0-9A-Fa-f]{8})"\s*\)', text):
        if re.search(r'::\s*%s\s*\([^;{]*\)\s*(?:const\s*)?\{' % re.escape(name), text) or \
                re.search(r'\b%s\s*\([^;{}]*\)\s*(?:const\s*)?\{' % re.escape(name), text):
            bound.append(int(addr, 16))
    for tier in (defs, bound,
                 [int(x, 16) for x in re.findall(r'func_([0-9A-Fa-f]{8})', comment)],
                 [int(x, 16) for x in re.findall(r'(?<![0-9a-f])([0-9a-f]{6})(?![0-9a-f])', Path(filename).name)],
                 [int(x, 16) for x in re.findall(r'0x([0-9a-fA-F]{6})\b', comment)]):
        found = valid(tier)
        if found:
            return found
    return []


def unwrap_draft(text):
    """Drop the `#ifdef NONMATCHING` / `#if 0` ... `#endif` wrapper of a draft file and rename the macro; returns the body."""
    lines = text.rstrip('\n').split('\n')
    idx = [i for i, l in enumerate(lines) if re.match(r'\s*#\s*(ifdef\s+NONMATCHING|if\s+0)\s*(//.*|/\*.*)?$', l)]
    if idx and lines[-1].strip().startswith('#endif'):
        i = idx[0]
        depth = 0
        ok = True
        for l in lines[i + 1:-1]:
            s = l.strip()
            if s.startswith(('#if', '#ifdef', '#ifndef')):
                depth += 1
            elif s.startswith('#endif'):
                depth -= 1
                if depth < 0:
                    ok = False
                    break
        if ok and depth == 0:
            lines = lines[:i] + lines[i + 1:-1]
    body = '\n'.join(lines)
    body = re.sub(r'\bNONMATCHING\b', 'NON_MATCHING', body)
    return body.strip('\n')


def make_pieces(world):
    pieces, by_source = [], collections.defaultdict(list)
    for u in world.units:
        by_source[u['source']].append(u)
    starts = set(world.starts)
    used = set()
    for u in world.units:
        src = u['source']
        path = ROOT / src
        if not path.exists():
            raise SystemExit('missing source %s of unit %s' % (src, u['name']))
        srcs = [f['addr'] for f in u['functions'] if f['status'] == 'source']
        funcs = [f['addr'] for f in u['functions']]
        shared = len(by_source[src]) > 1
        if shared and src in used:
            continue
        text = path.read_text()
        if shared:
            used.add(src)
            p = Piece('src:' + src, src, text, [a for v in by_source[src] for f in v['functions'] if f['status'] == 'source'
                                                 for a in [f['addr']]], [f['addr'] for v in by_source[src] for f in v['functions']],
                      unit=u)
            p.frozen = True
            p.units = by_source[src]
        else:
            p = Piece('unit:' + u['name'], src, text, srcs, funcs, unit=u, draft=not srcs)
            p.units = [u]
        pieces.append(p)
    # drafts nobody uses
    referenced = {u['source'] for u in world.units}
    for path in sorted(glob.glob(str(ROOT / 'src/*/nonmatching/*'))):
        rel = Path(path).relative_to(ROOT).as_posix()
        if rel in referenced:
            continue
        text = Path(path).read_text()
        funcs = draft_functions(text, rel, starts, {})
        p = Piece('draft:' + rel, rel, text, [], funcs, draft=True)
        if not funcs:
            tokens = sorted({int(x, 16) for x in re.findall(r'func_([0-9A-Fa-f]{8})', text)} & starts)
            p.anchor = tokens[len(tokens) // 2] if tokens else None
        p.units = []
        pieces.append(p)
    return pieces


# --------------------------------------------------------------------------------------------------------- text parts

def safe_cut(text, cut):
    """Move a cut point out of any #if block that is open there (markers must not land in an inactive region)."""
    depth, outer, pos = 0, 0, 0
    for line in text[:cut].split('\n'):
        m = re.match(r'\s*#\s*(if|ifdef|ifndef|endif)\b', line)
        if m:
            if m.group(1) == 'endif':
                depth -= 1
            else:
                if depth == 0:
                    outer = pos
                depth += 1
        pos += len(line) + 1
    return outer if depth > 0 else cut


def split_source(text):
    """(includes, preamble lines, body) of a plain C draft: everything before the first function definition is preamble."""
    lines = text.split('\n')
    inc, pre, i = [], [], 0
    while i < len(lines):
        l = lines[i]
        if l.startswith('#include'):
            inc.append(l)
        elif l.strip() == '' or l.startswith(('extern', 'typedef', 'const', 'static const')):
            if l.strip():
                pre.append(l)
        else:
            break
        i += 1
    return inc, pre, '\n'.join(lines[i:]).strip('\n')


def plain_segments(piece):
    """(includes, preamble, [(text, set of compiled addresses)]) of a plain piece, cut at its 'Assembly between' notes."""
    text = TU_NOTE.sub('', piece.text)
    inc, pre, body = split_source(text)
    parts = GAP.split(body)                       # text, names, text, names, ...
    segs, srcs, lo = [], list(piece.srcs), None
    for k in range(0, len(parts), 2):
        seg = parts[k].strip('\n')
        if k + 1 < len(parts):
            m = re.search(r'func_([0-9A-Fa-f]{8})', parts[k + 1])
            limit = int(m.group(1), 16) if m else None
        else:
            limit = None
        mine = {a for a in srcs if limit is None or a < limit}
        srcs = [a for a in srcs if a not in mine]
        if seg:
            segs.append((seg, mine))
    if srcs and segs:
        segs[-1] = (segs[-1][0], segs[-1][1] | set(srcs))
    return inc, pre, segs


def definition_start(text):
    """Character offset of the first function definition at file scope (namespaces and extern "C" are transparent)."""
    blanked = include_asm.blank_comments(text)
    n, i = len(blanked), 0
    stack, stmt, line_start = [], None, True
    while i < n:
        c = blanked[i]
        if line_start and c == '#':
            while i < n and blanked[i] != '\n':
                if blanked[i] == '\\' and i + 1 < n and blanked[i + 1] == '\n':
                    i += 1
                i += 1
            continue
        if c == '\n':
            line_start = True
            i += 1
            continue
        if not c.isspace():
            line_start = False
        if c in '"\'':
            j = i + 1
            while j < n and blanked[j] != c and blanked[j] != '\n':
                j += 2 if blanked[j] == '\\' else 1
            i = j + 1
            continue
        top = 'B' not in stack
        if top and not c.isspace() and stmt is None:
            stmt = i
        if c == '{':
            if top:
                header = blanked[stmt:i] if stmt is not None else ''
                if re.match(r'\s*(namespace\b|extern\s*"[^"]*"\s*$)', header):
                    stack.append('T')
                    stmt = None
                elif '(' in header and not re.match(r'\s*(typedef|struct|class|union|enum|using)\b', header) \
                        and re.search(r'\)\s*(const\s*)?(throw\s*\([^)]*\)\s*)?$', header.strip() + ' '):
                    return stmt
                else:
                    stack.append('B')
            else:
                stack.append('B')
        elif c == '}':
            if stack:
                stack.pop()
            if 'B' not in stack:
                stmt = None
        elif c == ';' and top:
            stmt = None
        i += 1
    return None




# ------------------------------------------------------------------------------------------------------------ plan

class Part:
    """One output file: merged pieces (live), draft blocks, and the address range [lo, hi) of the file."""

    def __init__(self, pieces, kind):
        self.pieces, self.kind = pieces, kind       # kind: live | draft | frozen
        self.drafts = []
        self.lo = self.hi = None
        self.path = None
        self.nofs = False                           # compile without -ffunction-sections
        self.reason = None
        self.tus = []

    @property
    def srcs(self):
        return sorted({a for p in self.pieces for a in p.srcs})

    @property
    def suffix(self):
        return self.pieces[0].suffix if self.pieces else self.drafts[0].suffix

    @property
    def key(self):
        return self.pieces[0].key if self.pieces else None


def home_addresses(p):
    return p.srcs or p.funcs[:1] or ([p.anchor] if p.anchor else [])


def build_groups(world, pieces):
    """Union-find the TUs that a live piece spans; drafts only name the TU of their first function."""
    parent = {}

    def find(x):
        parent.setdefault(x, x)
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    homes = {}
    for p in pieces:
        if p.srcs:
            keys = sorted({world.tu_index(a) for a in p.srcs} - {None})
        else:
            keys = sorted({world.tu_index(a) for a in home_addresses(p)} - {None})
        if not keys:
            homes[p.id] = None
            continue
        if p.srcs:
            for k in keys[1:]:
                parent[find(k)] = find(keys[0])
        find(keys[0])
        homes[p.id] = keys[0]
    groups, lost = collections.defaultdict(list), []
    for p in pieces:
        if homes[p.id] is None:
            lost.append(p)
        else:
            groups[find(homes[p.id])].append(p)
    members = collections.defaultdict(list)
    for k in list(parent):
        members[find(k)].append(k)
    ranges = {r: (min(world.tu_starts[k] for k in ks), max(world.tu_ends[k] for k in ks), sorted(ks))
              for r, ks in members.items()}
    return groups, ranges, lost


def plan_group(world, pieces, lo, hi, notes):
    """Parts of one TU group: merge compatible plain pieces, tile the group range, attach drafts."""
    live = sorted([p for p in pieces if p.srcs and not p.frozen], key=lambda p: p.srcs[0])
    frozen = [p for p in pieces if p.frozen and p.srcs]
    drafts = [p for p in pieces if not p.srcs and not p.frozen]
    parts, cur = [], None
    for p in live:
        if cur is not None and p.plain and cur.pieces[-1].plain and not p.level and not cur.pieces[-1].level:
            if p.key != cur.pieces[-1].key:
                cur.reason = cur.reason or 'flags or language differ'
            elif not world.layout_ok(set(cur.srcs) | set(p.srcs)):
                cur.reason = 'constants of assembly functions interleave'
            else:
                cur.pieces.append(p)
                continue
        cur = Part([p], 'live')
        cur.nofs = p.level == 1 or (p.level >= 2 and not p.had_sections)
        parts.append(cur)
    movable = list(parts)
    for i, pt in enumerate(movable):
        pt.lo = lo if i == 0 else pt.srcs[0]
        nxt = movable[i + 1].srcs[0] if i + 1 < len(movable) else hi
        pt.hi = hi if i + 1 == len(movable) else max(world.ends[pt.srcs[-1]], nxt)
    for p in frozen:
        pt = Part([p], 'frozen')
        pt.lo, pt.hi = p.srcs[0], world.ends[p.srcs[-1]]
        parts.append(pt)
    extra = []
    for d in sorted(drafts, key=lambda d: home_addresses(d)[0]):
        home = home_addresses(d)[0]
        target = next((pt for pt in movable if pt.lo <= home < pt.hi and pt.suffix == d.suffix
                       and pt.pieces[0].compiler == DEFAULT_COMPILER), None)
        if target is not None:
            target.drafts.append(d)
            continue
        e = next((x for x in extra if x.suffix == d.suffix), None)
        if e is None:
            e = Part([], 'draft')
            if not movable and not extra:
                e.lo, e.hi = lo, hi
            else:
                members = d.funcs or [home]
                e.lo, e.hi = min(members), world.ends[max(members)]
            extra.append(e)
        e.drafts.append(d)
        e.lo = min(e.lo, home)
        e.hi = max(e.hi, world.ends[home]) if home in world.ends else e.hi
    return parts + extra


STATE = Path(__file__).with_name('migrate_include_asm_state.json')   # per-piece fallback levels found by the first run


def load_state():
    return json.loads(STATE.read_text()) if STATE.exists() else {}


def plan(world, state=None):
    state = state if state is not None else load_state()
    pieces = make_pieces(world)
    for p in pieces:
        p.level = state.get(p.id, 0)
        if p.level == 1 and p.srcs:
            idx = [world.starts.index(x) for x in p.srcs]
            if idx != list(range(idx[0], idx[0] + len(idx))):
                p.level = 2                    # without function sections the functions must be adjacent
    allsrc = {a for p in pieces for a in p.srcs}
    for p in pieces:                                   # notes-only drafts follow the siblings with the same name prefix
        if p.draft and not p.funcs and not p.anchor:
            prefix = Path(p.src).stem.rsplit('_', 1)[0]
            sib = next((q for q in pieces if q is not p and q.funcs and Path(q.src).stem.startswith(prefix)), None)
            p.anchor = sib.funcs[0] if sib else None
    stale, kept = [], []
    for p in pieces:
        if not p.srcs and not p.frozen:
            if p.funcs:
                rest = [a for a in p.funcs if a not in allsrc]
                if not rest:
                    stale.append(p)
                    continue
                p.funcs = rest
        kept.append(p)
    groups, ranges, lost = build_groups(world, kept)
    notes = []
    parts = []
    for root, ps in groups.items():
        lo, hi, tus = ranges[root]
        for pt in plan_group(world, ps, lo, hi, notes):
            pt.tus = tus
            parts.append(pt)
    parts.sort(key=lambda pt: (pt.lo, pt.path or '', pt.kind))
    assign_paths(world, parts)
    return parts, stale, lost


def assign_paths(world, parts):
    used = set()
    for pt in parts:                                   # hand-written files keep their names
        if pt.kind == 'frozen' or (pt.kind == 'live' and len(pt.pieces) == 1 and not pt.pieces[0].plain):
            pt.path = pt.pieces[0].src
            used.add(pt.path)
    for pt in parts:
        if pt.path:
            continue
        suffix = pt.suffix
        stem = layout.stem_for(pt.lo)
        path = 'src/%s/%s%s' % (layout.library_of(pt.lo), stem, suffix)
        n = 1
        while path in used:
            n += 1
            path = 'src/%s/%s_%d%s' % (layout.library_of(pt.lo), stem, n, suffix)
        used.add(path)
        pt.path = path


# --------------------------------------------------------------------------------------------------------- rendering

def draft_block(d, members):
    body = unwrap_draft(d.text)
    out = ['#ifdef NON_MATCHING', body, '#else' if members else None]
    out += [include_asm.marker_line('func_%08X' % a, ASM_DIR) for a in members]
    out.append('#endif')
    return '\n'.join(x for x in out if x is not None)


def render_part(world, part):
    """(text, include-asm count, draft-block count) of the TU file of a part."""
    F = world.functions_in(part.lo, part.hi)
    plain = bool(part.pieces) and part.pieces[0].plain
    segs, incs, pres = [], [], []
    for piece in part.pieces:
        if piece.plain:
            inc, pre, ss = plain_segments(piece)
            incs += [l for l in inc if l not in incs]
            pres += [l for l in pre if l not in pres]
            segs += ss
        else:
            segs.append((TU_NOTE.sub('', piece.text).strip('\n'), set(piece.srcs)))
    if plain and len(part.pieces) > 1:
        defined = set()
        for text, _ in segs:
            for m in re.finditer(r'^[A-Za-z_][^;{}]*?\b(\w+)\s*\([^;{]*\)\s*\{', text, re.M):
                defined.add(m.group(1))
        if defined:
            rx = re.compile(r'\b(%s)\s*\(' % '|'.join(map(re.escape, sorted(defined))))
            pres = [l for l in pres if not (l.startswith('extern') and rx.search(l))]
    seg_of = {a: i for i, (_, addrs) in enumerate(segs) for a in addrs}
    block_of, member_of = collections.defaultdict(list), set()
    for d in part.drafts:
        members = [a for a in d.funcs if part.lo <= a < part.hi and a in set(F)]
        anchor = members[0] if members else None
        if anchor is None:
            anchor = d.anchor if d.anchor and part.lo <= d.anchor < part.hi else None
        d.render_members = members
        if anchor is None:
            anchor = F[0]
        block_of[anchor].append(d)
        member_of.update(members)
    items, done = [], set()
    for a in F:
        for d in block_of.get(a, []):
            items.append(('draft', d))
        if a in seg_of:
            if seg_of[a] not in done:
                done.add(seg_of[a])
                items.append(('seg', seg_of[a]))
        elif a in member_of:
            continue
        else:
            items.append(('asm', a))
    lines = {'asm': lambda a: include_asm.marker_line('func_%08X' % a, ASM_DIR)}
    chunks, n_asm, n_draft = [], 0, 0
    run = []

    def flush():
        nonlocal run
        if run:
            chunks.append('\n'.join(run))
            run = []

    for kind, v in items:
        if kind == 'asm':
            run.append(lines['asm'](v))
            n_asm += 1
        elif kind == 'draft':
            flush()
            chunks.append(draft_block(v, v.render_members))
            n_draft += 1
            n_asm += len(v.render_members)
        else:
            flush()
            chunks.append(('SEG', v))
    flush()
    if plain:
        body = '\n\n'.join(segs[c[1]][0] if isinstance(c, tuple) else c for c in chunks)
        head = ['#include "include_asm.h"'] + incs
        text = '\n'.join(head) + '\n\n' + ('\n'.join(pres) + '\n\n' if pres else '') + body + '\n'
        return text, n_asm, n_draft
    # hand-written file: its own text stays as it is; markers before its first definition go in front of it
    seg_text = segs[0][0] if segs else ''
    before, after, seen = [], [], False
    for c in chunks:
        if isinstance(c, tuple):
            seen = True
        else:
            (after if seen else before).append(c)
    cut = definition_start(seg_text) if seg_text else None
    cut = len(seg_text) if cut is None else safe_cut(seg_text, cut)
    head_t, rest_t = seg_text[:cut].rstrip('\n'), seg_text[cut:].strip('\n')
    pieces = ['#include "include_asm.h"']
    if head_t:
        pieces.append(head_t)
    if before:
        pieces.append('\n\n'.join(before))
    if rest_t:
        pieces.append(rest_t)
    if after:
        pieces.append('\n\n'.join(after))
    if not segs:
        pieces = ['#include "include_asm.h"'] + before + after
    return '\n\n'.join(pieces) + '\n', n_asm, n_draft


# ------------------------------------------------------------------------------------------------------------- units

def entry_name(path, taken, lo):
    """Unit/object name of a file: its stem, plus the start of the range when several units share the file."""
    stem = Path(path).stem
    name = stem if stem not in taken else '%s_%06x' % (stem, lo)
    n = 1
    while name in taken:
        n += 1
        name = '%s_%06x_%d' % (stem, lo, n)
    taken.add(name)
    return name


def unit_entries(world, parts, path_map):
    """config/units.yaml entries (the format of the old layout) for the new files."""
    stems = collections.Counter(Path(pt.path).stem for pt in parts if pt.kind != 'frozen')
    frozen_stems = collections.Counter(Path(u['source']).stem for pt in parts if pt.kind == 'frozen' for u in pt.pieces[0].units)
    names = set()
    out = []
    for pt in parts:
        if pt.kind == 'frozen':
            for u in sorted(pt.pieces[0].units, key=lambda u: u['functions'][0]['addr']):
                e = dict(u)
                first = min(f['addr'] for f in u['functions'])
                e['name'] = entry_name(pt.path, names, first)
                out.append((e, pt))
            continue
        names_key = Path(pt.path).stem
        name = entry_name(pt.path, names, pt.lo)
        first = pt.pieces[0].unit if pt.pieces else (pt.drafts[0].unit or {})
        flags = list(pt.pieces[0].base_flags) if pt.pieces else list(DEFAULT_FLAGS)
        if pt.pieces and not pt.nofs:
            flags.append('-ffunction-sections')
        externs = {}
        funcs = {}
        for piece in pt.pieces + pt.drafts:
            for u in piece.units:
                externs.update(u.get('externs') or {})
                for f in u['functions']:
                    if f['addr'] in funcs and funcs[f['addr']]['status'] == 'source':
                        continue
                    funcs[f['addr']] = dict(f)
        for f in funcs.values():
            nm = f.get('nonmatching')
            if nm and nm.get('source') in path_map:
                f['nonmatching'] = dict(nm, source=path_map[nm['source']])
        in_range = {a: f for a, f in funcs.items() if pt.lo <= a < pt.hi or f.get('evidence')}
        e = {k: v for k, v in first.items() if k in ('provenance', 'tier', 'origin', 'owner', 'claim', 'tu', 'language',
                                                     'assembler_evidence', 'trim') or k in SPECIAL_KEYS}
        entry = dict(name=name, source=pt.path, library=Path(pt.path).parts[1],
                     provenance='auto' if pt.pieces and all(p.plain for p in pt.pieces) else e.get('provenance', 'manual'),
                     tier='exact' if pt.srcs else 'draft', origin=e.get('origin', 'auto'))
        for k in ('owner', 'claim', 'tu', 'language'):
            if k in e:
                entry[k] = e[k]
        if pt.pieces and pt.pieces[0].compiler != DEFAULT_COMPILER:
            entry['compiler'] = pt.pieces[0].compiler
        entry['flags'] = flags
        if externs:
            entry['externs'] = externs
        for k in SPECIAL_KEYS:
            if k in e:
                entry[k] = e[k]
        if 'assembler_evidence' in e:
            entry['assembler_evidence'] = e['assembler_evidence']
        entry['functions'] = sorted(in_range.values(), key=lambda f: f['addr'])
        entry['range'] = ['0x%06x' % pt.lo, '0x%06x' % pt.hi]
        if pt.nofs:
            entry['sections'] = False
        if pt.reason:
            entry['note'] = pt.reason
        out.append((entry, pt))
    return out


# -------------------------------------------------------------------------------------------------------------- write

import copy


def save_units_yaml(units):
    out = []
    for u in units:
        d = {k: v for k, v in u.items() if k not in ('compiler',) or v != 'ee-gcc2.95.3-136'}
        choices = [f.split('=', 1)[1] for f in u.get('flags', []) if f.startswith('--assembler=')]
        sn_driver_gnu = u.get('compiler', 'ee-gcc2.95.3-136').startswith('ee-gcc2.95') and '-snas' not in u.get('flags', [])
        if choices or sn_driver_gnu:
            d['assembler_evidence'] = dict(strength='weak', basis='individually verified output',
                                           historical_provenance='unresolved')
        else:
            d.pop('assembler_evidence', None)
        d['functions'] = [{k: (hex(v) if k == 'addr' else v) for k, v in f.items()} for f in u['functions']]
        if not d.get('externs'):
            d.pop('externs', None)
        else:
            d['externs'] = {k: hex(v) for k, v in sorted(d['externs'].items())}
        out.append(d)
    (ROOT / 'config/units.yaml').write_text(
        '# Provisional translation units that replace assembly functions with source; see docs/units.md.\n'
        '# status: source = provided by the unit; asm = stays assembly, with a one-word reason.\n' +
        yaml.safe_dump({'variant': SLUG, 'units': out}, sort_keys=False, width=140))




def write(world, parts, stale, report):
    """Write the TU files, remove the superseded sources and rewrite config/units.yaml."""
    path_map = {}
    for pt in parts:
        for piece in pt.pieces + pt.drafts:
            path_map[piece.src] = pt.path
    texts, counts = {}, collections.Counter()
    for pt in parts:
        if pt.kind == 'frozen':
            continue
        text, n_asm, n_draft = render_part(world, pt)
        texts[pt.path] = text
        counts['files'] += 1
        counts['include_asm'] += n_asm
        counts['non_matching'] += n_draft
        counts['merged_pieces'] += max(len(pt.pieces) - 1, 0)
    old = {p.src for pt in parts for p in pt.pieces + pt.drafts} | {p.src for p in stale}
    keep = set(texts) | {pt.path for pt in parts if pt.kind == 'frozen'}
    entries = unit_entries(world, parts, path_map)
    for path, text in texts.items():
        (ROOT / path).parent.mkdir(parents=True, exist_ok=True)
        (ROOT / path).write_text(text)
    for path in sorted(old - keep):
        (ROOT / path).unlink(missing_ok=True)
    for d in glob.glob(str(ROOT / 'src/*/nonmatching')):
        try:
            Path(d).rmdir()
        except OSError:
            print('not empty:', d)
    units = [dict(e) for e, _ in entries]
    for u in units:
        for f in u['functions']:
            f['addr'] = f['addr'] if isinstance(f['addr'], int) else num(f['addr'])
        if u.get('externs'):
            u['externs'] = {k: num(v) for k, v in u['externs'].items()}
    save_units_yaml(units)
    report.update(counts)
    return entries


def validate(world, parts):
    """Offline check of the rendered files: markers are exactly the functions of the range that the part does not compile."""
    bad = []
    for pt in parts:
        if pt.kind == 'frozen':
            continue
        text, _, _ = render_part(world, pt)
        F = set(world.functions_in(pt.lo, pt.hi))
        want = F - set(pt.srcs)
        got = set(include_asm.marker_addresses(text, ()))
        if got != want:
            bad.append((pt.path, 'normal', sorted(got ^ want)[:4]))
        members = {a for d in pt.drafts for a in d.render_members} if pt.drafts else set()
        got_nm = set(include_asm.marker_addresses(text, {'NON_MATCHING'}))
        if got_nm != want - members:
            bad.append((pt.path, 'non-matching', sorted(got_nm ^ (want - members))[:4]))
    return bad


def summarize(parts, stale):
    live = [p for p in parts if p.kind == 'live']
    print('parts: %d live, %d draft-only, %d frozen; %d stale drafts dropped' % (
        len(live), sum(p.kind == 'draft' for p in parts), sum(p.kind == 'frozen' for p in parts), len(stale)))
    reasons = collections.Counter(p.reason for p in live if p.reason)
    print('split reasons:', dict(reasons))


def settle(expected):
    """Compile, link and compare with the old tools; returns {unit name: reason} of units that lost source functions."""
    import settle_units as T
    import units_verify
    from units import load_units
    print(T.run('tools/build/split_objects.py', SLUG).stdout.strip().split('\n')[-1])
    print(T.run('tools/build/make_ld.py', SLUG).stdout.strip())
    results = BUILD / 'results.json'
    results.unlink(missing_ok=True)
    compiled = T.run('tools/build/build_objects.py', SLUG, '--compile-only', check=False)
    if compiled.returncode and not results.exists():
        raise SystemExit(compiled.stdout + compiled.stderr)
    print(compiled.stdout.strip().split('\n')[-1])
    print(T.run('tools/build/units_verify.py', 'prepare').stdout.strip())
    for rnd in range(12):
        rc, out = T.ninja()
        if T.infrastructure_failure(out):
            raise SystemExit(out)
        if 'build:' in out and 'rc=0' not in out:
            print('link failed:', T.run('tools/build/units_verify.py', 'link').stdout.strip().split('\n')[0])
            continue
        if rc == 0:
            print(out.strip().split('\n')[-1])
            break
        print(T.run('tools/build/units_verify.py', 'compare', '--fix').stdout.strip().split('\n')[-1])
    failed = {}
    for u in load_units(variant=SLUG):
        want = expected.get(u['name'])
        if want is None:
            continue
        have = {f['addr'] for f in u['functions'] if f.get('status') == 'source'}
        if have != want:
            reasons = {f.get('reason') for f in u['functions'] if f.get('status') == 'asm' and f['addr'] in want}
            failed[u['name']] = sorted(str(r) for r in reasons)
    return failed


def restore():
    subprocess.run(['git', 'checkout', '--', 'src', 'config/units.yaml'], cwd=ROOT, check=True)
    subprocess.run(['git', 'clean', '-fdq', 'src'], cwd=ROOT, check=True)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('command', choices=['plan', 'write', 'run'])
    ap.add_argument('--rounds', type=int, default=6)
    a = ap.parse_args()
    if a.command == 'run':
        state = load_state()
        for rnd in range(a.rounds):
            restore()
            world = World()
            parts, stale, lost = plan(world, state)
            summarize(parts, stale)
            bad = validate(world, parts)
            if bad:
                raise SystemExit('marker check failed: %s' % bad[:3])
            report = {}
            entries = write(world, parts, stale, report)
            print(dict(report))
            expected = {e['name']: {f['addr'] for f in e['functions'] if f['status'] == 'source'} for e, _ in entries}
            by_name = {e['name']: pt for e, pt in entries}
            failed = settle(expected)
            print('round %d: %d units did not place identically' % (rnd, len(failed)))
            for name, why in sorted(failed.items())[:40]:
                print('  ', name, why)
            if not failed:
                return 0
            for name in failed:
                pt = by_name[name]
                for piece in pt.pieces:
                    cur = state.get(piece.id, 0)
                    idx = [world.starts.index(x) for x in piece.srcs]
                    contiguous = idx == list(range(idx[0], idx[0] + len(idx)))
                    state[piece.id] = 1 if (cur == 0 and len(pt.pieces) == 1 and contiguous) else max(2, cur + 1)
            STATE.write_text(json.dumps(state, indent=1))
        return 1
    world = World()
    parts, stale, lost = plan(world)
    summarize(parts, stale)
    bad = validate(world, parts)
    print('marker check: %d files differ' % len(bad))
    for b in bad[:10]:
        print('  ', b)
    if a.command == 'plan':
        return 0
    if bad:
        raise SystemExit('refusing to write: the marker check failed')
    report = {}
    write(world, parts, stale, report)
    print(dict(report))
    return 0


if __name__ == '__main__':
    sys.exit(main())
