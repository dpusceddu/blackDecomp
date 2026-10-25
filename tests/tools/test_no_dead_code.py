"""The sources hold no code that no build can reach (docs/units.md, "Drafts").

A draft is an `#ifdef NON_MATCHING` block above its INCLUDE_ASM line, and readable code whose function is not known is not
kept. The only other conditional that may surround function bodies is FULL_TU_CONTEXT, which the split list defines for the
units that compile unfinished bodies as context ("Full TU context"). Every other macro in a conditional must be an include
guard, __cplusplus, a guard for a definition a standard header may already have, or a macro some source file defines itself
(a code-shape switch), and none may look like a draft guard (NONMATCHING)."""
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ALLOWED = {'NON_MATCHING', 'FULL_TU_CONTEXT', '__cplusplus', 'INCLUDE_ASM', 'offsetof', 'FLT_MAX'}
CONDITIONAL = re.compile(r'^\s*#\s*(if|ifdef|ifndef|elif)\b(.*)$')


def sources():
    for base in ('src', 'include'):
        for path in sorted((ROOT / base).rglob('*')):
            if path.suffix in ('.c', '.cpp', '.h', '.hpp'):
                yield path, path.read_text(errors='replace').split('\n')


def macros_of(kind, rest):
    if kind in ('ifdef', 'ifndef'):
        return re.findall(r'[A-Za-z_]\w*', rest)[:1]
    return [m for m in re.findall(r'[A-Za-z_]\w*', re.sub(r'/\*.*?\*/|//.*', '', rest)) if m != 'defined']


class NoDeadCode(unittest.TestCase):
    def test_no_if_0_block_in_src_or_include(self):
        found = [p.relative_to(ROOT).as_posix() for p, lines in sources() if any(re.match(r'^\s*#\s*if\s+0\b', l) for l in lines)]
        self.assertEqual([], found)

    def test_no_nonmatching_style_or_undefined_guard_macro(self):
        found = []
        every = list(sources())
        defined = {m.group(1) for _, lines in every for l in lines for m in [re.match(r'^\s*#\s*define\s+(\w+)', l)] if m}
        for path, lines in every:
            for n, line in enumerate(lines):
                m = CONDITIONAL.match(line)
                if not m:
                    continue
                kind, rest = m.groups()
                for name in macros_of(kind, rest):
                    guard = kind == 'ifndef' and any(re.match(r'^\s*#\s*define\s+%s\b' % re.escape(name), l) for l in lines[n + 1:n + 4])
                    if name not in ALLOWED and 'NONMATCHING' in name.upper().replace('_', ''):
                        found.append('%s:%d: %s' % (path.relative_to(ROOT).as_posix(), n + 1, line.strip()))
                    elif name in ALLOWED or guard or name.isdigit() or name in defined:
                        continue
                    found.append('%s:%d: %s' % (path.relative_to(ROOT).as_posix(), n + 1, line.strip()))
        self.assertEqual([], found)

    def test_nonmatching_is_the_only_draft_macro_and_the_split_list_defines_the_other(self):
        flags = (ROOT / 'config/SLUS_213.76/splits.yaml').read_text()
        defined = set(re.findall(r'-D(\w+)', flags))
        self.assertEqual({'FULL_TU_CONTEXT'}, defined)


if __name__ == '__main__':
    unittest.main()
