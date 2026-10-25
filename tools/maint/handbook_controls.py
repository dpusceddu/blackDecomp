#!/usr/bin/env python3
"""Verify handbook recipes with isolated SN 1.36 retail controls and perturbations.

Recompiles existing source units, resolves their real bindings, and checks retail
instruction equality. Perturbations diagnose a scoped compiler/assembler effect;
they never change the production source or promote a candidate into the build.
Private objects and the reproducible result ledger stay under build/.
"""
import argparse
import hashlib
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import autodecomp as A
import units
import units_verify
from elfinfo import Elf


CONTROLS = {
    'scheduling': 0x1052A0,
    'loop-padding': 0x18C178,
    'switch': 0x18DCE0,
    'gp-data': 0x10BBF8,
    'ee128-vu': 0x17BDF0,
    'vu-fixed-register': 0x3440B8,
    'inline-helper': 0x2D16B8,
    'cleanup': 0x2D6E48,
    'argument-order': 0x1ED9C8,
    'float-return-temporary': 0x30E9C8,
    'volatile-vector-lifetimes': 0x33BA90,
    'address-view-lifetime': 0x3511D0,
    'aggregate-result': 0x33AEE8,
    'native-scalar-temporary': 0x33EB08,
    'loop-index-lifetime': 0x345510,
    'global-reference-view': 0x345DC0,
    'vector-value-lifetimes': 0x2D3300,
    'node-address-order': 0x2D77A0,
    'pool-slot-lifetimes': 0x317C20,
    'native-float-absolute-body': 0x34FB58,
    'native-float-absolute-header': 0x34FC80,
    'scene-alias-and-null': 0x32CDE0,
    'scene-partner-index': 0x32D108,
    'scene-storage-alignment': 0x32BC70,
    'full-tu-context': 0x32DCE8,
    'branch-native-lifetimes': 0x346510,
    'complete-quaternion-difference': 0x346940,
    'overlay-iterator-lifetimes': 0x347600,
    'root-quaternion-view-lifetime': 0x346CB0,
    'commuting-initializer-stores': 0x319ED0,
    'registry-result-branches': 0x319950,
    'pool-failure-result-boundary': 0x317E40,
    'steering-scaled-radius': 0x3059F0,
    'event-positive-branch': 0x1998C0,
}


def flatten(text, parent=ROOT):
    """Inline quoted project headers for an isolated, uncommitted perturbation."""
    def include(match):
        for path in (parent / match[1], ROOT / 'include' / match[1]):
            if path.is_file():
                return flatten(path.read_text(), path.parent)
        raise ValueError('missing quoted header: ' + match[1])
    return re.sub(r'^\s*#\s*include\s+"([^\"]+)"\s*$', include, text, flags=re.M)


def variants(label, source, flags):
    """Controlled departures from known exact source, not universal fixes."""
    if label == 'scheduling':
        yield 'enable-first-scheduler', source, [x for x in flags if x != '-fno-schedule-insns']
    elif label == 'loop-padding':
        yield 'stock-assembler', source, [x for x in flags if not x.startswith('--assembler=')]
        # Preserve iteration count and accesses; change the source induction shape.
        changed = source.replace('var_7 = 0;', 'var_7 = 2;').replace('var_7 += 1;', 'var_7 -= 1;').replace('var_7 < 2U', 'var_7 != 0')
        yield 'count-down', changed, flags
    elif label == 'gp-data':
        yield 'G0', source, ['-G0' if x == '-G8' else x for x in flags]
        changed = source.replace('extern signed char D_0040D9A2;', 'extern signed char D_0040D9A2[];').replace('D_0040D9A2 = 0', 'D_0040D9A2[0] = 0')
        yield 'unsized-extern', changed, flags
    elif label == 'switch':
        start = source.index('    switch (temp_2)')
        changed = source[:start] + '''    if (temp_2 == 36 || temp_2 == 37) return 0x22;
    if (temp_2 == 38) return 0x26;
    if (temp_2 == 39) return 0x33;
    if (temp_2 == 40) return 0x36;
    if (temp_2 == 41) return 0x31;
    if (temp_2 == 42) return 0x2A;
    if (temp_2 == 29) return 0x46;
    if (temp_2 == 30) return 0x47;
    if (temp_2 == 31) return 0x48;
    return 0;
}
'''
        yield 'if-chain', changed, flags
    elif label == 'ee128-vu':
        # Deliberate ABI-negative control: narrowing is not behavior-preserving.
        changed = source.replace('func_0017BDF0(Value point)', 'func_0017BDF0(unsigned long point)').replace('basis,point)', 'basis,(Value)point)')
        yield 'narrow-argument-ABI-negative', changed, flags
    elif label == 'vu-fixed-register':
        first = '    Ps2Math::AnimationMath::Multiply(&out->rotation, &a->rotation, &b->rotation);'
        second = '    Ps2Math::AnimationMath::Add(&out->position, &a->position, &b->position);'
        yield 'independent-operation-order', source.replace(first + '\n' + second, second + '\n' + first), flags
    elif label == 'inline-helper':
        source = flatten(source)
        helper = re.search(r'template<class Entry>\s*static inline bool IsPrivateProperty\(Entry \*entry\)\s*\{.*?\n\}', source, re.S)[0]
        changed = source.replace(helper, 'template<class Entry> static inline bool IsPrivateProperty(Entry *entry);')
        changed += '\nnamespace Ps2Math { namespace Kynapse {\n' + helper + '\n} }\n'
        yield 'definition-after-caller', changed, flags
        old = 'long parsed = func_0035E730(value);\n                    Engine* engine = gEngine;'
        new = 'Engine* engine; long parsed;\n                    parsed = func_0035E730(value); engine = gEngine;'
        if old not in source:
            raise ValueError('declaration-order control source changed')
        yield 'declaration-reordered', source.replace(old, new), flags
    elif label == 'cleanup':
        source = flatten(source)
        changed = source.replace('~ActorIterator() {}', '~ActorIterator();')
        changed += '\nnamespace Kaim { inline ActorIterator::~ActorIterator() {} }\n'
        yield 'destructor-after-caller', changed, flags
        changed = source.replace('for (ActorIterator it(gEngine->actors->head); it.node; ++it)',
                                 'ActorIterator it(gEngine->actors->head);\n    for (; it.node; ++it)')
        yield 'iterator-function-scope', changed, flags
    elif label == 'argument-order':
        source = flatten(source)
        changed = source.replace('RegisterEnvelopeParameter(void *,void *,const char *,const char *,const char *,int,float,float,int)',
                                 'RegisterEnvelopeParameter(float,float,void *,void *,const char *,const char *,const char *,int,int)')
        changed = re.sub(r'RegisterEnvelopeParameter\((D_003C09E8\+4,&\w+,"[^\"]+",name,D_003BDA08),0,0\.0f,0\.0f,0\)',
                         r'RegisterEnvelopeParameter(0.0f,0.0f,\1,0,0)', changed)
        yield 'floats-first', changed, flags
    elif label == 'float-return-temporary':
        yield 'direct-zero-literal', source.replace('= Zero();', '= 0.0f;'), flags
    elif label == 'volatile-vector-lifetimes':
        source = flatten(source)
        yield 'nonvolatile-native-read', source.replace('const volatile EeS128*', 'const EeS128*'), flags
        yield 'nonvolatile-scalar-members', source.replace('volatile float x, y, z, unspecifiedW;',
                                                          'float x, y, z, unspecifiedW;'), flags
    elif label == 'full-tu-context':
        yield 'omit-real-neighbor-bodies', source, [x for x in flags if x != '-DBLACK_NONMATCHING']
    elif label == 'scene-alias-and-null':
        source = flatten(source)
        old = 'if(!node->previous)lists[node->index]=node->next;else node->previous->next=node->next;'
        new = 'if(node->previous)node->previous->next=node->next;else lists[node->index]=node->next;'
        if source.count(old) != 1:
            raise ValueError('scene release-pair control source changed')
        yield 'omit-strict-aliasing', source, [x for x in flags if x != '-fstrict-aliasing']
        yield 'nonnull-first', source.replace(old, new), flags
    elif label == 'scene-storage-alignment':
        old = '''    unsigned size = (SceneStorageAlign(
        SceneStorageAlign((settings->instances << 5) + 256, tree.alignment) + tree.size,
        solver.alignment) + solver.size + 127) & 0xffffff80UL;'''
        new = '''    unsigned size = SceneStorageAlign((settings->instances << 5) + 256, tree.alignment) + tree.size;
    size = (SceneStorageAlign(size, solver.alignment) + solver.size + 127) & 0xffffff80UL;'''
        helper = '(bytes + (alignment - 1u)) & -alignment'
        if source.count(old) != 1 or source.count(helper) != 1:
            raise ValueError('scene nested-alignment control source changed')
        yield 'split-alignment-stages', source.replace(old, new), flags
        yield 'left-associated-helper', source.replace(helper, '((bytes + alignment) - 1u) & -alignment'), flags
    elif label == 'scene-partner-index':
        old = 'pairNodes[i].partner = &pairNodes[next - (i & 1) * 2];'
        if source.count(old) != 1:
            raise ValueError('scene partner-index control source changed')
        yield 'independent-partner-index', source.replace(old, 'pairNodes[i].partner = &pairNodes[i - (i & 1) * 2 + 1];'), flags
    elif label == 'root-quaternion-view-lifetime':
        start = source.index('Pose* Operations::Weight(')
        end = source.index('\nnamespace ArmsPose', start)
        body = source[start:end]
        view = '    float* rootRotation=out->quaternion;\n'
        operation = '        Ps2Math::AnimationMicro::Slerp(rootRotation,identity,pose,strength);'
        stores = ('float identity[4] __attribute__((aligned(16)));\n'
                  '    identity[3]=1.0f;\n'
                  '    identity[2]=zero;\n'
                  '    identity[1]=zero;\n'
                  '    identity[0]=zero;')
        positions = ('        const float* input=pose->translation;\n'
                     '        float* output=out->translation;')
        if any(body.count(text) != 1 for text in (view, operation, stores, positions)):
            raise ValueError('root quaternion lifetime control source changed')
        changed = body.replace(view, '').replace(operation, '        ' + view.strip() + '\n' + operation)
        yield 'branch-local-root-view', source[:start] + changed + source[end:], flags
        changed = body.replace(stores,
                               'float identity[4] __attribute__((aligned(16)))={zero,zero,zero,1.0f};')
        yield 'literal-identity-initializer', source[:start] + changed + source[end:], flags
        changed = body.replace(positions, '        float* output=out->translation;\n'
                                         '        const float* input=pose->translation;')
        yield 'output-position-capture-first', source[:start] + changed + source[end:], flags
    elif label == 'overlay-iterator-lifetimes':
        start = source.index('Pose* Operations::Overlay(')
        end = source.index('\nnamespace ArmsPose', start)
        body = source[start:end]
        declarations = ('        Pose* outputBone = outputBase;\n'
                        '        Pose* firstBone = firstBase;\n'
                        '        Pose* secondBone = secondBase;\n')
        if body.count(declarations) != 1:
            raise ValueError('overlay iterator lifetime control source changed')
        body = body.replace(declarations, '')
        for base, iterator in (('firstBase', 'firstBone'), ('secondBase', 'secondBone'),
                               ('outputBase', 'outputBone')):
            body = body.replace(base, iterator)
        yield 'shared-setup-and-loop-iterators', source[:start] + body + source[end:], flags
    elif label == 'complete-quaternion-difference':
        start = source.index('static inline void DifferenceRotation(')
        end = source.index('\nstatic inline void DifferenceBone(', start)
        helper = source[start:end]
        boundary = 'sqc2 vf1,0(%2)\\n\\t.set pop"'
        if helper.count(boundary) != 1:
            raise ValueError('complete quaternion difference control source changed')
        prefix = helper[:helper.index(boundary) + len(boundary)]
        prefix = prefix.replace('DifferenceRotation(void* out,const void* first,const void* second,void* inverse)',
                                'DifferenceInverse(void* inverse,const void* second)')
        split = prefix + '''
                 : "=&f"(norm) : "r"(second),"r"(inverse)
                 :"$8","vf1","vf2","vf9","vf10","vf31","memory");
}
static inline void DifferenceRotation(void* out,const void* first,const void* second,void* inverse) {
    DifferenceInverse(inverse,second);
    Ps2Math::AnimationMath::Multiply(out,inverse,first);
}
'''
        yield 'split-inverse-and-product', source[:start] + split + source[end:], flags
    elif label == 'branch-native-lifetimes':
        start = source.index('extern "C" f32 * func_00346510(')
        head, body = source[:start], source[start:]
        declaration = '    s32 remaining;'
        position = 's128 position=M2C_FIELD('
        store = '                    M2C_FIELD(outputBone,s128*,0x10)=position;'
        join = '                firstBone = '
        if body.count(declaration) != 1 or body.count(position) != 2 or body.count(store) != 2 or body.count(join) != 1:
            raise ValueError('branch native lifetime control source changed')
        body = body.replace(declaration, declaration + '\n    s128 position;')
        body = body.replace(position, 'position=M2C_FIELD(').replace(store, '')
        body = body.replace(join, '                M2C_FIELD(outputBone,s128*,0x10)=position;\n' + join)
        yield 'shared-position-join', head + body, flags
    elif label.startswith('native-float-absolute-'):
        old = 'static inline float SampleAbs(float value){return __builtin_fabsf(value);}'
        if old not in source:
            raise ValueError('native float absolute-value control source changed')
        operation = 'float result; __asm__("abs.s %0,%1" : "=f"(result) : "f"(value)); return result;'
        yield 'opaque-absolute-asm', source.replace(old, 'static inline float SampleAbs(float value) { ' + operation + ' }'), flags
        operation = operation.replace('__asm__(', '__asm__ volatile(')
        yield 'volatile-absolute-asm', source.replace(old, 'static inline float SampleAbs(float value) { ' + operation + ' }'), flags
    elif label == 'address-view-lifetime':
        yield 'direct-row-address', source.replace('NativeRowAddress(parentCopy.row + 3)',
                                                   '(parentCopy.row + 3)'), flags
    elif label == 'aggregate-result':
        changed = source.replace('StorageRequirement func_0033A3B0(unsigned int, unsigned int);',
                                 'StorageRequirement* func_0033A3B0(StorageRequirement*, unsigned int, unsigned int);')
        changed = changed.replace('StorageRequirement manifold = func_0033A3B0(vertices, triangles);\n    unsigned int manifoldSize = manifold.size;',
                                  'StorageRequirement manifold;\n    StorageRequirement* result = func_0033A3B0(&manifold, vertices, triangles);\n    unsigned int manifoldSize = result->size;')
        yield 'pointer-result-ABI-negative', changed, flags
    elif label == 'native-scalar-temporary':
        yield 'nonvolatile-absolute-temporary', source.replace('volatile union { int bits; float value; } scalar;',
                                                               'union { int bits; float value; } scalar;'), flags
    elif label == 'loop-index-lifetime':
        yield 'separate-skeleton-indices', source.replace('for (i = 0;', 'for (int i = 0;'), flags
    elif label == 'global-reference-view':
        yield 'direct-global-value', source.replace('unsigned pending=RetirementQueueIndex() ^ 1;',
                                                    'unsigned pending=AnimationRetire_Current ^ 1;'), flags
    elif label == 'pool-slot-lifetimes':
        before = 'u8 mask = PoolSlotMask(slot - (byte << 3));\n            u8 *bitmap = (u8 *)block + 8;'
        after = 'u8 *bitmap = (u8 *)block + 8;\n            u8 mask = PoolSlotMask(slot - (byte << 3));'
        yield 'bitmap-address-before-mask', source.replace(before, after), flags
        start = source.index('void func_00317C20(AudioPoolObject *pool, void *allocation) {')
        head, tail = source[:start], source[start:]
        tail = tail.replace('next = pool->blocks.next;\n            if (next == PoolBlockHeader(pool)',
                            'if (pool->blocks.next == PoolBlockHeader(pool)', 1)
        tail = tail.replace('*(void **)block = next;', '*(void **)block = pool->blocks.next;', 1)
        yield 'separate-next-lifetimes', head + tail, flags
    elif label == 'commuting-initializer-stores':
        start = source.index('AudioPlayback *func_00319ED0(')
        end = source.index('\n}', start) + 2
        head, body, tail = source[:start], source[start:end], source[end:]
        for name, left, right in (
                ('zero-store-order', 'emitter->last_tick=0;', 'emitter->position_bytes=0;'),
                ('shared-byte-store-order', 'emitter->priority=0x7f;', 'emitter->blend=0x7f;')):
            if body.count(left) != 1 or body.count(right) != 1:
                raise ValueError('initializer store-order control source changed')
            changed = body.replace(left, 'HANDBOOK_SWAP').replace(right, left).replace('HANDBOOK_SWAP', right)
            yield name, head + changed + tail, flags
    elif label == 'registry-result-branches':
        start = source.index('RwaPropertyClass *func_00319950(void)')
        end = source.index('\n}', start) + 2
        head, body, tail = source[:start], source[start:end], source[end:]
        old = '}else result=NULL;\n return result;'
        if body.count(old) != 1 or body.count('result=&D_004584D8.type;') != 1:
            raise ValueError('registry result-branch control source changed')
        changed = body.replace('RwaPropertyClass *result;\n ', '')
        changed = changed.replace('result=&D_004584D8.type;', 'return &D_004584D8.type;')
        changed = changed.replace(old, '}\n return NULL;')
        yield 'direct-branch-returns', head + changed + tail, flags
    elif label == 'pool-failure-result-boundary':
        start = source.index('AudioPoolObject *func_00317E40(u32 bytes,')
        end = source.index('\n}', start) + 2
        head, body, tail = source[:start], source[start:end], source[end:]
        old = ('        if(pool==NULL) return NULL;\n'
               '        pool->flags=2;\n'
               '    } else {\n'
               '        pool->flags=3;\n'
               '    }\n'
               '    stride=PoolAlignLastByte(bytes-1,alignment);')
        new = ('        {\n'
               '        AudioPoolObject *result=NULL;\n'
               '        if(pool!=NULL) {\n'
               '            pool->flags=2;\n'
               '            goto initialize;\n'
               '        }\n'
               '        return result;\n'
               '        }\n'
               '    }\n'
               '    pool->flags=3;\n'
               'initialize:\n'
               '    stride=PoolAlignLastByte(bytes-1,alignment);')
        if body.count(old) != 1:
            raise ValueError('pool failure-result control source changed')
        yield 'nested-failure-result', head + body.replace(old, new) + tail, flags
    elif label == 'steering-scaled-radius':
        old = '  float c = (((dx * dx) + (dy * dy)) + (dz * dz)) - (((*radius) * 1.5f) * ((*radius) * 1.5f));'
        new = ('  float reach = (*radius) * 1.5f;\n'
               '  float c = (((dx * dx) + (dy * dy)) + (dz * dz)) - (reach * reach);')
        if source.count(old) != 1:
            raise ValueError('steering scaled-radius control source changed')
        yield 'hoisted-scaled-radius', source.replace(old, new), flags
    elif label == 'event-positive-branch':
        old = ('    if (*eventKind == 5) {\n'
               '        func_001998F8(action);\n'
               '        return 1;\n'
               '    }\n'
               '    return 0;')
        new = ('    if (*eventKind != 5) return 0;\n'
               '    func_001998F8(action);\n'
               '    return 1;')
        if source.count(old) != 1:
            raise ValueError('event branch control source changed')
        yield 'negative-early-return', source.replace(old, new), flags
    elif label == 'node-address-order':
        yield 'base-before-byte-offset', source.replace('(NavNode*)(offset+(unsigned)nodes)',
                                                        '(NavNode*)((unsigned)nodes+offset)'), flags
    elif label == 'vector-value-lifetimes':
        source = flatten(source)
        yield 'byte-bool-comparison', source.replace('short operator==(const Vec3& q) const',
                                                     'bool operator==(const Vec3& q) const'), flags
        yield 'int-comparison', source.replace('short operator==(const Vec3& q) const',
                                               'int operator==(const Vec3& q) const'), flags
        yield 'materialized-product-copy', source.replace('return Vec3(scale*x,scale*y,scale*z);',
                                                           'Vec3 p; p.x=scale*x;p.y=scale*y;p.z=scale*z;return p;'), flags


def verify(output, selected=None):
    if selected == ['asm-source-identity']:
        output.parent.mkdir(parents=True, exist_ok=True)
        rows = verify_asm_source_identity(output.parent)
        output.write_text(json.dumps(dict(compiler='ee-gcc2.95.3-136',
                                          synthetic_asm_source_identity=rows), indent=2) + '\n')
        return
    if selected == ['consumed-next-cursor-native-cfi']:
        output.parent.mkdir(parents=True, exist_ok=True)
        result = verify_consumed_next_cursor_native_cfi(output.parent)
        output.write_text(json.dumps(dict(compiler='ee-gcc2.95.3-136',
                                          consumed_next_cursor_native_cfi=result), indent=2) + '\n')
        return
    if selected == ['builder-cursor-lifetimes']:
        output.parent.mkdir(parents=True, exist_ok=True)
        result = verify_consumed_next_cursor_native_cfi(output.parent, builder=True)
        output.write_text(json.dumps(dict(compiler='ee-gcc2.95.3-136',
                                          builder_cursor_lifetimes=result), indent=2) + '\n')
        return
    all_units = units.load_units()
    owners = {f['addr']: (u, f) for u in all_units for f in u['functions'] if f.get('status') == 'source'}
    inventory = {f['addr']: f for f in A.load_inventory()}
    symbols = {f['symbol']: f['addr'] for u in all_units for f in u['functions'] if f.get('symbol')}
    imported = units_verify.bindings()
    image = A.OrigImage()
    placement = json.loads((A.BUILD / 'placement.json').read_text())
    placement_addresses = {f['name']: f['addr'] for f in placement['functions']}
    jobs, cases = [], []
    for label, address in CONTROLS.items():
        if selected and label not in selected:
            continue
        unit, function = owners[address]
        if unit['compiler'] != 'ee-gcc2.95.3-136':
            raise ValueError('control does not use SN 1.36: ' + label)
        source = (ROOT / unit['source']).read_text()
        flags = list(unit['flags'])
        if Path(unit['source']).suffix == '.cpp' and '-x' not in flags:
            flags = ['-x', 'c++'] + flags
        bindings = dict(symbols)
        bindings.update(imported.get(unit['name'], {}))
        bindings.update(unit.get('externs', {}))
        section_bindings = {r['input']: units._num(r['start']) for r in unit.get('data_ranges', [])}
        # Owned compiler pools use their actual first placement slot. In
        # particular, SN LITERAL addends require this base plus the object's GP0.
        live_addresses = {f['addr'] for f in unit['functions'] if f.get('status') == 'source'}
        for section in ('.rodata', '.lit4', '.gcc_except_table'):
            entries = placement['sections'].get(section, [])
            slots = [i for i, entry in enumerate(entries)
                     if placement_addresses.get(entry.get('owner')) in live_addresses]
            if slots:
                if slots != list(range(slots[0], slots[-1] + 1)):
                    raise ValueError('control has noncontiguous owned constants: ' + label)
                section_bindings.setdefault(section, entries[slots[0]]['key'])
        for variant, text, options in [('exact', source, flags), *variants(label, source, flags)]:
            key = label + '/' + variant
            # An explicit stamp permits a fresh compiler run without changing code.
            text += '\n/* matching-handbook control v1 */\n'
            jobs.append((key, text, options))
            cases.append(dict(key=key, label=label, variant=variant, address=hex(address),
                              source=unit['source'], symbol=function['symbol'], flags=options,
                              bindings=bindings, section_bindings=section_bindings))
            if variant == 'exact' and label in ('inline-helper', 'cleanup', 'argument-order'):
                jobs.append((key + '-dumps', text, options + ['-da', '-fdump-unnumbered']))
    result = A.worker_compile(jobs, tag='handbook-controls')
    rows = []
    dumps = []
    failed = []
    for case in cases:
        rc, message, obj = result[case['key']]
        tokens, error = A.compiled_tokens(obj, case['symbol'], bindings=case['bindings'],
                                         section_bindings=case['section_bindings']) if not rc else (None, message)
        if tokens is None:
            row = dict(case, compile_rc=rc, error=error)
        else:
            address = int(case['address'], 0)
            exact, difference, reason = A.score(A.Target(inventory[address], image), tokens, image.word)
            row = dict(case, compile_rc=rc, exact=exact, differing_instructions=difference, mismatch_class=reason)
            path = output.parent / 'objects' / (case['key'].replace('/', '-') + '.o')
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(obj)
        row.pop('bindings')
        if case['variant'] in ('exact', 'declaration-reordered', 'omit-real-neighbor-bodies'):
            if not row.get('exact'):
                failed.append(case['key'])
        elif tokens is None or row.get('exact'):
            failed.append(case['key'] + ': perturbation must compile and diverge')
        rows.append(row)
        print(case['key'], row.get('differing_instructions', row.get('error')))
        if case['key'] + '-dumps' in result:
            dump_rc, dump_message, dump_obj = result[case['key'] + '-dumps']
            def texts(data):
                elf = Elf(data)
                return {s['name']: elf.content(s) for s in elf.sections if s['name'].startswith('.text')}
            identical = not rc and not dump_rc and texts(obj) == texts(dump_obj)
            dumps.append(dict(label=case['label'], text_sections_identical=identical, message=dump_message))
            if not identical:
                failed.append(case['key'] + ': debug dumps changed code')
    synthetic = verify_cleanup_alias(output.parent)
    asm_identity = verify_asm_source_identity(output.parent)
    unwind = verify_unwind_scope(owners, inventory, image)
    strings = verify_native_string_storage(owners, inventory, image)
    next_cursor = (verify_consumed_next_cursor_native_cfi(output.parent)
                   if not selected or 'consumed-next-cursor-native-cfi' in selected else [])
    builder = (verify_consumed_next_cursor_native_cfi(output.parent, builder=True)
               if not selected or 'builder-cursor-lifetimes' in selected else [])
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(dict(compiler='ee-gcc2.95.3-136', controls=rows, dump_flags=dumps,
                                     synthetic_cleanup=synthetic, unwind_scope=unwind,
                                     synthetic_asm_source_identity=asm_identity,
                                     consumed_next_cursor_native_cfi=next_cursor,
                                     builder_cursor_lifetimes=builder,
                                     native_string_storage=strings, failed=failed), indent=2) + '\n')
    if failed:
        raise ValueError('exact controls failed: ' + ', '.join(failed))


def verify_asm_source_identity(directory):
    """Measure pure-asm CSE identity; this synthetic control is not a retail match."""
    helper = ('static inline Native NAME(Native input){Native value;'
              'asm("qmtc2.ni %1,%0":"=j"(value):"r"(input));return value;}')
    caller = ('\nextern "C" void probe(Native* out,Native input)'
              '{out[0]=A(input);out[1]=B(input);}\n')
    prefix = 'typedef long long Native; typedef char NativeWidth[sizeof(Native)==16?1:-1];\n'
    first, second = helper.replace('NAME', 'A'), helper.replace('NAME', 'B')
    sources = {'shared': prefix + first + caller.replace('B(input)', 'A(input)'),
               'separate-lines': prefix + first + '\n' + second + caller,
               'same-line': prefix + first + second + caller}
    flags = ['-x', 'c++', '-O2', '-G8', '-snas', '-ffunction-sections',
             '-fno-exceptions', '-mvu0-use-vf0-vf31']
    result = A.worker_compile([(key, text, flags) for key, text in sources.items()],
                              tag='handbook-pure-asm-source-identity')
    rows, bodies = [], {}
    for key, source in sources.items():
        rc, message, obj = result[key]
        if rc:
            raise ValueError('native pure-asm control did not compile: ' + message)
        elf = Elf(obj)
        symbol = next(s for s in elf.symbols() if s['name'] == 'probe')
        section = elf.sections[symbol['shndx']]
        body = elf.content(section)[symbol['value']:symbol['value'] + symbol['size']]
        words = struct.unpack('<%dI' % (len(body) // 4), body)
        transfers = sum(word >> 26 == 0x12 and (word >> 21) & 31 == 5 for word in words)
        bodies[key] = body
        rows.append(dict(variant=key, native_value_bits=128, bytes=len(body),
                         text_input_bytes=section['size'], qmtc2=transfers, flags=flags))
        (directory / ('asm-identity-' + key + '.cpp')).write_text(source)
        (directory / ('asm-identity-' + key + '.o')).write_bytes(obj)
    if bodies['shared'] != bodies['same-line'] or [r['qmtc2'] for r in rows] != [1, 2, 1]:
        raise ValueError('unexpected native pure-asm source-identity/CSE result')
    return rows


def verify_cleanup_alias(directory):
    """A synthetic destructor control; these bytes are not a retail match claim."""
    base = 'struct Probe { Probe(); ~Probe(); }; extern int body(); extern "C" int probe() { Probe object; return body(); }\n'
    sources = {'normal': base,
               'abi-alias': base.replace('~Probe();', '~Probe() __asm__("_$_5Probe");'),
               'plain-alias': base.replace('~Probe();', '~Probe() __asm__("cleanup");')}
    flags = ['-x', 'c++', '-O2', '-G0', '-snas', '-ffunction-sections']
    results = A.worker_compile([(key, text, flags) for key, text in sources.items()], tag='handbook-cleanup-alias')
    rows, text_bytes = [], {}
    for key, source in sources.items():
        rc, message, obj = results[key]
        if rc:
            raise ValueError('synthetic cleanup failed: ' + message)
        elf = Elf(obj)
        symbols = elf.symbols()
        function = next(s for s in symbols if s['name'] == 'probe')
        section = elf.sections[function['shndx']]
        text_bytes[key] = elf.content(section)[function['value']:function['value'] + function['size']]
        calls = []
        for relocation in elf.sections:
            if relocation['type'] != 9 or relocation['info'] != section['index']:
                continue
            for offset, info in struct.iter_unpack('<II', elf.content(relocation)):
                if function['value'] <= offset < function['value'] + function['size'] and info & 255 == 4:
                    calls.append(symbols[info >> 8]['name'])
        (directory / ('cleanup-' + key + '.cpp')).write_text(source)
        rows.append(dict(variant=key, bytes=function['size'], calls=calls))
    if text_bytes['normal'] != text_bytes['abi-alias']:
        raise ValueError('destructor-shaped alias changed the synthetic control')
    if rows[0]['calls'].count('_$_5Probe') != 2 or 'cleanup' in rows[2]['calls'] or len(text_bytes['plain-alias']) >= len(text_bytes['normal']):
        raise ValueError('unexpected SN destructor alias lowering')
    return rows


def verify_unwind_scope(owners, inventory, image):
    """Move typed data definitions and check the native leaf FDE endpoint."""
    unit, _ = owners[0x2E7490]
    source = (ROOT / unit['source']).read_text()
    start = source.index('#define NEAREST_DATA')
    end = source.index('#undef NEAREST_DATA', start) + len('#undef NEAREST_DATA')
    block = source[start:end]
    changed = source[:start] + source[end:]
    marker = 'RegistrationStorage D_004513D8 __attribute__((aligned(8)));'
    if marker not in changed:
        raise ValueError('unwind control data declaration changed')
    changed = changed.replace(marker, block + '\n' + marker)
    flags = unit['flags']
    results = A.worker_compile([('scope-before', source, flags), ('scope-after', changed, flags)],
                               tag='handbook-unwind-scope')
    data = []
    for key in ('scope-before', 'scope-after'):
        rc, message, obj = results[key]
        if rc:
            raise ValueError('unwind control did not compile: ' + message)
        for function in unit['functions']:
            tokens, error = A.compiled_tokens(obj, function['symbol'])
            if tokens is None or not A.score(A.Target(inventory[function['addr']], image), tokens, image.word)[0]:
                raise ValueError('unwind source perturbation changed retail code: ' + str(error))
        elf = Elf(obj)
        data.append(elf.content(elf.section('.data')))
    if len(data[0]) != len(data[1]):
        raise ValueError('unwind control changed metadata size')
    words = [struct.unpack('<%dI' % (len(value) // 4), value) for value in data]
    differences = [(left, right) for left, right in zip(*words) if left != right]
    if differences != [(12, 16)]:
        raise ValueError('unexpected native leaf FDE scope change: ' + str(differences))
    return dict(address='0x2e7490', exact_text_functions=len(unit['functions']),
                native_metadata_bytes=len(data[0]), differing_metadata_words=1,
                original_extent=12, moved_data_extent=16)


def verify_native_string_storage(owners, inventory, image):
    """Verify natural string placement, including a code-identical bad data order."""
    unit, _ = owners[0x3063A8]
    source = (ROOT / unit['source']).read_text()
    names = ('SteeringClassName', 'RootTypeName', 'IteratorTypeName')
    declarations = []
    for name in names:
        match = re.search(r'^const char ' + name + r'\[\].*;$', source, re.M)
        if match is None:
            raise ValueError('native string declaration changed: ' + name)
        declarations.append(match.group())
    first, second = declarations[1:]
    changed = source.replace(first + '\n' + second, second + '\n' + first)
    if changed == source:
        raise ValueError('native string order control did not change source')
    flags = unit['flags']
    result = A.worker_compile([('natural', source, flags), ('reordered', changed, flags)],
                              tag='handbook-native-string-storage')
    expected = b''.join(bytes.fromhex(image.word(a)) for a in range(0x408630, 0x408690, 4))
    rows = []
    for key in ('natural', 'reordered'):
        rc, message, obj = result[key]
        if rc:
            raise ValueError('native string control did not compile: ' + message)
        elf = Elf(obj)
        section = elf.section('.rodata')
        if section is None:
            raise ValueError('native string control lost its rodata input')
        for function in unit['functions']:
            tokens, error = A.compiled_tokens(obj, function['symbol'],
                                             section_bindings={'.rodata': 0x408630})
            if tokens is None or not A.score(A.Target(inventory[function['addr']], image), tokens, image.word)[0]:
                raise ValueError('native string order changed retail code: ' + str(error))
        offsets = {symbol['name']: symbol['value'] for symbol in elf.symbols()
                   if symbol['shndx'] == section['index'] and symbol['name'].startswith('D_004086')}
        rows.append(dict(variant=key, exact_text_functions=len(unit['functions']),
                         native_bytes_exact=elf.content(section) == expected,
                         bytes=section['size'], alignment=section['align'], offsets=offsets))
    if not rows[0]['native_bytes_exact'] or rows[0]['offsets'] != {
            'D_00408630': 0, 'D_00408650': 32, 'D_00408660': 48}:
        raise ValueError('natural native strings no longer reproduce their original placement')
    if rows[1]['native_bytes_exact']:
        raise ValueError('reordered native strings unexpectedly reproduce their original data')
    return rows


def verify_consumed_next_cursor_native_cfi(directory, builder=False):
    """Audit real pose-cursor lifetime controls and their natural native unwind."""
    all_units = units.load_units()
    unit = next(u for u in all_units if any(f['addr'] == 0x346510 for f in u['functions']))
    if unit['compiler'] != 'ee-gcc2.95.3-136':
        raise ValueError('next-cursor control no longer uses SN 1.36')
    source = (ROOT / unit['source']).read_text()
    if builder:
        raw = ('            const Pose* input=(const Pose*)source->tracks;\n'
               '            input+=skeleton->count*(int)frame;')
        guard = ('        int i=0;\n'
                 '        if(i<skeleton->count) {\n'
                 '            Pose* result=scratch;')
        if source.count(raw) != 1 or source.count(guard) != 1:
            raise ValueError('builder cursor control source changed')
        combined = source.replace(raw,
                    '            const Pose* input=(const Pose*)source->tracks+skeleton->count*(int)frame;')
        hoisted = source.replace(guard,
                    '        Pose* result=scratch;\n'
                    '        int i=0;\n'
                    '        if(i<skeleton->count) {')
        flags = ['-x', 'c++'] + list(unit['flags'])
        sources = {'exact-build': source, 'combined-raw-initialization': combined,
                   'hoisted-output-cursor': hoisted}
    else:
        start = source.index('static inline Pose* BlendCopyAdvance(')
        end = source.index('// Unmatched:', start)
        helpers = source[start:end]
        if helpers.count('return out+1;') != 2:
            raise ValueError('complete bone-operation result changed')
        current = helpers.replace('return out+1;', 'return out;')
        changed = source[:start] + current + source[end:]
        start = changed.index('Pose* Operations::Blend(')
        end = changed.index('\nnamespace ArmsPose', start)
        body = changed[start:end]
        body, count = re.subn(r'result=(Blend(?:Copy|Bone)Advance\([^;\n]+\));',
                              r'result=\1+1;', body)
        if count != 6:
            raise ValueError('complete bone-operation call sites changed: ' + str(count))
        current_plus_one = changed[:start] + body + changed[end:]
        split_helpers = helpers.replace('    out->translation[3]=0.0f;\n', '').replace('return out+1;', 'return out;')
        changed = source[:source.index('static inline Pose* BlendCopyAdvance(')] + split_helpers + source[source.index('// Unmatched:', source.index('static inline Pose* BlendCopyAdvance(')):]
        start = changed.index('Pose* Operations::Blend(')
        end = changed.index('\nnamespace ArmsPose', start)
        body = changed[start:end]
        masked = 'result=BlendCopyAdvance(result,a);\n            }'
        if body.count(masked) != 1:
            raise ValueError('masked complete-operation tail changed')
        body = body.replace(masked, 'result=BlendCopyAdvance(result,a);\n'
                            '                result->translation[3]=0.0f;\n'
                            '                ++result;\n            }')
        body, count = re.subn(r'(\n                \+\+[ab];\n                \+\+[ab];)',
                              '\n                result->translation[3]=0.0f;\n                ++result;'+r'\1', body)
        if count != 1:
            raise ValueError('unmasked complete-operation tail changed')
        split = changed[:start] + body + changed[end:]
        flags = ['-x', 'c++'] + list(unit['flags'])
        sources = {'consumed-next': source, 'current-plus-one': current_plus_one,
                   'caller-clears-and-advances': split}
    result = A.worker_compile([(key, text, flags) for key, text in sources.items()],
                              tag='handbook-builder-cursor-lifetimes' if builder else 'handbook-consumed-next-cursor-native-cfi')
    image = A.OrigImage()
    inventory = {f['addr']: f for f in A.load_inventory()}
    bindings = {f['symbol']: f['addr'] for u in all_units for f in u['functions'] if f.get('symbol')}
    bindings.update(units_verify.bindings().get(unit['name'], {}))
    bindings.update(unit.get('externs', {}))
    section_bindings = {r['input']: units._num(r['start']) for r in unit.get('data_ranges', [])}
    image_section = image.e.section('.data')
    expected = image.e.content(image_section)[0x3D20E4-image_section['addr']:0x3D247C-image_section['addr']]
    rows = []
    for key, text in sources.items():
        rc, message, obj = result[key]
        if rc:
            raise ValueError('next-cursor control failed to compile: ' + message)
        exact = []
        blend = build = None
        for function in unit['functions']:
            tokens, error = A.compiled_tokens(obj, function['symbol'], bindings=bindings,
                                             section_bindings=section_bindings)
            if tokens is None:
                raise ValueError('next-cursor control lost body: ' + str(error))
            score = A.score(A.Target(inventory[function['addr']], image), tokens, image.word)
            if function.get('status') == 'source':
                changed_builder = builder and key != 'exact-build' and function['addr'] == 0x346F58
                if not score[0] and not changed_builder:
                    raise ValueError('next-cursor control changed selected exact body: ' + hex(function['addr']))
                if score[0]:
                    exact.append(hex(function['addr']))
            if function['addr'] == 0x346230:
                blend = dict(differing_instructions=score[1], mismatch_class=score[2],
                             instructions=len(tokens))
            if function['addr'] == 0x346F58:
                build = dict(differing_instructions=score[1], mismatch_class=score[2],
                             instructions=len(tokens))
        elf = Elf(obj)
        data = bytearray(elf.content(elf.section('.data')))
        symbols = elf.symbols()
        for at, info in struct.iter_unpack('<II', elf.content(elf.section('.rel.data'))):
            symbol = symbols[info >> 8]
            if info & 255 != 2:
                raise ValueError('unexpected native unwind relocation kind')
            if symbol['type'] == 3:
                functions = [f for f in symbols if f['type'] == 2 and f['bind'] in (1, 2)
                             and f['shndx'] == symbol['shndx'] and f['value'] == symbol['value']]
                if len(functions) != 1:
                    raise ValueError('ambiguous native unwind function entry')
                symbol = functions[0]
            address = bindings.get(symbol['name'])
            if address is None:
                raise ValueError('unbound native unwind function: ' + symbol['name'])
            addend, = struct.unpack_from('<I', data, at)
            struct.pack_into('<I', data, at, address + addend)
        if len(data) != len(expected):
            raise ValueError('next-cursor control changed native unwind size')
        differences = [hex(0x3D20E4+i) for i, (a, b) in enumerate(zip(data, expected)) if a != b]
        (directory / (('builder-cursor-' if builder else 'next-cursor-') + key + '.cpp')).write_text(text)
        (directory / (('builder-cursor-' if builder else 'next-cursor-') + key + '.o')).write_bytes(obj)
        rows.append(dict(variant=key, source=unit['source'],
                         source_sha256=hashlib.sha256(text.encode()).hexdigest(),
                         object_sha256=hashlib.sha256(obj).hexdigest(), flags=flags,
                         exact_selected_functions=exact, blend=blend, build=build,
                         native_bytes=len(data), native_exact=not differences,
                         differing_native_bytes=differences,
                         behavior_scope='Source-equivalent cursor/scope expressions; this compiler control runs no EE states.'))
    if builder:
        if (not all(row['native_exact'] for row in rows)
                or [row['build']['differing_instructions'] for row in rows] != [0, 10, 3]):
            raise ValueError('unexpected exact builder cursor lifetime result')
    elif (not rows[0]['native_exact'] or not rows[1]['native_exact']
            or rows[2]['differing_native_bytes'] != ['0x3d2152', '0x3d2153', '0x3d2167', '0x3d2168']):
        raise ValueError('unexpected consumed-next-cursor native CFI result')
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'build/handbook-controls/handbook-controls.json')
    parser.add_argument('--only', choices=sorted([*CONTROLS, 'asm-source-identity', 'consumed-next-cursor-native-cfi', 'builder-cursor-lifetimes']), action='append')
    args = parser.parse_args()
    verify(args.output, args.only)


if __name__ == '__main__':
    main()
