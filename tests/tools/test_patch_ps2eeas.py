"""Synthetic patch guards; no SDK, game data, or binary execution."""
import copy
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import patch_ps2eeas as patcher


class SyntheticAssembler:
    def setUp(self):
        data = bytearray(0x4e00)
        for offset, before, _ in patcher.PATCHES:
            data[offset:offset + len(before)] = before
        self.source = bytes(data)
        for offset, before, after in patcher.PATCHES:
            data[offset:offset + len(before)] = after
        self.result = bytes(data)
        self.hashes = patch.multiple(patcher,
                                    ORIGINAL_SHA256=patcher.sha256(self.source),
                                    PATCHED_SHA256=patcher.sha256(self.result))
        self.hashes.start()
        self.addCleanup(self.hashes.stop)


class PatchGuards(SyntheticAssembler, unittest.TestCase):
    def test_only_two_immediates_change(self):
        original = self.source
        result = patcher.patch(original)
        self.assertEqual(result, self.result)
        self.assertEqual(original, self.source)
        self.assertEqual(len(result), len(original))
        self.assertEqual([i for i, (a, b) in enumerate(zip(original, result)) if a != b],
                         [0x4db9, 0x4deb])

    def test_source_hash_guard(self):
        with self.assertRaisesRegex(ValueError, 'not the pinned'):
            patcher.patch(self.source + b'x')

    def test_each_full_instruction_preimage_is_guarded(self):
        for offset, _, _ in patcher.PATCHES:
            damaged = bytearray(self.source)
            damaged[offset] ^= 1
            with patch.object(patcher, 'ORIGINAL_SHA256', patcher.sha256(damaged)):
                with self.assertRaisesRegex(ValueError, 'unexpected instruction'):
                    patcher.patch(bytes(damaged))

    def test_result_hash_guard(self):
        with patch.object(patcher, 'PATCHED_SHA256', '0' * 64):
            with self.assertRaisesRegex(ValueError, 'unexpected SHA-256'):
                patcher.patch(self.source)

    def test_file_install_retains_original_and_is_idempotent(self):
        with tempfile.TemporaryDirectory() as directory:
            original = Path(directory) / 'original.exe'
            target = Path(directory) / 'derivative.exe'
            original.write_bytes(self.source)
            self.assertTrue(patcher.write_derivative(original, target))
            self.assertFalse(patcher.write_derivative(original, target))
            self.assertEqual(original.read_bytes(), self.source)
            self.assertEqual(target.read_bytes(), self.result)

    def test_refuses_in_place_or_unexpected_target(self):
        with tempfile.TemporaryDirectory() as directory:
            original = Path(directory) / 'original.exe'
            target = Path(directory) / 'derivative.exe'
            original.write_bytes(self.source)
            with self.assertRaisesRegex(ValueError, 'separate output'):
                patcher.write_derivative(original, original)
            target.write_bytes(b'other work')
            with self.assertRaisesRegex(ValueError, 'unexpected derivative'):
                patcher.write_derivative(original, target)
            self.assertEqual(target.read_bytes(), b'other work')

    def test_refuses_broken_target_symlink(self):
        with tempfile.TemporaryDirectory() as directory:
            original = Path(directory) / 'original.exe'
            target = Path(directory) / 'derivative.exe'
            original.write_bytes(self.source)
            target.symlink_to('missing.exe')
            with self.assertRaisesRegex(ValueError, 'symlink'):
                patcher.write_derivative(original, target)
            self.assertTrue(target.is_symlink())


if __name__ == '__main__':
    unittest.main()
