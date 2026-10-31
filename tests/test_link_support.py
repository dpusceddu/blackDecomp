"""Keep real data definitions intact when resolving splat's undefined labels."""
import contextlib
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools' / 'build'))
import link_support


class LinkSupportWorkflow(unittest.TestCase):
    def test_defined_data_label_needs_no_self_alias(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            build = root / 'build' / 'test'
            data = root / 'asm' / 'test' / 'data'
            build.mkdir(parents=True)
            data.mkdir(parents=True)
            (root / 'config').mkdir()
            (root / 'config' / 'versions.json').write_text(json.dumps({'test': {'boot': 'test'}}))
            (build / 'layout.json').write_text(json.dumps({'sections': [
                {'name': '.sdata', 'addr': 0x40D980, 'orig_size': 16, 'source': 'linked'}
            ]}))
            (root / 'asm' / 'test' / 'text.s').write_text('')
            (data / 'sdata.s').write_text('dlabel D_0040D980\n.byte 0\ndlabel D_0040D985\n.byte 0\n')
            (build / 'undefined_funcs_auto.txt').write_text('')
            (build / 'undefined_syms_auto.txt').write_text(
                'D_0040D983 = 0x40D983;\nD_0040D985 = 0x40D985;\n')
            with patch.object(link_support, 'ROOT', root), patch.object(sys, 'argv', ['link_support.py', 'test']):
                with contextlib.redirect_stdout(io.StringIO()):
                    link_support.main()
            self.assertEqual((build / 'symbols.ld').read_text(), 'D_0040D983 = D_0040D980 + 0x3;\n')


if __name__ == '__main__':
    unittest.main()
