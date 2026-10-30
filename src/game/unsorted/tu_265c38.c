#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00266808();

extern u128 D_00440EF0[];
extern u8* D_00442ED0;
extern u32* D_00442ED4;
extern s32 D_00442ED8;

#ifdef NON_MATCHING
/* Native quadword packet storage; original producer and packet type identities are UNVERIFIED. */
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

extern s32 D_00442EE8;
extern s32 D_0040E690;
extern void func_00268928(void);
extern s128 D_00443030;
extern s128 D_00443100;
extern s128 D_00443110;
extern s128 D_00443120;
extern s128 D_00443130;
extern s128 D_00443140;

void func_00266698(void) {
    s32 count;
    u8* second;
    u8* third;
    u8* first;
    u8* fourth;

    D_00442EE8 = D_0040E690;
    D_00442ED0 = (u8*)D_00440EF0;
    D_00442ED4 = NULL;
    D_00442ED8 = 0xC;
    func_00268928();
    if (D_00442ED8 != 0xB) {
        if ((s32)D_00442ED0 & 0xF) { D_00442ED0 = (u8*)(((s8*)D_00442ED0) + 8); }
        D_00442ED8 = 0xB;
        M2C_FIELD(D_00442ED0, s128*, 0) = D_00443030;
        D_00442ED4 = (u32*)D_00442ED0;
        D_00442ED0 = (u8*)(((s8*)D_00442ED0) + 0x10);
    }
    M2C_FIELD(D_00442ED0, s128*, 0) = D_00443100;
    first = D_00442ED0;
    D_00442ED0 = (u8*)(((s8*)first) + 0x10);
    M2C_FIELD(first, s128*, 0x10) = (s128)D_00443110;
    second = D_00442ED0;
    D_00442ED0 = (u8*)(((s8*)second) + 0x10);
    M2C_FIELD(second, s128*, 0x10) = (s128)D_00443120;
    third = D_00442ED0;
    D_00442ED0 = (u8*)(((s8*)third) + 0x10);
    M2C_FIELD(third, s128*, 0x10) = (s128)D_00443130;
    fourth = D_00442ED0;
    D_00442ED0 = (u8*)(((s8*)fourth) + 0x10);
    M2C_FIELD(fourth, s128*, 0x10) = (s128)D_00443140;
    D_00442ED0 = (u8*)(((s8*)D_00442ED0) + 0x10);
    count = *D_00442ED4 + 5;
    *D_00442ED4 = count;
    return;
}

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
