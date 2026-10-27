#!/usr/bin/env python3
"""Regenerate docs/tools.md, the index of the tools, from the docstring of every tool.

Usage: tools_index.py [--check]       --check only reports whether docs/tools.md is current (exit status 1 if not)
The sections and the order of the tools are listed here (everyday tools first); a tool that no section lists is reported and must
be added below. The purpose of each tool is the first sentence of its module docstring.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import ast, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / 'docs' / 'tools.md'

SECTIONS = [
    ('Everyday tools: working on a function', [
        'setup.py', 'next.py', 'brief.py', 'decompile.py', 'objdiff.py', 'trysrc.py', 'autodecomp.py', 'where.py', 'split_function.py', 'relocate_sources.py', 'permuter/prepare.py', 'permuter/cc.py',
        'permuter/as.py', 'permuter/import.py', 'permuter/abi.py']),
    ('Everyday tools: build, check and progress', [
        'container.py', 'toolchain.py', 'compile.py', 'check_versions.py', 'check_elf.py', 'diffelf.py', 'objdump.py', 'progress.py',
        'badges.py', 'tools_index.py']),
    ('Build internals (`tools/build/`)', [
        'build/check_graph.py', 'build/graph_io.py', 'build/ninja_graph.py', 'build/prepare.py', 'build/inventory.py', 'build/object_graph.py', 'build/object_compile.py', 'build/unit_link.py', 'build/unit_compare.py', 'build/asm_syntax.py', 'build/split_objects.py',
        'build/splat_config.py', 'build/make_ld.py', 'build/link_support.py', 'build/pack_elf.py', 'build/elf_layout.py',
        'build/elfinfo.py', 'build/elfobj.py', 'build/include_asm.py', 'build/splits.py', 'build/units.py',
        'build/units_verify.py', 'build/layout.py', 'build/text_placement.py', 'build/constant_relocs.py',
        'build/source_data.py', 'build/ownership.py', 'build/preflight.py', 'build/assembler.py', 'build/patch_ps2eeas.py', 'build/fixasm.py',
        'build/build_telemetry.py', 'build/tus.py', 'build/linkonce_owners.py', 'build/boundaries.py']),
    ('Automatic pipeline (`tools/pipeline/`)', [
        'pipeline/tu_files.py', 'pipeline/m2c_input.py', 'pipeline/m2c_wrap.py', 'pipeline/ee_prep.py', 'pipeline/vu0_m2c.py',
        'pipeline/vu0_micro.py', 'pipeline/stack_context.py', 'pipeline/context_recovery.py',
        'pipeline/compiler_dumps.py']),
    ('Maintainer and analysis tools (`tools/maint/`)', [
        'maint/class_skeletons.py', 'maint/rtti_evidence.py',
        'maint/shift_test.py', 'maint/handbook_controls.py', 'maint/symbols.py', 'maint/discs.py', 'maint/iso.py', 'maint/inputs.py']),
]
NOTES = {
    'check_elf.py': 'Build check, run by `ninja`.',
    'diffelf.py': 'Convenience script; binutils `readelf` and `objdump` work too.',
    'objdump.py': 'Convenience script; binutils `mipsel-linux-gnu-objdump` and `readelf` work too.',
}
INTRO = '''# Tools

Every tool answers `--help`. One-line purposes are taken from each tool's docstring; this file is written by
`python3 tools/tools_index.py`.

A contributor needs the first two sections, which are the files directly in `tools/` (and `tools/permuter/`). `ninja` runs the
build internals itself, the automatic pipeline is reached through `tools/autodecomp.py`, and the maintainer tools regenerate
committed data. Tools import each other by bare module name; every tool puts `tools/` and its subdirectories on `sys.path`.
'''


def purpose(path):
    doc = ast.get_docstring(ast.parse(path.read_text())) or ''
    text = ' '.join(doc.strip().split('\n\n')[0].split())
    for i, ch in enumerate(text):
        if ch == '.' and (i + 1 == len(text) or text[i + 1] == ' ') and not text[:i].endswith(('e.g', 'i.e')):
            return text[:i + 1]
    return text


def row(rel, path):
    name = Path(rel).name
    extra = NOTES.get(name)
    text = purpose(path) + (' ' + extra if extra else '')
    return '| `tools/%s` | %s |' % (rel, text.replace('|', '\\|'))


def render():
    listed = {rel for _, tools in SECTIONS for rel in tools}
    missing = sorted(p.name for p in (ROOT / 'tools').glob('*.py') if p.name not in listed)
    for sub in ('permuter', 'build', 'pipeline', 'maint'):
        missing += sorted('%s/%s' % (sub, p.name) for p in (ROOT / 'tools' / sub).glob('*.py') if '%s/%s' % (sub, p.name) not in listed)
    if missing:
        raise SystemExit('tools not listed in tools/tools_index.py: ' + ', '.join(missing))
    out = [INTRO]
    for title, tools in SECTIONS:
        out += ['## %s\n' % title, '| Tool | Purpose |', '| --- | --- |']
        out += [row(rel, ROOT / 'tools' / rel) for rel in tools if (ROOT / 'tools' / rel).is_file()]
        out.append('')
    return '\n'.join(out) + '\n'


def main():
    text = render()
    if '--check' in sys.argv:
        current = OUTPUT.read_text() if OUTPUT.exists() else ''
        print('docs/tools.md is current' if current == text else 'docs/tools.md is out of date; run tools/tools_index.py')
        return 0 if current == text else 1
    OUTPUT.write_text(text)
    print('wrote docs/tools.md')
    return 0


if __name__ == '__main__':
    sys.exit(main())
