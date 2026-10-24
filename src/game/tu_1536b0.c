#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00165AE0();
extern s32 func_00165AF8();
extern s32 func_00154530(s32);
extern s32 func_00165B98();

void func_001536B0(void) {

}

void func_001536B8(void *arg0) {
    func_00165AE0();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
}

s32 func_001536E0(void *arg0) {
    func_00165AF8();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    return 1;
}

void func_00153710(void *arg0) {
    func_00154530(M2C_FIELD(arg0, s32 *, 0x18));
}

s32 func_00153730(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00153750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00153758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00153B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00153EB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00153F78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00154110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001543C8);

void func_00154518(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x94) == 0) {
        M2C_FIELD(arg0, s32 *, 0x94) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00154530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001545D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00154640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00154698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001546A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00154A10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00154A70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00154AE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00154DD0);
