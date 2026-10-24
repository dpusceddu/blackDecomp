"""Host-only analyses of authored synthetic instructions; no compiler is run here."""
import importlib.util
import sys
import unittest
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[2] / 'tools'
sys.path.insert(0, str(TOOLS))
import context_recovery as cr


def i(op, rs, rt, imm):
    return op << 26 | rs << 21 | rt << 16 | (imm & 0xffff)


def r(rs, rt, rd, op=0x21):
    return rs << 21 | rt << 16 | rd << 11 | op


def fn(words, addr=0x100000, rel=None):
    return dict(addr=addr, name='func_%08X' % addr, words=words, rel=rel or {}, size=len(words)*4)


class ControlFlowTests(unittest.TestCase):
    def test_delay_slot_call_argument_survives_call_clobbers(self):
        f = fn([0x0c080000, r(5, 0, 4), r(4, 0, 2), 0x03e00008, 0], rel={'0': ['jal', 0x200000, 0, 'func_00200000']})
        a = cr.analyze_function(f)
        call = next(iter(a['calls'].values()))
        self.assertIn(('arg', 1, 0), call[0].origins)
        # Reading a0 after the call is not a use of the caller's incoming a0.
        self.assertFalse(any(k == 0 for kind, k, typ, pc in a['uses'] if pc == 2))

    def test_branch_join_keeps_both_possible_bases(self):
        # beq a2,zero,L; move s0,a0; b end; nop; L: move s0,a1; end: lw v0,4(s0)
        f = fn([i(4, 6, 0, 3), r(4, 0, 16), i(4, 0, 0, 2), 0,
                r(5, 0, 16), i(0x23, 16, 2, 4), 0x03e00008, 0])
        fields = cr.analyze_function(f)['fields']
        self.assertEqual({slot for kind, slot, off, size, typ, pc in fields}, {0, 1})

    def test_branch_likely_annuls_untaken_delay_slot(self):
        f = fn([i(0x14, 6, 0, 3), r(5, 0, 4), i(0x23, 4, 2, 8), 0x03e00008, 0,
                0x03e00008, 0])
        fields = cr.analyze_function(f)['fields']
        self.assertIn(('arg', 0, 8, 4, 's32', 2), fields)
        self.assertNotIn(('arg', 1, 8, 4, 's32', 2), fields)

    def test_alias_and_displacement_fields(self):
        f = fn([r(4, 0, 16), i(9, 16, 16, 12), i(0x23, 16, 2, 8), 0x03e00008, 0])
        self.assertIn(('arg', 0, 20, 4, 's32', 2), cr.analyze_function(f)['fields'])

    def test_loop_displacement_widens_and_terminates(self):
        f = fn([i(9, 4, 4, 4), i(5, 5, 0, -2), 0, 0x03e00008, 0])
        self.assertIsInstance(cr.analyze_function(f)['uses'], set)

    def test_tail_call_observes_delay_slot(self):
        f = fn([0x08080000, r(5, 0, 4)], rel={'0': ['jal', 0x200000, 0, 'func_00200000']})
        a = cr.analyze_function(f)
        self.assertIn(('arg', 1, 0), a['calls'][(0, 0x200000, True)][0].origins)


class SignatureTests(unittest.TestCase):
    def test_varargs_register_homing_is_not_fifteen_fixed_arguments(self):
        words = [i(9, 29, 29, -128), r(4, 0, 2, 0x2d)]
        words += [i(0x3f, 29, reg, 0x48 + 8*(reg - 5)) for reg in range(5, 12)]
        words += [i(0x39, 29, reg, 0x38 + 4*n) for n, reg in enumerate((12, 14, 16, 18))]
        leaf = fn(words + [0x03e00008, i(9, 29, 29, 128)], 0x200000)
        analysis = {leaf['addr']: cr.analyze_function(leaf)}
        seed = dict(params=[('s32', None)]*8 + [('f32', None)]*7, ret='s32',
                    quality=1.5, source='auto', cls=None)
        rows, _ = cr.recover_signatures([leaf], analysis, {leaf['addr']: seed})
        row = rows[leaf['addr']]
        self.assertEqual(row['register_slots'], [0])
        self.assertTrue(row['variadic'])
        self.assertEqual(cr.prototype(row), 's32 func_00200000(s32, ...);')
        self.assertEqual(cr.prototype(row, True), 's32 func_00200000(s32, ...);')
        seed['quality'] = 4
        rows, _ = cr.recover_signatures([leaf], analysis, {leaf['addr']: seed})
        self.assertEqual(rows[leaf['addr']]['arity'], 15)
        self.assertFalse(rows[leaf['addr']].get('variadic', False))
        # One missing FP home or nonconsecutive GPR home is not this ABI.
        broken = fn(leaf['words'][:])
        broken['words'][9] = 0
        self.assertIsNone(cr.variadic_register_saves(broken))
        broken['words'] = leaf['words'][:]
        broken['words'][3] += 8
        self.assertIsNone(cr.variadic_register_saves(broken))

    def test_authored_variadic_signature_has_only_fixed_register_slots(self):
        leaf = fn([r(4, 0, 2), 0x03e00008, 0])
        declaration = cr.parse_declarations('int func_00100000(int code, ...);')[0]
        self.assertEqual(cr.abi_slots(declaration['params']), [(0, 's32')])
        declaration.update(quality=4, source='authored', cls=None)
        rows, _ = cr.recover_signatures([leaf], {leaf['addr']: cr.analyze_function(leaf)}, {leaf['addr']: declaration})
        self.assertEqual(rows[leaf['addr']]['register_slots'], [0])
        self.assertEqual(cr.prototype(rows[leaf['addr']]), 's32 func_00100000(s32, ...);')

    def test_closed_leaf_ignores_caller_temporaries_and_weak_draft_extra_parameters(self):
        leaf = fn([i(0x23, 4, 2, 4), 0x03e00008, r(2, 4, 2)], 0x200000)
        caller = fn([i(9, 0, 9, 6), 0x0c080000, i(9, 0, 4, 1), 0x03e00008, 0],
                    rel={'4': ['jal', 0x200000, 0, 'func_00200000']})
        analysis = {f['addr']: cr.analyze_function(f) for f in (leaf, caller)}
        seed = dict(params=[('void *', None)] + [('s32', None)]*5, ret='s32', quality=1.5,
                    source='auto', cls=None)
        rows, _ = cr.recover_signatures([leaf, caller], analysis, {leaf['addr']: seed})
        self.assertEqual(rows[leaf['addr']]['register_slots'], [0])
        self.assertIn('minimum', rows[leaf['addr']]['arity_kind'])
        seed['quality'] = 4
        rows, _ = cr.recover_signatures([leaf, caller], analysis, {leaf['addr']: seed})
        self.assertEqual(rows[leaf['addr']]['arity'], 6)  # authored unused parameters remain real
        self.assertFalse(cr.closed_leaf(caller))
        self.assertFalse(cr.closed_leaf(fn([i(4, 4, 0, 1), 0, 0x03e00008, 0])))

    def test_named_c_alias_float_and_pointer_parameters(self):
        ds = cr.parse_declarations('float *Pose(void *owner, Node *node, float time) ANIMATION_FUNCTION(0034BFB8);\nfloat *Pose(void *owner, Node *node, float time) { return 0; }')
        self.assertEqual(ds[0]['address'], 0x34bfb8)
        self.assertEqual(ds[0]['ret'], 'f32 *')
        self.assertEqual(ds[1]['params'], [('void *', None), ('void *', 'Node'), ('f32', None)])

    def test_cpp_method_this_and_constructor(self):
        ds = cr.parse_declarations('int Queue::Get(unsigned short n) const { return n; }\nQueue::Queue(int n) { value = n; }')
        self.assertEqual(ds[0]['params'], [('void *', 'Queue'), ('u16', None)])
        self.assertEqual(ds[1]['params'][0], ('void *', 'Queue'))
        self.assertEqual(cr.demangle_method('Get__5QueueUs'), 'Queue::Get')

    def test_function_pointer_parameter_is_one_slot(self):
        ps = cr.split_params('int (*callback)(int, float), float weight, int count')
        self.assertEqual(len(ps), 3)
        self.assertEqual(cr.param_type(ps[0])[0], 'void *')

    def test_old_gcc_qualified_method_names(self):
        cases = {
            'SetTarget__Q213CampaignActor16CameraControllerxxfl': 'CampaignActor::CameraController::SetTarget',
            'Button__CQ216CampaignGraphics10ControllerUi': 'CampaignGraphics::Controller::Button',
            '__Q24Kaim6CBrain': 'Kaim::CBrain::CBrain',
            '_$_Q24Kaim18CPathObjectManager': 'Kaim::CPathObjectManager::~CPathObjectManager',
            '___5Queue': 'Queue::~Queue',
        }
        for symbol, name in cases.items():
            with self.subTest(symbol=symbol):
                self.assertEqual(cr.demangle_method(symbol), name)
        for symbol in ('Get__Q0', 'Get__Q24Kaim99Short', 'Get__t5Queue1Zi', 'plain_c'):
            self.assertIsNone(cr.demangle_method(symbol))

    def test_target_widths_do_not_conflate_real64_with_ee128(self):
        self.assertEqual(cr.normalize_type('long')[0], 's64')
        self.assertEqual(cr.normalize_type('long long')[0], 's128')
        self.assertEqual(cr.normalize_type('undefined8')[0], 'u64')
        row = dict(name='func_00100000', ret='s128', arity=2, params=['s64', 's128'])
        self.assertIn('(s64, s128)', cr.prototype(row))
        self.assertIn('(s64, s64)', cr.prototype(row, True))
        self.assertEqual(cr.context_type('s128 *', True), 's64 *')

    def test_unknown_count_is_not_zero_parameters(self):
        self.assertIn('()', cr.prototype(dict(name='func_00100000', ret='unknown', arity=None, params=[])))
        self.assertIn('(void)', cr.prototype(dict(name='func_00100000', ret='void', arity=0, params=[])))

    def test_width_conflicts_are_opaque(self):
        self.assertEqual(cr.resolve_type({'s64', 's128'}), ('unknown', ['s128', 's64']))
        self.assertEqual(cr.resolve_type({'f32', 's32'})[0], 'unknown')
        self.assertEqual(cr.resolve_type({'u32', 's32'})[0], 's32')

    def test_return_width_propagates_beyond_old_size_cutoff(self):
        callee = fn([i(0x1e, 4, 2, 0), 0x03e00008, 0], 0x200000)
        caller = fn([0x0c080000, 0, 0x03e00008, 0], 0x100000,
                    {'0': ['jal', 0x200000, 0, 'func_00200000']})
        caller['size'] = 2048
        consumer = fn([0x0c040000, 0, i(0x1f, 5, 2, 0), 0x03e00008, 0], 0x300000,
                      {'0': ['jal', caller['addr'], 0, caller['name']]})
        inv = [consumer, caller, callee]
        signatures, links = cr.recover_signatures(inv, {f['addr']: cr.analyze_function(f) for f in inv}, {})
        self.assertEqual(signatures[0x100000]['ret'], 's128')
        self.assertEqual(signatures[0x200000]['ret'], 's128')


class WideReturnDemandTests(unittest.TestCase):
    def infer(self, functions, seeds=None):
        return cr.recover_signatures(functions,
            {f['addr']: cr.analyze_function(f) for f in functions}, seeds or {})[0]

    def seed(self, ret, quality=4, params=None):
        return dict(params=params or [('void *', None)], ret=ret,
                    quality=quality, cls=None, source='authored.c')

    def test_incidental_vector_copy_is_not_return_abi_evidence(self):
        f = fn([i(0x1e, 4, 2, 0), i(0x1f, 5, 2, 0), 0x03e00008, 0])
        row = self.infer([f])[f['addr']]
        self.assertEqual(row['ret'], 'unknown')
        self.assertEqual(row['return_evidence']['direct_types']['gpr'], ['s128'])
        self.assertFalse(row['return_evidence']['gpr_demand'])
        weak = self.infer([f], {f['addr']: self.seed('s128', 1.5)})[f['addr']]
        self.assertEqual(weak['ret'], 'unknown')
        self.assertEqual(weak['return_hint'], 's128')

    def test_source_anchored_vector_return_survives_without_callers(self):
        f = fn([i(0x1e, 4, 2, 0), 0x03e00008, 0])
        for typ in ('s128', 'u128'):
            self.assertEqual(self.infer([f], {f['addr']: self.seed(typ)})[f['addr']]['ret'], typ)

    def test_demand_flows_backward_through_copy_and_tail_wrappers_only(self):
        getter = fn([i(0x1e, 4, 2, 0), 0x03e00008, 0], 0x300000)
        for tail in (False, True):
            words = [0x080c0000, 0] if tail else [0x0c0c0000, 0, 0x03e00008, 0]
            # Inventory normalizes both direct calls and tail jumps as 'jal'.
            wrapper = fn(words, 0x200000, {'0': ['jal', getter['addr'], 0, getter['name']]})
            dead = fn([0x0c0c0000, 0, 0x03e00008, 0], 0x400000,
                      {'0': ['jal', getter['addr'], 0, getter['name']]})
            consumer = fn([0x0c080000, 0, i(0x1f, 5, 2, 0), 0x03e00008, 0], 0x100000,
                          {'0': ['jal', wrapper['addr'], 0, wrapper['name']]})
            rows = self.infer([consumer, wrapper, getter, dead])
            self.assertEqual(rows[getter['addr']]['ret'], 's128')
            self.assertEqual(rows[wrapper['addr']]['ret'], 's128')
            self.assertEqual(rows[dead['addr']]['ret'], 'unknown')
            self.assertNotIn('s128', rows[dead['addr']]['params'])

    def test_return_passed_to_typed_sink_is_real_demand(self):
        sink = fn([0x03e00008, 0], 0x300000)
        for typ in ('s128', 'f64'):
            # por copies all 128 bits; daddu suffices for the software double.
            to_v0 = 0x708014a9 if typ == 's128' else r(4, 0, 2, 0x2d)
            to_a0 = 0x704024a9 if typ == 's128' else r(2, 0, 4, 0x2d)
            producer = fn([to_v0, 0x03e00008, 0], 0x200000)
            caller = fn([0x0c080000, 0, to_a0, 0x0c0c0000, 0, 0x03e00008, 0],
                        rel={'0': ['jal', producer['addr'], 0, producer['name']],
                             '3': ['jal', sink['addr'], 0, sink['name']]})
            rows = self.infer([caller, producer, sink],
                {sink['addr']: self.seed('void', params=[(typ, None)])})
            self.assertEqual(rows[producer['addr']]['ret'], typ)
            self.assertEqual(rows[producer['addr']]['params'][0], typ)
            self.assertEqual(rows[producer['addr']]['return_evidence']['consumers'], 0)


class LayoutTests(unittest.TestCase):
    def test_signedness_is_not_a_false_overlap(self):
        fields = [(4, 4, 's32', 1, 0), (4, 4, 'u32', 2, 0), (8, 4, 'f32', 1, 1)]
        self.assertEqual([f['offset'] for f in cr.layout_fields(fields)], [4, 8])

    def test_union_overlap_and_unaligned_fields_stay_opaque(self):
        fields = [(0, 8, 'u64', 1, 0), (4, 4, 'u32', 2, 0), (9, 4, 's32', 3, 0), (16, 4, 'f32', 3, 1)]
        self.assertEqual([f['offset'] for f in cr.layout_fields(fields)], [16])

    def test_two_types_same_offset_are_not_silently_chosen(self):
        self.assertEqual(cr.layout_fields([(0, 4, 'u32', 1, 0), (0, 4, 'f32', 2, 0)]), [])



class EvidenceBoundaryTests(unittest.TestCase):
    def test_software_double_uses_integer_argument_bank(self):
        params = [('s32', None), ('f64', None), ('f32', None), ('s128', None)]
        self.assertEqual(cr.abi_slots(params), [(0, 's32'), (1, 'f64'), (8, 'f32'), (2, 's128')])

    def test_double_return_links_integer_argument(self):
        f = fn([r(4, 0, 2, 0x2d), 0x03e00008, 0])
        seed = dict(params=[('f64', None)], ret='f64', quality=3, cls=None, source='double.c')
        signatures, _ = cr.recover_signatures([f], {f['addr']: cr.analyze_function(f)}, {f['addr']: seed})
        self.assertEqual(signatures[f['addr']]['params'][0], 'f64')
        self.assertEqual(signatures[f['addr']]['ret'], 'f64')

    def test_vector_store_does_not_type_unrelated_integer_argument(self):
        f = fn([i(0x3e, 4, 5, 0), 0x03e00008, 0])
        result = cr.analyze_function(f)
        self.assertFalse(any(kind == 'arg' and slot == 1 and typ in ('u128', 's128')
                             for kind, slot, typ, pc in result['uses']))
        self.assertTrue(any(size == 16 for kind, slot, off, size, typ, pc in result['fields']))

    def test_statements_are_not_declarations(self):
        parsed = cr.parse_declarations('int Caller(int x) {\n return Callee(x, 1);\n}\nextern float Callee(int, float);')
        self.assertEqual([p['name'] for p in parsed], ['Caller', 'Callee'])
        self.assertEqual(parsed[1]['ret'], 'f32')

    def test_ee_banks_are_independent(self):
        params = [('void *', None), ('f32', None), ('s32', None), ('f32', None)]
        self.assertEqual(cr.abi_slots(params), [(0, 'void *'), (8, 'f32'), (1, 's32'), (9, 'f32')])
        slots = cr.abi_slots([('s32', None)] * 9 + [('f32', None)])
        self.assertEqual(slots[-2:], [(16, 's32'), (8, 'f32')])

    def test_integer_copy_is_not_a_64bit_abi_argument(self):
        # daddu s0,a0,zero: the instruction is 64-bit, the C value may be a pointer.
        f = fn([r(4, 0, 16, 0x2d), i(0x23, 16, 2, 0), 0x03e00008, 0])
        analysis = cr.analyze_function(f)
        self.assertFalse(any(typ == 's64' for kind, n, typ, pc in analysis['uses']))

    def test_syscall_source_stub_does_not_prove_zero_arity(self):
        call = fn([i(9, 0, 4, 1), 0x0c080000, 0, 0x03e00008, 0], rel={'1': ['jal', 0x200000, 0, 'func_00200000']})
        stub = fn([0x0000000c, 0x03e00008, 0], 0x200000)
        seed = dict(params=[], ret='void', body='__asm__("syscall");', quality=3, cls=None, source='stub.c')
        signatures, _ = cr.recover_signatures([call, stub], {f['addr']: cr.analyze_function(f) for f in (call, stub)}, {0x200000: seed})
        self.assertEqual(signatures[0x200000]['arity'], 1)

    def test_generic_api_does_not_flood_unresolved_conflicts(self):
        self.assertEqual(cr.resolve_type({'f32', 's128', 'void *'})[0], 'unknown')


class FieldPointerTests(unittest.TestCase):
    def test_loaded_pointer_field_is_recognized_when_dereferenced(self):
        f = fn([i(0x23, 4, 2, 8), i(0x23, 2, 3, 4), 0x03e00008, 0])
        fields = cr.analyze_function(f)['fields']
        self.assertIn(('arg', 0, 8, 4, 'void *', 1), fields)
        self.assertEqual(cr.layout_fields([(8, 4, 's32', 1, 0), (8, 4, 'void *', 1, 1)])[0]['type'], 'void *')


class VerificationTests(unittest.TestCase):
    def test_namespaced_camera_method_exports_exact_128_bit_arguments(self):
        from unittest.mock import patch
        unit = dict(source='src/game/camera/actor_camera.cpp', externs={}, functions=[dict(
            addr=0x141248, symbol='SetTarget__Q213CampaignActor16CameraControllerxxfl', status='source')])
        with patch('units.load_units', return_value=[unit]):
            seeds, _ = cr.source_seeds(matched_only=True)
        self.assertEqual(seeds[0x141248]['ret'], 'void')
        self.assertTrue(seeds[0x141248]['this_usage'])
        self.assertEqual([kind for kind, _ in seeds[0x141248]['params']],
                         ['void *', 's128', 's128', 'f32', 's64'])

    def test_qualified_owner_disambiguates_same_leaf_class_names(self):
        import tempfile
        from unittest.mock import patch
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'include').mkdir()
            (root / 'src').mkdir()
            (root / 'src/classes.cpp').write_text('''
namespace First { struct Queue { int Get(short); };
int Queue::Get(short n) { return n; } }
namespace Other { struct Queue { float Get(float); };
float Queue::Get(float n) { return n; } }
''')
            unit = dict(source='src/classes.cpp', externs={}, functions=[dict(
                addr=0x100000, symbol='Get__Q25First5QueueSs', status='source')])
            with patch('units.load_units', return_value=[unit]), patch(
                    'units.dependencies', return_value=[Path(unit['source'])]):
                seeds, _ = cr.source_seeds(root, matched_only=True)
            self.assertEqual(seeds[0x100000]['ret'], 's32')
            self.assertEqual(seeds[0x100000]['params'][1], ('s16', None))

    def test_undecoded_overload_arguments_do_not_select_a_signature(self):
        import tempfile
        from unittest.mock import patch
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'include').mkdir()
            (root / 'src').mkdir()
            (root / 'src/overloads.cpp').write_text('''
namespace First { struct Queue { int Get(short); float Get(float); };
int Queue::Get(short n) { return n; }
float Queue::Get(float n) { return n; } }
''')
            unit = dict(source='src/overloads.cpp', externs={}, functions=[dict(
                addr=0x100000, symbol='Get__Q25First5QueueSs', status='source')])
            with patch('units.load_units', return_value=[unit]), patch(
                    'units.dependencies', return_value=[Path(unit['source'])]):
                seeds, evidence = cr.source_seeds(root, matched_only=True)
            self.assertNotIn(0x100000, seeds)
            self.assertTrue(any(e['kind'] == 'source-overload-ambiguous' for e in evidence))

    def test_address_only_asm_claim_is_not_source_evidence(self):
        import tempfile
        from unittest.mock import patch
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'include').mkdir()
            (root / 'src').mkdir()
            (root / 'src/claimed.cpp').write_text('''
extern int func_00100000(short);
int func_00100010(float n) { return n; }
''')
            unit = dict(source='src/claimed.cpp', externs={}, functions=[
                dict(addr=0x100000, status='asm'),
                dict(addr=0x100010, symbol='func_00100010', status='source')])
            with patch('units.load_units', return_value=[unit]), patch(
                    'units.dependencies', return_value=[Path(unit['source'])]):
                matched, _ = cr.source_seeds(root, matched_only=True)
                all_seeds, _ = cr.source_seeds(root)
            self.assertEqual(set(matched), {0x100010})
            self.assertEqual(all_seeds[0x100000]['params'], [('s16', None)])
            self.assertFalse(all_seeds[0x100000]['matched'])
            self.assertEqual(all_seeds[0x100000]['symbol'], 'func_00100000')

    def test_alias_context_is_per_translation_unit(self):
        import tempfile
        from unittest.mock import patch
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'include').mkdir()
            (root / 'src').mkdir()
            (root / 'include/vector.hpp').write_text('''
namespace BlackGame { typedef long long PositionArg; typedef PositionArg Vec; }
namespace BlackPS2 { namespace VU0 { typedef BlackGame::Vec Value; } }
''')
            (root / 'src/wide.cpp').write_text('''
#include "vector.hpp"
using BlackPS2::VU0::Value;
Value func_00100000(Value point) { return point; }
''')
            (root / 'src/narrow.cpp').write_text('''
typedef unsigned short Value;
Value func_00100010(Value count) { return count; }
''')
            (root / 'src/unknown.cpp').write_text('''
Value func_00100020(Value count) { return count; }
''')
            units = [dict(source='src/' + name + '.cpp', externs={}, functions=[
                dict(addr=addr, symbol='func_%08X' % addr, status='source')])
                for name, addr in [('wide', 0x100000), ('narrow', 0x100010), ('unknown', 0x100020)]]
            def dependencies(source):
                return [Path(source)] + ([Path('include/vector.hpp')] if 'wide' in source else [])
            with patch('units.load_units', return_value=units), patch('units.dependencies', side_effect=dependencies):
                seeds, _ = cr.source_seeds(root, matched_only=True)
            self.assertEqual((seeds[0x100000]['ret'], seeds[0x100000]['params']), ('s128', [('s128', None)]))
            self.assertEqual((seeds[0x100010]['ret'], seeds[0x100010]['params']), ('u16', [('u16', None)]))
            self.assertEqual((seeds[0x100020]['ret'], seeds[0x100020]['params']), ('unknown', [('unknown', None)]))

    def test_exact_matrix_consumers_export_signed_128_bit_values(self):
        from unittest.mock import patch
        # These production consumers also validate the shared matrix helpers against retail.
        unit = dict(source='src/game/ai/vu0_matrix.cpp', externs={}, functions=[
            dict(addr=addr, symbol='func_%08X' % addr, status='source')
            for addr in (0x17bdf0, 0x1a71f8)])
        with patch('units.load_units', return_value=[unit]):
            seeds, _ = cr.source_seeds(matched_only=True)
        self.assertEqual(seeds[0x17bdf0]['ret'], 'void')
        self.assertEqual(seeds[0x17bdf0]['params'], [('s128', None)])
        self.assertEqual(seeds[0x1a71f8]['ret'], 's128')
        self.assertEqual(seeds[0x1a71f8]['params'], [('void *', 'BlackPS2::DirectionSource')])

    def test_unmatched_signature_does_not_hide_matched_layout_user(self):
        import tempfile
        from unittest.mock import patch
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for name in ('src/auto', 'include/game/partial'):
                (root / name).mkdir(parents=True)
            (root / 'src/owner.cpp').write_text('')
            (root / 'include/owner.h').write_text(
                'struct OriginalOwner { int Read() __asm__("func_00100000"); };')
            (root / 'include/game/partial/Recovered_Node.h').write_text('')
            (root / 'src/auto/a.c').write_text(
                'int func_00100000(Recovered_Node *p) { return p->field_4; }')
            units = [dict(source='src/owner.cpp', functions=[], externs={}),
                     dict(source='src/auto/a.c', origin='auto', externs={},
                          functions=[dict(addr=0x100000, symbol='func_00100000', status='source')])]
            def dependencies(source):
                header = ('include/owner.h' if source == 'src/owner.cpp'
                          else 'include/game/partial/Recovered_Node.h')
                return [Path(source), Path(header)]
            with patch('units.load_units', return_value=units), patch('units.dependencies', side_effect=dependencies):
                seeds, _ = cr.source_seeds(root)
                self.assertFalse(seeds[0x100000]['matched'])
                self.assertEqual(cr.verified_layout_users(['Recovered_Node'], root),
                                 {'Recovered_Node': [0x100000]})

    def test_layout_verification_counts_only_matched_member_users(self):
        from unittest.mock import patch
        seeds = {1: dict(matched=True, source='src/a.c', raw='void a(Recovered_Node *n)', body='n->field_4 = 1;'),
                 2: dict(matched=True, source='src/a.c', raw='void b(Recovered_Node *n)', body='sink(n);'),
                 3: dict(matched=False, source='src/a.c', raw='void c(Recovered_Node *n)', body='n->field_4 = 1;')}
        with patch.object(cr, 'source_seeds', return_value=(seeds, [])), patch('units.dependencies', return_value=[Path('include/game/partial/Recovered_Node.h')]):
            self.assertEqual(cr.verified_layout_users(['Recovered_Node']), {'Recovered_Node': [1]})


class CppAbiTests(unittest.TestCase):
    def test_namespace_and_class_aliases_resolve_without_global_name_guesses(self):
        declarations = cr.parse_declarations('''
namespace BlackGame {
typedef long long PositionArg;
typedef long long PositionResult;
typedef PositionArg Vec;
PositionResult Load(PositionArg);
struct Reader { typedef unsigned short Value; Value Count(Value); };
}
namespace BlackPS2 { namespace VU0 {
typedef BlackGame::Vec Value;
Value Transform(Value point);
} }
namespace Other { typedef unsigned int Value; Value Read(Value count); }
BlackGame::Vec Wide(BlackGame::PositionArg point);
Value Unresolved(Value point);
''')
        methods = {d['short']: d for d in declarations}
        for name in ('Load', 'Transform', 'Wide'):
            self.assertEqual(methods[name]['ret'], 's128')
            self.assertEqual(methods[name]['params'], [('s128', None)])
        self.assertEqual(methods['Count']['ret'], 'u16')
        self.assertEqual(methods['Count']['params'][-1], ('u16', None))
        self.assertEqual(methods['Read']['ret'], 'u32')
        self.assertEqual(methods['Unresolved']['ret'], 'unknown')
        self.assertEqual(methods['Unresolved']['params'], [('unknown', None)])
        self.assertEqual(cr.normalize_type('Value')[0], 'unknown')

    def test_explicit_import_and_out_of_class_alias_lookup(self):
        declarations = cr.parse_declarations('''
namespace N { struct Reader { typedef long long Result; Result Read(Result); }; }
N::Reader::Result N::Reader::Read(Result value) { return value; }
using N::Reader::Result;
Result Sink(Result value);
''')
        self.assertTrue(all(d['ret'] == 's128' for d in declarations))
        self.assertTrue(all(d['params'][-1] == ('s128', None) for d in declarations))

    def test_unsupported_or_conflicting_aliases_remain_unknown(self):
        declarations = cr.parse_declarations('''
typedef int EeS128 __attribute__((mode(TI)));
typedef unsigned int EeU128 __attribute__((mode(__TI__)));
typedef int Conflict;
typedef long long Conflict;
typedef CycleA CycleB;
typedef CycleB CycleA;
typedef char Storage[16];
EeS128 Signed(EeU128 value);
Conflict Uncertain(CycleA value, Storage storage);
void Local() { typedef long long Hidden; }
Hidden Outside(Hidden value);
const char *example = "typedef long long Example;";
Example Unproved(Example value);
''')
        methods = {d['short']: d for d in declarations}
        self.assertEqual(methods['Signed']['ret'], 's128')
        self.assertEqual(methods['Signed']['params'], [('u128', None)])
        self.assertEqual(methods['Uncertain']['ret'], 'unknown')
        self.assertEqual(methods['Uncertain']['params'], [('unknown', None), ('unknown', None)])
        self.assertEqual(methods['Outside']['ret'], 'unknown')
        self.assertEqual(methods['Unproved']['ret'], 'unknown')

    def test_class_scoped_alias_preserves_receiver_and_static_methods(self):
        declarations = cr.parse_declarations('''namespace Sample {
struct View {
    const char* Read() const __asm__("func_00100000");
    static int Count(unsigned short n);
    virtual ~View();
};
}''')
        methods = {d['short']: d for d in declarations}
        self.assertEqual(methods['Read']['name'], 'View::Read')
        self.assertEqual(methods['Read']['address'], 0x100000)
        self.assertEqual(methods['Read']['params'], [('void *', 'View')])
        self.assertTrue(methods['Read']['implicit_this'])
        self.assertEqual(methods['Count']['params'], [('u16', None)])
        self.assertFalse(methods['Count']['implicit_this'])
        self.assertEqual(methods['~View']['ret'], 'void')
        self.assertTrue(methods['~View']['abi_uncertainty'])

    def test_lexical_scope_ignores_literals_and_function_local_declarations(self):
        declarations = cr.parse_declarations('''struct Outer {
struct Inner {
    const char* Name() { return "}"; }
    int Read() { extern int helper(int); return helper(1); }
};
};''')
        methods = {d['short']: d for d in declarations}
        self.assertEqual(methods['Name']['name'], 'Outer::Inner::Name')
        self.assertEqual(methods['Read']['params'], [('void *', 'Outer::Inner')])
        self.assertEqual(methods['helper']['params'], [('s32', None)])
        self.assertFalse(methods['helper']['implicit_this'])

    def test_namespace_and_static_method_have_no_this(self):
        from unittest.mock import patch
        with patch.object(cr, 'CLASS_NAMES', {'Object'}), patch.object(cr, 'NAMESPACE_NAMES', {'Library'}), patch.object(cr, 'STATIC_METHODS', {('Object', 'Static')}):
            namespace = cr.parse_declarations('int Library::Value(int x) { return x; }')[0]
            static = cr.parse_declarations('int Object::Static(int x) { return x; }')[0]
        self.assertEqual(namespace['params'], [('s32', None)])
        self.assertEqual(static['params'], [('s32', None)])
        self.assertFalse(namespace['implicit_this'])
        self.assertFalse(static['implicit_this'])

    def test_hidden_cpp_abi_arguments_are_explicitly_ambiguous(self):
        from unittest.mock import patch
        with patch.object(cr, 'CLASS_NAMES', {'Object'}):
            constructor = cr.parse_declarations('Object::Object(void) {}')[0]
            aggregate = cr.parse_declarations('Object Object::Value(void) { return *this; }')[0]
        self.assertTrue(any('in-charge' in x for x in constructor['abi_uncertainty']))
        self.assertTrue(any('aggregate-return' in x for x in aggregate['abi_uncertainty']))

    def test_automatic_void_signature_cannot_override_caller_argument(self):
        call = fn([i(9, 0, 4, 1), 0x0c080000, 0, 0x03e00008, 0], rel={'1': ['jal', 0x200000, 0, 'func_00200000']})
        stub = fn([0x03e00008, 0], 0x200000)
        seed = dict(params=[], ret='void', body='return;', quality=1.5, cls=None, source='auto.c')
        signatures, _ = cr.recover_signatures([call, stub], {f['addr']: cr.analyze_function(f) for f in (call, stub)}, {0x200000: seed})
        self.assertEqual(signatures[0x200000]['arity'], 1)




class CalleeReturnEvidenceTests(unittest.TestCase):
    def test_weak_void_wrapper_preserves_integer_callee_return(self):
        callee = fn([i(9, 0, 2, 1), 0x03e00008, 0], 0x200000)
        wrapper = fn([i(9, 29, 29, -16), i(0x3f, 29, 31, 0), 0x0c080000, 0,
                      i(0x37, 29, 31, 0), 0x03e00008, i(9, 29, 29, 16)],
                     rel={'2': ['jal', 0x200000, 0, callee['name']]})
        seed = dict(params=[], ret='void', quality=1.5, source='auto.c', cls=None)
        analysis = {f['addr']: cr.analyze_function(f) for f in (wrapper, callee)}
        signatures, _ = cr.recover_signatures([wrapper, callee], analysis, {wrapper['addr']: seed})
        self.assertEqual(signatures[wrapper['addr']]['ret'], 's32')
        seed['quality'] = 4
        signatures, _ = cr.recover_signatures([wrapper, callee], analysis, {wrapper['addr']: seed})
        self.assertEqual(signatures[wrapper['addr']]['ret'], 'void')

    def float_call_fixture(self):
        # A realistic caller saves ra, calls a helper, then consumes its f0 result.
        caller = fn([i(9, 29, 29, -16), i(0x3f, 29, 31, 0), 0x0c080000, 0,
                     0x46000002, i(0x37, 29, 31, 0), 0x03e00008, i(9, 29, 29, 16)],
                    0x100000, {'2': ['jal', 0x200000, 0, 'func_00200000']})
        # lwc1 f0,0(a0); jr ra; nop -- the helper physically returns a float.
        callee = fn([i(0x31, 4, 0, 0), 0x03e00008, 0], 0x200000)
        return caller, callee

    def seed(self, quality, ret):
        return dict(params=[('void *', None)], ret=ret, body='return 0;',
                    quality=quality, cls=None, source='guarded.c', matched=quality >= 2)

    def test_float_return_consumption_is_recorded_without_incoming_argument(self):
        caller, callee = self.float_call_fixture()
        analysis = cr.analyze_function(caller)
        self.assertIn(('ret', callee['addr'], 'f32', 4), analysis['uses'])
        rows, _ = cr.recover_signatures([caller, callee],
            {f['addr']: cr.analyze_function(f) for f in (caller, callee)}, {})
        self.assertLessEqual(rows[caller['addr']]['arity'] or 0, 16)
        self.assertEqual(rows[callee['addr']]['ret'], 'f32')

    def test_unmatched_wrong_integer_return_is_hint_not_authority(self):
        caller, callee = self.float_call_fixture()
        rows, _ = cr.recover_signatures([caller, callee],
            {f['addr']: cr.analyze_function(f) for f in (caller, callee)},
            {callee['addr']: self.seed(1.75, 's32')})
        helper = rows[callee['addr']]
        self.assertEqual(helper['ret'], 'f32')
        self.assertEqual(helper['return_hint'], 's32')
        self.assertTrue(any(conflict.get('kind') == 'source-hint-disagrees' for conflict in helper['conflicts']))

    def test_matched_signature_stays_anchored_and_conflict_is_retained(self):
        caller, callee = self.float_call_fixture()
        rows, _ = cr.recover_signatures([caller, callee],
            {f['addr']: cr.analyze_function(f) for f in (caller, callee)},
            {callee['addr']: self.seed(4, 's32')})
        self.assertEqual(rows[callee['addr']]['ret'], 's32')
        self.assertTrue(rows[callee['addr']]['conflicts'])

    def test_return_used_as_address_does_not_create_caller_argument(self):
        caller = fn([0x0c080000, 0, i(0x23, 2, 3, 0), 0x03e00008, 0],
                    0x100000, {'0': ['jal', 0x200000, 0, 'func_00200000']})
        analysis = cr.analyze_function(caller)
        self.assertIn(('ret', 0x200000, 'void *', 2), analysis['uses'])
        rows, _ = cr.recover_signatures([caller], {caller['addr']: analysis}, {})
        self.assertIsNone(rows[caller['addr']]['arity'])


    def test_compatible_unmatched_pointer_hint_preserves_pointee(self):
        callee = fn([i(0x23, 4, 2, 0), 0x03e00008, 0], 0x200000)
        rows, _ = cr.recover_signatures([callee], {callee['addr']: cr.analyze_function(callee)},
            {callee['addr']: self.seed(1.75, 'f32 *')})
        self.assertEqual(rows[callee['addr']]['ret'], 'f32 *')




class ScalarPointeeTests(unittest.TestCase):
    def field(self):
        return [dict(offset=8, size=4, type='void *', functions=[1])]

    def test_compatible_zero_offset_scalars_refine_across_users(self):
        fields = cr.refine_scalar_pointees(self.field(), [(8,0,4,'s32',1,0),(8,0,4,'u32',2,0)])
        self.assertEqual(fields[0]['type'], 's32 *')
        self.assertEqual(fields[0]['pointee_accesses'], 2)
        self.assertEqual(cr.refine_scalar_pointees(self.field(), [(8,0,4,'f32',1,0)])[0]['type'], 'f32 *')

    def test_conflicting_nonzero_and_unknown_accesses_stay_opaque(self):
        for nested in ([(8,0,4,'s32',1,0),(8,0,4,'f32',2,0)],
                       [(8,4,4,'s32',1,0)],[(8,None,0,'unknown-use',1,0)],
                       [(8,0,4,'s32',1,0),(8,None,0,'nested-pointer',1,1)]):
            self.assertEqual(cr.refine_scalar_pointees(self.field(), nested)[0]['type'], 'void *')

    def test_pointer_arithmetic_preserves_parent_and_records_pointee_offset(self):
        f = fn([i(0x23,4,2,8),i(9,2,2,4),i(0x23,2,3,0),0x03e00008,0])
        analysis = cr.analyze_function(f)
        self.assertIn((0,8,4,4,'s32',2), analysis['nested'])
        self.assertFalse(any(off == 12 for kind, slot, off, size, typ, pc in analysis['fields']))
        self.assertIn(('arg',0,8,4,'void *',2),analysis['fields'])

    def test_nested_pointer_chasing_blocks_scalar_pointee(self):
        f = fn([i(0x23,4,2,8),i(0x23,2,3,0),i(0x23,3,5,0),0x03e00008,0])
        analysis=cr.analyze_function(f)
        rows=[(parent,off,size,typ,f['addr'],pc) for slot,parent,off,size,typ,pc in analysis['nested']]
        self.assertEqual(cr.refine_scalar_pointees(self.field(), rows)[0]['type'],'void *')


    def test_null_check_does_not_disqualify_scalar_pointee(self):
        f=fn([i(0x23,4,2,8),i(4,2,0,2),0,i(0x23,2,3,0),0x03e00008,0])
        analysis=cr.analyze_function(f)
        rows=[(parent,off,size,typ,f['addr'],pc) for slot,parent,off,size,typ,pc in analysis['nested']]
        self.assertEqual(cr.refine_scalar_pointees(self.field(),rows)[0]['type'],'s32 *')


if __name__ == '__main__':
    unittest.main()
