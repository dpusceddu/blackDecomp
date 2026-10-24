#!/usr/bin/env python3
"""Regenerate docs/tools.md, the index of the tools, from the docstring of every tool.

Usage: tools_index.py [--check]       --check only reports whether docs/tools.md is current (exit status 1 if not)
The sections and the order of the tools are listed here; a tool in tools/ that no section lists is reported and must be added
below. The purpose of each tool is the first sentence of its module docstring.
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
    ('Build', [
        'backend.py', 'toolchain.py', 'sandbox.py', 'compile.py', 'build_objects.py', 'build_job.py', 'split_objects.py',
        'splat_config.py', 'make_ld.py', 'link_support.py', 'pack_elf.py', 'elf_layout.py', 'elfobj.py', 'check_elf.py',
        'diffelf.py', 'check_versions.py', 'include_asm.py', 'splits.py', 'tu_files.py', 'units.py', 'units_verify.py',
        'nm_build.py', 'text_placement.py', 'constant_relocs.py', 'source_data.py', 'assembler.py', 'patch_ps2eeas.py',
        'boundaries.py', 'fixasm.py']),
    ('Working on a function', [
        'decompile.py', 'objdiff.py', 'objdiff_job.py', 'trysrc.py', 'permuter/prepare.py', 'permuter/cc.py', 'permuter/as.py',
        'next.py']),
    ('Progress and reports', ['progress.py', 'badges.py', 'build_telemetry.py', 'tools_index.py']),
    ('Matching pipeline', [
        'autodecomp.py', 'm2c_input.py', 'm2c_wrap.py', 'ee_prep.py', 'vu0_m2c.py', 'vu0_micro.py', 'stack_context.py',
        'shared_context.py', 'mod_context.py', 'context_recovery.py', 'permuter_service.py', 'permuter_worker.py',
        'permuter_lanes.py', 'compiler_dumps.py', 'equiv.py']),
    ('Analysis and metadata', [
        'tus.py', 'layout.py', 'class_skeletons.py', 'rtti_evidence.py', 'ghidra_export.py', 'ghidra_types.py', 'symbols.py',
        'discs.py', 'iso.py', 'inputs.py', 'elfinfo.py', 'objdump.py']),
]
MAINTAINER_ONLY = {
    'ghidra_export.py': 'Maintainer only: needs private Ghidra exports; a headless Ghidra script is a possible future improvement.',
    'ghidra_types.py': 'Maintainer only: needs private Ghidra exports; a headless Ghidra script is a possible future improvement.',
}
NOTES = {
    'check_elf.py': 'Build check, run by `ninja`.',
    'diffelf.py': 'Convenience script; binutils `readelf` and `objdump` work too.',
    'objdump.py': 'Convenience script; binutils `mipsel-linux-gnu-objdump` and `readelf` work too.',
}
INTRO = '''# Tools

Every tool answers `--help`. One-line purposes are taken from each tool's docstring; this file is written by
`python3 tools/tools_index.py`.
'''
FOOTER = '''
## Equivalence harness (`tools/eeharness/`)

An EE interpreter and differential-test driver for the `equivalent` evidence tier; see its README.

## Finished studies (`tools/studies/`)

Experiments and one-time migrations whose results are recorded in [history.md](history.md). They are kept for reproducibility and are not part of the normal workflow.
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
    extra = MAINTAINER_ONLY.get(name) or NOTES.get(name)
    text = purpose(path) + (' ' + extra if extra else '')
    return '| `tools/%s` | %s |' % (rel, text.replace('|', '\\|'))


def render():
    listed = {rel for _, tools in SECTIONS for rel in tools}
    missing = sorted(p.name for p in (ROOT / 'tools').glob('*.py') if p.name not in listed)
    missing += sorted('permuter/' + p.name for p in (ROOT / 'tools/permuter').glob('*.py') if 'permuter/' + p.name not in listed)
    if missing:
        raise SystemExit('tools not listed in tools/tools_index.py: ' + ', '.join(missing))
    out = [INTRO]
    for title, tools in SECTIONS:
        out += ['## %s\n' % title, '| Tool | Purpose |', '| --- | --- |']
        out += [row(rel, ROOT / 'tools' / rel) for rel in tools if (ROOT / 'tools' / rel).is_file()]
        out.append('')
    out.append(FOOTER.strip('\n') + '\n')
    studies = sorted((ROOT / 'tools/studies').glob('*.py'))
    out += ['| Tool | Purpose |', '| --- | --- |']
    out += [row('studies/' + p.name, p) for p in studies if p.name != '__init__.py']
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
