#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00198568();

void func_00198E28(void *arg0) {
    func_00198568();
    M2C_FIELD(arg0, s8 *, 0x20) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1984f0_198e28", func_00198E50);
