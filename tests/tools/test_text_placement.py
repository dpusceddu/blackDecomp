"""Authored alignment fixtures; no target compiler or game bytes."""
import sys
import unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
from text_placement import natural_text_span, InputAlignments


class TextPlacementTests(unittest.TestCase):
    def test_alignment_comes_from_the_unique_actual_cached_input(self):
        import json
        import tempfile
        from unittest.mock import patch
        from types import SimpleNamespace
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'object.o').write_bytes(b'authored fixture')
            (root / 'objects_cache.json').write_text(json.dumps({'units/u': 'object.o'}))
            obj = {'name': 'units/u', 'rename': {'.text.f': '.text.00001080'}}
            (root / 'objects.json').write_text(json.dumps([obj]))
            with patch('text_placement.Elf', return_value=SimpleNamespace(
                    section=lambda name: {'align': 8, 'size': 24} if name == '.text.f' else None)):
                self.assertEqual(InputAlignments(root).at(0x1080), 8)
                self.assertIsNone(InputAlignments(root).at(0x1090))
                (root / 'objects.json').write_text(json.dumps([obj, obj]))
                self.assertIsNone(InputAlignments(root).at(0x1080))

    def test_natural_zero_fill_to_actual_next_section(self):
        self.assertTrue(natural_text_span(116, 0x1008, 0x1080, 8, bytes(4), 8))
        self.assertTrue(natural_text_span(196, 0x1000, 0x10c8, 8, bytes(4), 8))

    def test_data_alignment_resolves_source_and_assembly_inputs(self):
        import json
        import tempfile
        from unittest.mock import patch
        from types import SimpleNamespace
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'object.o').write_bytes(b'authored fixture')
            (root / 'objects_cache.json').write_text(json.dumps({
                'units/u': 'object.o', 'rodata/a': 'object.o'}))
            (root / 'objects.json').write_text(json.dumps([
                {'name': 'units/u', 'rename': {'.rodata': '.rodata.00002000'}},
                {'name': 'rodata/a'}]))
            (root / 'placement.json').write_text(json.dumps({'sections': {'.rodata': [
                {'obj': 'rodata/a', 'sec': '.rodata.00002010', 'key': 0x2010}]}}))
            with patch('text_placement.Elf', return_value=SimpleNamespace(
                    section=lambda name: {'align': 8 if name == '.rodata' else 4, 'size': 12})):
                inputs = InputAlignments(root)
                self.assertEqual(inputs.data_at('.rodata', 0x2000), 8)
                self.assertEqual(inputs.data_at('.rodata', 0x2010), 4)
                self.assertIsNone(inputs.data_at('.rodata', 0x2020))

    def test_owned_data_requires_real_input_and_proven_zero_fill(self):
        from unittest.mock import patch
        from types import SimpleNamespace
        from units_verify import owned_data_gap_fits
        self.assertFalse(owned_data_gap_fits(0, 0x2000, 0x2008, '.rodata', 8))
        data = bytearray(b'fixture-data' + bytes(4))
        original = SimpleNamespace(section=lambda name: {'addr': 0x2000}, content=lambda sec: data)
        inputs = SimpleNamespace(data_at=lambda sec, addr: 16)
        with patch.object(Path, 'read_bytes', return_value=b'authored ELF fixture'), \
                patch('units_verify.Elf', return_value=original), \
                patch('text_placement.InputAlignments', return_value=inputs):
            self.assertTrue(owned_data_gap_fits(12, 0x2000, 0x2010, '.rodata', 8))
            inputs.data_at = lambda sec, addr: 4
            self.assertFalse(owned_data_gap_fits(12, 0x2000, 0x2010, '.rodata', 8))
            inputs.data_at = lambda sec, addr: 16
            data[-1] = 1
            self.assertFalse(owned_data_gap_fits(12, 0x2000, 0x2010, '.rodata', 8))

    def test_no_invented_padding_or_alignment_changes(self):
        self.assertFalse(natural_text_span(116, 0x1008, 0x1080, 4, bytes(4), 8))
        self.assertFalse(natural_text_span(116, 0x1008, 0x1080, None, bytes(4), 8))
        self.assertFalse(natural_text_span(116, 0x1008, 0x1080, 8, b'\x01\0\0\0', 8))
        self.assertFalse(natural_text_span(116, 0x1008, 0x1080, 8, bytes(3), 8))
        self.assertFalse(natural_text_span(112, 0x1008, 0x1080, 8, bytes(8), 8))
        self.assertFalse(natural_text_span(120, 0x1008, 0x1080, 8, b'', 8))
        self.assertFalse(natural_text_span(124, 0x1008, 0x1080, 8, b'', 8))
        self.assertFalse(natural_text_span(116, 0x1008, 0x1080, 8, bytes(4), 16))


if __name__ == '__main__':
    unittest.main()
