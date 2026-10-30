"""Matched linkage signatures must anchor recovery without hiding aggregate ABI ambiguity."""
import json
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d)
                for d in ('', 'build', 'pipeline', 'maint')]
import context_recovery as cr
import autodecomp as A
import decompile


class SignatureEvidence(unittest.TestCase):
    def test_drafting_exports_current_context_with_multiline_prototypes(self):
        with tempfile.TemporaryDirectory() as directory, patch.dict(os.environ):
            os.environ.pop('AUTODECOMP_FREEZE_CONTEXT', None)
            root = Path(directory)
            auto = root / 'build/auto'
            auto.mkdir(parents=True)
            header, types = root / 'prototypes.h', root / 'types.h'
            header.write_text('''extern s32 func_00175C30(PS2CollisionQueue*,
                         PS2GameObjectRecord*); /* object argument unused */
''')
            types.write_text('typedef struct Queue PS2CollisionQueue;\ntypedef struct Object PS2GameObjectRecord;\n')
            context = dict(layouts={}, signatures={str(0x175c30): dict(name='func_00175C30', ret='s32',
                           params=['void *', 'void *'], arity=2, source_quality=0)})
            cr.write_build_context(context, root)
            (auto / 'ctx.c').write_text('stale export')
            (auto / 'context.json').write_text('{}')
            function = dict(addr=0x175c30, name='func_00175C30', size=12,
                            words=[0x24020000, 0x03e00008, 0])
            # Substitute only the native inventory and m2c boundary; use the real
            # context exporters and draft cleaner, with no game files or tools.
            m2c = {'func_00175C30': dict(ret='s32', params='void *arg0, void *arg1', body='return 0;', decls={})}
            with patch.object(decompile, 'ROOT', root), patch.object(A, 'AUTO', auto), \
                    patch.object(A, 'HEADER', header), patch.object(A, 'TYPES_HEADER', types), \
                    patch.object(A, 'recovered_context', return_value=context), \
                    patch.object(A, 'load_inventory', return_value=[function]), patch.object(A, 'run_m2c', return_value=m2c):
                _, _, source, _ = decompile.draft(function['addr'], 'ctx.c')
            self.assertIsNotNone(source)
            self.assertNotIn('AUTODECOMP_FREEZE_CONTEXT', os.environ)
            declaration = 'extern s32 func_00175C30(PS2CollisionQueue*, PS2GameObjectRecord*);'
            for name in ('ctx.c', 'ctx2.c', 'ctx3.c', 'ctx_void.c'):
                text = (auto / name).read_text()
                self.assertEqual(text.count(declaration), 1)
                self.assertNotIn('\n                         PS2GameObjectRecord*);', text)

    def test_matched_c_linkage_void_beats_leftover_return_register(self):
        declaration, = cr.parse_declarations('''
extern "C" void func_00100100(void* self, void* definition, void* shared) {
    self = definition;
}
''')
        self.assertEqual(declaration['ret'], 'void')
        self.assertEqual(declaration['abi_uncertainty'], [])
        seed = dict(declaration, source='src/actor.cpp', quality=4, matched=True)
        # Native code leaves an integer in v0, which is not proof of a return value.
        function = dict(addr=0x100100, name='func_00100100',
                        words=[0x24020001, 0x03e00008, 0], rel={})
        rows, _ = cr.recover_signatures([function], {function['addr']: cr.analyze_function(function)},
                                        {function['addr']: seed})
        row = rows[function['addr']]
        self.assertEqual((row['ret'], row['arity_kind']), ('void', 'signature'))
        self.assertEqual(row['params'], ['void *'] * 3)
        self.assertEqual(row['source_evidence']['declaration'], declaration['raw'])
        self.assertTrue(row['source_evidence']['matched_owner'])

    def test_conflicting_source_views_remain_visible_in_scoped_report(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            (root / 'src/storage.c').write_text('''
void* func_00100000(void* output, s32 count, void* type, s32 offset) {
    return output;
}
''')
            (root / 'src/actor.cpp').write_text('''
extern "C" AllocationRequest ListRequirements(s32, void*, s32) __asm__("func_00100000");
extern "C" void func_00100100(void* self) { ListRequirements(1, self, 64); }
''')
            units = [dict(source=path, functions=[dict(addr=addr, symbol='func_%08X' % addr, status='source')],
                          externs={}) for path, addr in [('src/storage.c', 0x100000), ('src/actor.cpp', 0x100100)]]
            with patch('units.load_units', return_value=units), patch('units.dependencies', side_effect=lambda p: [p]):
                seeds, conflicts = cr.source_seeds(root)
        self.assertEqual(seeds[0x100000]['ret'], 'void *')
        conflict, = conflicts
        self.assertEqual({d['path'] for d in conflict['declarations']}, {'src/storage.c', 'src/actor.cpp'})
        aggregate, = [d for d in conflict['declarations'] if 'ListRequirements' in d['declaration']]
        self.assertTrue(aggregate['abi_uncertainty'])
        # The aggregate view is a caller declaration, not a matched owner definition.
        self.assertFalse(aggregate['matched_owner'])
        inv = [dict(addr=0x100100, name='func_00100100', words=[0x0c040000, 0, 0x03e00008, 0],
                    rel={'0': ['jal', 0x100000, 0]})]
        context = dict(signatures={str(a): dict(name='func_%08X' % a, source_evidence=cr.source_evidence(s))
                                   for a, s in seeds.items()}, source_conflicts=conflicts)
        local = cr.focused_report(context, [0x100100])
        self.assertEqual(list(local['signatures']), ['func_00100100'])
        self.assertEqual(local['source_conflicts'], [])
        report = cr.focused_report(context, [0x100100], callees=True, inv=inv)
        self.assertEqual(set(report['signatures']), {'func_00100000', 'func_00100100'})
        self.assertEqual(report['source_conflicts'], conflicts)
        self.assertEqual(report['calls'][0]['callee'], 'func_00100000')
        self.assertEqual(report['calls'][0]['pc'], '0x00100100')
        self.assertEqual(json.loads(json.dumps(report)), report)
        with self.assertRaisesRegex(ValueError, 'no recovered signature'):
            cr.focused_report(context, [0x123456])


if __name__ == '__main__':
    unittest.main()
