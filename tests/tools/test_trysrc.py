"""Scratch C++ candidates use the owning file recipe."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline')]
import autodecomp as A
import splits as S
import trysrc as T


class Recipes(unittest.TestCase):
    def test_owner_continuation_inherits_cpp_compiler_flags_and_assembler(self):
        entries = [dict(src='src/a.cpp', range=[1, 2], compiler='sony', flags=['-O1', '-G8'], assembler='sn-min6'),
                   dict(src='src/a.cpp', range=[3, 4])]
        with patch.object(T, 'load_splits', return_value=[S.Split(e, {}) for e in entries]):
            flags, language = T.source_recipe(3, 'scratch.c')
        self.assertEqual(language, 'c++')
        self.assertEqual(flags, ['--cc=sony', '-O1', '-G8', '--assembler=sn-min6', '-ffunction-sections'])

    def test_cpp_scratch_and_explicit_recipe_overrides(self):
        with patch.object(T, 'load_splits', return_value=[S.Split(dict(src='src/a.c', range=[1, 2]), {})]):
            flags, language = T.source_recipe(1, 'scratch.cpp', ['--cc=other', '-O1', '-x', 'c'])
            self.assertEqual(language, 'c++')
            self.assertEqual(flags, ['--cc=other', '-O1', '-x', 'c'])
            self.assertEqual(T.source_recipe(1, 'scratch.cpp', variants=True), (None, 'c++'))

    def test_try_source_selects_cpp_and_respects_explicit_language(self):
        for initial, expected in ((['-O2'], ['-O2', '-x', 'c++']), (['-x', 'c'], ['-x', 'c'])):
            with patch.object(A, 'worker_compile', return_value={}) as compile_, \
                 patch.object(A, 'OrigImage'), patch.object(A, 'Target'):
                A.try_source(dict(name='f'), 'source', initial, language='c++')
            self.assertEqual(compile_.call_args[0][0][0][2], expected)

    def test_worker_writes_cpp_candidate(self):
        with tempfile.TemporaryDirectory() as folder, patch.object(A, 'AUTO', Path(folder)), \
             patch.object(A, 'compile_dependencies', return_value={}), \
             patch('object_compile.environment'), patch.object(A.subprocess, 'run') as run:
            run.return_value = subprocess.CompletedProcess([], 1, '', 'rejected')
            A.worker_compile([('cpp', 'class C {};', ['-x', 'c++'])])
            args = run.call_args[0][0]
            self.assertTrue(any(str(arg).endswith('.cpp') for arg in args))


if __name__ == "__main__":
    unittest.main()
