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

    def test_target_widths_do_not_conflate_real64_with_ee128(self):
        self.assertEqual(cr.normalize_type('long')[0], 's64')
        self.assertEqual(cr.normalize_type('long long')[0], 's128')
        self.assertEqual(cr.normalize_type('undefined8', True)[0], 'u64')
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
        inv = [caller, callee]
        signatures, links = cr.recover_signatures(inv, {f['addr']: cr.analyze_function(f) for f in inv}, {})
        self.assertEqual(signatures[0x100000]['ret'], 's128')
        self.assertEqual(signatures[0x200000]['ret'], 's128')


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
    def test_layout_verification_counts_only_matched_member_users(self):
        from unittest.mock import patch
        seeds = {1: dict(matched=True, source='src/a.c', raw='void a(Recovered_Node *n)', body='n->field_4 = 1;'),
                 2: dict(matched=True, source='src/a.c', raw='void b(Recovered_Node *n)', body='sink(n);'),
                 3: dict(matched=False, source='src/a.c', raw='void c(Recovered_Node *n)', body='n->field_4 = 1;')}
        with patch.object(cr, 'source_seeds', return_value=(seeds, [])), patch('units.dependencies', return_value=[Path('include/recovered/Recovered_Node.h')]):
            self.assertEqual(cr.verified_layout_users(['Recovered_Node']), {'Recovered_Node': [1]})


class CppAbiTests(unittest.TestCase):
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


if __name__ == '__main__':
    unittest.main()
