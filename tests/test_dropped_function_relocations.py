"""Native metadata entry pointers must survive dropping unfinished TU code."""
from pathlib import Path
import struct
import sys
import unittest

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
from elfinfo import Elf
from elfobj import undefine_dropped


def object_fixture(addend=0, value=0, kind=2, alias=False, symbol_type=2,
                   section_binding=0, function_name=1):
    names = ['', '.text.pending', '.data.keep', '.data.drop', '.rel.keep',
             '.rel.drop', '.strtab', '.symtab', '.shstrtab']
    strings = b'\0'; offsets = [0]
    for name in names[1:]:
        offsets.append(len(strings)); strings += name.encode() + b'\0'
    symbols = [bytes(16), struct.pack('<IIIBBH', 0, 0, 0, section_binding << 4 | 3, 0, 1),
               struct.pack('<IIIBBH', function_name, value, 12 - value, 0x10 | symbol_type, 0, 1)]
    if alias:
        symbols.append(struct.pack('<IIIBBH', 9, value, 12 - value, 0x12, 0, 1))
    content = [b'', bytes(12), struct.pack('<I', addend), bytes(4),
               struct.pack('<II', 0, 1 << 8 | kind), struct.pack('<II', 0, 1 << 8 | 2),
               b'\0pending\0alias\0', b''.join(symbols), strings]
    raw = bytearray(52); headers = []
    for index, payload in enumerate(content):
        raw.extend(bytes((-len(raw)) % 4)); at = len(raw); raw.extend(payload)
        typ = 0 if not index else 9 if index in (4, 5) else 3 if index in (6, 8) else 2 if index == 7 else 1
        flags = 6 if index == 1 else 3 if index in (2, 3) else 0
        link = 7 if index in (4, 5) else 6 if index == 7 else 0
        info = 2 if index in (4, 7) else 3 if index == 5 else 0
        headers.append((offsets[index], typ, flags, 0, at, len(payload), link, info, 4, 8 if index in (4, 5) else 16 if index == 7 else 0))
    raw.extend(bytes((-len(raw)) % 4)); shoff = len(raw)
    raw.extend(b''.join(struct.pack('<10I', *h) for h in headers))
    raw[:7] = b'\x7fELF\x01\x01\x01'
    struct.pack_into('<HHIIIIIHHHHHH', raw, 16, 1, 8, 1, 0, 0, shoff, 0, 52, 0, 0, 40, len(headers), 8)
    return bytes(raw)


class DroppedFunctionRelocations(unittest.TestCase):
    def edit(self, **kwargs):
        raw = object_fixture(**kwargs)
        result, count = undefine_dropped(raw, {'.data.keep'})
        return Elf(raw), Elf(result), count

    def symbol_index(self, elf, section='.rel.keep'):
        _, info = struct.unpack('<II', elf.content(elf.section(section)))
        return info >> 8

    def test_kept_native_entry_pointer_resolves_to_existing_original_symbol(self):
        before, after, count = self.edit()
        self.assertEqual(self.symbol_index(after), 2)
        self.assertEqual(after.symbols()[2]['name'], 'pending')
        self.assertEqual(after.symbols()[2]['shndx'], 0)
        self.assertEqual(count, 1)
        for name in ('.text.pending', '.data.keep', '.data.drop'):
            self.assertEqual(before.content(before.section(name)), after.content(after.section(name)))

    def test_nonzero_known_entry_preserves_address_by_rebasing_addend(self):
        _, after, _ = self.edit(addend=4, value=4)
        self.assertEqual(self.symbol_index(after), 2)
        self.assertEqual(after.content(after.section('.data.keep')), bytes(4))

    def test_interior_and_ambiguous_entries_are_not_guessed(self):
        for options in (dict(addend=4), dict(alias=True)):
            _, after, _ = self.edit(**options)
            self.assertEqual(self.symbol_index(after), 1)

    def test_only_absolute_function_entry_relocations_are_redirected(self):
        for options in (dict(kind=4), dict(symbol_type=1),
                        dict(section_binding=1), dict(function_name=0)):
            _, after, _ = self.edit(**options)
            self.assertEqual(self.symbol_index(after), 1)

    def test_dropped_source_relocations_do_not_become_link_roots(self):
        _, after, _ = self.edit()
        self.assertEqual(self.symbol_index(after, '.rel.drop'), 1)


if __name__ == '__main__':
    unittest.main()
