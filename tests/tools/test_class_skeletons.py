"""Synthetic legacy-ABI tests; no game bytes or target tools."""
from pathlib import Path
import sys
import json
import tempfile
import unittest
sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
from class_skeletons import (decode_name, identifier, cpp_type, field_type, table_inventory,
                             vptr_stores, signature, render_header, rendered_files, generate, load_context, table_fields)


class SyntheticImage:
    def __init__(self, sections):
        self.sections = sections
    def words(self, section):
        return self.sections.get(section, (0, []))


def class_row(name='Example'):
    return dict(name=name, cpp_name=name, class_identity='RTTI', getters=[], bases=[], methods=[],
                fields=[], constructors=[], destructors=[], vtables=[], virtual_view=None,
                header='game/classes/other/' + name + '.hpp')


class LegacyNames(unittest.TestCase):
    def test_qualified_and_nested_classes(self):
        self.assertEqual(decode_name('Q24Kaim7CObject'), ('Kaim::CObject', True))
        self.assertEqual(decode_name('Q34Kaim8CService5Entry'), ('Kaim::CService::Entry', True))
    def test_templates_and_nested_members(self):
        self.assertEqual(decode_name('Q34Kaimt5CList1ZPQ24Kaim7CEntity8Iterator'),
                         ('Kaim::CList<Kaim::CEntity*>::Iterator', True))
    def test_function_pointer_template_argument_and_integral_argument(self):
        name, valid = decode_name('Q24Kaimt4CMap2ZPFi_vUi16')
        self.assertTrue(valid)
        self.assertIn('void (*)(int)', name)
        self.assertIn('16 /* unsigned int */', name)
    def test_anonymous_names_never_export_source_paths(self):
        component = '_GLOBAL_$N$directory_source.cpp'
        encoded = 'Q2' + str(len(component)) + component + '7Example'
        name, valid = decode_name(encoded)
        self.assertTrue(valid)
        self.assertTrue(name.startswith('Anonymous_'))
        self.assertNotIn('directory', name)
        self.assertNotIn('source.cpp', name)
    def test_malformed_names_remain_explicitly_unknown_without_copying_raw_text(self):
        name, valid = decode_name('Q2incomplete')
        self.assertFalse(valid)
        self.assertTrue(name.startswith('UnparsedType_'))
    def test_long_template_identifiers_are_stable_and_bounded(self):
        encoded = 'synthetic'
        self.assertEqual(identifier('A<' + 'B' * 300 + '>', encoded), identifier('A<' + 'B' * 300 + '>', encoded))
        self.assertLess(len(identifier('A<' + 'B' * 300 + '>', encoded)), 110)


class VtableEvidence(unittest.TestCase):
    def inv(self, *addresses):
        return [dict(addr=a, rel={}, words=[]) for a in addresses]
    def test_rtti_header_is_not_a_virtual_method(self):
        image = SyntheticImage({'.data': (0x2000, [0, 0x1100, 0, 0x1200, 0, 0x1300])})
        table, = table_inventory(image, self.inv(0x1100, 0x1200, 0x1300), {0x1100: 'Class'})
        self.assertEqual(table['getter'], 0x1100)
        self.assertEqual([s['function'] for s in table['slots']], [0x1200, 0x1300])
        self.assertEqual(table['slots'][0]['offset'], 8)
    def test_this_delta_is_signed_sixteen_bits_not_signed_word(self):
        image = SyntheticImage({'.data': (0x2000, [0, 0x1100, 0xfff0, 0x1200])})
        table, = table_inventory(image, self.inv(0x1100, 0x1200), {0x1100: 'Class'})
        self.assertEqual(table['slots'][0]['adjustment'], -16)
    def test_referenced_zero_header_can_identify_a_single_destructor_table(self):
        inv = self.inv(0x1200)
        inv[0]['rel'] = {'0': ['lo', 0x2000, 0, 'table']}
        image = SyntheticImage({'.data': (0x2000, [0, 0, 0, 0x1200])})
        table, = table_inventory(image, inv, {})
        self.assertEqual(table['vptr'], 0x2000)
        self.assertEqual(table['context_group'], 0x2008)
    def test_unreferenced_callback_run_stays_unverified(self):
        image = SyntheticImage({'.data': (0x2000, [0, 0x1200, 0, 0x1300, 0, 0x1400])})
        table, = table_inventory(image, self.inv(0x1200, 0x1300, 0x1400), {})
        self.assertIsNone(table['vptr'])
        self.assertTrue(table['basis'].startswith('unverified'))
    def test_store_offset_is_only_evidence_not_complete_object_identity(self):
        inv = [dict(addr=0x1000, rel={'0': ['hi', 0x3d0100, 0, 'table']},
                    words=[0x3c08003d, 0x25080100, 0xac880010])]
        stores = vptr_stores(inv, {0x3d0100})
        self.assertEqual(stores[0x3d0100][0]['offset'], 16)


class TypesAndGeneration(unittest.TestCase):
    def test_exact_named_receiver_retains_fields_after_vtable_group_split(self):
        field = dict(offset=0x100, size=4, type='s32', functions=[0x1200])
        table = dict(context_group=0x2000, slots=[dict(function=0x1200)])
        context = dict(signatures={'4608': dict(this=True, source_quality=4)}, layouts={
            'Recovered_Named': dict(nodes=[[0x1200, 0]], fields=[field])})
        fields = list(table_fields(table, context, {0x1200}))
        self.assertEqual(fields[0][0], field)
        self.assertEqual(fields[0][1], [0x1200])
        context['layouts']['Recovered_Named']['nodes'] = [[0x1200, 1]]
        self.assertEqual(list(table_fields(table, context, {0x1200})), [])
        context['layouts']['Recovered_Named']['nodes'] = [[0x1200, 0]]
        table['slots'][0]['adjustment'] = 8
        self.assertEqual(list(table_fields(table, context, {0x1200})), [])

    def test_named_receiver_does_not_replace_an_existing_or_explicit_view(self):
        old = dict(offset=0x100, size=4, type='u32', functions=[0x1200])
        new = dict(old, type='s32')
        table = dict(context_group=0x2000, slots=[dict(function=0x1200)])
        context = dict(signatures={'4608': dict(this=True, source_quality=4)}, layouts={
            'Recovered_Vtable_00002000': dict(fields=[old]),
            'Recovered_Named': dict(nodes=[[0x1200, 0]], fields=[new])})
        self.assertEqual([f[0] for f in table_fields(table, context, {0x1200})], [old])
        del context['layouts']['Recovered_Vtable_00002000']
        self.assertEqual(list(table_fields(table, context, {0x1200}, {0x100})), [])

    def test_missing_context_fails_with_the_required_recovery_command(self):
        with tempfile.TemporaryDirectory() as directory:
            with self.assertRaisesRegex(SystemExit, 'tools/autodecomp.py context --refresh'):
                load_context(Path(directory))
    def test_context_is_loaded_without_a_self_referential_fingerprint_check(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 'build/auto/context.json'
            path.parent.mkdir(parents=True)
            expected = {'fingerprint': 'previous-generation', 'layouts': {}}
            path.write_text(json.dumps(expected))
            self.assertEqual(load_context(root), expected)
    def test_ee_widths_are_explicit(self):
        self.assertEqual(cpp_type('u128'), 'U128')
        self.assertEqual(cpp_type('s64'), 'long')
        self.assertEqual(field_type('unknown', 16), 'U128')
        self.assertEqual(field_type('unknown', 8), 'unsigned long')
        self.assertIsNone(field_type('unknown', 3))
    def test_matched_source_path_does_not_verify_inferred_return_type(self):
        context = {'signatures': {'4096': {'ret': 's32', 'params': ['void *'], 'source': 'src/example.c', 'source_quality': 0}}}
        self.assertFalse(signature(0x1000, context, {0x1000}, {})['verified'])
    def test_exact_probe_status_depends_on_registered_source(self):
        config = {'0x1000': {'return': 'void', 'params': []}}
        self.assertFalse(signature(0x1000, {}, set(), config)['verified'])
        self.assertTrue(signature(0x1000, {}, {0x1000}, config)['verified'])
    def test_variadic_parameter_is_not_named(self):
        row = class_row()
        row['methods'] = [dict(address=0x1000, name='Function_00001000', ret='void', params=['...'], verified=False, basis='test')]
        self.assertIn('Function_00001000(...);', render_header(row))
        self.assertNotIn('... argument', render_header(row))
    def test_callback_fields_use_a_named_function_pointer_typedef(self):
        row = class_row()
        row['fields'] = [dict(type='void (*)(int)', offset=16, verified_by=[])]
        header = render_header(row)
        self.assertIn('typedef void (*FieldType_0010)(int);', header)
        self.assertIn('FieldType_0010 & Field_0010()', header)
    def test_identified_deleting_destructor_occupies_its_real_virtual_slot(self):
        row = class_row()
        row['vtables'] = [dict(address=0x2000, vptr_offset=None, basis='RTTI header', slots=[
            dict(index=0, offset=8, adjustment=0, function=0x1000,
                 signature=dict(ret='void', params=[], verified=False), deleting_destructor={'evidence': 'synthetic'})])]
        text = render_header(row)
        self.assertIn('virtual ~VirtualInterface0();', text)
        self.assertNotIn('Slot000(', text)
    def test_probed_nonzero_vptr_view_keeps_prefix_before_virtual_members(self):
        row = class_row()
        row['virtual_view'] = dict(vptr_offset=16, return_type='void', params=[], slot_count=2)
        row['virtual_view']['return'] = 'void'
        text = render_header(row)
        self.assertLess(text.index('unknown_prefix[0x10]'), text.index('virtual void Slot000()'))
    def test_hierarchy_is_separate_from_storage_and_generated_tree_is_repeatable(self):
        base = class_row('Base')
        child = class_row('Child')
        child['bases'] = [dict(cpp_name='Base', access='public', offset=0, virtual=False)]
        model = {'classes': [child, base], 'records': {}}
        files = rendered_files(model)
        self.assertIn('Hierarchy_Child : public Hierarchy_Base', files[Path('game/classes/hierarchy.hpp')])
        self.assertNotIn('struct Child :', files[Path('game/classes/other/Child.hpp')])
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            generate(model, root)
            first = {p.relative_to(root): p.read_bytes() for p in root.rglob('*.hpp')}
            (root / 'game/classes/stale.hpp').write_text('obsolete')
            generate(model, root)
            self.assertEqual(first, {p.relative_to(root): p.read_bytes() for p in root.rglob('*.hpp')})


if __name__ == '__main__':
    unittest.main()
