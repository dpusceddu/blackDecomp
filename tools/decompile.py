#!/usr/bin/env python3
"""Friendly front door for one function: an m2c draft, ready to replace its INCLUDE_ASM line, and where to put it.

Usage: decompile.py func_XXXXXXXX|0xADDRESS [--write] [--ctx ctx.c] [--raw]
Prints the translation unit file and line holding the function's INCLUDE_ASM marker, then a C draft made by m2c with the
project's context (recovered prototypes and layouts, EE preprocessing) and the mechanical cleaning that `autodecomp.py`
applies; nothing is compiled here. With --write the marker line is replaced by the draft (declarations the draft needs are
added after the file's #include lines); then run `ninja` and compare in objdiff (`ninja objdiff`, see CONTRIBUTING.md).
A function that already has a draft in an `#ifdef NON_MATCHING` block is replaced as a whole. --raw prints m2c's own output
without the cleaning, which is also what you get when the cleaning gives up (the reason is printed).
Needs one finished `ninja` (the per-function assembly under asm/) and `pip install -r requirements.txt` (m2c). The first
run recovers the context from the committed headers and configuration (about a minute; it works on a fresh checkout) and
writes it to the ignored build/auto/; later runs reuse build/auto/ctx.c. `python3 tools/autodecomp.py context --refresh` renews
it after shared headers change. The only tracked file this tool ever changes is the translation unit file named by --write;
the committed headers under include/ are hand-maintained source and are never rewritten here.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import argparse, re, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
import include_asm
import splits as S

ROOT = S.ROOT
SLUG = S.DEFAULT_SLUG


def parse_target(text):
    """Address of `func_00100258`, `0x100258` or a bare hexadecimal number."""
    m = re.fullmatch(r'(?:func_|0x)?([0-9A-Fa-f]{1,8})', text.strip())
    if not m:
        raise SystemExit('expected func_XXXXXXXX or an address, got %r' % text)
    return int(m.group(1), 16)


def locate(addr):
    """(split, path, line) of the INCLUDE_ASM marker of the function, or None when no source file lists it as assembly.

    Two files may cover the same range (a broad file and a narrower one carved out of it for other flags or language,
    docs/units.md); the function belongs to the narrowest file that lists it."""
    name = 'func_%08X' % addr
    found = []
    for split in S.load_splits(SLUG):
        if not split.start <= addr < split.end:
            continue
        path = ROOT / split.src
        if not path.is_file():
            continue
        for marker in include_asm.markers(path.read_text(), split.defines()):
            if marker.name == name:
                found.append((split.end - split.start, split, path, marker.line))
                break
    if not found:
        return None
    _, split, path, line = min(found, key=lambda f: f[0])
    return split, path, line


def draft(addr, ctx):
    """(function record, m2c result, cleaned source or None, note). The note is the signature, or why cleaning gave up."""
    import os
    auto = ROOT / 'build' / 'auto'
    if all((auto / n).is_file() for n in ('context.json', 'ctx.c', 'recovered_layouts.c')):
        # reuse the recovered context of the last run instead of recovering it again (a minute)
        os.environ.setdefault('AUTODECOMP_FREEZE_CONTEXT', '1')
    import autodecomp as A
    inventory = A.load_inventory()
    f = next((x for x in inventory if x['addr'] == addr), None)
    if f is None:
        raise SystemExit('func_%08X is not a function of the image' % addr)
    if A.is_orphan(f['words']) or f['size'] <= 4:
        raise SystemExit('func_%08X is not a real function (an orphan piece or a single instruction between functions)' % addr)
    A.write_context()
    A.write_context_arity(inventory)
    result = A.run_m2c([f], ctx=ctx)[f['name']]
    source, note = A.clean_function(f['name'], result, {}, f.get('strings'))
    if source is None and note.startswith('stack-object'):
        from stack_context import detect_frame_size
        frame = detect_frame_size(f['words'])
        for n in sorted({frame - 16 - 8 * j for j in range(9)} | {16, 32}) if frame is not None else ():
            if n > 0 and (alt := A.clean_function(f['name'], result, {}, f.get('strings'), stack=n))[0]:
                source, note = alt
                break
    if source is None and (idiom := A.idiom_source(f)):
        source, note = idiom[0], 'idiom'
    return f, result, source, note


def split_draft(name, source):
    """(declaration lines, function text) of a cleaned draft."""
    import autodecomp as A
    return A.split_source(dict(source=source, name=name))


def write(path, name, decls, code):
    import tu_files
    path.write_text(tu_files.insert_declarations(include_asm.replace(path.read_text(), name, code.rstrip('\n')), decls))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('function', help='func_XXXXXXXX or an address (0x...)')
    ap.add_argument('--write', action='store_true', help='replace the INCLUDE_ASM line in its translation unit file')
    ap.add_argument('--ctx', default='ctx.c', help='m2c context in build/auto/ (ctx.c, ctx2.c, ctx3.c, ctx_void.c)')
    ap.add_argument('--raw', action='store_true', help="print m2c's output without the mechanical cleaning")
    a = ap.parse_args(argv)
    addr = parse_target(a.function)
    name = 'func_%08X' % addr
    if not (ROOT / 'asm' / SLUG / 'nonmatchings' / (name + '.s')).is_file():
        raise SystemExit('%s: no assembly under asm/%s/nonmatchings; run `ninja` once first' % (name, SLUG))
    found = locate(addr)
    if found is None:
        raise SystemExit('%s is not an INCLUDE_ASM line of any source file: it is already recovered (see `python3 tools/next.py tus`)' % name)
    split, path, line = found
    f, result, source, note = draft(addr, a.ctx)
    rel = path.relative_to(ROOT).as_posix()
    print('// %s: %s line %d, %d bytes, compiler %s %s' % (name, rel, line, f['size'], split.compiler, ' '.join(split.flags)))
    if rel.endswith(('.cpp', '.cc')):
        print('// note: the file is C++; the draft is C and may need methods, references or extern "C" declarations')
    if a.raw or source is None:
        if source is None:
            print('// the cleaning gave up: %s' % note)
        if result.get('body') is None:
            print('// m2c produced no code for this function')
            return 1
        print('%s %s(%s) {\n%s\n}' % (result['ret'], name, result['params'], result['body']))
        if a.write:
            print('// not written: this is raw m2c output', file=sys.stderr)
        return 1 if source is None else 0
    decls, code = split_draft(name, source)
    decls = [d for d in decls if d.strip() and not re.match(r'^extern .*\b%s\b' % name, d)]
    if decls:
        print('// declarations the draft uses (added to the file by --write):')
        print('\n'.join(decls))
        print()
    print(code, end='')
    if a.write:
        write(path, name, decls, code)
        print('// wrote %s; now run `ninja`' % rel)
    else:
        print('// replace line %d of %s with this (or run again with --write), then run `ninja`' % (line, rel))
    return 0


if __name__ == '__main__':
    sys.exit(main())
