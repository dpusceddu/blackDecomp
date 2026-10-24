#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00281388();

void func_002813A0(void *arg0) {
    func_00281388();
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002813D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281620);
