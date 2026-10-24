"""Owned sections resolve GPREL and literal addresses only with verified GP0."""
import struct
import sys
import types
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import autodecomp as auto


class SourceSectionRelocations(unittest.TestCase):
    def object(self, reginfo=True, literal=False):
        sections = [dict(index=0, name='', type=0),
                    dict(index=1, name='.text', type=1),
                    dict(index=2, name='.lit4' if literal else '.sbss', type=1 if literal else 8, size=16),
                    dict(index=3, name='.rel.text', type=9, info=1)]
        if reginfo:
            sections.append(dict(index=4, name='.reginfo', type=0x70000006, size=24))
        symbols = [dict(name='', shndx=0, value=0, size=0),
                   dict(name='func_00011000', shndx=1, value=0, size=8, type=2),
                   dict(name='', shndx=2, value=0, size=0, type=3)]
        kind = auto.LITERAL if literal else auto.GP
        words = (0xc781c000, 0xc780c004) if literal else (0x2784c000, 0x2784c008)
        content = {1: struct.pack('<II', *words), 2: b'\0D\xacF\0@\x1cF' if literal else b'',
                   3: struct.pack('<IIII', 0, 2 << 8 | kind, 4, 2 << 8 | kind),
                   4: struct.pack('<6I', 0, 0, 0, 0, 0, 0x4000)}
        return types.SimpleNamespace(sections=sections, symbols=lambda: symbols,
            section=lambda name: next((s for s in sections if s['name'] == name), None),
            content=lambda section: content[section['index']])

    def tokens(self, obj, **kwargs):
        with patch.object(auto, 'Elf', return_value=obj):
            result, error = auto.compiled_tokens(b'synthetic', 'func_00011000', **kwargs)
        self.assertIsNone(error)
        return result

    def test_local_section_restores_gp0_before_resolving_signed_addends(self):
        result = self.tokens(self.object(), section_bindings={'.sbss': 0x28000})
        self.assertEqual(result, [(0x27840000, ('gprel', 0x28000)),
                                  (0x27840000, ('gprel', 0x28008))])
        target = auto.Target(dict(words=[0x27840000, 0x27840000],
                                 rel={'0': ['gprel', 0x28000, 0], '1': ['gprel', 0x28008, 0]}), None)
        self.assertTrue(auto.score(target, result, lambda _: None)[0])
        wrong = self.tokens(self.object(), section_bindings={'.sbss': 0x28008})
        self.assertFalse(auto.score(target, wrong, lambda _: None)[0])

    def test_unknown_section_or_gp0_cannot_claim_an_address(self):
        for obj, bindings in [(self.object(), {}), (self.object(False), {'.sbss': 0x28000})]:
            result = self.tokens(obj, section_bindings=bindings)
            self.assertEqual(result[0][1], ('gprel', ('const', '.sbss', 'unresolved-constant-relocation')))

    def test_external_named_gp_symbol_does_not_receive_local_gp0(self):
        address = auto.source_symbol_address(self.object(),
            dict(name='D_00028000', shndx=0, value=0, type=0), auto.GP, {}, {'.sbss': 0x30000})
        self.assertEqual(address, 0x28000)

    def test_non_gp_section_relocation_does_not_receive_gp0(self):
        address = auto.source_symbol_address(self.object(),
            dict(name='', shndx=2, value=8, type=3), auto.LO, {}, {'.sbss': 0x28000})
        self.assertEqual(address, 0x28008)

    def test_literal_pool_restores_gp0_and_checks_both_exact_addresses(self):
        result = self.tokens(self.object(literal=True), section_bindings={'.lit4': 0x40d89c})
        self.assertEqual(result, [(0xc7810000, ('gprel', 0x40d89c)),
                                  (0xc7800000, ('gprel', 0x40d8a0))])
        target = auto.Target(dict(words=[0xc7810000, 0xc7800000],
            rel={'0': ['gprel', 0x40d89c, 0], '1': ['gprel', 0x40d8a0, 0]}), None)
        self.assertTrue(auto.score(target, result, lambda _: None)[0])
        shifted = self.tokens(self.object(literal=True), section_bindings={'.lit4': 0x40d8a0})
        self.assertFalse(auto.score(target, shifted, lambda _: None)[0])

    def test_literal_unknown_placement_or_missing_gp0_remains_unresolved(self):
        for obj, bindings in [(self.object(literal=True), {}),
                              (self.object(False, literal=True), {'.lit4': 0x40d89c})]:
            result = self.tokens(obj, section_bindings=bindings)
            self.assertEqual(result[0][1],
                ('gprel', ('const', '.lit4', 'unresolved-constant-relocation')))

    def test_named_literal_symbol_uses_its_image_address_without_local_gp0(self):
        address = auto.source_symbol_address(self.object(literal=True),
            dict(name='D_0040D89C', shndx=0, value=0, type=0), auto.LITERAL,
            {}, {'.lit4': 0x30000})
        self.assertEqual(address, 0x40d89c)


if __name__ == '__main__':
    unittest.main()
