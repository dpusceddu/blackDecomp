"""Conservative stack-frame facts for automatic drafts; no target tools run here."""


def _control(word):
    opcode = word >> 26
    return (opcode in (1, 2, 3, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17)
            or opcode == 0 and word & 63 in (8, 9, 12, 13)
            or opcode in (0x10, 0x11, 0x12) and word >> 21 & 31 == 8)


def detect_frame_size(words, max_prefix=16):
    """One fixed addiu sp,sp,-N, optionally scheduled behind harmless instructions.

    Refuse pre-frame branches/stack accesses, dynamic SP writes and multiple
    allocations. Positive restores must equal the allocation. This is a frame
    bound, not proof that any part of it is an object or has a particular lifetime.
    """
    import rabbitizer
    frame, allocation = None, None
    for index, word in enumerate(words):
        rs, rt = word >> 21 & 31, word >> 16 & 31
        immediate = (word & 0xffff) - (0x10000 if word & 0x8000 else 0)
        adjustment = word >> 26 == 9 and rs == rt == 29
        if adjustment:
            if immediate < 0:
                if frame is not None or index >= max_prefix or -immediate > 0x4000 or (-immediate) % 8:
                    return None
                frame, allocation = -immediate, index
            elif frame is None or immediate != frame:
                return None
            continue
        instruction = rabbitizer.Instruction(word, index*4, rabbitizer.InstrCategory.R5900)
        writes_sp = ((instruction.modifiesRd() and word >> 11 & 31 == 29)
                     or (instruction.modifiesRt() and rt == 29)
                     or (instruction.modifiesRs() and rs == 29))
        if writes_sp:
            return None
        if frame is None:
            if index >= max_prefix or _control(word):
                return None
            if rs == 29 and (instruction.doesLoad() or instruction.doesStore()):
                return None
    return frame
