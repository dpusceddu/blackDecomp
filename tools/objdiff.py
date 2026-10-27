#!/usr/bin/env python3
"""Generate a per-object objdiff project, build one comparison view, or write a fresh report.

The GUI runs `ninja build/<version>/objdiff/base/<unit>.o`; it never links the
image. Assembly-backed functions stay in the linked object but are removed from
the comparison base, so progress measures recovered source only.
"""
import argparse
import json
from pathlib import Path
import re
import subprocess
import struct
import sys
sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
from elfinfo import Elf
import elfobj
from object_compile import environment

ROOT = Path(__file__).resolve().parents[1]
DEFAULT = 'SLUS_213.76'
OPTIONS = {'demangler': 'gnu_legacy'}

INSTRUCTION = re.compile(r'^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/', re.M)


SECTION = re.compile(r'^\s*\.section\s+(\S+)', re.M)


def code_size(asm_text, addr, span):
    """Bytes of the function's code: from its start to its last `endlabel` in the text section, without the alignment
    padding that follows (the compiler's own symbol size does not include the padding either). A function with switch
    cases has several labelled fragments, hence the last one. `span` (up to the next function) is the fallback."""
    text = asm_text
    for m in SECTION.finditer(asm_text):
        if not m.group(1).strip(',"').startswith('.text'):
            text = asm_text[:m.start()]
            break
    end = text.rfind('\nendlabel')
    if end < 0:
        return span
    last = [int(m.group(1), 16) for m in INSTRUCTION.finditer(text[:end])]
    return min(span, last[-1] + 4 - addr) if last else span


ABSOLUTE = re.compile(r'^(D_[0-9A-Fa-f]+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', re.M)
NAME = re.compile(r'\bD_[0-9A-Fa-f]+\b')


def numeric_names(text, constants):
    """The assembly with the numeric names (`%lo(D_10F00)`) replaced by their values: the original code holds the number,
    and an assembler would still emit a relocation against the name."""
    def value(m):
        v = constants.get(m.group(2))
        if v is None:
            return m.group(0)
        lo = (v & 0xFFFF) - 0x10000 if v & 0x8000 else v & 0xFFFF
        return str(lo) if m.group(1) == 'lo' else '%#x' % (((v - lo) >> 16) & 0xFFFF)
    return re.sub(r'%(hi|lo)\((D_[0-9A-Fa-f]+)\)', value, text)


def absolute_symbols(slug):
    """Numeric constants the split assembly names like data (`%lo(D_10F00)`), from the linker symbols of the build: the
    original code holds the number, not a relocation, so the target object must define the name as a number too."""
    path = ROOT / 'build' / slug / 'symbols.ld'
    return {m.group(1): int(m.group(2), 16) for m in ABSOLUTE.finditer(path.read_text())} if path.is_file() else {}


DATA_SECTIONS = ('.rodata', '.lit4', '.lit8', '.sdata', '.sbss', '.data', '.bss', '.gcc_except_table')
DATA_NAME = re.compile(r'\bD_([0-9A-Fa-f]{8})\b')


def data_slots(slug):
    """{unit name: {section: address}}: where the link places each data section of a compiled unit. The build renames them
    to `<section>.<ADDRESS>` (build/<GAME_ID>/plan.json); the address is that of the original data the unit replaces."""
    path = ROOT / 'build' / slug / 'plan.json'
    slots = {}
    for entry in json.loads(path.read_text()).get('rename', []) if path.is_file() else []:
        unit = entry['obj'][len('obj/units/'):-len('.o')]
        for old, new in entry['sections'].items():
            key = new[len(old) + 1:]
            if old in DATA_SECTIONS and new.startswith(old + '.') and re.fullmatch(r'[0-9A-Fa-f]{8}', key):
                slots.setdefault(unit, {})[old] = int(key, 16)
    return slots


def local_data_symbols(texts, slots, sizes, known):
    """{name: (section, offset)} for the data the unit's own functions refer to by address name (`D_003F7150`) that the
    compiler keeps in a section of the unit's object: the object has no symbol there, so its reference would read
    `.rodata+0x8`, which objdiff does not equate with the original's name."""
    found = {}
    for text in texts:
        for m in DATA_NAME.finditer(text):
            name, address = m.group(0), int(m.group(1), 16)
            if name in known or name in found:
                continue
            for section, key in slots.items():
                if key <= address < key + sizes.get(section, 0):
                    found[name] = (section, address - key)
                    break
    return found



def unit_plan(slug):
    """One comparison unit for each ordinary source object."""
    build = ROOT / 'build' / slug
    objects = json.loads((build / 'unit_objects.json').read_text())
    return [dict(name=o['unit']['name'], library=o['unit']['library'], source=o['src'],
                 base_in='obj/'+o['name']+'.o', functions=o['unit']['functions'],
                 complete=all(f['status']=='source' for f in o['unit']['functions']))
            for o in objects if o['kind']=='cc']


def write_project(slug, plan):
    libraries = sorted({u['library'] for u in plan})
    units = [dict(name=u['library']+'/'+u['name'],
                  target_path='build/%s/objdiff/target/%s.o' % (slug,u['name']),
                  base_path='build/%s/objdiff/base/%s.o' % (slug,u['name']),
                  metadata=dict(source_path=u['source'], complete=u['complete'], progress_categories=[u['library']])) for u in plan]
    project = {'$schema':'https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json',
               'min_version':'3.0.0','custom_make':'ninja','custom_args':[], 'build_target':False, 'build_base':True,
               'watch_patterns':['src/**/*.c','src/**/*.cpp','include/**/*'], 'options':OPTIONS,
               'progress_categories':[dict(id=l,name=l) for l in libraries], 'units':units}
    local = ROOT / '.local/objdiff.json'
    if local.is_file():
        override = json.loads(local.read_text())
        for key in ('custom_make','custom_args'):
            if key in override:
                project[key] = override[key]
    (ROOT/'objdiff.json').write_text(json.dumps(project,indent=2)+'\n')
    return len(units)


def build_view(spec_path, output):
    spec = json.loads(Path(spec_path).read_text())
    raw_path = Path(output).parents[2] / 'obj' / (spec['name']+'.o')
    raw = raw_path.read_bytes()
    state = json.loads(Path(str(raw_path)+'.json').read_text())
    source = Elf(raw)
    symbols = source.symbols()
    present = {s['name'] for s in symbols}
    slug = raw_path.parts[1]
    from progress import orphan_pieces
    placement = json.loads((ROOT/'build'/slug/'placement.json').read_text())
    orphans = orphan_pieces(slug, placement['functions'])
    functions, lines, texts, keep, redefine, renames = [], [], [], set(), {}, {}
    constants = absolute_symbols(slug)
    for f in spec['unit']['functions']:
        if f['addr'] in orphans:
            continue
        label = 'func_%08X' % f['addr']
        original = ROOT/'asm'/slug/'nonmatchings'/(label+'.s')
        text = original.read_text()
        size = code_size(text,f['addr'],f['size'])
        texts.append(text)
        lines += [numeric_names(text,constants), '.type %s, @function' % label, '.size %s, %d' % (label,size)]
        r = state['resolved'].get(str(f['addr']))
        if r and r['status']=='source':
            keep.add(r['section'])
            redefine[r['link_name']] = label
            if r['section'].startswith('.text.'):
                renames[r['section']] = '.text.'+label
    # Retain compiler data, but remove assembly inputs and discarded context.
    keep.update(sec for sec in DATA_SECTIONS if source.section(sec))
    keep.update(item['input'] for item in spec['unit'].get('data_ranges', []))
    # A retained table may point into an included function through a local
    # section symbol. Keep that symbolic reference when removing assembly from
    # the comparison base: its public function entry denotes the same zero base.
    edited = bytearray(raw)
    by_name = {s['name']:i for i,s in enumerate(symbols)}
    assembly_sections = {source.section(r['section'])['index']:by_name[r['link_name']]
                         for r in state['resolved'].values() if r['status']=='asm'}
    for relocation in source.sections:
        if relocation['type'] != 9:
            continue
        for offset in range(relocation['offset'],relocation['offset']+relocation['size'],8):
            info = struct.unpack_from('<I',edited,offset+4)[0]
            symbol = symbols[info>>8]
            replacement = assembly_sections.get(symbol['shndx'])
            if symbol['type']==3 and replacement is not None:
                if symbols[replacement]['value'] != 0:
                    raise ValueError('included function does not start its input section')
                struct.pack_into('<I',edited,offset+4,replacement<<8 | (info&255))
    edited, _ = elfobj.undefine_dropped(bytes(edited), keep)
    output = Path(output)
    output.parent.mkdir(parents=True,exist_ok=True)
    output.write_bytes(edited)
    base, env = environment()
    args = [env['BLACK_BINUTILS_PREFIX']+'objcopy']
    for s in source.sections:
        if s['flags'] & 2 and s['name'] not in keep:
            args += ['--remove-section='+s['name']]
    # Original-name references and per-unit compiler bindings share canonical names.
    for s in symbols:
        m = re.fullmatch(r'(.+)\$([0-9A-F]+)',s['name'])
        if m and s['name'] not in redefine:
            addr = int(m[2],16)
            name = ('func_%08X' if any(f['addr']==addr for f in placement['functions']) else 'D_%08X') % addr
            if name not in present:
                redefine[s['name']] = name
    # Several C++ declarations can bind the same original function. objcopy
    # rejects duplicate rename targets, so first merge their relocation uses.
    groups = {}
    for old,new in redefine.items():
        groups.setdefault(new,[]).append(old)
    redirects = {}
    for new,old_names in groups.items():
        if len(old_names)<2:
            continue
        primary = next((n for n in old_names if symbols[by_name[n]]['shndx']),old_names[0])
        for name in old_names:
            if name!=primary:
                redirects[by_name[name]]=by_name[primary]
                del redefine[name]
    if redirects:
        data=bytearray(output.read_bytes())
        for relocation in source.sections:
            if relocation['type']==9:
                for offset in range(relocation['offset'],relocation['offset']+relocation['size'],8):
                    info=struct.unpack_from('<I',data,offset+4)[0]
                    if info>>8 in redirects:
                        struct.pack_into('<I',data,offset+4,redirects[info>>8]<<8 | (info&255))
        output.write_bytes(data)
    args += ['--redefine-sym=%s=%s' % x for x in redefine.items() if x[0]!=x[1]]
    args += ['--rename-section=%s=%s' % x for x in renames.items() if x[0]!=x[1]]
    slots = {sec:min(a for a,b,addr in intervals if state['resolved'].get(str(addr),{}).get('status')=='source')
             for sec,intervals in spec.get('slots',{}).items()
             if any(state['resolved'].get(str(addr),{}).get('status')=='source' for a,b,addr in intervals)}
    sizes = {s['name']:s['size'] for s in source.sections}
    local = local_data_symbols(texts,slots,sizes,present | set(redefine.values()))
    args += ['--add-symbol=%s=%s:%d,global,object' % (n,sec,off) for n,(sec,off) in local.items()]
    subprocess.run(args+[str(output)],env=env,check=True)
    output.write_bytes(elfobj.literal_as_gprel(output.read_bytes()))
    target = output.parent.parent/'target'/output.name
    target.parent.mkdir(parents=True,exist_ok=True)
    assembly = target.with_suffix('.s')
    assembly.write_text('\n'.join(lines)+'\n')
    subprocess.run([str(base/'compilers/ee-gcc2.96/ee/bin/as'),'-I','include','-o',str(target),str(assembly)],env=env,check=True)
    target.write_bytes(elfobj.copy_header_flags(target.read_bytes(),raw))


def report(slug):
    import toolchain
    cli = toolchain.root() / 'bin' / 'objdiff-cli'
    if not cli.is_file():
        raise SystemExit('objdiff-cli is not installed; run: python3 tools/toolchain.py install --objdiff')
    output = ROOT / 'build' / slug / 'report.json'
    subprocess.run([str(cli), 'report', 'generate', '-p', str(ROOT), '-o', str(output), '-f', 'json-pretty'], check=True)
    data = json.loads(output.read_text())
    m = data.get('measures', {})
    print('report: %s' % output.relative_to(ROOT))
    for key in ('fuzzy_match_percent', 'matched_code_percent', 'matched_functions_percent', 'complete_code_percent'):
        if key in m:
            print('  %-26s %s' % (key, m[key]))
    for key in ('total_code', 'matched_code', 'total_functions', 'matched_functions', 'complete_code', 'total_units', 'complete_units'):
        if key in m:
            print('  %-26s %s' % (key, m[key]))



def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('version',nargs='?',default=DEFAULT)
    ap.add_argument('--report',action='store_true')
    ap.add_argument('--project',action='store_true',help='write only objdiff.json')
    ap.add_argument('--report-only',action='store_true',help='report from existing comparison objects')
    ap.add_argument('--unit',help='build the view of this generated object specification')
    ap.add_argument('--output')
    a=ap.parse_args()
    if a.unit:
        build_view(a.unit,a.output)
        return
    if a.version!=DEFAULT:
        ap.error('source units apply to '+DEFAULT+' only')
    import preflight
    preflight.require(a.version)
    if a.report_only:
        report(a.version)
        return
    plan=unit_plan(a.version)
    write_project(a.version,plan)
    if a.project:
        return
    result = subprocess.run(['ninja','objdiff_objects'])
    if result.returncode:
        raise SystemExit(result.returncode)
    if a.report:
        report(a.version)


if __name__=='__main__':
    main()
