#!/usr/bin/env python3
"""Phase 0 assembler check: does a given EE-aware GNU assembler reassemble retail instruction words identically?

`gen` samples the USA retail .text (every distinct mnemonic plus random contiguous windows), disassembles with
rabbitizer's R5900 support and writes sample.s plus sample.json (original words and texts) under .local/asmcheck/.
`run` assembles it inside the build toolchain (tools/build/sandbox.py) with each available assembler, retries after
removing lines the assembler rejects, and compares the resulting .text words with the originals.

Usage: asmcheck.py gen [--windows N --window-size N --per-mnemonic N --seed N]
       asmcheck.py run
"""
import sys as _sys
from pathlib import Path as _Path
_sys.path[:0] = [str(_Path(__file__).resolve().parents[1] / _d) for _d in ('', 'build', 'pipeline', 'maint')]  # the core tools
import argparse, collections, json, random, struct, subprocess, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import rabbitizer
from rabbitizer import Instruction, InstrCategory
rabbitizer.config.regNames_namedRegisters = False
rabbitizer.config.regNames_vr4300Cop0NamedRegisters = False
rabbitizer.config.regNames_userFpcCsr = False
from elfinfo import Elf

ROOT = Path(__file__).resolve().parents[2]
WORK = ROOT / '.local/asmcheck'
ASSEMBLERS = {
    'gas-2.10-ee-001003-1': '/toolchains/compilers/ee-gcc2.96/ee/bin/as',
    'gas-2.9-ee-991111': '/toolchains/compilers/ee-gcc2.9-991111-01/ee/bin/as',
    'gas-2.9-ee-991111b(wibo)': 'wibo /toolchains/compilers/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe',
}
HEADER = '\t.set noreorder\n\t.set noat\n\t.set nomacro\n\t.text\n'


def load_words():
    e = Elf((ROOT / 'orig/SLUS_213.76/SLUS_213.76').read_bytes())
    t = e.section('.text')
    c = e.content(t)
    return t['addr'], struct.unpack('<%dI' % (len(c) // 4), c)


def fix_special(txt):
    # rabbitizer prints VU0 special registers with a leading '$'; the EE assemblers want them bare.
    for special in ('$ACC', '$Q', '$I', '$R', '$P'):
        txt = txt.replace(special + ',', special[1:] + ',').replace(special + ' ', special[1:] + ' ')
        if txt.endswith(special):
            txt = txt[:-len(special)] + special[1:]
    return txt


def render(word, vram, label=None):
    """Return (mnemonic, text, branch_offset_words or None). `label` replaces a branch target."""
    ins = Instruction(word, vram, InstrCategory.R5900)
    if not ins.isValid():
        return 'invalid', '.word 0x%08X' % word, None
    name = ins.getOpcodeName()
    try:
        if ins.isJumpWithAddress():
            return name, ins.disassemble(immOverride='0x%X' % ins.getInstrIndexAsVram()), None
        if ins.isBranch():
            off = ins.getProcessedImmediate()
            return name, ins.disassemble(immOverride=label or '.'), off
    except Exception:
        pass
    txt = ins.disassemble()
    if txt.startswith('.word'):
        return 'unknown-to-rabbitizer', '.word 0x%08X' % word, None
    return name, fix_special(txt.split('#')[0].rstrip()), None


def gen(a):
    base, W = load_words()
    rnd = random.Random(a.seed)
    by = collections.defaultdict(list)
    for i, w in enumerate(W):
        by[render(w, base + 4 * i)[0]].append(i)
    picks = set()
    for n, idx in by.items():
        picks.update(rnd.sample(idx, min(a.per_mnemonic, len(idx))))
    WORK.mkdir(parents=True, exist_ok=True)
    rows, lines = [], [HEADER]
    for i in sorted(picks):
        k = len(rows)
        n, txt, off = render(W[i], base + 4 * i, label='t%d' % k)
        rows.append(dict(index=i, addr=base + 4 * i, word=W[i], mnemonic=n, text=txt, branch=off is not None))
        # isolated row: instruction, delay-slot/hazard nop, then the branch target label
        lines.append('r%d:\t%s\n\tnop\nt%d:\n' % (k, txt, k))
    (WORK / 'sample.s').write_text(''.join(lines))
    wins = []
    for wi in range(a.windows):
        s0 = rnd.randrange(0, len(W) - a.window_size)
        wl, words = [HEADER], []
        for j in range(a.window_size):
            i = s0 + j
            n, txt, off = render(W[i], base + 4 * i, label='w%d' % 0)
            if off is not None:
                tgt = j + 1 + off
                if -a.raw_short <= off < 0:
                    txt = '.word 0x%08X' % W[i]
                elif 0 <= tgt < a.window_size:
                    n, txt, _ = render(W[i], base + 4 * i, label='w%d' % tgt)
                else:
                    txt = '.word 0x%08X' % W[i]
            wl.append('w%d:\t%s\n' % (j, txt))
        (WORK / ('win%d.s' % wi)).write_text(''.join(wl))
        wins.append(dict(start=s0, addr=base + 4 * s0, words=list(W[s0:s0 + a.window_size])))
    (WORK / 'sample.json').write_text(json.dumps(dict(rows=rows, windows=wins)))
    print(len(rows), 'isolated words,', len(by), 'mnemonics,', len(wins), 'windows of', a.window_size)


SCRIPT = r"""
import subprocess, re, sys, json, os, shlex
asms = json.load(open('asms.json'))
nwin = json.load(open('asms.json')) and int(open('nwin.txt').read())
env = dict(os.environ, WINEDEBUG='-all', WIBO_PATH='/toolchains/compilers/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3')
def assemble(cmd, src, out, retry):
    lines = open(src).read().split('\n')
    bad = {}
    for rnd in range(4 if retry else 1):
        open('t.s', 'w').write('\n'.join(lines) + '\n')
        if os.path.exists(out): os.remove(out)
        p = subprocess.run(shlex.split(cmd) + ['-o', out, 't.s'], capture_output=True, text=True, env=env)
        errs = re.findall(r't\.s:(\d+): Error: (.*)', p.stdout + p.stderr)
        if not errs or not retry:
            break
        for ln, msg in errs:
            ln = int(ln) - 1
            bad.setdefault(ln, (lines[ln].strip(), msg))
            lines[ln] = '\tnop'
    errs = re.findall(r't\.s:(\d+): (?:Error|Warning): (.*)', p.stdout + p.stderr)
    return dict(bad={str(k): v for k, v in bad.items()}, rounds=rnd + 1, ok=os.path.exists(out),
                diag=sorted(set(m for _, m in errs))[:6])
res = {}
for name, cmd in asms.items():
    tag = name.split('(')[0]
    r = dict(sample=assemble(cmd, 'sample.s', tag + '.o', True), windows=[])
    for w in range(nwin):
        r['windows'].append(assemble(cmd, 'win%d.s' % w, '%s.win%d.o' % (tag, w), False))
    res[name] = r
json.dump(res, open('result.json', 'w'))
"""


def text_words(path):
    e = Elf(path.read_bytes())
    t = e.section('.text')
    c = e.content(t)
    return e, t, struct.unpack('<%dI' % (len(c) // 4), c)


def run(a):
    data = json.loads((WORK / 'sample.json').read_text())
    rows, wins = data['rows'], data['windows']
    (WORK / 'run.py').write_text(SCRIPT)
    (WORK / 'asms.json').write_text(json.dumps({k: v + ' ' + a.flags for k, v in ASSEMBLERS.items()}))
    (WORK / 'nwin.txt').write_text(str(len(wins)))
    tags = [n.split('(')[0] for n in ASSEMBLERS]
    outs = ['result.json'] + [t + '.o' for t in tags] + ['%s.win%d.o' % (t, w) for t in tags for w in range(len(wins))]
    cmd = [sys.executable, str(ROOT / 'tools/build/sandbox.py'), str(WORK / 'run.py'), '--timeout', '900',
           '--file', 'sample.s=' + str(WORK / 'sample.s'), '--file', 'asms.json=' + str(WORK / 'asms.json'),
           '--file', 'nwin.txt=' + str(WORK / 'nwin.txt')]
    cmd += sum((['--file', 'win%d.s=%s' % (w, WORK / ('win%d.s' % w))] for w in range(len(wins))), [])
    for o in outs:
        cmd += ['--out', o + '=' + str(WORK / 'out' / o)]
    if subprocess.run(cmd).returncode:
        raise SystemExit('sandbox failed')
    res = json.loads((WORK / 'out/result.json').read_text())
    summary = {}
    for name in ASSEMBLERS:
        tag, info = name.split('(')[0], res[name]
        sm = info['sample']
        bad = {(int(k) - 4) // 4: v for k, v in sm['bad'].items()}  # 4 header lines, 4 lines per row
        rej = collections.Counter()
        rej_ex = {}
        for k, v in bad.items():
            if 0 <= k < len(rows):
                rej[rows[k]['mnemonic']] += 1
                rej_ex.setdefault(rows[k]['mnemonic'], v)
        mism, mism_ex, same, total = collections.Counter(), {}, 0, 0
        obj = WORK / 'out' / (tag + '.o')
        if obj.exists():
            e, t, got_all = text_words(obj)
            idx = e.sections.index(t)
            pos = {x['name']: x['value'] for x in e.symbols() if x['shndx'] == idx and x['name'][:1] in 'rt'
                   and x['name'][1:].isdigit()}
            for k, row in enumerate(rows):
                if k in bad:
                    continue
                total += 1
                off, nxt = pos.get('r%d' % k), pos.get('t%d' % k)
                if off is None or nxt is None:
                    mism[row['mnemonic']] += 1
                    continue
                g = got_all[off // 4] if off is not None else None
                want = row['word']
                if row['branch']:  # target label is the next-next word: compare everything but the offset field
                    want &= 0xFFFF0000
                    g = None if g is None else g & 0xFFFF0000
                    ok = nxt is not None and nxt - off == 8
                else:
                    ok = nxt is not None and nxt - off == 8
                if g == want and ok:
                    same += 1
                else:
                    mism[row['mnemonic']] += 1
                    mism_ex.setdefault(row['mnemonic'], (row['text'], '%08x' % row['word'],
                                                         None if g is None else '%08x' % g,
                                                         None if nxt is None else nxt - off))
        wsum = []
        for w, wi in enumerate(info['windows']):
            f = WORK / 'out' / ('%s.win%d.o' % (tag, w))
            orig = wins[w]['words']
            if not f.exists():
                wsum.append(dict(assembled=False, diag=wi['diag']))
                continue
            _, _, got = text_words(f)
            first = next((i for i in range(min(len(got), len(orig))) if got[i] != orig[i]), None)
            wsum.append(dict(assembled=True, words=len(orig), got_words=len(got), identical=list(got) == list(orig),
                             first_diff_word=first, diag=wi['diag']))
        summary[name] = dict(isolated_words=len(rows), rejected=sum(rej.values()), assembled=total,
                             identical=same, rejected_by_mnemonic=dict(rej), rejected_examples=rej_ex,
                             differing_by_mnemonic=dict(mism), differing_examples=mism_ex,
                             sample_diag=sm['diag'], windows=wsum)
        print(name, 'isolated: rejected', sum(rej.values()), 'differ', sum(mism.values()), 'identical', same, '/',
              total, '| windows identical', sum(1 for x in wsum if x.get('identical')), '/', len(wsum))
    (WORK / a.summary).write_text(json.dumps(summary, indent=1))


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest='cmd', required=True)
    g = sub.add_parser('gen')
    g.add_argument('--windows', type=int, default=6)
    g.add_argument('--window-size', type=int, default=400)
    g.add_argument('--per-mnemonic', type=int, default=12)
    g.add_argument('--seed', type=int, default=1)
    g.add_argument('--raw-short', type=int, default=5, help='emit backward branches of up to N words as raw .word')
    r = sub.add_parser('run')
    r.add_argument('--flags', default='')
    r.add_argument('--summary', default='summary.json')
    a = ap.parse_args()
    gen(a) if a.cmd == 'gen' else run(a)


if __name__ == '__main__':
    main()
