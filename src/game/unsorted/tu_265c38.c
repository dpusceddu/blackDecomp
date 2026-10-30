#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00266808();

#ifdef NON_MATCHING
/* Native quadword packet storage; original producer and packet type identities are UNVERIFIED. */
extern u128 D_00440EF0[];
extern u8* D_00442ED0;
extern u32* D_00442ED4;
extern s32 D_00442ED8;
extern u128* D_0040E5F0;
extern void func_002B3D88(u32, s32);

// Unmatched: burst-copy register allocation and loop/branch scheduling differ.
void func_00265C38(void) {
    u128* source = D_00440EF0;
    s32 count;
    s32 copied;
    s32 limit;
    u128* destination;
    *D_00442ED4 |= 0x8000;
    count = ((u32)D_00442ED0 - (u32)source + 8) >> 4;
    func_002B3D88(0x80000000, count);
    destination = D_0040E5F0;
    copied = 0;
    if (count - 8 > 0) {
        limit = count - 8;
        do {
            u128 a = *source++;
            u128 b = *source++;
            u128 c = *source++;
            u128 d = *source++;
            u128 e = *source++;
            u128 f = *source++;
            u128 g = *source++;
            u128 h = *source++;
            *destination++ = a;
            *destination++ = b;
            *destination++ = c;
            *destination++ = d;
            *destination++ = e;
            *destination++ = f;
            *destination++ = g;
            *destination++ = h;
            copied += 8;
        } while (copied < limit);
    }
    if (copied < count) {
        copied = count - copied;
        do {
            *destination++ = *source++;
            copied--;
        } while (copied);
        D_0040E5F0 = destination;
    } else {
        D_0040E5F0 = destination;
    }
    D_00442ED0 = (u8*)D_00440EF0;
    D_00442ED4 = NULL;
    D_00442ED8 = 12;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00265C38);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00265DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00266088);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_002662A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_002664A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00266698);

s32 func_002667E8(s32 arg0) {
    return func_00266808(arg0, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00266808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00266A18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00266D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00266F50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00267258);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00267668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00267670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_002679E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00267EA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00267EB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00268250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_002683A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_002684E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_002685D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_002687B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_002688E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_265c38", func_00268928);
