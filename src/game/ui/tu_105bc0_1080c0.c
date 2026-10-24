#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00367750();
extern void * D_0040F4C4;

s32 func_001080C0(void) {
    return func_00367750() == M2C_FIELD(D_0040F4C4, s32 *, 0xE08);
}

s32 func_001080F0(void) {
    return func_00367750() == M2C_FIELD(D_0040F4C4, s32 *, 0xE0C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00108120);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00108218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00108328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00108458);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001084A8);
