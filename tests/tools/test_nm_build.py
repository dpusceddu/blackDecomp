"""The NON_MATCHING build converges the same way on every run (tools/build/nm_build.py), whatever an earlier run left behind.

`units_verify prepare` writes unit_facts.json from the objects of the current attempt and the units read it back; a stale copy
used to decide which units are compiled, so every other run failed to link ("undefined symbol func_00112808"). The build steps
are replaced by recorders; no game files or build backend are needed."""
import contextlib
import io
import json
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import nm_build


class FakeBuild:
    """Stands in for the build steps. Records, at every `units.py`, whether facts of an earlier attempt are still there."""

    def __init__(self, root, link_failures):
        self.root = root
        self.out = root / 'build' / 'SLUS_213.76-nm'
        self.link_failures = list(link_failures)       # per link attempt: the unit names the link error is attributed to
        self.facts_seen_by_units = []
        self.calls = []

    def run(self, *args, check=True):
        step = Path(str(args[0])).name
        previous = self.calls[-1] if self.calls else None
        self.calls.append(step + (' ' + str(args[1]) if step == 'units_verify.py' else ''))
        rc = 0
        if step == 'units.py':
            if previous in (None, 'units_verify.py link'):         # the first step of an attempt
                self.facts_seen_by_units.append((self.out / 'unit_facts.json').exists())
            (self.out / 'units-nm.json').write_text(json.dumps(dict(units=[
                dict(functions=[dict(addr=0x100000, status='source')])])))
        elif step == 'build_objects.py' and '--compile-only' in args:
            (self.out / 'results.json').write_text('{}')
        elif step == 'units_verify.py' and args[1] == 'prepare':
            (self.out / 'unit_facts.json').write_text('{"unit": {"assembly": [1048576]}}')
        elif step == 'build_objects.py':
            if self.link_failures:
                rc = 1
        elif step == 'units_verify.py' and args[1] == 'link':
            (self.out / 'unit_problems.json').write_text(json.dumps([[n, None, 'link'] for n in self.link_failures.pop(0)]))
        elif step == 'pack_elf.py':
            Path(args[4]).write_bytes(b'elf')
        return SimpleNamespace(returncode=rc, stdout='', stderr='')


class NonMatchingBuild(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        (self.root / 'config').mkdir()
        (self.root / 'config/versions.json').write_text(json.dumps({'SLUS_213.76': {'boot': 'SLUS_213.76'}}))
        build = self.root / 'build/SLUS_213.76'
        build.mkdir(parents=True)
        (build / 'units.json').write_text(json.dumps(dict(units=[dict(functions=[])])))
        self.out = self.root / 'build/SLUS_213.76-nm'
        self.out.mkdir(parents=True)
        for name in ('unit_facts.json', 'unit_problems.json'):
            (self.out / name).write_text('stale')       # left by an earlier run

    def run_build(self, link_failures=()):
        fake = FakeBuild(self.root, link_failures)
        with patch.object(nm_build, 'ROOT', self.root), patch.object(nm_build, 'run', fake.run), \
                patch.object(sys, 'argv', ['nm_build.py']), contextlib.redirect_stdout(io.StringIO()):
            nm_build.main()
        return fake

    def test_facts_of_an_earlier_run_never_reach_the_first_attempt(self):
        fake = self.run_build()
        self.assertEqual([False], fake.facts_seen_by_units)

    def test_facts_of_an_earlier_attempt_do_not_reach_the_next_one(self):
        fake = self.run_build(link_failures=[['unit_a']])
        self.assertEqual([False, False], fake.facts_seen_by_units)
        self.assertEqual(['unit_a'], json.loads((self.out / 'nm_fallback.json').read_text()))

    def test_the_facts_the_last_attempt_wrote_stay_for_the_link(self):
        self.run_build()
        self.assertTrue((self.out / 'unit_facts.json').exists())
        self.assertEqual('{"unit": {"assembly": [1048576]}}', (self.out / 'unit_facts.json').read_text())


if __name__ == '__main__':
    unittest.main()
