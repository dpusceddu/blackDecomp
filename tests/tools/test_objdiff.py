"""The objdiff project file: one unit per object, a category per library, asm-only units without a base object."""
import json, sys, tempfile, unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import objdiff


class ProjectFile(unittest.TestCase):
    def plan(self):
        return [dict(name='kynapse_a', base_in='cache/x.o', source='src/kynapse/a.cpp', library='kynapse',
                     functions=[], redefine={}, complete=True),
                dict(name='asm_game_tu_100000', base_in=None, source=None, library='game',
                     functions=[], redefine={}, complete=False)]

    def test_units_categories_and_paths(self):
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(objdiff, 'ROOT', Path(directory)):
                self.assertEqual(2, objdiff.write_project('SLUS_213.76', self.plan()))
            project = json.loads((Path(directory) / 'objdiff.json').read_text())
        self.assertEqual(['game', 'kynapse'], [c['id'] for c in project['progress_categories']])
        source, asm = project['units']
        self.assertEqual('kynapse/kynapse_a', source['name'])
        self.assertEqual('build/SLUS_213.76/objdiff/base/kynapse_a.o', source['base_path'])
        self.assertEqual('src/kynapse/a.cpp', source['metadata']['source_path'])
        self.assertTrue(source['metadata']['complete'])
        self.assertNotIn('base_path', asm)
        self.assertTrue(asm['metadata']['auto_generated'])
        self.assertEqual(['kynapse'], source['metadata']['progress_categories'])

    def test_only_the_usa_version_has_source_units(self):
        with patch.object(sys, 'argv', ['objdiff.py', 'SLES_538.86']):
            with self.assertRaises(SystemExit):
                objdiff.main()


if __name__ == '__main__':
    unittest.main()
