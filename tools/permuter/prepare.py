#!/usr/bin/env python3
"""Write the assembly of one function in the plain form decomp-permuter's import.py reads.

Usage: prepare.py func_XXXXXXXX|0xADDRESS      writes build/permuter/func_XXXXXXXX.s and prints the next commands
The split assembly (asm/SLUS_213.76/nonmatchings/func_XXXXXXXX.s, after `tools/setup.py`) puts the code in a section
named .text.<address>; import.py only recognizes a plain `.text` before `glabel`. The function's .lit4 constants, if it
has any, are appended. Nothing else changes, so the permuter's target is the original code.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, re, shlex, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ASM = ROOT / 'asm' / 'SLUS_213.76' / 'nonmatchings'


def prepare(name):
    source = ASM / (name + '.s')
    if not source.is_file():
        raise SystemExit('%s: no assembly under asm/SLUS_213.76/nonmatchings; run `python3 tools/setup.py` first' % name)
    text = re.sub(r'^\s*\.section\s+\.text\.[0-9A-Fa-f]+[^\n]*$', '.text', source.read_text(), flags=re.M)
    lit4 = ASM / (name + '.lit4.s')
    if lit4.is_file():
        text += '\n' + lit4.read_text()
    out = ROOT / 'build' / 'permuter' / (name + '.s')
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(text)
    sys.path[:0] = [str(ROOT/'tools/build'),str(ROOT/'tools/permuter')]
    from splits import load_splits
    from cc import recipe
    addr = int(name[-8:],16)
    owner = next(s.src for s in load_splits() if s.start <= addr < s.end)
    split = recipe(owner)
    flags = [f for f in split.flags if f.startswith(('-D','-U'))]
    settings = out.with_suffix('.toml')
    commands = dict(compiler_type='gcc',
        compiler_command=shlex.join(['python3','tools/permuter/cc.py','--file',owner,'-Iinclude']+flags),
        assembler_command=shlex.join(['python3','tools/permuter/as.py','--file',owner]),
        asm_prelude_file='tools/permuter/prelude.inc',
        objdump_command='mipsel-linux-gnu-objdump -drz -m mips:5900')
    # Upstream's macro-preserving preprocessor also retains inline assembly as
    # literal pragmas. NULL's ordinary pointer type enables that standard path.
    settings.write_text('\n'.join(k+' = '+json.dumps(v) for k,v in commands.items())+
                        '\n\n[preserve_macros]\n"NULL" = "void *"\n')
    return out


def main(args):
    if len(args) != 1:
        raise SystemExit(__doc__)
    m = re.fullmatch(r'(?:func_|0x)?([0-9A-Fa-f]{1,8})', args[0])
    if not m:
        raise SystemExit('expected func_XXXXXXXX or an address')
    name = 'func_%08X' % int(m.group(1), 16)
    out = prepare(name)
    print('wrote %s\nUse python3 tools/permuter/import.py --settings %s DRAFT.c %s (C++ parsing is a known limitation).' % (out.relative_to(ROOT),out.with_suffix('.toml').relative_to(ROOT),out.relative_to(ROOT)))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
