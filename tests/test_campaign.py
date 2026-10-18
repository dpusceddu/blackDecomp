import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from campaign import band, compare


class CampaignMetrics(unittest.TestCase):
    def test_band_boundaries(self):
        self.assertEqual([band(n) for n in (96, 100, 300, 304)], ['<100', '100-300', '100-300', '>300'])

    def test_new_large_match_and_padding_bytes(self):
        before = dict(source_addresses=[1], source_bytes=8, text_bytes=1000, complete_code_tus=[],
            functions=[dict(addr=1, size=8, span=8, band='<100'), dict(addr=2, size=304, span=312, band='>300')])
        after = dict(source_addresses=[1, 2], source_bytes=320, complete_code_tus=['module'])
        result = compare(before, after, 30, [2])
        self.assertEqual((result['new_functions'], result['new_text_bytes'], result['large_attempt_matches']), (1, 312, 1))
        self.assertEqual(result['bytes_per_agent_hour'], 624)
        self.assertEqual(result['new_code_complete_tus'], ['module'])

    def test_regression_is_fatal(self):
        before = dict(source_addresses=[1], functions=[])
        with self.assertRaises(ValueError):
            compare(before, dict(source_addresses=[]))


if __name__ == '__main__':
    unittest.main()
