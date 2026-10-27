"""Permuter imports preserve target typedefs and require a successful seed compile."""
import importlib.util
from pathlib import Path
import subprocess
import sys
import tempfile
import types
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline')]
def module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


P = module("permuter_import", ROOT / "tools/permuter/import.py")


class Permuter(unittest.TestCase):
    def test_protection_is_idempotent_and_does_not_rewrite_strings_or_macros(self):
        source = ('typedef int s128 __attribute__((mode(TI))); typedef unsigned int u128 __attribute__((mode(TI)));\n'
                  'char *s = "typedef int u128;";\n#define X typedef int u128;\n')
        protected = P.preserve_typedefs(source)
        self.assertEqual(P.preserve_typedefs(protected), protected)
        self.assertIn('char *s = "typedef int u128;";', protected)
        self.assertIn('#define X typedef int u128;', protected)
        self.assertEqual(protected.count('b64literal'), 2)

    def test_import_rejects_upstream_warning_only_compile_failure(self):
        with tempfile.TemporaryDirectory() as folder:
            upstream = types.SimpleNamespace(
                STUB_FN_MACROS=['-D__attribute__(x)=', '-DOTHER=1'],
                import_c_file=lambda: 'typedef int u128;',
                prune_source=lambda text: (text, 'compiler source'),
                compile_base=lambda *args: None)
            def main(args):
                self.assertIn('--no-prune', args)
                self.assertEqual(upstream.STUB_FN_MACROS, ['-DOTHER=1'])
                source = upstream.import_c_file()
                self.assertIn('b64literal', source)
                upstream.prune_source(source)
                upstream.compile_base('script', 'source', 'input', str(Path(folder) / 'missing.o'))
            upstream.main = main
            with patch.object(P, 'load_importer', return_value=upstream):
                with self.assertRaisesRegex(SystemExit, 'did not compile'):
                    P.main(['seed.c', 'target.s'])

    def test_attribute_declarations_and_size_checks_survive_upstream_ast(self):
        source = ('typedef int s128 __attribute__((mode(TI)));\n'
                  'typedef unsigned int EeU128 __attribute__((mode(__TI__)));\n'
                  'typedef int Broken128;\ns128 f(s128 x) {return x;}\n')
        protected = P.preserve_typedefs(source)
        self.assertIn('latedefine start', protected)
        path = ROOT / '.venv/decomp-permuter'
        if not path.is_dir():
            self.skipTest('optional pinned decomp-permuter is not installed')
        script = ('import sys; sys.path.insert(0, sys.argv[1]); from src import ast_util; '
                  'text=sys.stdin.read(); print(ast_util.to_c(ast_util.parse_c(text)))')
        result = subprocess.run([sys.executable, '-c', script, str(path)], input=protected, text=True,
                                capture_output=True, check=True).stdout
        self.assertIn('typedef int s128 __attribute__((mode(TI)));', result)
        self.assertIn('sizeof(s128) == 16', result)
        self.assertIn('sizeof(EeU128) == 16', result)
        self.assertNotIn('latedefine', result)
        self.assertEqual(result.count('typedef int s128'), 1)

    def test_stripped_known_wide_typedef_gets_a_failing_size_check(self):
        text = P.preserve_typedefs('typedef int u128;\nu128 f(u128 x) {return x;}')
        import base64
        literal = next(line.split()[-1] for line in text.splitlines() if 'b64literal' in line)
        self.assertIn('sizeof(u128) == 16', base64.b64decode(literal).decode())


if __name__ == "__main__":
    unittest.main()
