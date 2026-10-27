#!/usr/bin/env python3
"""Preserve PS2 scalar typedef attributes across decomp-permuter parser round trips."""
import base64
import re

# These are target ABI names, including the aliases used by hand-written headers.
WIDE_TYPES = {'s128', 'u128', 'EeS128', 'EeU128'}
TYPEDEF = re.compile(r'(?P<skip>"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*.*?\*/|^[ \t]*\#[^\n]*)'
                     r'|(?P<typedef>\btypedef\s+[^;{}]+;)', re.M | re.S)
ATTRIBUTE = re.compile(r'__attribute__\s*\(\(.*\)\)', re.S)


def preserve_typedefs(source):
    """Opaque compiler declarations paired with parser-only views, using upstream pragmas.

    Upstream both stubs attributes during preprocessing and drops them in its AST
    printer. Keeping the attribute text alone therefore does not protect the ABI.
    """
    def protect(match):
        if match.group('skip') is not None:
            return match.group()
        declaration = match.group()
        plain = ATTRIBUTE.sub('', declaration)
        name = re.search(r'\b(\w+)\s*;\s*$', plain)
        if not name:
            return declaration
        name = name[1]
        wide = name in WIDE_TYPES or bool(re.search(r'\bmode\s*\(\s*(?:TI|__TI__)\s*\)', declaration))
        if '__attribute__' not in declaration and not wide:
            return declaration
        compiler = declaration
        if wide:
            compiler += '\ntypedef char PermuterSize_%s[sizeof(%s) == 16 ? 1 : -1];' % (name, name)
        encoded = base64.b64encode(compiler.encode()).decode()
        return ('\n#pragma _permuter latedefine start\n' + plain +
                '\n#pragma _permuter latedefine end\n#pragma _permuter b64literal ' + encoded + '\n')
    # Reapplying this to a seed must not wrap its parser-only declarations again.
    chunks = re.split(r'(#pragma _permuter latedefine start.*?#pragma _permuter latedefine end)', source, flags=re.S)
    return ''.join(chunk if i % 2 else TYPEDEF.sub(protect, chunk) for i, chunk in enumerate(chunks))


if __name__ == '__main__':
    print(__doc__)
