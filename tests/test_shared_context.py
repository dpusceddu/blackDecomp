"""An include, declaration or comment must not stand in for a real helper consumer."""
import sys
import unittest
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
from shared_context import source_body


class SourceConsumerScope(unittest.TestCase):
    def test_prototype_and_adjacent_function_are_excluded(self):
        source = 'void Probe(); void Probe() { Actual(); } void Other() { Unused(); }'
        body = source_body(source, 'Probe')
        self.assertIn('Actual()', body)
        self.assertNotIn('Unused', body)

    def test_comments_and_string_names_are_not_evidence(self):
        source = 'void Probe() { /* ClaimedHelper(); */ const char* p="ClaimedHelper"; }'
        self.assertNotIn('ClaimedHelper', source_body(source, 'Probe'))

    def test_literal_braces_do_not_extend_the_consumer(self):
        source = 'void Probe() { const char* p="{"; Actual(); } void Other() { Unused(); }'
        body = source_body(source, 'Probe')
        self.assertIn('Actual()', body)
        self.assertNotIn('Unused', body)

    def test_a_declaration_is_not_a_definition(self):
        with self.assertRaises(ValueError):
            source_body('void Probe(); // void Probe() { Fake(); }', 'Probe')


if __name__ == '__main__':
    unittest.main()
