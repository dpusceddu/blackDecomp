#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00251A60();
extern s32 func_0035CFD8(s32, s32, s32);
extern s32 D_003BE904;
extern s32 func_0035CCD8(s32);
extern s32 func_0023DB58(void *, s32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021DD40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021DF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021E0B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021E170);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021E420);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021E960);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021EA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021F0F0);

void func_0021F0F8(void) {
    func_00251A60();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021F118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021F120);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021F1C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002202C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002205D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00220828);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00220B88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00220D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00220D78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00220ED0);

s32 func_00221050(s32 arg0, s32 arg1) {
    return func_0035CFD8(arg1, D_003BE904, func_0035CCD8(D_003BE904)) == 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00221098);

void func_002210E8(void) {

}

void func_002210F0(s32 arg0, void *arg1) {
    void *temp_16;
    void *temp_4;

    temp_16 = M2C_FIELD(arg1, void **, 4);
    func_0023DB58(temp_16, M2C_FIELD(M2C_FIELD(temp_16, void **, 0x48), s32 *, 0x18) + 1);
    temp_4 = M2C_FIELD(temp_16, void **, 0x48);
    M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFDFFFFFF);
}

void func_00221140(s32 arg0, void *arg1) {
    void *temp_16;
    void *temp_4;

    temp_16 = M2C_FIELD(arg1, void **, 4);
    func_0023DB58(temp_16, M2C_FIELD(M2C_FIELD(temp_16, void **, 0x48), s32 *, 0x18) - 1);
    temp_4 = M2C_FIELD(temp_16, void **, 0x48);
    M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFDFFFFFF);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00221190);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00221290);

void func_00221320(void) {

}

void func_00221328(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00221330);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00221618);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00221900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00221BE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00221E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002220C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00222360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00222628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002228F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00222A58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00222DD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00222F98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00223318);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002233B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00223548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00223678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002237D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00223900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00223B18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00223D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00223E38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00223F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00224010);
