#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0011C878(s32);
extern s32 func_0011C8C0();
extern s32 func_0011C930();
extern s32 func_0011C9C8();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_001199D8);

void func_0011A0A8(void* self) {
    func_0011C878((s32)self);
}

s32 func_0011A0C8(void) {
    func_0011C8C0();
    return 1;
}

void func_0011A0E8(void) {
    func_0011C930();
}

s32 func_0011A108(void) {
    func_0011C9C8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011A128);
extern void func_00382348(void*, s32);
extern void func_0014A8F8(void*);
void func_0011A130(void* self) {
    u8* entry = (u8*)self + 0x20;
    u8* flags = (u8*)self + 0x140;
    s8 i = 0;
    func_00382348((u8*)self + 0x10, 0x02B9D6F8);
    M2C_FIELD(self, s32*, 0x144) = 0;
    do {
        func_0014A8F8(entry);
        entry += 0x120;
        flags[i] = 0;
        i++;
    } while (i <= 0);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011A1C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011A270);

s32 func_0011A888(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011A890);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011A9D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011ABA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011AF50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011AFB0);

void func_0011BF20(void* unused) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011BF28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011BFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011C0F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1199d8", func_0011C4A8);
