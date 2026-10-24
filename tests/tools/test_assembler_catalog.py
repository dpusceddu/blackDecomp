"""Catalog recipe checks use synthetic data and never launch SDK programs."""
import json
from pathlib import Path
import sys
import unittest
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import assembler


class CatalogRecipe(unittest.TestCase):
    def test_recipe_hash_matches_recorded_derivative(self):
        record = json.loads((Path(__file__).resolve().parents[2] /
                             'config/toolchain-assemblers.json').read_text())['assemblers'][0]
        self.assertEqual(record['sha256'], assembler.MIN6_SHA256)
        command = assembler.command('sn-min6', ['-G8'], 'source.s', 'output.o')
        self.assertIn('/assemblers/' + record['id'] + '/', command[1])
        self.assertIn('-G8', command)

    def test_bad_derivative_is_rejected_before_any_compiler_or_assembler_runs(self):
        with patch.object(assembler.Path, 'read_bytes', return_value=b'corrupt derivative'), \
             patch.object(assembler.subprocess, 'run') as run:
            result = assembler.compile_with_assembler(['cc'], ['--assembler=sn-min6'],
                                                       'input.c', 'output.o', {}, 30)
        self.assertEqual(result.returncode, 1)
        self.assertIn('hash mismatch', result.stderr)
        run.assert_not_called()

    def test_missing_derivative_is_an_actionable_catalog_error(self):
        with patch.object(assembler.Path, 'read_bytes', side_effect=FileNotFoundError), \
             patch.object(assembler.subprocess, 'run') as run:
            result = assembler.compile_with_assembler(['cc'], ['--assembler=sn-min6'],
                                                       'input.c', 'output.o', {}, 30)
        self.assertEqual(result.returncode, 1)
        self.assertIn('toolchain.py install', result.stderr)
        run.assert_not_called()


if __name__ == '__main__':
    unittest.main()
