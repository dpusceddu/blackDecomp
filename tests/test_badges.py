"""Badge colors, endpoint format and table rows of tools/badges.py."""
import sys
import contextlib
import io
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import badges


class Badges(unittest.TestCase):
    def test_publication_refreshes_both_status_sections_and_leaves_readme_alone(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root / 'progress').mkdir()
            (root / 'docs').mkdir()
            build = root / 'build/SLUS_213.76'
            build.mkdir(parents=True)
            counts = dict(functions=10, matched_functions=4, bytes=1000, matched_bytes=150)
            data = dict(code_by_library={'game': counts}, code=counts,
                        rows={'ALL': dict(functions=11, source_functions=4, bytes=1100, source_bytes=170)})
            (build / 'progress.json').write_text(json.dumps(data))
            readme = root / 'README.md'
            readme.write_text('Contributor quick start\n')
            status = root / 'docs/status.md'
            status.write_text('# Progress\n%s\nold table\n%s\n%s\nold facts\n%s\n## Open problems\nKeep this.\n' % (
                badges.BEGIN, badges.END, badges.FACTS_BEGIN, badges.FACTS_END))
            with patch.object(badges, 'ROOT', root), patch.object(badges.sys, 'argv', ['badges.py', '--no-progress']), \
                 patch.object(badges.preflight, 'require'), patch.object(badges, 'source_facts', return_value='- New facts.'), \
                 contextlib.redirect_stdout(io.StringIO()):
                badges.main()
            self.assertIn('| game | 4 / 10 |', status.read_text())
            self.assertIn('- New facts.', status.read_text())
            self.assertIn('## Open problems\nKeep this.', status.read_text())
            self.assertNotIn('old table', status.read_text())
            self.assertNotIn('old facts', status.read_text())
            self.assertEqual(readme.read_text(), 'Contributor quick start\n')
            self.assertEqual(json.loads((root / 'progress/code.json').read_text())['message'], '15.0%')


if __name__ == '__main__':
    unittest.main()
