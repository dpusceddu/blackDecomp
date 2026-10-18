"""Present split sections to m2c without changing the assembly used by the build.

m2c recognizes .text.* but only exact names for data sections. Address suffixes in
our migrated .rodata therefore hide switch tables and literals from its parser.
"""
import re


SECTION = re.compile(r'^(\s*\.section\s+)(\.(?:rodata|rdata|late_rodata|lit4|sdata2|data|sdata|bss|sbss))(?:\.[0-9A-Fa-f]{8})?(?=\s|,|$)', re.M)
READONLY = {'.rodata', '.rdata', '.late_rodata', '.lit4', '.sdata2'}


def normalize_sections(text):
    def section(match):
        name = match.group(2)
        target = '.rodata' if name in READONLY else '.bss' if name in ('.bss', '.sbss') else '.data'
        return match.group(1) + target
    return SECTION.sub(section, text)


def prepare(text):
    import ee_prep
    return ee_prep.prep(normalize_sections(text))
