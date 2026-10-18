"""Recognize natural linker alignment after source text, without adding code bytes."""
import json
from pathlib import Path
from elfinfo import Elf


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
        self.slots, self.objects = {}, {}
        for obj in json.loads((self.build / 'objects.json').read_text()):
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

    def at(self, address):
        slots = self.slots.get(address, [])
        if len(slots) != 1:
            return None
        obj, section = slots[0]
        if obj not in self.objects:
            path = self.build / self.cache.get(obj, 'missing')
            self.objects[obj] = Elf(path.read_bytes()) if path.is_file() else None
        elf = self.objects[obj]
        record = elf.section(section) if elf else None
        return record['align'] if record and record['size'] else None
