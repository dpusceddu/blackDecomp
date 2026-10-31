#!/usr/bin/env python3
"""Preserve PS2 typedef attributes across decomp-permuter parser round trips."""
import base64
import re

# These are target ABI names, including the aliases used by hand-written headers.
WIDE_TYPES = {'s128', 'u128', 'EeS128', 'EeU128'}
TOKEN = re.compile(r'(?P<skip>"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*.*?\*/|^[ \t]*\#[^\n]*)'
                   r'|\btypedef\b|[{};]', re.M | re.S)
ATTRIBUTE = re.compile(r'\b__attribute__\s*\(\(')


def without_attributes(declaration):
    """Remove balanced attributes only from the parser's view of a declaration."""
    out, at = [], 0
    for match in ATTRIBUTE.finditer(declaration):
        if match.start() < at:
            continue
        out.append(declaration[at:match.start()])
        depth, at = 2, match.end()
        while at < len(declaration) and depth:
            depth += (declaration[at] == '(') - (declaration[at] == ')')
            at += 1
    return ''.join(out) + declaration[at:]


def typedefs(source):
    """Locate whole typedefs, including aggregate bodies and nested field semicolons."""
    start, depth = None, 0
    for token in TOKEN.finditer(source):
        if token.group('skip') is not None:
            continue
        value = token.group()
        if start is None:
            if value == 'typedef':
                start = token.start()
        elif value == '{':
            depth += 1
        elif value == '}':
            depth -= 1
        elif value == ';' and depth == 0:
            yield start, token.end()
            start = None


def preserve_typedefs(source):
    """Opaque compiler declarations paired with parser-only views, using upstream pragmas.

    Upstream both stubs attributes during preprocessing and drops them in its AST
    printer. Keeping the attribute text alone therefore does not protect the ABI.
    """
    def protect(declaration):
        plain = without_attributes(declaration)
        name = re.search(r'\b(\w+)\s*;\s*$', plain)
        if not name:
            return declaration
        name = name[1]
        wide = name in WIDE_TYPES or ('{' not in plain and bool(
            re.search(r'\bmode\s*\(\s*(?:TI|__TI__)\s*\)', declaration)))
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
    def rewrite(chunk):
        out, at = [], 0
        for start, end in typedefs(chunk):
            out.extend((chunk[at:start], protect(chunk[start:end])))
            at = end
        return ''.join(out) + chunk[at:]
    return ''.join(chunk if i % 2 else rewrite(chunk) for i, chunk in enumerate(chunks))


if __name__ == '__main__':
    print(__doc__)
