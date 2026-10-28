"""The code measure of tools/progress.py (objdiff's definition) and its agreement check against an objdiff report."""
import sys
import unittest
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import progress


def report(functions, **measures):
    return dict(measures=measures, units=[dict(name='u', functions=[
        dict(name='func_%08X' % a, size=str(size), fuzzy_match_percent=pct) for a, size, pct in functions])])


SIZES = {0x100000: 40, 0x100030: 8, 0x100040: 16}      # the last address is an exact function in a library of its own
LIBRARY = {0x100000: 'game', 0x100030: 'game', 0x100040: 'libc'}.get


class CodeTotals(unittest.TestCase):
    def test_overall_and_per_library(self):
        total, libs = progress.code_totals(SIZES, {0x100000, 0x100040}, LIBRARY)
        self.assertEqual(total, dict(functions=3, matched_functions=2, bytes=64, matched_bytes=56))
        self.assertEqual(libs['game'], dict(functions=2, matched_functions=1, bytes=48, matched_bytes=40))
        self.assertEqual(libs['libc'], dict(functions=1, matched_functions=1, bytes=16, matched_bytes=16))


class Agreement(unittest.TestCase):
    functions = [(0x100000, 40, 100.0), (0x100030, 8, 87.5), (0x100040, 16, 100.0)]
    measures = dict(total_code='64', matched_code='56', total_functions=3, matched_functions=2)

    def totals(self, exact):
        return progress.code_totals(SIZES, exact, LIBRARY)[0]

    def test_matching_sets_and_totals_agree(self):
        exact = {0x100000, 0x100040}
        self.assertEqual([], progress.agreement_problems(exact, self.totals(exact), report(self.functions, **self.measures)))

    def test_exact_function_that_objdiff_does_not_match_fails(self):
        exact = {0x100000, 0x100030, 0x100040}
        problems = progress.agreement_problems(exact, self.totals(exact), report(self.functions, **self.measures))
        self.assertTrue(any('exact in the image but not matched by objdiff' in p and 'func_00100030' in p for p in problems))
        self.assertTrue(any(p.startswith('matched_code') for p in problems))

    def test_matched_function_that_is_not_exact_fails(self):
        exact = {0x100000}
        problems = progress.agreement_problems(exact, self.totals(exact), report(self.functions, **self.measures))
        self.assertTrue(any('matched by objdiff but not exact in the image' in p and 'func_00100040' in p for p in problems))


if __name__ == '__main__':
    unittest.main()
