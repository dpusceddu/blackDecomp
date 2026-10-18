"""Switch words must compare their linked targets, never raw object offsets."""
import struct
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from constant_relocs import constant_word


class Object:
    def __init__(self, target, kind=2):
        self.sections = [dict(index=0, type=1), dict(index=1, type=1),
                         dict(index=2, type=1), dict(index=3, type=9, info=2)]
        self.data = {2: struct.pack('<II', 0x24, 7), 3: struct.pack('<II', 0, 256 | kind)}
        self.symbols = [dict(name='', shndx=0, value=0), target]

    def content(self, section):
        return self.data[section['index']]


class ConstantRelocations(unittest.TestCase):
    function = dict(shndx=1, value=0x10)

    def test_local_switch_target_with_nonzero_function_offset(self):
        obj = Object(dict(name='', shndx=1, value=0))
        result = constant_word(obj, obj.symbols, obj.sections[2], 0, self.function, 0x100000)
        self.assertEqual(result, struct.pack('<I', 0x100014))

    def test_named_external_target(self):
        obj = Object(dict(name='func_00100100', shndx=0, value=0))
        self.assertEqual(constant_word(obj, obj.symbols, obj.sections[2], 0, self.function, 0x100000), struct.pack('<I', 0x100124))

    def test_unrelated_section_is_not_assumed_to_be_code(self):
        obj = Object(dict(name='', shndx=2, value=0))
        self.assertIsNone(constant_word(obj, obj.symbols, obj.sections[2], 0, self.function, 0x100000))

    def test_unsupported_relocation_is_not_accepted_as_literal(self):
        obj = Object(dict(name='', shndx=1, value=0), kind=5)
        self.assertIsNone(constant_word(obj, obj.symbols, obj.sections[2], 0, self.function, 0x100000))

    def test_nonrelocated_literal_is_unchanged(self):
        obj = Object(dict(name='', shndx=1, value=0))
        self.assertEqual(constant_word(obj, obj.symbols, obj.sections[2], 4, self.function, 0x100000), struct.pack('<I', 7))


if __name__ == '__main__':
    unittest.main()
