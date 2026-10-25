"""A source-only pass must have the next assembly input's alignment evidence: cached, or assembled in the pass."""
import contextlib
import io
import json
from pathlib import Path
import subprocess
import sys
import tarfile
import tempfile
import unittest
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import build_objects as build


class CompileOnlyCacheTests(unittest.TestCase):
    def test_assembly_mapping_is_current_and_missing_objects_are_assembled_without_linking(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            target = root / 'build/test'
            (target / 'cache').mkdir(parents=True)
            for name in ('include/macro.inc', 'tools/build/elfobj.py', 'tools/build/assembler.py', 'build/test/link.ld'):
                path = root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text('')
            assembly = root / 'original.s'
            assembly.write_text('.section .text.original\n.align 3\n')
            objects = [dict(name='original', kind='asm', src='original.s'),
                       dict(name='unit', kind='cc', src='unit.c', compiler='test', flags=[])]
            (target / 'objects.json').write_text(json.dumps(objects))
            asm_key = build.sha('as', build.VERSION, assembly.read_bytes(), b'', b'')
            unit_key = build.sha('cc', build.VERSION, 'test', '[]')
            for key in (asm_key, unit_key):
                (target / 'cache' / (key + '.o')).write_bytes(b'cached')
            (target / 'objects_cache.json').write_text(json.dumps({'original': 'cache/stale.o'}))
            with patch.object(build, 'ROOT', root), patch.object(build, 'dependencies', return_value=[]), \
                 patch.object(sys, 'argv', ['build_objects.py', 'test', '--compile-only']), \
                 patch.object(build.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0, '', '')):
                with contextlib.redirect_stdout(io.StringIO()):
                    self.assertEqual(build.main(), 0)
                    first_mapping = json.loads((target / 'objects_cache.json').read_text())
                    (root / 'include/macro.inc').write_text('.macro glabel name\n.align 4\n.endm\n')
                    self.assertEqual(build.main(), 0)
            mapping = json.loads((target / 'objects_cache.json').read_text())
            self.assertEqual(first_mapping, dict(original='cache/' + asm_key + '.o', unit='cache/' + unit_key + '.o'))
            self.assertNotEqual(mapping['original'], first_mapping['original'])
            self.assertEqual(mapping['unit'], first_mapping['unit'])
            plan = json.loads((target / 'plan.json').read_text())
            self.assertEqual(plan['assemble'], [['original.s', 'obj/original.o']])
            self.assertEqual(plan['rename'], [])
            self.assertNotIn('link', plan)
            with tarfile.open(target / 'inputs.tgz') as packet:
                self.assertIn('original.s', packet.getnames())
                self.assertNotIn('obj/original.o', packet.getnames())


if __name__ == '__main__':
    unittest.main()
