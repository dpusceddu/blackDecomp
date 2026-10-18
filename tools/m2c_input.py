"""Present split sections and assembler-escaped instructions to m2c.

m2c recognizes .text.* but only exact names for data sections. Address suffixes in
our migrated .rodata therefore hide switch tables and literals from its parser.
Raw short branches and legal odd-FPR operations also need instruction syntax.
These changes affect only decompiler input, never the real build's assembly.
"""
import re


SECTION = re.compile(r'^(\s*\.section\s+)(\.(?:rodata|rdata|late_rodata|lit4|sdata2|data|sdata|bss|sbss))(?:\.[0-9A-Fa-f]{8})?(?=\s|,|$)', re.M)
READONLY = {'.rodata', '.rdata', '.late_rodata', '.lit4', '.sdata2'}
RAW = re.compile(r'^(\s*/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s+\*/\s*)\.word\s+(0x[0-9A-Fa-f]+)\b.*$')


def decode_raw_instructions(text):
    """Recover instructions hidden from m2c by assembler compatibility directives.

    Only address-annotated text words are candidates. Short branches are emitted
    raw by fixasm, and Rabbitizer emits some legal EE odd-FPR single operations
    as words. Data words and other unsupported instructions remain untouched.
    """
    import rabbitizer
    from fixasm import branch_offset
    lines = text.splitlines()
    replacements, targets, section = {}, set(), ''
    addresses = {}
    for index, line in enumerate(lines):
        if line.lstrip().startswith('.section '):
            section = line.split()[1].split(',')[0]
        if not section.startswith('.text'):
            continue
        address = re.search(r'/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s+\*/', line)
        if address:
            addresses[int(address.group(1), 16)] = index
        match = RAW.match(line)
        if not match:
            continue
        word, pc = int(match.group(3), 16), int(match.group(2), 16)
        instruction = rabbitizer.Instruction(word, pc, rabbitizer.InstrCategory.R5900)
        if not instruction.isValid():
            continue
        offset = branch_offset(word)
        if offset is not None:
            target = pc + 4 + offset * 4
            opcode, rs, rt = word >> 26, word >> 21 & 31, word >> 16 & 31
            # Split files use numeric GPRs. m2c rejects a mixture of aliases
            # ($v0 and $2), even when they identify the same register.
            if opcode in (4, 5, 0x14, 0x15):
                name = {4: 'beq', 5: 'bne', 0x14: 'beql', 0x15: 'bnel'}[opcode]
                branch = '%s $%d, $%d, ' % (name, rs, rt)
            elif opcode in (6, 7, 0x16, 0x17):
                name = {6: 'blez', 7: 'bgtz', 0x16: 'blezl', 0x17: 'bgtzl'}[opcode]
                branch = '%s $%d, ' % (name, rs)
            elif opcode == 1:
                branch = '%s $%d, ' % (instruction.getOpcodeName(), rs)
            else:
                branch = instruction.getOpcodeName() + ' '
            replacements[index] = (match.group(1) + branch + '.Lm2c_%08X' % target, target)
            targets.add(target)
        elif word >> 26 == 0x11 and word >> 21 & 31 in (16, 20):
            disassembly = instruction.disassemble()
            if disassembly.lstrip().startswith('.word') and '#' in disassembly:
                disassembly = disassembly.split('#', 1)[1].split('#', 1)[0].strip()
            if disassembly.split()[0] == instruction.getOpcodeName():
                replacements[index] = (match.group(1) + disassembly, None)
    labels = {addresses[a]: '.Lm2c_%08X:' % a for a in targets if a in addresses}
    out = []
    for index, line in enumerate(lines):
        if index in labels:
            out.append(labels[index])
        replacement = replacements.get(index)
        out.append(replacement[0] if replacement and (replacement[1] is None or replacement[1] in addresses) else line)
    return '\n'.join(out) + ('\n' if text.endswith('\n') else '')


def normalize_sections(text):
    def section(match):
        name = match.group(2)
        target = '.rodata' if name in READONLY else '.bss' if name in ('.bss', '.sbss') else '.data'
        return match.group(1) + target
    return SECTION.sub(section, text)


def prepare(text):
    import ee_prep
    return ee_prep.prep(decode_raw_instructions(normalize_sections(text)))
