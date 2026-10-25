#!/usr/bin/env python3
"""Translate EE function includes for the selected assembler, preserving symbolic relocations.

SN uses expanded labels (no splat macros or .size), fixed encodings for ordinary
instructions, and explicit symbolic-word records for GP and direct-jump fixups.
Old GNU and SN both use symbolic GP records, independent of the file's -G threshold.
"""
import re

ITEM = re.compile(r'^(\s*/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/\s*)(.*)$')
LABEL = re.compile(r'^\s*(?:glabel|alabel|jlabel|dlabel|ehlabel)\s+(\S+)')
GP = re.compile(r'gp_rel: \((\w+)(?:\s*\+\s*(0x[0-9a-fA-F]+))?\)')


def translate(text, sn=False):
    """Return assembler syntax and the linker aliases used by GP addends."""
    out, aliases, seen = [], {}, set()
    function = None
    for line in text.splitlines():
        if line.startswith('.include "macro.inc"') or line.lstrip().startswith(('endlabel ', 'enddlabel ')):
            continue
        if line.startswith('.section .text.'):
            function = 'func_'+line.split()[1].split('.')[-1].rstrip(',')
            line = '.section .text.'+function+', "ax"'
        label = LABEL.match(line)
        if label:
            name = label[1]
            if name not in seen:
                seen.add(name)
                out += ['.globl '+name, name+':']
                if name == function:
                    out += ['.globl __nonmatching_'+name, '__nonmatching_'+name+':']
            continue
        if sn and line.strip() == '.set nomacro':
            line = '.set macro'
        m = ITEM.match(line)
        if m:
            word = int.from_bytes(bytes.fromhex(m[2]), 'little')
            instruction = m[3].strip()
            address = m[1].split()[2]
            gp = GP.search(instruction)
            jump = re.match(r'(?:jal|j)\s+(\w+)', instruction)
            if gp:
                target = gp[1]
                if gp[2]:
                    alias = target+'_add_'+gp[2][2:]
                    aliases[alias] = target+' + '+gp[2]
                    target = alias
                marker = '__gprel_%08X_%s' % (word & 0xffff0000, address)
                out += ['.globl '+marker, marker+':']
                line = m[1]+'.word '+target
            elif sn and jump:
                marker = '__jump_%08X_%s' % (word & 0xfc000000, address)
                out += ['.globl '+marker, marker+':']
                line = m[1]+'.word '+jump[1]
            elif sn and instruction.startswith('.float'):
                line = m[1]+'.word 0x%08X' % word
            elif sn and not re.search(r'%(?:hi|lo)\(|\.(?:word|float|double|byte|ascii|space)', instruction):
                line = m[1]+'.word 0x%08X' % word
        out.append(line)
    # Do not leak assembler state into the compiler output after this include.
    out += ['.text', '.set reorder', '.set at', '.set macro']
    return '\n'.join(out)+'\n', aliases


if __name__ == '__main__':
    import argparse
    argparse.ArgumentParser(description=__doc__).parse_args()
