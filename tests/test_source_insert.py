"""Recovered source insertion must preserve complete declarations and helper bodies."""
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import decompile


class SourceInsertionWorkflow(unittest.TestCase):
    def test_repeated_draft_insertion_preserves_types_and_inline_helpers(self):
        first = 'typedef struct First {\n    s32 value;\n} First;'
        second = 'typedef struct Second {\n    s32 value;\n    s32 count;\n} Second;'
        helper = '''static inline s32 ReadValue(Second* self) {
    const char* punctuation = "}; // not a brace or comment";
    if (self->count) {
        return self->value;
    }
    return 0;
}'''
        prototype = 'extern s32 Consume(\n    s32 value,\n    s32 count);'
        existing = 's32 Existing(void) {\n    return 0;\n}'
        header = '#include "ps2/prelude.h"'
        with tempfile.TemporaryDirectory() as directory:
            owner = Path(directory) / 'owner.c'
            owner.write_text(header + '\n' + first + '\n' + existing + '\n'
                             'INCLUDE_ASM("fixture", func_00100010);\n'
                             'INCLUDE_ASM("fixture", func_00100020);\n')
            for name in ('func_00100010', 'func_00100020'):
                body = f's32 {name}(Second* self) {{ return Consume(ReadValue(self), self->count); }}'
                source = '\n'.join((header, first, second, helper, prototype, body))
                declarations, code = decompile.split_draft(name, source)
                decompile.write(owner, name, declarations, code)
            result = owner.read_text()
            for block in (header, first, second, helper, prototype, existing):
                self.assertEqual(result.count(block), 1, block)
            self.assertNotIn('INCLUDE_ASM', result)
            self.assertIn('s32 func_00100010(Second* self)', result)
            self.assertIn('s32 func_00100020(Second* self)', result)


if __name__ == '__main__':
    unittest.main()
