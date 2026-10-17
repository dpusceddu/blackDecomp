#!/usr/bin/env python3
"""Phase 0 triage of every procured disc variant (run tools/discs.py first).

Reads orig/<slug>/ and writes config/variants.json (hashes and ELF metadata only) plus raw dumps
(string lists, listings, similarity details) under .local/inputs/.

Usage: inputs.py [--no-similarity]
"""
import argparse, collections, json, re, struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfinfo import Elf, sha256

ROOT = Path(__file__).resolve().parents[1]
RETAIL = 'usa-retail'
DEBUG_PATTERNS = ('.symtab', '.strtab', '.mdebug', '.debug_', '.stab', '.comment', '.gcc_except_table',
                  '.pdr', '.line', '.gnu', '.note', '.eh_frame', '.sdata', '.lit')
# Version 1 CIE emitted by SN EE (see frames.py in the companion project): marks per-object unwind groups.
CIE = bytes.fromhex('100000000000000001000178400c1d0009401f00')

STR_RE = re.compile(rb'[\x20-\x7e\t]{5,}')
PATTERNS = {
    'source_paths': re.compile(r'[\w./\\:+-]*\w\.(?:cpp|cxx|cc|c|h|hpp|inl|s)\b', re.I),
    'toolchain': re.compile(r'GCC:|\bgcc\b|SN Systems|ProDG|\bSCE\b|Sony Computer|Codewarrior|Metrowerks', re.I),
    'dates': re.compile(r'\b(?:Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)[a-z]* +\d{1,2},? +\d{4}\b|'
                        r'\b\d{4}[-/.]\d\d[-/.]\d\d\b|\b\d\d[-/.]\d\d[-/.]\d{4}\b'),
    'versions': re.compile(r'\bv(?:er(?:sion)?)?\.? ?\d+\.\d+|\bbuild\b[ :]*\d+|\bversion\b', re.I),
    'asserts': re.compile(r'assert|ASSERT|Assertion|\bFATAL\b|\bPANIC\b|\.cpp\W*\d+|line +\d+', re.I),
    'debug_dev': re.compile(r'debug|dev(?:elop|kit|menu)|cheat|warp|level.?select|\bTEST\b|prototype|'
                            r'profil|wireframe|freecam|free.?cam|god.?mode|console', re.I),
}


def strings(data):
    return [m.group().decode('latin1') for m in STR_RE.finditer(data)]


# ---------- code comparison ----------
def mask_text(words):
    """Mask address-dependent fields. Returns (smart, loose) masked word lists.

    smart: j/jal targets, branch offsets, lui immediates, and 16-bit immediates whose base register was
    set by a preceding lui (the %lo half of an address) or is gp. loose: every I-type immediate.
    """
    smart, loose = [], []
    lui_regs = set()
    imm_ops = {8, 9, 10, 11, 12, 13, 14, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a,
               0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x36, 0x37, 0x38, 0x39, 0x3e, 0x3f, 0x1e, 0x1f,
               0x32, 0x3a, 0x34, 0x3c}
    for w in words:
        op = w >> 26
        rs = (w >> 21) & 31
        rt = (w >> 16) & 31
        sm = lo = w
        if op in (2, 3):
            sm = lo = w & 0xfc000000
        elif op in (1, 4, 5, 6, 7, 20, 21, 22, 23) or (op in (0x10, 0x11, 0x12) and rs == 8):
            sm = lo = w & 0xffff0000
        elif op == 0x0f:
            sm = lo = w & 0xffff0000
            lui_regs.add(rt)
        elif op in imm_ops:
            lo = w & 0xffff0000
            if rs == 28 or rs in lui_regs:
                sm = lo
            if op in (8, 9, 10, 11, 12, 13, 14, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x37, 0x1e):
                if not (op in (8, 9, 13) and rt in lui_regs and rs == rt):
                    lui_regs.discard(rt)
        elif op == 0:
            lui_regs.discard((w >> 11) & 31)
        if w == 0x03e00008:
            lui_regs.clear()
        smart.append(sm)
        loose.append(lo)
    return smart, loose


def windows(words):
    """Split at every `jr ra` plus its delay slot: function-sized windows (start, end) in word indices."""
    out, start = [], 0
    for i, w in enumerate(words):
        if w == 0x03e00008 and i + 1 < len(words):
            out.append((start, i + 2))
            start = i + 2
    if start < len(words):
        out.append((start, len(words)))
    return out


def shingles(words, k):
    return [hash(tuple(words[i:i + k])) for i in range(len(words) - k + 1)]


class Retail:
    def __init__(self, words):
        self.words = words
        self.smart, self.loose = mask_text(words)
        self.win = {hash(tuple(self.smart[a:b])) for a, b in windows(words)}
        self.win_loose = {hash(tuple(self.loose[a:b])) for a, b in windows(words)}
        self.sh_smart = set(shingles(self.smart, 8))
        self.sh_loose = set(shingles(self.loose, 8))


def coverage(masked, store, k=8):
    hs = shingles(masked, k)
    cov = bytearray(len(masked))
    for i, h in enumerate(hs):
        if h in store:
            for j in range(i, i + k):
                cov[j] = 1
    return sum(cov) / max(1, len(masked))


def compare_text(words, retail):
    smart, loose = mask_text(words)
    wins = windows(words)
    exact_w = sum(b - a for a, b in wins if hash(tuple(smart[a:b])) in retail.win)
    exact_l = sum(b - a for a, b in wins if hash(tuple(loose[a:b])) in retail.win_loose)
    same_pos = sum(a == b for a, b in zip(words, retail.words))
    return dict(text_words=len(words), windows=len(wins),
                window_masked_exact_share=round(exact_w / len(words), 4),
                window_loose_exact_share=round(exact_l / len(words), 4),
                shingle8_smart_share=round(coverage(smart, retail.sh_smart), 4),
                shingle8_loose_share=round(coverage(loose, retail.sh_loose), 4),
                same_position_raw_share=round(same_pos / max(1, min(len(words), len(retail.words))), 4))


# ---------- per-file analysis ----------
def elf_report(path, data, out_dir, banner_scan):
    e = Elf(data)
    sections = e.summary()['sections']
    names = [s['name'] for s in sections]
    debug = {}
    for s in sections:
        if any(s['name'].startswith(p) for p in DEBUG_PATTERNS):
            debug[s['name']] = s['size']
    rep = dict(file=path, size=len(data), sha256=sha256(data), type=e.type, machine=e.machine,
               entry=e.entry, flags=e.flags, nsections=len(sections), nsegments=len(e.segments),
               debug_sections=debug, sections=sections,
               segments=[dict(t=g['type'], va=g['vaddr'], fsz=g['filesz'], msz=g['memsz']) for g in e.segments])
    symtab = e.section('.symtab')
    if symtab and symtab['size']:
        syms = e.symbols()
        rep['symbols'] = dict(total=len(syms), functions=sum(s['type'] == 2 for s in syms),
                              objects=sum(s['type'] == 1 for s in syms),
                              files=sum(s['type'] == 4 for s in syms))
    if banner_scan:
        ss = strings(data)
        out_dir.mkdir(parents=True, exist_ok=True)
        (out_dir / (Path(path).name + '.strings.txt')).write_text('\n'.join(ss) + '\n')
        found = {}
        for key, rx in PATTERNS.items():
            hits = []
            for s in ss:
                if rx.search(s):
                    hits.append(s)
            found[key] = hits
        (out_dir / (Path(path).name + '.findings.json')).write_text(json.dumps(found, indent=1))
        rep['string_counts'] = {k: len(v) for k, v in found.items()}
        rep['strings_total'] = len(ss)
        rep['source_path_tokens'] = sorted({m.group() for s in found['source_paths']
                                            for m in PATTERNS['source_paths'].finditer(s)})[:40]
    text = e.section('.text')
    if text:
        rep['text'] = dict(addr=text['addr'], size=text['size'])
    data_sec = e.section('.data')
    if data_sec:
        c = e.content(data_sec)
        rep['sn_cie_count'] = c.count(CIE)
    return e, rep


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--no-similarity', action='store_true')
    a = ap.parse_args()
    raw = ROOT / '.local/inputs'
    raw.mkdir(parents=True, exist_ok=True)
    discs = {p.parent.name: json.loads(p.read_text()) for p in sorted((ROOT / 'orig').glob('*/disc.json'))}
    listings = {s: {r['path']: r for r in json.loads((ROOT / 'orig' / s / 'listing.json').read_text())}
                for s in discs}
    retail_exe = ROOT / 'orig' / RETAIL / 'files' / discs[RETAIL]['boot']
    retail_elf = Elf(retail_exe.read_bytes())
    rtext = retail_elf.section('.text')
    retail_words = struct.unpack('<%dI' % (rtext['size'] // 4), retail_elf.content(rtext))
    retail = Retail(list(retail_words)) if not a.no_similarity else None
    retail_names = {s['name'] for s in retail_elf.sections}
    retail_sizes = {s['name']: s['size'] for s in retail_elf.sections}
    retail_files = {p: sha256((ROOT / 'orig' / RETAIL / 'files' / p).read_bytes())
                    for p in discs[RETAIL]['kept']}
    result = {}
    for slug, d in discs.items():
        files = ROOT / 'orig' / slug / 'files'
        entry = dict(slug=slug, zip=d['zip'], zip_size=d['zip_size'], zip_sha256=d['zip_sha256'],
                     image=d['image'], image_size=d['image_size'], image_sha256=d['image_sha256'],
                     sector_size=d['sector'], boot=d['boot'], system_cnf=d['system_cnf'].replace('\r', '').split('\n')[:-1],
                     file_count=len(listings[slug]))
        # extra disc files compared with retail
        rl, vl = listings[RETAIL], listings[slug]
        entry['listing_vs_retail'] = dict(
            only_here=sorted(set(vl) - set(rl)), missing=len(set(rl) - set(vl)),
            size_differs=sum(1 for p in vl if p in rl and vl[p]['size'] != rl[p]['size']),
            same=sum(1 for p in vl if p in rl and vl[p]['size'] == rl[p]['size']))
        entry['listing_vs_retail']['only_here_count'] = len(entry['listing_vs_retail']['only_here'])
        entry['listing_vs_retail']['only_here'] = entry['listing_vs_retail']['only_here'][:40]
        elfs = []
        for p, reason in d['kept'].items():
            if reason not in ('boot', 'elf'):
                continue
            data = (files / p).read_bytes()
            is_boot = reason == 'boot'
            e, rep = elf_report(p, data, raw / slug, banner_scan=is_boot)
            rep['role'] = 'boot' if is_boot else 'module'
            if not is_boot:
                rep['same_as_retail'] = retail_files.get(p) == rep['sha256']
                rep['sections'] = [s['name'] for s in rep['sections']]
                rep.pop('segments')
            else:
                rep['sections_not_in_retail'] = sorted({s['name'] for s in rep['sections']} - retail_names)
                rep['sections_not_in_variant'] = sorted(retail_names - {s['name'] for s in rep['sections']})
                rep['section_size_diffs'] = {s['name']: s['size'] - retail_sizes[s['name']]
                                             for s in rep['sections']
                                             if s['name'] in retail_sizes and s['size'] != retail_sizes[s['name']]
                                             and not s['name'].startswith('.DVP.overlay')}
                overlays = [s for s in rep['sections'] if s['name'].startswith('.DVP.overlay')]
                rep['dvp_overlays'] = len(overlays)
                if retail and slug != RETAIL:
                    t = e.section('.text')
                    words = list(struct.unpack('<%dI' % (t['size'] // 4), e.content(t)))
                    rep['similarity_vs_retail'] = compare_text(words, retail)
                rep['identical_to_retail'] = rep['sha256'] == sha256(retail_exe.read_bytes())
            elfs.append(rep)
        entry['elfs'] = elfs
        result[slug] = entry
        print(slug, 'done', flush=True)
    (ROOT / 'config').mkdir(exist_ok=True)
    slim = json.loads(json.dumps(result))
    for v in slim.values():
        for e in v['elfs']:
            if e['role'] == 'boot':
                e['source_path_tokens'] = e.get('source_path_tokens', [])[:0]
    (ROOT / 'config/variants.json').write_text(json.dumps(slim, indent=1) + '\n')
    (raw / 'variants-full.json').write_text(json.dumps(result, indent=1) + '\n')


if __name__ == '__main__':
    main()
