"""Source edits refresh contracts without repeating immutable native analysis."""
import copy
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d)
                for d in ('', 'build', 'pipeline', 'maint')]
import context_recovery as cr


class ContextCache(unittest.TestCase):
    def test_source_refresh_native_invalidation_and_cold_warm_equivalence(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'src').mkdir()
            (root / 'include').mkdir()
            source = root / 'src/test.c'
            source.write_text('int func_00100000(void) { return 1; }\n')
            inv = [dict(addr=0x100000, name='func_00100000', words=[0x24020001, 0x03e00008, 0], rel={}),
                   dict(addr=0x100100, name='func_00100100', words=[0x0c040000, 0, 0x03e00008, 0],
                        rel={'0': ['jal', 0x100000, 0]})]
            units = [dict(source='src/test.c', functions=[dict(addr=0x100000, status='source')], externs={})]
            cache = root / 'build/auto/context.json'
            real_analyze = cr.analyze_function
            with patch('units.load_units', return_value=units), patch('units.dependencies', side_effect=lambda p: [p]):
                first = cr.recover(inv, root)
                source.write_text('void func_00100000(void) {}\n')
                with patch.object(cr, 'analyze_function', side_effect=AssertionError('native cache lost')):
                    changed = cr.recover(inv, root)
                    self.assertEqual(changed['signatures'][str(0x100000)]['ret'], 'void')
                    # Default recovery and callers supplying the inventory share the context.
                    self.assertEqual(cr.recover(root=root), changed)
                    self.assertEqual(cr.focused_report(changed, [0x100100], True)['calls'][0]['callee'], 'func_00100000')
                self.assertEqual(first['native_fingerprint'], changed['native_fingerprint'])
                self.assertNotEqual(first['fingerprint'], changed['fingerprint'])
                cold = cr.recover(inv, root, refresh=True)
                self.assertEqual(json.loads(json.dumps(changed)), json.loads(json.dumps(cold)))
                modified = copy.deepcopy(inv)
                modified[0]['words'][0] = 0x24020002
                with patch.object(cr, 'analyze_function', wraps=real_analyze) as analysis:
                    binary = cr.recover(modified, root)
                    self.assertEqual([c.args[0]['addr'] for c in analysis.call_args_list], [0x100000])
                self.assertNotEqual(binary['native_fingerprint'], changed['native_fingerprint'])
                modified[1]['rel']['0'][1] = 0x100200
                with patch.object(cr, 'analyze_function', wraps=real_analyze) as analysis:
                    relocated = cr.recover(modified, root)
                    self.assertEqual([c.args[0]['addr'] for c in analysis.call_args_list], [0x100100])
                self.assertNotEqual(relocated['native_fingerprint'], binary['native_fingerprint'])
                with patch.object(cr, 'native_version', return_value='new decoder'), \
                        patch.object(cr, 'analyze_function', wraps=real_analyze) as analysis:
                    cr.recover(modified, root)
                    self.assertEqual(analysis.call_count, 2)
                # Corrupt disposable caches must recover rather than poison a session.
                cache.write_text('{')
                cache.with_name('context-native.json').write_text('{')
                cr.recover(inv, root)
                self.assertIsInstance(json.loads(cache.read_text())['signatures'], dict)

    def test_native_roundtrip_preserves_nested_origins_and_call_values(self):
        f = dict(addr=0x100000, words=[0x8c880004, 0x8d090008, 0x0c040040, 0, 0x03e00008, 0],
                 rel={'2': ['jal', 0x100100, 0]})
        analyzed = cr.analyze_function(f)
        restored = cr.decode_analysis(json.loads(json.dumps(cr.encode_analysis(analyzed))))
        self.assertEqual(analyzed, restored)
        self.assertTrue(restored['nested'])
        self.assertTrue(restored['calls'])


if __name__ == '__main__':
    unittest.main()
