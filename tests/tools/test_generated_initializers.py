"""Explicit address bindings for randomly named SN static I/D wrappers."""
import sys
import unittest
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build')]
from object_compile import generated_function_aliases


class GeneratedInitializers(unittest.TestCase):
    def function(self, role='I', address=0x100100):
        return dict(addr=address, symbol='_GLOBAL_$%s$%08X' % (role, address))

    def symbols(self, *names):
        return {name: dict(name=name, type=2) for name in names}

    def test_random_suffixes_bind_to_the_same_explicit_address(self):
        expected = '_GLOBAL_$I$00100100'
        for actual in ('_GLOBAL_$I$source.cppabc123', '_GLOBAL_$I$source.cppXYZ789'):
            self.assertEqual({expected: actual}, generated_function_aliases(
                [self.function()], self.symbols(actual)))

    def test_roles_are_distinct_and_nonfunctions_are_ignored(self):
        defined = self.symbols('_GLOBAL_$I$source.random', '_GLOBAL_$D$source.random')
        defined['data'] = dict(name='_GLOBAL_$I$data', type=1)
        self.assertEqual({'_GLOBAL_$D$00100100': '_GLOBAL_$D$source.random'},
                         generated_function_aliases([self.function('D')], defined))

    def test_missing_and_ambiguous_wrappers_fail(self):
        for defined in ({}, self.symbols('_GLOBAL_$I$one', '_GLOBAL_$I$two')):
            with self.assertRaisesRegex(ValueError, 'expected one compiler-generated'):
                generated_function_aliases([self.function()], defined)

    def test_address_must_belong_to_the_requested_function(self):
        function = self.function()
        function['addr'] += 8
        for actual in ('_GLOBAL_$I$source.random', function['symbol']):
            with self.subTest(actual=actual), self.assertRaisesRegex(ValueError, 'address disagrees'):
                generated_function_aliases([function], self.symbols(actual))

    def test_ordinary_names_and_existing_exact_bindings_are_unchanged(self):
        function = dict(addr=0x100100, symbol='func_00100100')
        self.assertEqual({}, generated_function_aliases([function], self.symbols('_GLOBAL_$I$one')))
        function = self.function()
        self.assertEqual({}, generated_function_aliases([function], self.symbols(function['symbol'])))

    def test_binding_can_be_one_of_several_candidates(self):
        function = dict(addr=0x100100, symbol='func_00100100',
                        candidates=['func_00100100', '_GLOBAL_$I$00100100'])
        self.assertEqual({'_GLOBAL_$I$00100100': '_GLOBAL_$I$source.random'},
                         generated_function_aliases([function], self.symbols('_GLOBAL_$I$source.random')))


if __name__ == '__main__':
    unittest.main()
