#!/usr/bin/env python3
"""Write the assembly of one function in the plain form decomp-permuter's import.py reads.

Usage: prepare.py func_XXXXXXXX|0xADDRESS      writes build/permuter/func_XXXXXXXX.s and prints the next commands
The split assembly (asm/SLUS_213.76/nonmatchings/func_XXXXXXXX.s, after the first `ninja`) puts the code in a section
named .text.<address>; import.py only recognizes a plain `.text` before `glabel`. The function's .lit4 constants, if it
has any, are appended. Nothing else changes, so the permuter's target is the original code.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ASM = ROOT / 'asm' / 'SLUS_213.76' / 'nonmatchings'


def prepare(name):
    source = ASM / (name + '.s')
    if not source.is_file():
        raise SystemExit('%s: no assembly under asm/SLUS_213.76/nonmatchings; run `ninja` once first' % name)
    text = re.sub(r'^\s*\.section\s+\.text\.[0-9A-Fa-f]+[^\n]*$', '.text', source.read_text(), flags=re.M)
    lit4 = ASM / (name + '.lit4.s')
    if lit4.is_file():
        text += '\n' + lit4.read_text()
    out = ROOT / 'build' / 'permuter' / (name + '.s')
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(text)
    return out


def main(args):
    if len(args) != 1:
        raise SystemExit(__doc__)
    m = re.fullmatch(r'(?:func_|0x)?([0-9A-Fa-f]{1,8})', args[0])
    if not m:
        raise SystemExit('expected func_XXXXXXXX or an address')
    name = 'func_%08X' % int(m.group(1), 16)
    out = prepare(name)
    print('wrote %s\nnext: python3 .venv/decomp-permuter/import.py src/<library>/<file> %s' % (out.relative_to(ROOT), out.relative_to(ROOT)))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
