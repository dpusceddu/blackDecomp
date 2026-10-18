"""A source-only pass must retain the next assembly input's alignment evidence."""
import json
from pathlib import Path
import subprocess
import sys
import tarfile
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import build_objects as build


class CompileOnlyCacheTests(unittest.TestCase):
    def test_assembly_mapping_is_current_but_not_dispatched_or_packaged(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            target = root / 'build/test'
            (target / 'cache').mkdir(parents=True)
            for name in ('include/macro.inc', 'tools/elfobj.py', 'build/test/link.ld'):
                path = root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text('')
            assembly = root / 'original.s'
            assembly.write_text('.section .text.original\n.align 3\n')
            objects = [dict(name='original', kind='asm', src='original.s'),
                       dict(name='unit', kind='cc', src='unit.c', compiler='test', flags=[])]
            (target / 'objects.json').write_text(json.dumps(objects))
            asm_key = build.sha('as', build.VERSION, assembly.read_bytes(), b'')
            unit_key = build.sha('cc', build.VERSION, 'test', '[]')
            for key in (asm_key, unit_key):
                (target / 'cache' / (key + '.o')).write_bytes(b'cached')
            (target / 'objects_cache.json').write_text(json.dumps({'original': 'cache/stale.o'}))
            with patch.object(build, 'ROOT', root), patch.object(build, 'dependencies', return_value=[]), \
                 patch.object(sys, 'argv', ['build_objects.py', 'test', '--compile-only']), \
                 patch.object(build.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0, '', '')):
                self.assertEqual(build.main(), 0)
            mapping = json.loads((target / 'objects_cache.json').read_text())
            self.assertEqual(mapping, dict(original='cache/' + asm_key + '.o', unit='cache/' + unit_key + '.o'))
            plan = json.loads((target / 'plan.json').read_text())
            self.assertEqual(plan['assemble'], [])
            self.assertNotIn('link', plan)
            with tarfile.open(target / 'inputs.tgz') as packet:
                self.assertNotIn('original.s', packet.getnames())
                self.assertNotIn('obj/original.o', packet.getnames())


if __name__ == '__main__':
    unittest.main()
