#include "include_asm.h"
#include "ps2/prelude.h"
extern void* D_0040F4BC;
extern void func_001354E0(void*, void*);
extern void func_0027F9C0(void*, s32);
extern void* D_0040F4D0;
extern void func_00103918(void*, s32);
extern void* D_0040F0E0;
// Local access view; original class identities are UNVERIFIED.
// The controller vtable event slot is func_0027D0D8(self, event, argument).

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
void func_0011C4A8(void* arg0) {
    void* temp_2;
    void* temp_4;

    if (M2C_FIELD(arg0, u8*, 0x15D) != 0) {
        M2C_FIELD(arg0, s32*, 0x158) = 0;
        if (M2C_FIELD(M2C_FIELD(arg0, void**, 0x150), s32*, 0x38C) == 2) {
            temp_2 = M2C_FIELD(D_0040F4BC, void**, 0x14);
            M2C_FIELD(temp_2, void (**)(void*, s32, s32),
                      0x24)((void*)(((s8*)D_0040F4BC) + M2C_FIELD(temp_2, s16*, 0x20)), 0xB, 0);
            temp_4 = M2C_FIELD(arg0, void**, 0x154);
            func_001354E0(temp_4, (void*)(((s8*)temp_4) + 0x4F0));
            M2C_FIELD(arg0, s32*, 4) = 0;
            M2C_FIELD(M2C_FIELD(arg0, void**, 0x154), s8*, 0x8B2) = 0;
            M2C_FIELD(arg0, s8*, 0x15C) = 0;
            func_0027F9C0(D_0040F4D0, 1);
            func_00103918(D_0040F0E0, 0);
            M2C_FIELD(arg0, u8*, 0x15D) = 0U;
            return;
        }
        M2C_FIELD(arg0, s32*, 4) = 6;
    }
}
