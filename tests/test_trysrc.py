"""Batch experiments preserve candidates and real relocation scores without publishing false progress."""
from contextlib import redirect_stdout
import io
import json
from pathlib import Path
import struct
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import autodecomp as A
import splits as S
import trysrc

FUNCTION = dict(addr=0x100000, name='func_00100000', words=[0x0C040040, 0], rel={'0': ['jal', 0x100100, 0]})


def object_bytes(second=0):
    """Minimal ELF32 MIPS object: a named call relocation and one other instruction."""
    strings = b'\0func_00100000\0NamedCallee\0'
    names = b'\0.text\0.strtab\0.symtab\0.rel.text\0.shstrtab\0'
    symbols = bytes(16) + struct.pack('<IIIBBH', 1, 0, 8, 0x12, 0, 1)
    symbols += struct.pack('<IIIBBH', strings.index(b'NamedCallee'), 0, 0, 0x10, 0, 0)
    bodies = [b'', struct.pack('<II', 0x0C000000, second), strings, symbols, struct.pack('<II', 0, (2 << 8) | 4), names]
    sections = [(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)]
    data = bytearray(52)
    for index in range(1, 6):
        data.extend(bytes((-len(data)) % 4))
        name = [b'', b'.text', b'.strtab', b'.symtab', b'.rel.text', b'.shstrtab'][index]
        kind = [0, 1, 3, 2, 9, 3][index]
        sections.append((names.index(name), kind, 6 if index == 1 else 0, 0, len(data), len(bodies[index]),
                         2 if index == 3 else 3 if index == 4 else 0, 1 if index in (3, 4) else 0,
                         4, 16 if index == 3 else 8 if index == 4 else 0))
        data.extend(bodies[index])
    data.extend(bytes((-len(data)) % 4))
    start = len(data)
    data.extend(b''.join(struct.pack('<IIIIIIIIII', *section) for section in sections))
    data[:52] = struct.pack('<16sHHIIIIIHHHHHH', b'\x7fELF\x01\x01\x01' + bytes(9), 1, 8, 1, 0, 0,
                            start, 0, 52, 0, 0, 40, 6, 5)
    return bytes(data)


class Experiments(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.root = Path(directory.name)
        (self.root / 'include').mkdir()
        self.header = self.root / 'include/fields.h'
        self.header.write_text('typedef int Field;\n')
        self.source = '#include "fields.h"\nvoid func_00100000(void) {}\n'
        self.owner = S.Split(dict(src='src/owner.c', range=[0x100000, 0x100200],
                                  compiler='ee-gcc2.9-991111-01', flags=['-O2', '-G8'], assembler='sn-min6'), {})
        self.flags = trysrc.source_recipe(self.owner, 'seed.c')[0] + ['-x', 'c']
        image = SimpleNamespace(e=SimpleNamespace(data=b'reference image'), word=lambda addr: None)
        for name, value in [('ROOT', self.root), ('OrigImage', lambda: image), ('worker_compile', self.compile)]:
            replacement = patch.object(A, name, value)
            replacement.start()
            self.addCleanup(replacement.stop)

    @staticmethod
    def compile(jobs, tag):
        return {key: (1, 'bad source', b'') if 'broken' in source else
                (0, '', object_bytes(0x24020001 if 'near' in source else 0)) for key, source, flags in jobs}

    def run_batch(self, candidates, bindings=None):
        return trysrc.run_batch(FUNCTION, candidates, dict(owner='src/owner.c'),
                                {'NamedCallee': 0x100100} if bindings is None else bindings,
                                'loop forms', self.root / 'build/experiments')

    def test_batch_saves_best_failures_and_history_without_touching_inputs(self):
        candidates = [(Path('broken.c'), self.source + 'broken', self.flags),
                      (Path('near.c'), self.source + '// near', self.flags),
                      (Path('best.c'), self.source, self.flags),
                      (Path('same.c'), self.source + '// same code', self.flags)]
        record, directory, previous = self.run_batch(candidates)
        self.assertFalse(previous)
        self.assertEqual([r['status'] for r in record['results']], ['compile-failed', 'near', 'object-match', 'object-match'])
        self.assertEqual(record['best'], 2)
        self.assertEqual(record['distinct_code'], 2)
        self.assertEqual((directory / 'best.c').read_text(), self.source)
        self.assertEqual((directory / 'best.o').read_bytes(), object_bytes())
        self.assertEqual((directory / 'diff.txt').read_text(), '')
        self.assertEqual(json.loads((directory / 'results.json').read_text())['results'][0]['message'], 'bad source')
        _, repeated, previous = self.run_batch(candidates)
        self.assertTrue(previous)
        self.assertEqual(directory, repeated)
        self.header.write_text('typedef unsigned int Field;\n')
        changed, later, previous = self.run_batch(candidates)
        self.assertNotEqual(directory, later)
        self.assertNotEqual(record['attempts'][0]['dependencies'], changed['attempts'][0]['dependencies'])
        self.assertTrue((directory / 'best.o').is_file())
        output = io.StringIO()
        with redirect_stdout(output), patch.object(trysrc.preflight, 'require', side_effect=AssertionError('game files needed')):
            self.assertEqual(trysrc.main(['00100000', '--history', '--output', str(self.root / 'build/experiments')]), 0)
        self.assertEqual(output.getvalue().count('loop forms:'), 2)
        self.assertEqual(self.source, candidates[2][1])
        self.assertFalse((self.root / 'build/auto.json').exists())

    def test_unknown_call_target_cannot_be_an_object_match_and_diff_omits_equal_instructions(self):
        record, directory, _ = self.run_batch([(Path('seed.c'), self.source, self.flags)], bindings={})
        self.assertEqual(record['results'][0]['status'], 'near')
        diff = (directory / 'diff.txt').read_text()
        self.assertIn('NamedCallee', diff)
        self.assertIn('00100000', diff)
        self.assertNotIn('00100004', diff)
        self.assertEqual(record['results'][0]['differences'], 1)

    def test_failed_batch_keeps_errors_and_has_no_best_artifact(self):
        record, directory, _ = self.run_batch([(Path('broken.c'), self.source + 'broken', self.flags)])
        self.assertIsNone(record['best'])
        self.assertFalse((directory / 'best.o').exists())
        self.assertEqual((directory / 'candidate-000.c').read_text(), self.source + 'broken')

    def test_failed_rerun_preserves_the_previous_successful_artifact(self):
        candidates = [(Path('seed.c'), self.source, self.flags)]
        original, directory, _ = self.run_batch(candidates)
        with patch.object(A, 'worker_compile', return_value={0: (1, 'compiler interrupted', b'')}):
            failed, later, previous = self.run_batch(candidates)
        self.assertEqual(original['inputs_sha256'], failed['inputs_sha256'])
        self.assertFalse(previous)
        self.assertNotEqual(directory, later)
        self.assertEqual((directory / 'best.o').read_bytes(), object_bytes())
        self.assertFalse((later / 'best.o').exists())

    def test_recipe_and_binding_controls_preserve_real_context(self):
        flags, language = trysrc.source_recipe(self.owner, 'candidate.cpp')
        self.assertEqual(language, 'c++')
        self.assertEqual(flags, ['--cc=ee-gcc2.9-991111-01', '-O2', '-G8', '--assembler=sn-min6', '-ffunction-sections'])
        self.assertEqual(trysrc.source_recipe(self.owner, 'candidate.c', ['-O1'])[0],
                         ['--cc=ee-gcc2.9-991111-01', '-O1'])
        symbols = S.Symbols([('NamedCallee', 0x100100, 'func'), ('Ambiguous', 1, 'data'),
                             ('Ambiguous', 2, 'data'), ('AliasOnly', 3, 'func alias')])
        self.assertEqual(trysrc.symbol_bindings(symbols, self.owner), {'NamedCallee': 0x100100})
        self.owner.extra['externs'] = {'Ambiguous': 2, 'LocalBinding': '0x40'}
        self.assertEqual(trysrc.symbol_bindings(symbols, self.owner),
                         {'NamedCallee': 0x100100, 'Ambiguous': 2, 'LocalBinding': 0x40})
        record, directory, _ = self.run_batch([(Path('seed.c'), self.source, self.flags)])
        other, later, _ = self.run_batch([(Path('seed.c'), self.source, self.flags + ['-O1'])])
        self.assertNotEqual(record['fingerprint'], other['fingerprint'])
        self.assertNotEqual(directory, later)


if __name__ == '__main__':
    unittest.main()
