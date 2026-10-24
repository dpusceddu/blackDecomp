"""Recognize natural linker alignment after source sections, without inventing bytes."""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json
from pathlib import Path
from elfinfo import Elf

DATA_SECTIONS = ('.rodata', '.lit4', '.gcc_except_table', '.data', '.sdata', '.bss', '.sbss')


def natural_text_span(size, start, stop, alignment, padding, input_alignment=1):
    """Only a zero-filled gap exactly produced by the next input's alignment fits."""
    gap = stop - start - size
    return bool(alignment and 1 < alignment <= 16 and alignment & (alignment - 1) == 0
                and start % max(1, input_alignment) == 0 and 0 < gap < alignment
                and (start + size + alignment - 1) // alignment * alignment == stop
                and len(padding) == gap and not any(padding))


class InputAlignments:
    """Actual next linked input section, from the same cached objects used by the link."""
    def __init__(self, build):
        self.build = Path(build)
        self.cache = json.loads((self.build / 'objects_cache.json').read_text())
        self.slots, self.objects, self.data_slots = {}, {}, {}
        objects = json.loads((self.build / 'objects.json').read_text())
        names = {obj['name'] for obj in objects}
        for obj in objects:
            sections = obj.get('rename', {})
            if obj['name'].startswith('text/func_') and '.' not in obj['name']:
                address = obj['name'].removeprefix('text/func_')
                sections = {'.text.' + address: '.text.' + address}
            for old, new in sections.items():
                if new.startswith('.text.'):
                    try:
                        address = int(new.removeprefix('.text.'), 16)
                    except ValueError:
                        continue
                    self.slots.setdefault(address, []).append((obj['name'], old))
                for sec in DATA_SECTIONS:
                    if new.startswith(sec + '.'):
                        try:
                            address = int(new.removeprefix(sec + '.'), 16)
                        except ValueError:
                            continue
                        self.data_slots.setdefault((sec, address), []).append((obj['name'], old))
        placement = self.build / 'placement.json'
        if placement.exists():
            for sec, entries in json.loads(placement.read_text())['sections'].items():
                if sec not in DATA_SECTIONS:
                    continue
                for entry in entries:
                    if entry['obj'] in names and 'key' in entry:
                        self.data_slots.setdefault((sec, entry['key']), []).append((entry['obj'], entry['sec']))

    def at(self, address):
        return self._alignment(self.slots.get(address, []))

    def data_at(self, section, address):
        return self._alignment(self.data_slots.get((section, address), []))

    def data_section(self, section, address):
        """The unique actual data input, including its native kind and alignment."""
        return self._section(self.data_slots.get((section, address), []))

    def _section(self, slots):
        if len(slots) != 1:
            return None
        obj, section = slots[0]
        if obj not in self.objects:
            path = self.build / self.cache.get(obj, 'missing')
            self.objects[obj] = Elf(path.read_bytes()) if path.is_file() else None
        elf = self.objects[obj]
        record = elf.section(section) if elf else None
        return record if record and record['size'] else None

    def _alignment(self, slots):
        record = self._section(slots)
        return record['align'] if record else None
