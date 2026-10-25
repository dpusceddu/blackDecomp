#include "include_asm.h"

/* Remaining drafts in animation/tu_34b498. */
#include "ps2/prelude.h"

extern s32 func_00347430(s32, s32, s32);
extern s32 func_0034B910();

s32 func_0034B5A8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x14);
}

void func_0034D920(s32 arg0, s32 arg1) {
    func_00347430(arg0, func_0034B910(), arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034B5B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034B6E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034B910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034BA50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034BC30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034BFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034C0C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034C128);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0034C7D8);
