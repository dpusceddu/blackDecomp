"""Synthetic provenance partition checks; no private executable or SDK needed."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools' / 'studies'))
import loop_provenance as provenance


def loop(address, length=6, padded=True, function=None, tu='test', confidence='exact', words=()):
    return dict(addr=hex(address), target=hex(address - (length - 2) * 4),
                function=hex(function if function is not None else address - 32),
                tu=tu, library='game', sn=True, tu_confidence=confidence,
                padded=padded, length=length, padding_nops=int(padded), words=list(words),
                other_branch=False, cop2=False)


class ProvenanceTests(unittest.TestCase):
    def mapping(self, confidence='exact'):
        return [dict(name='test', text=['0x1000', '0x2000'], confidence=confidence)], \
               [dict(name='game', text=['0x1000', '0x2000'])]

    def report(self, rows):
        tus, libraries = self.mapping()
        return provenance.report(dict(loops=rows), tus, libraries)

    def test_natural_seven_word_loop_is_not_seven_word_padding(self):
        result = self.report([loop(0x1100), loop(0x1200, length=7, padded=False)])
        row, = result['tables']['sn']['tu']
        self.assertEqual(row['candidate_seven'], 0)
        self.assertFalse(row['mixed'])

    def test_independent_function_evidence_is_required(self):
        same = self.report([loop(0x1100, function=0x1000), loop(0x1110, function=0x1000)])
        self.assertEqual(same['conservative_assignment_candidates'], [])
        different = self.report([loop(0x1100), loop(0x1200)])
        candidate, = different['conservative_assignment_candidates']
        self.assertEqual(candidate['assembler'], 'sn-min6')
        self.assertFalse(candidate['historical_identity_verified'])

    def test_cop0_counterexample_is_retained_but_not_used_as_compiler_proof(self):
        rows = [loop(0x1100), loop(0x1200, length=7, words=['0x4100fffa'])]
        result = self.report(rows)
        self.assertEqual(result['summary']['sn']['mixed_tus'], 1)
        self.assertEqual(result['summary']['sn']['simple_mixed_tus'], 0)
        self.assertEqual(len(result['mixed_tu_loops']), 2)

    def test_ordinary_conflicting_short_loop_blocks_candidate(self):
        result = self.report([loop(0x1100), loop(0x1200), loop(0x1300, length=5, padded=False)])
        self.assertEqual(result['conservative_assignment_candidates'], [])

    def test_weak_tu_boundary_does_not_promote_multi_function_evidence(self):
        result = self.report([loop(0x1100, confidence='medium'), loop(0x1200, confidence='medium')])
        self.assertEqual(result['conservative_assignment_candidates'], [])

    def test_library_hulls_are_not_treated_as_disjoint_ranges(self):
        rows = provenance.annotate([loop(0x1100)], [], [dict(name='game', text=['0x1000', '0x2000']),
                                                     dict(name='subsystem', text=['0x1080', '0x1200'])])
        self.assertEqual(rows[0]['library_hulls'], ['game', 'subsystem'])
        self.assertIsNone(rows[0]['tu_range'])

    def test_source_control_regression_keeps_independent_family_and_diff(self):
        audit = {'u': dict(family='SN-driver', functions={'0x10e0': dict(
            baseline=dict(exact=True, bytes=44), candidate=dict(exact=False, bytes=40, differences=3),
            padding_equivalent_to_baseline=True)})}
        result = provenance.recipe_controls(self.report([loop(0x1100, length=7)])['loops'], audit)
        control, = result
        self.assertEqual(control['family'], 'SN-driver')
        self.assertEqual(control['differences'], 3)
        self.assertEqual(control['loops'][0]['length'], 7)


if __name__ == '__main__':
    unittest.main()
