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
