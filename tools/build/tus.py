#!/usr/bin/env python3
"""Translation-unit (TU) boundary evidence and the TU map of the boot executable.

  tus.py evidence    collect every signal and print what each one says (build/<GAME_ID>/tus_evidence.json)
  tus.py map         combine the signals into build/SLUS_213.76/tus.yaml (ignored; `ninja` writes it) (hand corrections: config/tus_overrides.yaml)
  tus.py validate    agreement between the signals, with the exception-frame and constructor-stub signals held out
  tus.py all         evidence + map + validate

Everything is computed from the retail image (SLUS_213.76), the split in build/<GAME_ID>/ (run `ninja` first) and the
function inventory of the automatic pipeline (build/auto/inventory.json). Nothing here runs an SDK binary.

Signals (docs/tus.md has the findings):
  eh        Exception/unwind frames in .data. Each object file compiled with exceptions has one CIE and one FDE per function
            (the CIE of an object with a .gcc_except_table carries the address of its table). The FDEs of a group are
            contiguous in .text, so a group is exactly one object file, or in the link-once area one inline-function section.
  ctor      Static initialisation. A TU with global objects ends with __static_initialization_and_destruction_0, the
            __tcf_N destructor thunks, _GLOBAL__I_* and sometimes _GLOBAL__D_*; the I functions are listed in the
            __CTOR_LIST__ array (count word, then pointers) that the start-up code walks.
  libs      Library identity from strings, style (callee-saved register saves with sd or sq) and exception use.
  joins     Data that only one object file can own: constants (.rodata, .lit4, .gcc_except_table) used by several functions,
            and statics (.bss, .sbss, .sdata, .data) whose linker order is violated by functions in between (inversions).
  calls     Call edges and data items shared by neighbouring functions.
  orphan    Unreferenced `<instruction>; nop` pieces between functions (boundaries.py).
  shift     Functions whose code differs between USA and the PAL/Korean/Japanese builds only in immediates.
  xbuild    Adjacency of functions in the USA beta and demo builds.
"""
import argparse, bisect, collections, json, re, struct, sys
from itertools import accumulate
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / d) for d in ('', 'build', 'pipeline', 'maint')]
from elfinfo import Elf
import boundaries

ROOT = Path(__file__).resolve().parents[2]
SLUG = 'SLUS_213.76'
BETA, DEMO = 'SLUS_000.00', 'SLUS_291.80'   # earlier USA builds, kept only in the disc survey (orig/survey/)
CIE_SIMPLE = bytes.fromhex('100000000000000001000178400c1d0009401f00')
DATA_SECTIONS = ('.rodata', '.lit4', '.gcc_except_table', '.data', '.sdata', '.sbss', '.bss')
HARD_SECTIONS = ('.rodata', '.lit4', '.gcc_except_table')
SOFT_SECTIONS = ('.data', '.sdata', '.sbss', '.bss')

# --- tuning, chosen on the held-out evaluation (`tus.py validate`) ---------------------------------------------------
WINDOW = 0x4000      # a data item used by functions further apart than this (bytes of .text) is a shared global, not a join
MAXREFS = 12         # ... or used by more functions than this
INV_LOOKBACK = 12    # inversion joins compare an item with this many items before it in data order
INV_SPAN = 0x3000
MAXTU = 60           # a stretch of this many functions without a cut is split again with shorter relation edges
REL_DIST = 32        # relation edges (calls, shared items) connect functions at most this many functions apart
CALLERS = 999        # a callee with more callers than this is a utility (tested: 2..12 are no better than all)
ITEMREFS = 8         # a data item used by more functions than this is shared between object files


# ---------------------------------------------------------------------------------------------------------- loading
class Image:
    """The retail image and everything derived from it that the signals share."""

    def __init__(self, slug=SLUG):
        self.slug = slug
        build = ROOT / 'build' / slug
        boot = json.loads((ROOT / 'config/versions.json').read_text())[slug]['boot']
        self.elf = Elf((ROOT / 'orig' / slug / boot).read_bytes())
        layout = json.loads((ROOT / 'build' / boot / 'layout.json').read_text())
        self.sections = [(s['name'], s['addr'], s['orig_size']) for s in layout['sections']
                         if s['source'] == 'linked' and s['name'] not in ('.vutext', '.vubss')]
        text = self.elf.section('.text')
        self.tbase, self.tdata = text['addr'], self.elf.content(text)
        self.words = struct.unpack('<%dI' % (len(self.tdata) // 4), self.tdata)
        placement = json.loads((build / 'placement.json').read_text())['functions']
        self.F = [f['addr'] for f in placement]
        self.END = [f['end'] for f in placement]
        self.N = len(self.F)
        self.fidx = {a: i for i, a in enumerate(self.F)}
        sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
        import autodecomp
        self.inv = autodecomp.load_inventory()
        assert [f['addr'] for f in self.inv] == self.F
        self.load_symbols()
        self.find_orphans()
        self.load_refs()
        self.load_eh()
        self.load_ctors()
        self.load_style()
        self.load_strings()
        self.load_units()

    # basic helpers
    def W(self, a):
        return self.words[(a - self.tbase) >> 2]

    def sec(self, a):
        for n, b, s in self.sections:
            if b <= a < b + s:
                return n

    def fi(self, a):
        return bisect.bisect_right(self.F, a) - 1

    def hexf(self, i):
        return '0x%06x' % self.F[i]

    # --- symbols (readable function names: the aliases of config/<GAME_ID>/symbols.txt) ---
    def load_symbols(self):
        import splits
        self.alias = splits.load_symbols(self.slug).function_aliases()

    # --- orphan pieces ---
    def find_orphans(self):
        refs = boundaries.reference_targets(self.elf, self.tbase, self.words)
        self.orphan = [False] * self.N
        self.orphan_pieces = 0
        for i in range(self.N):
            sz = self.END[i] - self.F[i]
            if sz % 8 == 0 and sz >= 8 and self.F[i] not in refs:
                if all(self.W(self.F[i] + k) != 0 and self.W(self.F[i] + k + 4) == 0 and not boundaries.control(self.W(self.F[i] + k))
                       for k in range(0, sz, 8)):
                    self.orphan[i] = True
                    self.orphan_pieces += sz // 8
        self.real = [i for i in range(self.N) if not self.orphan[i]]       # functions in text order, orphan runs left out

    # --- data references of the code ---
    def load_refs(self):
        self.irefs = {s: collections.defaultdict(set) for s in DATA_SECTIONS}      # section -> data address -> function indices
        self.calls = [set() for _ in range(self.N)]
        self.gprel = [False] * self.N
        for i, f in enumerate(self.inv):
            for r in f['rel'].values():
                if isinstance(r[1], str):
                    continue
                if r[0] == 'jal':
                    j = self.fidx.get(r[1])
                    if j is not None:
                        self.calls[i].add(j)
                    continue
                if r[0] == 'gprel':
                    self.gprel[i] = True
                s = self.sec(r[1] + r[2])
                if s in self.irefs:
                    self.irefs[s][r[1] + r[2]].add(i)
        self.callers = [set() for _ in range(self.N)]
        for i, c in enumerate(self.calls):
            for j in c:
                self.callers[j].add(i)

    # --- exception/unwind frames ---
    def load_eh(self):
        d = self.elf.section('.data')
        dc, base = self.elf.content(d), d['addr']
        et = self.elf.section('.gcc_except_table')
        cands = []
        for o in range(0, len(dc) - 16, 4):
            L, idv = struct.unpack_from('<II', dc, o)
            if idv == 0 and 8 <= L <= 0x40 and dc[o + 8] == 1 and L % 4 == 0:
                e = dc.find(b'\0', o + 9)
                aug = dc[o + 9:e]
                if len(aug) <= 3 and all(32 <= x < 127 for x in aug):
                    cands.append((o, L, aug, e))
        groups = []
        for o, L, aug, e in cands:
            g = dict(cie=base + o, aug=aug.decode(), table=struct.unpack_from('<I', dc, e + 1)[0] if aug == b'eh' else None, fdes=[])
            p = o + 4 + L
            while p < len(dc) - 8:
                l = struct.unpack_from('<I', dc, p)[0]
                if l == 0:
                    g['end'] = base + p + 4
                    break
                if struct.unpack_from('<I', dc, p + 4)[0] == 0 or l > 0x100:
                    break
                pc, rng = struct.unpack_from('<II', dc, p + 8)
                if not self.tbase <= pc < self.tbase + len(self.tdata):
                    break
                g['fdes'].append((pc, rng))
                p += 4 + l
            if g['fdes'] and 'end' in g:
                g['lo'], g['hi'] = g['fdes'][0][0], g['fdes'][-1][0] + g['fdes'][-1][1]
                groups.append(g)
        groups.sort(key=lambda g: g['cie'])
        # link-once sections: their groups come last in .data and all name the first table
        first = next(k for k in range(len(groups) - 2) if k > 2 and all(groups[k + j]['table'] == et['addr'] for j in range(3)))
        self.eh = groups
        self.eh_linkonce_first = first
        self.linkonce_start = min(g['lo'] for g in groups[first:])
        self.eh_of = {}                      # function index -> group index
        for gi, g in enumerate(groups):
            for a, r in g['fdes']:
                if a in self.fidx:
                    self.eh_of[self.fidx[a]] = gi

    # --- static constructor machinery ---
    def load_ctors(self):
        """_GLOBAL__I/_D stubs, the sinit function they call, and the __CTOR_LIST__ array."""
        self.stub = {}
        for i in range(self.N):
            a, n = self.F[i], (self.END[i] - self.F[i]) // 4
            if not 8 <= n <= 9 or self.W(a) != 0x27bdfff0:
                continue
            ws = [self.W(a + 4 * k) for k in range(n)]
            if 0x3405ffff not in ws:
                continue
            kind = 'I' if 0x24040001 in ws else 'D' if 0x0000202d in ws else None
            jal = [w for w in ws if w >> 26 == 3]
            if kind and len(jal) == 1 and ((jal[0] & 0x3ffffff) << 2) in self.fidx:
                self.stub[i] = (kind, self.fidx[(jal[0] & 0x3ffffff) << 2])
        d = self.elf.section('.data')
        dc, base = self.elf.content(d), d['addr']
        lo, hi = self.tbase, self.tbase + len(self.tdata)
        # the list is [count][count pointers into .text][0]; take the longest one
        self.ctor_list, self.ctor_table = [], None
        for o in range(0, len(dc) - 12, 4):
            n = struct.unpack_from('<I', dc, o)[0]
            if 20 <= n <= 1000 and o + 8 + 4 * n <= len(dc):
                ptrs = struct.unpack_from('<%dI' % n, dc, o + 4)
                if all(lo <= p < hi for p in ptrs) and struct.unpack_from('<I', dc, o + 4 + 4 * n)[0] == 0 and n > len(self.ctor_list):
                    self.ctor_list, self.ctor_table = list(ptrs), base + o
        ctor_set = {self.fi(a) for a in self.ctor_list}
        self.ctor_i = ctor_set
        # end of a TU: the I function, or the D function that follows it and calls the same sinit
        self.ctor_end = {}
        for i in ctor_set:
            j = self.stub.get(i, (None, None))[1]
            end = i
            if j is not None and self.stub.get(i + 1) == ('D', j):
                end = i + 1
            self.ctor_end[end] = i

    # --- code-generation style ---
    def load_style(self):
        """How callee-saved registers are saved: `sd` (Sony compiler) or `sq` (SN 1.36); `ra` = only $ra via sd."""
        self.style = []
        for i in range(self.N):
            a, n = self.F[i], (self.END[i] - self.F[i]) // 4
            sd = sq = sw = ra = 0
            for k in range(min(n, 40)):
                w = self.W(a + 4 * k)
                op, rs, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
                if rs != 29:
                    continue
                saved = 16 <= rt < 24 or rt == 30
                if op == 0x3f:
                    if saved:
                        sd += 1
                    elif rt == 31:
                        ra += 1
                elif op == 0x1f and (saved or rt == 31):
                    sq += 1
                elif op == 0x2b and saved:
                    sw += 1
            self.style.append('sd' if sd and not sq else 'sq' if sq and not sd else 'mix' if sq and sd else 'sw' if sw else 'ra' if ra else '-')

    # --- strings used by the code ---
    def load_strings(self):
        self.strings = collections.defaultdict(list)      # function index -> [(address, string)]
        for sname in ('.rodata', '.data'):
            s = self.elf.section(sname)
            c, b = self.elf.content(s), s['addr']
            for a, fs in self.irefs[sname].items():
                o = a - b
                e = c.find(b'\0', o)
                if e - o >= 4 and all(32 <= x < 127 or x in (9, 10, 13) for x in c[o:e]):
                    t = c[o:e].decode()
                    for i in fs:
                        self.strings[i].append((a, t))

    # --- source units (what is already matched, with flags) ---
    def load_units(self):
        from units import load_units
        self.src = {}                                   # function index -> unit dict
        for u in load_units(variant=self.slug):
            for f in u['functions']:
                if f.get('status') == 'source' and f['addr'] in self.fidx:
                    self.src[self.fidx[f['addr']]] = u


# ---------------------------------------------------------------------------------------------------------- libraries
# (name, kind, regex on the strings a function uses, text range hint or None). Ranges are the hull of the largest
# cluster of functions that use a matching string; config/tus_overrides.yaml can replace them.
LIB_RULES = [
    ('vibuf', 'game', r'vibuf\.c|DMA ADD not active|ErrMessage : %s'),
    ('apt', 'middleware', r'^Apt|__Packages|AptTrace|registerClass|SuperConstructor|ParentScope|__INTERFACES|_level%d|instance%ld'),
    ('libipu_libmpeg', 'sony', r'sceMpeg|libipu|MPEG ERROR|macroblock|slice_start_code|motion_type|chroma_format|quantizer_matrix|Unknown buff type|internal alignment error'),
    ('libdbc', 'sony', r'libdbc|sceDbc'),
    ('libdma_libpad2', 'sony', r'libdma|libpad2|ROMVER'),
    ('libm', 'sony', r'^(atan2|acosf|asinf|fmodf|atan2f)$'),
    ('libcdvd', 'sony', r'SceCd|Libcdvd|sceCdC|DiskReady'),
    ('rw_core', 'middleware', r'Core built|Invalid combination type|Invalid projection type|Only rendering sub system'),
    ('kynapse', 'middleware', r'Kynogon|Kaim|kyastar|CAccessWays|CAstarData|CPathFinder|CFleeAgent|CHideAgent|CFollowerAgent|CShooterAgent|CActionShoot|CActionSpeed|CEntityEyePosition'),
    ('rw_audio', 'middleware', r'RwaRPC|RWA'),
    ('libmc2', 'sony', r'libmc2|sceMc2|Memory Card Format|MC2SOCKET|C-SJIS|C-EUCJP'),
    ('libc_stdio', 'runtime', r'^0123456789abcdefghijklmnopqrstuvwxyz|ungetc error|^\(null\)$'),
    ('libkernl', 'sony', r'libkernl|SceKernel|SceSifrpc|SceStdio|TLB spad|TTY:|rom0:UDNL|too long parameter'),
    ('libstdcxx_typeinfo', 'runtime', r'^\d+(exception|bad_exception|bad_cast|bad_typeid|__class_type_info|__si_type_info|__user_type_info|__array_type_info|__ptmd_type_info|__ptmf_type_info|__func_type_info)'),
    ('libgs', 'sony', r'sceGs'),
]


def detect_libs(img):
    """Library hulls from strings: {name: dict(kind, lo, hi, hits)}. The hull is that of the largest cluster of functions
    (clusters are separated by more than 0x10000 bytes of .text)."""
    out = {}
    for name, kind, rx in LIB_RULES:
        pat = re.compile(rx)
        hit = sorted(i for i, ss in img.strings.items() if any(pat.search(t) for _, t in ss) and img.F[i] < img.linkonce_start)
        if not hit:
            continue
        clusters, cur = [], [hit[0]]
        for i in hit[1:]:
            if img.F[i] - img.F[cur[-1]] > 0x10000:
                clusters.append(cur)
                cur = []
            cur.append(i)
        clusters.append(cur)
        c = max(clusters, key=len)
        out[name] = dict(kind=kind, lo=c[0], hi=c[-1], hits=len(c), stray=len(hit) - len(c))
    return out


# ---------------------------------------------------------------------------------------------------------- relations
class Relations:
    """Which gaps between neighbouring functions are crossed by evidence that the two sides belong to one object file.

    Positions are indices into img.real (functions in text order, orphan runs left out); gap p lies between real[p-1]
    and real[p]. `hard` counts joins from constants (an object file's own .rodata/.lit4/.gcc_except_table), `soft` joins
    from statics and linker-order inversions, `call` call edges and `item` shared data items between near functions."""

    def __init__(self, img, dist=REL_DIST, window=WINDOW, maxrefs=MAXREFS, lookback=INV_LOOKBACK, span=INV_SPAN, callers=CALLERS, itemrefs=ITEMREFS):
        self.img, n = img, len(img.real)
        self.pos = {f: p for p, f in enumerate(img.real)}
        self.dist = dist
        self.arr = {k: [0] * (n + 2) for k in ('hard', 'soft', 'call', 'item')}
        self.edges = collections.defaultdict(list)           # kind -> [(p, q)]
        F = img.F
        for sname in DATA_SECTIONS:
            items = []
            for a, fs in sorted(img.irefs[sname].items()):
                ps = sorted({self.pos[i] for i in fs if i in self.pos})
                if ps:
                    items.append((a, ps, F[img.real[ps[0]]], F[img.real[ps[-1]]]))
            kind = 'hard' if sname in HARD_SECTIONS else 'soft'
            local = [(a, ps) for a, ps, flo, fhi in items if len(ps) <= maxrefs and fhi - flo <= window]
            for a, ps in local:
                if len(ps) > 1:
                    self.add(kind, ps[0], ps[-1])
            for j in range(len(local)):
                lo_j = local[j][1][0]
                for k in range(max(0, j - lookback), j):
                    hi_k = local[k][1][-1]
                    if hi_k > lo_j and F[img.real[hi_k]] - F[img.real[lo_j]] <= span:
                        self.add('soft', lo_j, hi_k)
        for i in img.real:
            for j in img.calls[i]:
                if j in self.pos and len(img.callers[j]) <= callers:
                    self.add('call', self.pos[i], self.pos[j])
        # items shared by few functions (any section) that sit close together
        for sname in DATA_SECTIONS:
            for a, fs in img.irefs[sname].items():
                ps = sorted({self.pos[i] for i in fs if i in self.pos})
                if 2 <= len(ps) <= itemrefs:
                    self.add('item', ps[0], ps[-1])
        self.cover = {k: list(accumulate(v)) for k, v in self.arr.items()}

    def add(self, kind, a, b):
        if a > b:
            a, b = b, a
        if a == b or (kind in ('call', 'item') and b - a > self.dist):
            return
        self.arr[kind][a + 1] += 1
        self.arr[kind][b + 1] -= 1
        self.edges[kind].append((a, b))

    def at(self, p, kinds=('hard', 'soft', 'call', 'item')):
        return sum(self.cover[k][p] for k in kinds)

    def without_crossing(self, cuts):
        """A copy whose edges that cross a known cut (gap positions in `cuts`) are dropped: they cannot be real."""
        n = len(self.img.real)
        cum = list(accumulate(1 if p in cuts else 0 for p in range(n + 2)))
        out = object.__new__(Relations)
        out.img, out.pos, out.dist = self.img, self.pos, self.dist
        out.arr = {k: [0] * (n + 2) for k in self.arr}
        out.edges = collections.defaultdict(list)
        for kind, es in self.edges.items():
            for a, b in es:
                if cum[b] - cum[a] == 0:               # no cut in gaps a+1..b
                    out.arr[kind][a + 1] += 1
                    out.arr[kind][b + 1] -= 1
                    out.edges[kind].append((a, b))
        out.cover = {k: list(accumulate(v)) for k, v in out.arr.items()}
        return out


# ---------------------------------------------------------------------------------------------------------- cross-build signals
def build_signals(img):
    """Adjacency of USA-retail functions in the other builds, from 12-word shingles of immediate-masked code.
    Returns {slug: {gap word index: 'cont'|'break'}} for the beta and demo, and {function index: 'same'|'shifted'|'other'}
    for the PAL/Korean/Japanese builds (shifted = identical apart from immediates such as struct offsets)."""
    from inputs import mask_text
    K = 12
    cache = ROOT / 'build' / img.slug / 'tus_xbuild.json'
    if cache.exists():
        return json.loads(cache.read_text())
    rs, rl = mask_text(list(img.words))
    out = {'adjacency': {}, 'shift': {}}
    for slug in (BETA, DEMO, 'SLES_540.30', 'SLES_538.86', 'SLKA_253.72', 'SLPM_663.54'):
        path = ROOT / 'orig' / slug / slug
        if not path.exists():       # beta and demo executables come from the disc survey (tools/maint/discs.py)
            path = ROOT / 'orig/survey' / slug / 'files' / slug
        if not path.exists():
            continue
        e = Elf(path.read_bytes())
        t = e.section('.text')
        ow = struct.unpack('<%dI' % (t['size'] // 4), e.content(t))
        os_, ol = mask_text(list(ow))
        hb, dup = {}, set()
        for j in range(len(ol) - K + 1):
            h = hash(tuple(ol[j:j + K]))
            if h in hb:
                dup.add(h)
            else:
                hb[h] = j
        ha = collections.Counter(hash(tuple(rl[i:i + K])) for i in range(len(rl) - K + 1))
        m = {}
        for i in range(len(rl) - K + 1):
            h = hash(tuple(rl[i:i + K]))
            if ha[h] == 1 and h in hb and h not in dup:
                m[i] = hb[h]
        if slug in (BETA, DEMO):
            adj = {}
            for i in img.real[1:]:
                w = (img.F[i] - img.tbase) >> 2
                left = next(((m[j], j) for j in range(w - K, max(w - K - 48, -1), -1) if j in m), None)
                right = next(((m[j], j) for j in range(w, w + 48) if j in m), None)
                adj[str(w)] = 'unk' if not left or not right else 'cont' if left[0] - left[1] == right[0] - right[1] else 'break'
            out['adjacency'][slug] = adj
        else:
            sh = {}
            for i in range(img.N):
                a, b = (img.F[i] - img.tbase) >> 2, (img.END[i] - img.tbase) >> 2
                diag = next((m[j] - j for j in range(a, max(a + 1, b - K + 1)) if j in m), None)
                if diag is None or a + diag < 0 or b + diag > len(ow):
                    sh[str(i)] = 'other'
                    continue
                same = all(ow[a + diag + k] == img.words[a + k] or os_[a + diag + k] == rs[a + k] for k in range(b - a))
                loose = all(ol[a + diag + k] == rl[a + k] for k in range(b - a))
                sh[str(i)] = 'same' if same else 'shifted' if loose else 'other'
            out['shift'][slug] = sh
    cache.write_text(json.dumps(out))
    return out


# ---------------------------------------------------------------------------------------------------------- segmentation
def load_overrides():
    p = ROOT / 'config/tus_overrides.yaml'
    if not p.exists():
        return {}
    import yaml
    d = yaml.safe_load(p.read_text()) or {}
    num = lambda v: int(v, 0) if isinstance(v, str) else int(v)
    return dict(cuts=[num(v) for v in d.get('cuts') or []], joins=[(num(a), num(b)) for a, b in d.get('joins') or []],
                names={num(k): v for k, v in (d.get('names') or {}).items()},
                libraries={k: (num(v[0]), num(v[1])) for k, v in (d.get('libraries') or {}).items()},
                flags={num(k): v for k, v in (d.get('flags') or {}).items()})


def region_runs(img, min_len=12):
    """Counterpart-map regions (discovery leads) smoothed to runs of at least `min_len` functions: [(first pos, last pos, region)]."""
    from progress import regions
    reg, _ = regions(img.F)
    labels = [reg[i] for i in img.real]
    runs, s = [], 0
    for p in range(1, len(labels) + 1):
        if p == len(labels) or labels[p] != labels[s]:
            runs.append([s, p - 1, labels[s]])
            s = p
    changed = True
    while changed and len(runs) > 1:
        changed = False
        for k, r in enumerate(runs):
            if r[1] - r[0] + 1 < min_len:
                if k > 0:
                    runs[k - 1][1] = r[1]
                else:
                    runs[1][0] = r[0]
                del runs[k]
                changed = True
                break
        k = 0
        while k + 1 < len(runs):
            if runs[k][2] == runs[k + 1][2]:
                runs[k][1] = runs[k + 1][1]
                del runs[k + 1]
            else:
                k += 1
    return runs


class Segmentation:
    """Cut positions with the evidence behind each, and the segments they make."""

    def __init__(self, img, rel, exact=True, intervals=True, regions=True, overrides=None, libs=None):
        self.img, self.rel = img, rel
        R, n = img.real, len(img.real)
        self.n = n
        self.cuts = collections.defaultdict(set)         # gap position -> evidence kinds
        pos = rel.pos
        linkpos = next(p for p in range(n) if img.F[R[p]] >= img.linkonce_start)
        self.linkpos = linkpos
        ov = overrides or {}
        if exact:
            for p in range(1, linkpos):
                a, b = R[p - 1], R[p]
                ga, gb = img.eh_of.get(a), img.eh_of.get(b)
                if (ga is not None or gb is not None) and ga != gb:
                    self.cuts[p].add('eh')
                    if (ga is None) != (gb is None):
                        self.cuts[p].add('ehzone')               # code with unwind frames next to code without: another library
                if a in img.ctor_end:
                    self.cuts[p].add('ctor')
            self.cuts[linkpos].add('linkonce')
        for a in ov.get('cuts', []):
            self.cuts[bisect.bisect_left([img.F[i] for i in R], a)].add('override')
        self.joined = set()                                # gaps that cannot be cuts: inside an unwind group or a constructor sequence
        if exact:
            for p in range(1, linkpos):
                a, b = R[p - 1], R[p]
                if img.eh_of.get(a) is not None and img.eh_of.get(a) == img.eh_of.get(b):
                    self.joined.add(p)
            for end, i in img.ctor_end.items():
                j = img.stub.get(i, (None, None))[1]
                if j is not None and j in pos and end in pos:
                    self.joined.update(range(pos[j] + 1, pos[end] + 1))
        self.forced_joins = []
        for lo, hi in ov.get('joins', []):
            plo, phi = bisect.bisect_left([img.F[i] for i in R], lo), bisect.bisect_left([img.F[i] for i in R], hi)
            self.forced_joins.append((plo, phi))
        self.interval = []                                 # (kind, first gap, last gap, chosen gap)
        if intervals:
            self.add_intervals(libs or {}, regions)
        self.final_rel = rel.without_crossing(set(self.cuts))

    def pick(self, kind, glo, ghi, rel):
        """The most likely cut gap within gaps glo..ghi: least relation cover; leftmost among equals."""
        existing = [p for p in range(glo, ghi + 1) if self.cuts.get(p)]
        if existing:                                     # a certain cut already lies in the interval: it carries this evidence too
            self.cuts[existing[0]].add(kind)
            self.interval.append((kind, glo, ghi, existing[0]))
            return
        cand = [p for p in range(glo, ghi + 1) if p not in self.joined]
        if not cand:
            return
        best = min(cand, key=lambda p: (rel.at(p), p))
        self.cuts[best].add(kind)
        self.interval.append((kind, glo, ghi, best))

    def add_intervals(self, libs, use_regions):
        img, R = self.img, self.img.real
        rel = self.rel.without_crossing(set(self.cuts))
        # (1) style: the last definite sd/sq function of one kind and the first of the other
        last = None
        for p in range(self.linkpos):
            st = img.style[R[p]]
            if st not in ('sd', 'sq'):
                continue
            if last is not None and last[1] != st:
                self.pick('style', last[0] + 1, p, rel)
            last = (p, st)
        # (2) libraries from strings: consecutive hulls
        hulls = sorted((v for v in libs.values()), key=lambda v: v['lo'])
        for a, b in zip(hulls, hulls[1:]):
            pa, pb = self.rel.pos.get(a['hi']), self.rel.pos.get(b['lo'])
            if pa is not None and pb is not None and 0 < pb - pa <= 60:
                self.pick('lib', pa + 1, pb, rel)
        # (3) regions of the counterpart map (leads only)
        if use_regions:
            runs = region_runs(img)
            for r0, r1 in zip(runs, runs[1:]):
                lead = ('kynapse', 'animation', 'physics')
                if r0[2] != r1[2] and (r0[2] in lead or r1[2] in lead) and r1[0] < self.linkpos:
                    self.pick('region', r0[1] + 1, r1[0], rel)

    def proposals(self, kinds=('hard', 'soft', 'call', 'item'), rel=None, maxtu=MAXTU):
        """Gaps (before the link-once area) that no relation crosses: likely object boundaries. A stretch longer than `maxtu`
        functions is split again with shorter relation edges (16, 8, 4 functions)."""
        rel = rel or self.final_rel
        if getattr(self, '_props', None) is not None and rel is self.final_rel and kinds == ('hard', 'soft', 'call', 'item'):
            return self._props
        out = set()
        joined = set()
        for lo, hi in self.forced_joins:
            joined.update(range(lo + 1, hi + 1))
        joined |= self.joined
        for p in range(1, self.linkpos):
            if p not in self.cuts and p not in joined and rel.at(p, kinds) == 0:
                out.add(p)
        self.sub = {}
        if maxtu and rel is self.final_rel and kinds == ('hard', 'soft', 'call', 'item'):
            for d in (16, 8, 4):
                bounds = sorted(set(self.cuts) | out | {0, self.linkpos})
                big = [(a, b) for a, b in zip(bounds, bounds[1:]) if b - a > maxtu]
                if not big:
                    break
                r2 = Relations(self.img, dist=d).without_crossing(set(self.cuts) | out)
                for a, b in big:
                    for p in range(a + 1, b):
                        if p not in joined and r2.at(p) == 0:
                            out.add(p)
                            self.sub[p] = d
            self._props = out
        return out


# ---------------------------------------------------------------------------------------------------------- the map
CLASS_RE = re.compile(r'(?:Kaim_)?(C[A-Z][A-Za-z0-9]+?)(?:_|::)')
SN_FLAGS = ['-O2', '-G0', '-snas']
SN = 'ee-gcc2.95.3-136'
SONY = 'ee-gcc2.9-991111-01'         # the compiler whose output has the `sd` register-save style (see README)


def hx(v):
    return '0x%06x' % v


def assemble(img, seg, libs, ov):
    """TU records (dicts) from a segmentation: object files before the link-once area, then link-once sections."""
    R, n, F, END = img.real, len(img.real), img.F, img.END
    rel, props = seg.final_rel, seg.proposals()
    from progress import regions
    reg, _ = regions(F)
    bounds = sorted(set(seg.cuts) | props | {0})
    segs = [(a, b, 'object') for a, b in zip(bounds, bounds[1:] + [n]) if a < seg.linkpos]
    segs = [(a, min(b, seg.linkpos), k) for a, b, k in segs]
    p = seg.linkpos
    while p < n:                     # link-once area: one unit per unwind group; the rest where no relation crosses
        g = img.eh_of.get(R[p])
        q = p + 1
        if g is not None:
            while q < n and img.eh_of.get(R[q]) == g:
                q += 1
        else:
            while q < n and img.eh_of.get(R[q]) is None and rel.at(q) > 0:
                q += 1
        segs.append((p, q, 'linkonce'))
        p = q
    # which library does a function use strings of (inside the library's hull only)
    label = {}
    for name, kind, rx in LIB_RULES:
        v = libs.get(name)
        if not v:
            continue
        pat = re.compile(rx)
        for i in range(v['lo'], v['hi'] + 1):
            if not img.orphan[i] and any(pat.search(t) for _, t in img.strings.get(i, [])):
                label.setdefault(i, name)
    sec_end = {nm: ad + sz for nm, ad, sz in img.sections}
    all_items = {s_: sorted(img.irefs[s_]) for s_ in DATA_SECTIONS}
    tus = []
    for a, b, kind in segs:
        fn = R[a:b]
        lo, hi = F[fn[0]], (F[R[b]] if b < n else END[fn[-1]])
        fset = set(fn)
        orphans = sum((END[i] - F[i]) // 8 for i in range(img.fi(lo), img.fi(hi - 1) + 1) if img.orphan[i])
        start = seg.cuts.get(a, set()) if a else {'start'}
        end = seg.cuts.get(b, set()) if b < n else {'end'}
        proposed = [(a and a not in seg.cuts), (b < n and b not in seg.cuts and kind == 'object')]
        groups = {img.eh_of.get(i) for i in fn}
        egroup = img.eh[next(iter(groups))] if len(groups) == 1 and None not in groups else None
        ev = []
        if egroup:
            ev.append('eh')
        if any(i in img.ctor_i for i in fn):
            ev.append('ctor-list')
        for k in sorted(start | end):
            if k not in ('start', 'end', 'linkonce', 'ehzone') and k not in ev:
                ev.append({'ctor': 'ctor-end', 'eh': 'eh-edge'}.get(k, k))
        joins = [k for k in ('hard', 'soft', 'call', 'item') if any(rel.cover[k][q] > 0 for q in range(a + 1, b))]
        ev += ['join-' + k if k in ('hard', 'soft') else {'call': 'calls', 'item': 'shared-items'}[k] for k in joins]
        if any(proposed):
            ev.append('proposed-cut')
        if (a in seg.sub) or (b in seg.sub):
            ev.append('subdivided')
        exact_edges = not any(proposed)
        if kind == 'linkonce':
            conf = 'exact' if egroup else 'low'
        elif egroup and exact_edges and 'eh' in start and 'eh' in end:
            conf = 'exact'
        elif exact_edges:
            conf = 'high'
        elif 'hard' in joins or 'soft' in joins:
            conf = 'medium'
        else:
            conf = 'low'
        if kind == 'object' and len(fn) == 1 and all(proposed) and not (egroup or any(i in img.ctor_i for i in fn)):
            kind = 'isolated'                    # one function that no relation ties to either neighbour: an object of its own or a part of one
        # library and class name
        labs = collections.Counter(label[i] for i in fn if i in label)
        regc = collections.Counter(reg[i] for i in fn)
        classes = collections.Counter()
        for i in fn:
            m = CLASS_RE.match(img.alias.get(F[i], ''))
            if m:
                classes[m.group(1)] += 1
        data = {}
        for s_ in DATA_SECTIONS:
            owned = sorted(ad for ad, fs in img.irefs[s_].items() if fs and all(f in fset for f in fs))
            if owned:
                ia = all_items[s_]
                k = bisect.bisect_right(ia, owned[-1])
                data[s_] = (owned[0], ia[k] if k < len(ia) else sec_end[s_])
        tus.append(dict(a=a, b=b, kind=kind, lo=lo, hi=hi, fn=fn, orphans=orphans, ev=ev, conf=conf, egroup=egroup, labs=labs,
                        regc=regc, classes=classes, data=data, styles=collections.Counter(img.style[i] for i in fn)))
    assign_libraries(img, seg, tus, ov)
    for t in tus:
        flags_of(img, t, ov)
        name_of(img, t, ov)
    return tus


def assign_libraries(img, seg, tus, ov):
    """Library of each TU: the strings it uses; else the zone it is in. Zones are runs between cuts that mark a change of
    compiler style, library or counterpart-map region."""
    zone_cuts = {p for p, k in seg.cuts.items() if k & {'lib', 'style', 'region', 'override', 'ehzone'}}
    objs = [t for t in tus if t['kind'] in ('object', 'isolated')]
    zone, zones = 0, collections.defaultdict(lambda: dict(labs=collections.Counter(), regc=collections.Counter(), styles=collections.Counter()))
    for t in objs:
        if t['a'] in zone_cuts:
            zone += 1
        t['zone'] = zone
        z = zones[zone]
        z['labs'].update(t['labs'])
        z['regc'].update(t['regc'])
        z['styles'].update(t['styles'])
    lead = ('kynapse', 'animation', 'physics')
    for t in objs:
        z = zones[t['zone']]
        t['zone_sd'] = z['styles']['sd'] > z['styles']['sq']
        if t['labs']:
            t['library'] = t['labs'].most_common(1)[0][0]
        elif len(z['labs']) == 1:
            t['library'] = next(iter(z['labs']))
        elif z['styles']['sd'] > z['styles']['sq']:
            t['library'] = 'sony_unidentified'
        else:
            r = z['regc'].most_common(1)[0][0]
            t['library'] = r if r in lead else 'game'
    for t in tus:
        if t['kind'] == 'linkonce':
            t['library'] = 'linkonce'
    for name, (lo, hi) in ov.get('libraries', {}).items():
        for t in tus:
            if lo <= t['lo'] < hi:
                t['library'] = name

    import layout
    for t in tus:
        t['library'] = layout.library_of(t['lo'])


def flags_of(img, t, ov):
    """Compiler and flags: those of the TU's functions already matched, else a guess from the code-generation style."""
    units = collections.Counter()
    for i in t['fn']:
        u = img.src.get(i)
        if u:
            units[(u['compiler'], tuple(f for f in u['flags'] if f != '-ffunction-sections'))] += 1
    sd = t['styles'].get('sd', 0)
    gp = sum(1 for i in t['fn'] if img.gprel[i])
    if t['lo'] in ov.get('flags', {}):
        comp, fl = ov['flags'][t['lo']]
        basis = 'override'
    elif sd or t.get('zone_sd'):
        comp, fl, basis = SONY, ['-O2', '-G0'], 'style: callee-saved registers saved with sd'
    elif units:
        (comp, fl), cnt = units.most_common(1)[0]
        fl = list(fl)
        basis = 'matched %d of %d functions' % (sum(units.values()), len(t['fn']))
        t['flags_seen'] = len(units)
    else:
        comp, fl, basis = SN, list(SN_FLAGS), 'default'
        if gp:
            fl = ['-O2', '-G8', '-snas']
            basis = 'default with small data (gp-relative access)'
    t['compiler'], t['flags'], t['flags_basis'] = comp, fl, basis


def name_of(img, t, ov):
    if t['lo'] in ov.get('names', {}):
        t['name'] = ov['names'][t['lo']]
        return
    base = 'tu_%06x' % t['lo']
    if t['kind'] == 'linkonce':
        t['name'] = 'linkonce_%06x' % t['lo']
    elif len(t['classes']) == 1:
        t['name'] = '%s_%06x' % (next(iter(t['classes'])), t['lo'])
    else:
        t['name'] = base
    if t['library'] not in (None, 'game', 'linkonce') and t['kind'] in ('object', 'isolated'):
        t['name'] = '%s/%s' % (t['library'], t['name'])


def summarize(img, tus):
    """Coverage by confidence, library ranges."""
    total = img.END[-1] - img.F[0]
    by = {}
    for c in ('exact', 'high', 'medium', 'low'):
        ts = [t for t in tus if t['conf'] == c]
        by[c] = dict(tus=len(ts), functions=sum(len(t['fn']) for t in ts), bytes=sum(t['hi'] - t['lo'] for t in ts))
        by[c]['share'] = round(by[c]['bytes'] / total, 4)
    libs = {}
    for t in tus:
        v = libs.setdefault(t['library'], dict(lo=t['lo'], hi=t['hi'], tus=0, functions=0, bytes=0))
        v['lo'], v['hi'] = min(v['lo'], t['lo']), max(v['hi'], t['hi'])
        v['tus'] += 1
        v['functions'] += len(t['fn'])
        v['bytes'] += t['hi'] - t['lo']
    return by, libs


def write_map(img, tus, libs_found, path):
    import yaml
    by, libs = summarize(img, tus)

    def rng(lo, hi):
        return [hx(lo), hx(hi)]
    doc = {}
    doc['variant'] = img.slug
    doc['generated_by'] = 'tools/build/tus.py map (hand corrections: config/tus_overrides.yaml)'
    doc['summary'] = dict(tus=len(tus), by_confidence=by)
    doc['libraries'] = [dict(name=k, text=rng(v['lo'], v['hi']), tus=v['tus'], functions=v['functions'], bytes=v['bytes'])
                        for k, v in sorted(libs.items(), key=lambda kv: kv[1]['lo'])]
    out = []
    for t in tus:
        d = {}
        d['name'] = t['name']
        d['kind'] = t['kind']
        d['library'] = t['library']
        d['text'] = rng(t['lo'], t['hi'])
        d['functions'] = len(t['fn'])
        if t['orphans']:
            d['orphan_pieces'] = t['orphans']
        d['confidence'] = t['conf']
        d['evidence'] = t['ev']
        d['compiler'] = t['compiler']
        d['flags'] = t['flags']
        d['flags_basis'] = t['flags_basis']
        if t['data']:
            d['data'] = {k: rng(lo, hi) for k, (lo, hi) in t['data'].items()}
        out.append(d)
    doc['tus'] = out
    text = '# TU map of the retail image, generated by tools/build/tus.py (see docs/tus.md). Generated, not committed: change the evidence\n' \
           '# rules or config/tus_overrides.yaml and run `python3 tools/build/tus.py map`.\n'
    text += yaml.safe_dump(doc, sort_keys=False, default_flow_style=None, width=200)
    Path(path).write_text(text)


# ---------------------------------------------------------------------------------------------------------- evidence report
def gap_signals(img, rel, libs, xb):
    """Boolean signals per gap position of img.real (before the link-once area)."""
    R, n = img.real, len(img.real)
    linkpos = next(p for p in range(n) if img.F[R[p]] >= img.linkonce_start)
    sig = {}
    P = range(1, linkpos)
    sig['eh_cut'] = {p for p in P if (img.eh_of.get(R[p - 1]) is not None or img.eh_of.get(R[p]) is not None)
                     and img.eh_of.get(R[p - 1]) != img.eh_of.get(R[p])}
    sig['ctor_end'] = {p for p in P if R[p - 1] in img.ctor_end}
    sig['eh_inside'] = {p for p in P if img.eh_of.get(R[p - 1]) is not None and img.eh_of.get(R[p - 1]) == img.eh_of.get(R[p])}
    sig['orphan_run'] = {p for p in P if R[p] - R[p - 1] > 1}
    sig['join_hard'] = {p for p in P if rel.cover['hard'][p] > 0}
    sig['join_soft'] = {p for p in P if rel.cover['soft'][p] > 0}
    sig['calls'] = {p for p in P if rel.cover['call'][p] > 0}
    sig['shared_items'] = {p for p in P if rel.cover['item'][p] > 0}
    sig['no_data_join'] = {p for p in P if rel.cover['hard'][p] == 0 and rel.cover['soft'][p] == 0}
    sig['isolated'] = {p for p in P if rel.at(p) == 0}
    st = [img.style[i] if img.style[i] in ('sd', 'sq') else None for i in R]
    sig['style_change'] = set()
    last = None
    for p in P:
        if st[p] is None:
            continue
        if last is not None and last[1] != st[p]:
            sig['style_change'].update(range(last[0] + 1, p + 1))
        last = (p, st[p])
    for slug in xb['adjacency']:
        adj = xb['adjacency'][slug]
        sig['break_' + ('beta' if slug == BETA else 'demo')] = {p for p in P if adj.get(str((img.F[R[p]] - img.tbase) >> 2)) == 'break'}
    sh = xb['shift'].get('SLKA_253.72', {})
    sig['shift_change'] = {p for p in P if sh.get(str(R[p - 1])) in ('same', 'shifted') and sh.get(str(R[p])) in ('same', 'shifted')
                           and sh.get(str(R[p - 1])) != sh.get(str(R[p]))}
    return sig, linkpos


def pct(a, b):
    return '%5.1f%%' % (100.0 * a / b) if b else '    - '


def validate(img, out=print):
    rel = Relations(img)
    libs = detect_libs(img)
    xb = build_signals(img)
    sig, linkpos = gap_signals(img, rel, libs, xb)
    n = len(img.real)
    allgaps = set(range(1, linkpos))
    truth = sig['eh_cut'] | sig['ctor_end']
    inside = sig['eh_inside']
    evalset = truth | inside
    out('Held-out evaluation set: %d certain object boundaries (unwind-frame edges %d, constructor-stub ends %d) and %d gaps inside unwind-frame groups'
        % (len(truth), len(sig['eh_cut']), len(sig['ctor_end']), len(inside)))
    out('')
    out('1. Predicting object boundaries without the unwind-frame or constructor signals (a gap with no relation across it)')
    out('   %-34s %8s %8s %12s %14s' % ('relations used', 'cuts', 'recall', 'false-split', 'precision*'))
    for label, kinds in (('data joins (hard+soft)', ('hard', 'soft')), ('calls', ('call',)), ('shared items', ('item',)),
                         ('calls + items', ('call', 'item')), ('all four', ('hard', 'soft', 'call', 'item'))):
        cut = {p for p in allgaps if rel.at(p, kinds) == 0}
        tp, fp = len(cut & truth), len(cut & inside)
        out('   %-34s %8d %8s %12s %14s' % (label, len(cut), pct(tp, len(truth)), pct(fp, len(inside)), pct(tp, tp + fp)))
    out('   (* precision within the evaluation set; false-split = share of gaps inside unwind groups that would be cut)')
    out('   relation edge length (functions) vs recall/false-split, all four:')
    for d in (8, 16, 32, 64, 128):
        r2 = Relations(img, dist=d)
        cut = {p for p in allgaps if r2.at(p) == 0}
        out('     D=%3d  cuts %5d  recall %s  false-split %s' % (d, len(cut), pct(len(cut & truth), len(truth)), pct(len(cut & inside), len(inside))))
    out('')
    out('2. Containment: does a held-out proposal keep each known object whole?')
    held = {p for p in allgaps if rel.at(p) == 0}
    spans = [(sorted(g)[0], sorted(g)[-1]) for g in _eh_positions(img, rel)]
    whole = sum(1 for a, b in spans if not any(a < p <= b for p in held))
    out('   unwind groups of >=2 functions kept in one proposed TU: %d of %d (%s)' % (whole, len(spans), pct(whole, len(spans))))
    ctor_spans = []
    for end, i in img.ctor_end.items():
        j = img.stub.get(i, (None, None))[1]
        if j is not None and j in rel.pos and end in rel.pos and rel.pos[end] - rel.pos[j] >= 1:
            ctor_spans.append((rel.pos[j], rel.pos[end]))
    whole = sum(1 for a, b in ctor_spans if not any(a < p <= b for p in held))
    out('   constructor sequences (sinit .. _GLOBAL__I/D) kept in one proposed TU: %d of %d (%s)' % (whole, len(ctor_spans), pct(whole, len(ctor_spans))))
    out('')
    out('3. Agreement of each signal with the certain boundaries (precision = share of its gaps in the evaluation set that are boundaries)')
    out('   %-16s %7s %12s %10s %10s' % ('signal', 'gaps', 'in eval set', 'precision', 'recall'))
    for name, g in sig.items():
        if name in ('eh_cut', 'ctor_end', 'eh_inside'):
            continue
        e = g & evalset
        out('   %-16s %7d %12d %10s %10s' % (name, len(g), len(e), pct(len(e & truth), len(e)), pct(len(g & truth), len(truth))))
    out('   base rate of a boundary in the evaluation set: %s' % pct(len(truth), len(evalset)))
    out('')
    out('4. Orphan pieces (%d pieces in %d runs between functions)' % (img.orphan_pieces, len(sig['orphan_run'])))
    base = len(sig['orphan_run']) / len(allgaps)
    for label, g in (('all gaps', allgaps), ('gaps joined by constants (same object for sure)', sig['join_hard']),
                     ('gaps joined by statics', sig['join_soft']), ('gaps inside unwind groups', inside),
                     ('known object boundaries', truth), ('gaps with no data join (data-order boundary candidates)', sig['no_data_join']),
                     ('isolated gaps (no relation of any kind)', sig['isolated'])):
        k = len(g & sig['orphan_run'])
        out('   %-62s %5d gaps, orphan run in %s' % (label, len(g), pct(k, len(g))))
    out('   -> orphan runs are %s likely inside an object that is certainly one object as at an isolated gap: they do not mark boundaries.'
        % ('as' if abs(len(sig['join_hard'] & sig['orphan_run']) / max(len(sig['join_hard']), 1) - len(sig['isolated'] & sig['orphan_run']) / max(len(sig['isolated']), 1)) < 0.02 else 'not as'))
    out('')
    out('5. Cross-build and style signals: rate at certain boundaries vs inside objects')
    for name in [k for k in sig if k.startswith('break_') or k in ('shift_change', 'style_change', 'lib_change')]:
        g = sig[name]
        out('   %-14s at boundaries %s (%d of %d)   inside unwind groups %s (%d of %d)' % (
            name, pct(len(g & truth), len(truth)), len(g & truth), len(truth), pct(len(g & inside), len(inside)), len(g & inside), len(inside)))
    out('')
    out('6. Alignment: address of the first function of known objects vs the first function after a gap inside an object')
    for m in (16, 32, 64, 128):
        starts = [img.F[img.real[p]] for p in truth]
        inner = [img.F[img.real[p]] for p in inside]
        out('   multiple of %3d: object starts %s (%d)   inside objects %s (%d)' % (
            m, pct(sum(1 for a in starts if a % m == 0), len(starts)), len(starts), pct(sum(1 for a in inner if a % m == 0), len(inner)), len(inner)))
    out('   .text between functions: the original assembler/linker pad to 8 only (no larger steps at object starts); .data frames start at 4')
    out('')
    out('7. Library hulls (functions that use a library string; style of the functions in the hull)')
    for name, v in sorted(libs.items(), key=lambda kv: kv[1]['lo']):
        fs = [i for i in img.real if v['lo'] <= i <= v['hi']]
        st = collections.Counter(img.style[i] for i in fs)
        eh = sum(1 for i in fs if i in img.eh_of)
        out('   %-20s %s-%s %4d functions, %3d string hits (%d strays), sd %d sq %d, unwind frames %d' % (
            name, hx(img.F[v['lo']]), hx(img.END[v['hi']]), len(fs), v['hits'], v['stray'], st['sd'], st['sq'], eh))
    return sig


def _eh_positions(img, rel):
    gs = collections.defaultdict(list)
    for i, g in img.eh_of.items():
        if i in rel.pos and img.F[i] < img.linkonce_start:
            gs[g].append(rel.pos[i])
    return [v for v in gs.values() if len(v) >= 2]


def evidence(img, out=print):
    out('image: %d functions (%d after leaving out %d orphan runs of %d pieces), .text %s-%s' % (
        img.N, len(img.real), sum(img.orphan), img.orphan_pieces, hx(img.F[0]), hx(img.END[-1])))
    reg_groups = [g for g in img.eh if g['lo'] < img.linkonce_start]
    out('unwind frames: %d groups (%d with an exception table), %d FDEs; %d in the link-once area (from %s)' % (
        len(img.eh), sum(1 for g in img.eh if g['aug'] == 'eh'), sum(len(g['fdes']) for g in img.eh), len(img.eh) - len(reg_groups), hx(img.linkonce_start)))
    out('  regular objects with frames: %d, covering %d bytes of .text' % (len(reg_groups), sum(r for g in reg_groups for _, r in g['fdes'])))
    out('constructors: %d stubs (_GLOBAL__I %d, _GLOBAL__D %d); __CTOR_LIST__ at %s holds %d entries' % (
        len(img.stub), sum(1 for s in img.stub.values() if s[0] == 'I'), sum(1 for s in img.stub.values() if s[0] == 'D'),
        hx(img.ctor_table), len(img.ctor_list)))
    odd = [a for a in img.ctor_list if img.F[img.fi(a)] != a or img.fi(a) not in img.stub]
    out('  entries that are not a plain stub or not a split function start: %s' % ', '.join(hx(a) for a in odd))
    st = collections.Counter(img.style)
    out('save style: ' + ', '.join('%s %d' % kv for kv in sorted(st.items())))
    lo = [g for g in img.eh if g['lo'] >= img.linkonce_start]
    nlo = sum(1 for i in range(img.N) if img.F[i] >= img.linkonce_start)
    out('link-once area: %s-%s, %d functions in %d one-function-sized unwind sections (%d with an exception table pointer)' % (
        hx(img.linkonce_start), hx(img.END[-1]), nlo, len(lo), sum(1 for g in lo if g['aug'] == 'eh')))
    d = img.elf.section('.data')
    dc, base = img.elf.content(d), d['addr']
    vt = runs = 0
    o = 0
    while o < len(dc) - 16:
        k = 0
        while o + 8 * k + 8 <= len(dc) and struct.unpack_from('<I', dc, o + 8 * k)[0] == 0 and struct.unpack_from('<I', dc, o + 8 * k + 4)[0] in img.fidx:
            k += 1
        if k >= 3:
            vt, runs, o = vt + 1, runs + k, o + 8 * k
        else:
            o += 4
    out('vtables: %d runs of (0, method) pairs in .data, %d entries' % (vt, runs))
    libs = detect_libs(img)
    out('libraries by strings: ' + ', '.join('%s %s-%s' % (k, hx(img.F[v['lo']]), hx(img.END[v['hi']])) for k, v in sorted(libs.items(), key=lambda kv: kv[1]['lo'])))
    return libs


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('what', choices=['evidence', 'map', 'validate', 'all'])
    ap.add_argument('--out', default=str(ROOT / 'build/SLUS_213.76/tus.yaml'))
    a = ap.parse_args()
    img = Image()
    if a.what in ('evidence', 'all'):
        evidence(img)
        print()
    if a.what in ('validate', 'all'):
        validate(img)
        print()
    if a.what in ('map', 'all'):
        libs = detect_libs(img)
        ov = load_overrides()
        rel = Relations(img)
        seg = Segmentation(img, rel, libs=libs, overrides=ov)
        tus = assemble(img, seg, libs, ov)
        write_map(img, tus, libs, a.out)
        by, lb = summarize(img, tus)
        fl = collections.defaultdict(collections.Counter)
        for i, u in img.src.items():
            t = next((t for t in tus if t['lo'] <= img.F[i] < t['hi']), None)
            if t:
                fl[t['library']][(u['compiler'].replace('ee-gcc', ''), ' '.join(f for f in u['flags'] if f not in ('-snas', '-ffunction-sections')))] += 1
        print('flags of the functions already matched, by library:')
        for lib, c in sorted(fl.items()):
            print('  %-20s %s' % (lib, ', '.join('%s %s: %d' % (k[0], k[1], v) for k, v in c.most_common())))
        print('wrote %s: %d TUs' % (Path(a.out).name, len(tus)))
        for c, v in by.items():
            print('  %-7s %5d TUs %6d functions %8d bytes (%.1f%% of .text)' % (c, v['tus'], v['functions'], v['bytes'], 100 * v['share']))


if __name__ == '__main__':
    main()
