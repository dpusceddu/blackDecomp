"""The split list, the symbol table and the units derived from them (no game files needed)."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import splits as S
import units as U

SPLITS = '''variant: SLUS_213.76
defaults: {compiler: ee-gcc2.95.3-136, flags: [-O2, -G0, -snas]}
splits:
  - {src: src/game/tu_100000.c, range: [0x100000, 0x100030]}
  - {src: src/game/tu_100030.cpp, range: [0x100030, 0x100050], flags: [-O1, -G0, -snas], assembler: sn-min6, sections: false, owner: me}
  - {src: src/game/tu_100030.cpp, range: [0x100050, 0x100060]}
'''
SYMBOLS = '''# comment
Tick__4Game = 0x100010; // type:func
gClock = 0x40f0e0; // type:data
'''
TABLE = [(0x100000, 0x100008), (0x100008, 0x100010), (0x100010, 0x100030), (0x100030, 0x100040), (0x100040, 0x100050),
         (0x100050, 0x100060)]


class Splits(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.TemporaryDirectory()
        self.path = Path(self.dir.name) / 'splits.yaml'
        self.path.write_text(SPLITS)

    def tearDown(self):
        self.dir.cleanup()

    def test_defaults_and_overrides(self):
        a, b, c = S.load_splits(path=self.path)
        self.assertEqual((a.start, a.end, a.flags, a.sections, a.library), (0x100000, 0x100030, ['-O2', '-G0', '-snas'], True, 'game'))
        self.assertEqual(b.compile_flags(), ['-O1', '-G0', '-snas', '--assembler=sn-min6'])
        self.assertEqual(a.compile_flags(non_matching=True), ['-O2', '-G0', '-snas', '-ffunction-sections', '-DNON_MATCHING'])
        self.assertEqual(b.owner, 'me')

    def test_unknown_key_is_rejected(self):
        self.path.write_text('splits:\n- {src: a.c, range: [1, 2], colour: red}\n')
        with self.assertRaises(ValueError):
            S.load_splits(path=self.path)

    def test_names_are_unique_per_file(self):
        names = S.unit_names(S.load_splits(path=self.path))
        self.assertEqual(names, ['tu_100000', 'tu_100030_100030', 'tu_100030_100050'])

    def test_symbols(self):
        sym = S.Symbols(S.parse_symbols(SYMBOLS))
        self.assertEqual(sym.function_names(0x100010), ['Tick__4Game'])
        self.assertEqual(sym.address('gClock'), 0x40F0E0)
        self.assertIsNone(sym.address('missing'))
        self.assertEqual(sym.address('dup', {'dup': '0x1234'}), 0x1234)
        with self.assertRaises(ValueError):
            S.parse_symbols('this is not a symbol')
        text = S.format_symbols([('b', 2, 'func'), ('a', 1, 'data')])
        self.assertEqual([r[:2] for r in S.parse_symbols(text)], [('a', 1), ('b', 2)])

    def test_aliases_are_readable_names_that_never_bind_or_define(self):
        text = SYMBOLS + ('GameClock_Tick = 0x100010; // type:func alias\n'
                          'REG_GS_CSR = 0x12001000; // type:data alias\n'
                          'Tick__4Game_other = 0x100010; // type:func\n')
        sym = S.Symbols(S.parse_symbols(text))
        self.assertEqual(sym.function_names(0x100010), ['Tick__4Game', 'Tick__4Game_other'])    # the alias is not a definition
        self.assertIsNone(sym.address('GameClock_Tick'))
        self.assertIsNone(sym.address('REG_GS_CSR'))
        self.assertEqual(sym.function_aliases(), {0x100010: 'GameClock_Tick'})
        self.assertEqual(sym.data_aliases(), {0x12001000: 'REG_GS_CSR'})
        self.assertEqual([n for n, _, _ in sym.rows], ['Tick__4Game', 'gClock', 'Tick__4Game_other'])

    def test_alias_lines_survive_a_rewrite(self):
        rows = [(n, a, k or 'func') for n, a, k in S.parse_symbols(SYMBOLS + 'Readable = 0x100010; // type:func alias\n')]
        again = S.parse_symbols(S.format_symbols(rows))
        self.assertEqual(sorted(again), sorted(S.parse_symbols(SYMBOLS + 'Readable = 0x100010; // type:func alias\n')))
        text = S.format_symbols([('A_alias', 0x100010, 'func alias'), ('Tick__4Game', 0x100010, 'func')])
        lines = [l for l in text.split('\n') if l and not l.startswith('#')]
        self.assertEqual(lines, ['Tick__4Game = 0x100010; // type:func', 'A_alias = 0x100010; // type:func alias'])

    def test_committed_symbols_parse_and_keep_aliases_apart(self):
        sym = S.load_symbols('SLUS_213.76')
        self.assertGreater(len(sym.function_aliases()), 200)
        self.assertIn('REG_GS_CSR', sym.data_aliases().values())
        self.assertEqual(sym.function_aliases()[0x129160], 'GameObjectManager_FindByName')
        for name, _, _ in sym.aliases:
            self.assertNotIn(name, sym.by_name, name)             # an alias never doubles as a bound or defined name
        for addr in sym.function_aliases():
            self.assertNotIn(sym.function_aliases()[addr], sym.by_addr.get(addr, []))

    def test_format_split_round_trips(self):
        entry = {'src': 'src/a.c', 'range': [0x100, 0x200], 'flags': ['-O1', '-G0'], 'sections': False}
        line = S.format_split(entry)
        self.assertEqual(line, '- {src: src/a.c, range: [0x000100, 0x000200], flags: [-O1, -G0], sections: false}')
        import yaml
        back = yaml.safe_load('[' + line[2:] + ']')[0]
        self.assertEqual(back['range'], [0x100, 0x200])


class Derive(unittest.TestCase):
    def units(self, text, **kw):
        splits = [S.Split({'src': 'src/game/a.c', 'range': [0x100000, 0x100060]}, {})]
        return U.derive_units(splits, TABLE, S.Symbols(S.parse_symbols(SYMBOLS)), read=lambda p: text, **kw)

    def test_an_alias_does_not_rename_the_defined_symbol(self):
        splits = [S.Split({'src': 'src/game/a.c', 'range': [0x100000, 0x100060]}, {})]
        sym = S.Symbols(S.parse_symbols('Readable = 0x100010; // type:func alias\n' + SYMBOLS))
        units = U.derive_units(splits, TABLE, sym, read=lambda p: '')
        self.assertEqual({f['addr']: f['symbol'] for f in units[0]['functions']}[0x100010], 'Tick__4Game')

    def test_unmarked_functions_are_source(self):
        text = ('INCLUDE_ASM("asm/x", func_00100000);\nINCLUDE_ASM("asm/x", func_00100008);\n'
                'void Tick__4Game(void) {}\nINCLUDE_ASM("asm/x", func_00100030);\n')
        unit, = self.units(text)
        status = {f['addr']: f['status'] for f in unit['functions']}
        self.assertEqual(status, {0x100000: 'asm', 0x100008: 'asm', 0x100010: 'source', 0x100030: 'asm',
                                  0x100040: 'source', 0x100050: 'source'})
        by = {f['addr']: f for f in unit['functions']}
        self.assertEqual(by[0x100010]['symbol'], 'Tick__4Game')
        self.assertEqual(by[0x100040]['symbol'], 'func_00100040')
        self.assertEqual(by[0x100010]['size'], 0x20)
        self.assertEqual(unit['flags'][-1], '-ffunction-sections')

    def test_marker_outside_the_range_is_an_error(self):
        with self.assertRaises(ValueError):
            self.units('INCLUDE_ASM("asm/x", func_00200000);')

    def test_non_matching_mode_reads_the_draft_blocks(self):
        text = ('INCLUDE_ASM("asm/x", func_00100000);\n#ifdef NON_MATCHING\nint func_00100008(void) { return 0; }\n#else\n'
                'INCLUDE_ASM("asm/x", func_00100008);\n#endif\n')
        normal, = self.units(text)
        draft, = self.units(text, is_non_matching=True)
        self.assertEqual({f['addr'] for f in normal['functions'] if f['status'] == 'asm'}, {0x100000, 0x100008})
        self.assertEqual({f['addr'] for f in draft['functions'] if f['status'] == 'asm'}, {0x100000})
        self.assertIn('-DNON_MATCHING', draft['flags'])

    def test_facts_resolve_symbols_and_bind_externs(self):
        unit, = self.units('')
        U.apply_facts([unit], {unit['name']: {'symbols': {str(0x100010): 'func_00100010'}, 'externs': {'gClock': '0x40f0e0'}}})
        self.assertEqual(unit['externs'], {'gClock': 0x40F0E0})
        self.assertEqual({f['addr']: f['symbol'] for f in unit['functions']}[0x100010], 'func_00100010')


if __name__ == '__main__':
    unittest.main()
