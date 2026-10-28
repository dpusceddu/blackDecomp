#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_001F1C08(void*);
extern void func_00200A68(void *arg0);
extern void func_001F9028(void *);
extern void func_001FA468(void *);

#ifdef NON_MATCHING
// Unmatched: address-add operand order differs.
void func_001F9028(void* self) {
    u8 i = 0;
    s32* slots = (s32*)((u8*)self + 0xB20);
    func_001F1C08(self);
    M2C_FIELD(self, s32*, 0xB90) = 0;
    do {
        func_00200A68((u8*)self + ((i << 7) + 0x20));
        slots[i] = 0;
        i++;
    } while (i < 0x16);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F9028);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F9098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F92A0);

void func_001F9980(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xB90) = 1;
}

extern void func_001F1E58(void*, void*);
extern void func_00278F00(void*, s32, s32);
extern s32 D_003F9C50;
extern s32 D_0040F518;
#ifdef NON_MATCHING
// Unmatched: loop counter initialization is scheduled after the first call.
s32 func_001F9990(void* self) {
    s32* slot = (s32*)((u8*)self + 0xB20);
    s8 i = 0;
    func_001F1E58(self, &D_003F9C50);
    do {
        func_00278F00((void*)(M2C_FIELD(self, s8*, 0x12) * 0xA8 + D_0040F518 + 0x40),
                      M2C_FIELD(self, s16*, 0x10) + 1, *slot);
        *slot = 0;
        i++;
        slot++;
    } while (i < 0x16);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F9990);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F9A40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F9AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F9BE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F9DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F9DE8);

void func_001F9EB0(void *arg0) {
    func_001F1C08(arg0);
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    func_00200A68(arg0 + 0x20);
    func_001F9028(arg0 + 0xC0);
    func_001FA468(arg0 + 0xC80);
    M2C_FIELD(arg0, s32 *, 0xEA8) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001F9EF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001FA130);
extern void func_001F1E20(void*, void*);
extern s32 D_003F9C80;
s32 func_001FA3A8(void* self) {
    func_001F1E20(self, &D_003F9C80);
    func_00278F00((void*)(M2C_FIELD(self, s8*, 0x12) * 0xA8 + D_0040F518 + 0x40), M2C_FIELD(self, s16*, 0x10), M2C_FIELD(self, s32*, 0xA0));
    M2C_FIELD(self, s32*, 0xA0) = 0;
    func_00278F00((void*)(M2C_FIELD(self, s8*, 0x12) * 0xA8 + D_0040F518 + 0x40), M2C_FIELD(self, s16*, 0x10), M2C_FIELD(self, s32*, 0xA4));
    M2C_FIELD(self, s32*, 0xA4) = 0;
    return 1;
}
void func_001FA438(void* self) {
    func_001F9980((u8*)self + 0xC0);
    M2C_FIELD(self, s32*, 0xEA8) = 1;
}
#ifdef NON_MATCHING
// Unmatched: address-add operand order differs.
void func_001FA468(void* self) {
    u8 i = 0;
    s32* slots = (s32*)((u8*)self + 0x1F0);
    func_001F1C08(self);
    do {
        func_00200A68((u8*)self + ((i << 7) + 0x70));
        slots[i] = 0;
        i++;
    } while (i < 3);
    M2C_FIELD(self, s32*, 0x218) = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001FA468);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001FA4D8);

s32 func_001FAB98(void) {
    return 1;
}

void func_001FABA0(void* self) {
    s32 value = M2C_FIELD(self, u8*, 0x214) + 1;
    M2C_FIELD(self, u8*, 0x214) = value;
    if ((s8)value >= 4) {
        M2C_FIELD(self, u8*, 0x214) = 3;
        return;
    }
    M2C_FIELD(self, s32*, 0x210) = 1;
}
void func_001FABD8(void* self) {
    s32 value = M2C_FIELD(self, u8*, 0x214) - 1;
    M2C_FIELD(self, u8*, 0x214) = value;
    if ((s8)value < 0) {
        M2C_FIELD(self, u8*, 0x214) = 0;
        return;
    }
    M2C_FIELD(self, s32*, 0x210) = 3;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1f9028", func_001FAC00);
