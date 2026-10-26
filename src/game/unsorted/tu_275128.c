#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275128);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275338);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275370);
#ifdef NON_MATCHING
// Unmatched: copy-loop scheduling and temporary registers differ.
u16* func_00275398(u16* destination, s32 capacity, const u16* source) {
    u16* end = (u16*)((u8*)destination + (capacity * 2 - 2));
    u16 value = *source;
    *destination = value;
    if ((u32)destination < (u32)end) {
        do {
            value = *source++;
            if (value == 0)
                return destination;
            destination++;
            value = *source;
            *destination = value;
        } while ((u32)destination < (u32)end);
    }
    *end = 0;
    return end;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275398);
#endif
#ifdef NON_MATCHING
// Unmatched: scan and copy-loop scheduling differ.
u16* func_002753F0(u16* destination, const u16* source) {
    while (*destination != 0)
        destination++;
    *destination = *source;
    while (*source++ != 0) {
        destination++;
        *destination = *source;
    }
    return destination;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_002753F0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275448);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275560);

#include "ps2/recovered_types.h"
extern u16 D_0040DE7A;
extern s16 D_0040DE7C;
extern void func_0028EED8(void* block);

// UNVERIFIED: offsets and table roles are inferred from the asset fixup.
typedef struct {
    u32 unk_00;
    u32 unk_04;
    f32 unk_08;
    u32 unk_0C;
    f32 unk_10;
    u8 unk_14[8];
    u32 unk_1C;
    u32 buckets[128];
} Recovered_FontOffsets;

// UNVERIFIED: glyph metrics and flags are inferred from the width draft.
typedef struct {
    u8 unk_00[8];
    f32 unk_08;
    u32 unk_0C;
    f32 unk_10;
    u32 unk_14;
    f32 unk_18;
    u16 code;
    u8 unk_1E[2];
    s32 unk_20;
    u32 unk_24;
} Recovered_FontGlyph;


void func_002756A8(s32 arg0, s32 arg1) {
    D_0040DE7A = (u16) arg0;
    D_0040DE7C = (s16) arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_002756B8);
#ifdef NON_MATCHING
// Unmatched: format-scan branch shape and character widths differ.
s32 func_002756C0(u16** output, const u16** input) {
    const u16* source = *input;
    u16 character = *source;
    u16* destination = *output;
    u32 code;
    if (character != 0) {
        code = character & 0xFFFF;
    loop:
        if (code != '%') {
            *destination++ = character;
            source++;
        } else {
            u16 next = *++source;
            if (next == code) {
                *destination++ = next;
                source++;
            }
            if ((u32)(next - '1') < 9) {
                *output = destination;
                *input = source + 1;
                return next - '0';
            }
        }
        character = *source;
        code = character & 0xFFFF;
        if (character != 0)
            goto loop;
    }
    *destination = 0;
    *output = destination;
    *input = source;
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_002756C0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275748);
u32 func_00275878(Recovered_FontOffsets* font) {
    u32 index = 0;
    u32* bucket = font->buckets;
    u32 offset;
    do {
        index++;
        *bucket += (u32)font;
        bucket++;
    } while (index < 128);
    offset = font->unk_04;
    if (offset != 0) {
        font->unk_04 = offset + (u32)font;
        func_0028EED8((void*)font->unk_04);
    }
    font->unk_1C += (u32)font;
    return font->unk_1C;
}
#ifdef NON_MATCHING
// Unmatched: glyph search loop allocation and branches differ.
f32 func_002758E0(Recovered_FontOffsets* font, const u16* text) {
    u16 firstCode = *text;
    Recovered_FontGlyph* glyph = (Recovered_FontGlyph*)font->buckets[firstCode & 0x7F];
    Recovered_FontGlyph* current = glyph;
    f32 width;
    if (glyph->code != firstCode) {
        Recovered_FontGlyph* end = (Recovered_FontGlyph*)font->unk_1C;
        if (glyph != end) {
        firstLookup:
            glyph++;
            if (glyph->code != firstCode && glyph != end)
                goto firstLookup;
        }
        current = glyph;
    }
    text++;
    width = -current->unk_10;
    if (*text != 0) {
        do {
            u16 code = *text++;
            glyph = (Recovered_FontGlyph*)font->buckets[code & 0x7F];
            width += current->unk_18;
            if (glyph->code != code) {
                Recovered_FontGlyph* end = (Recovered_FontGlyph*)font->unk_1C;
                if (glyph != end) {
                nextLookup:
                    glyph++;
                    if (glyph->code != code && glyph != end)
                        goto nextLookup;
                }
            }
            current = glyph;
        } while (*text != 0);
    }
    if (current->unk_20 == 0)
        width += current->unk_10 + current->unk_08;
    else
        width += current->unk_10 + current->unk_08 * font->unk_10;
    return width * font->unk_08;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_002758E0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_002759E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275AD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00275DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_00276110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_002761A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_002761E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128", func_002761E8);
