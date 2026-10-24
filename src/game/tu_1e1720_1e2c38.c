#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001E1BA0();

void func_001E2C38(s32 arg0, void *arg1) {
    func_001E1BA0(arg1);
    M2C_FIELD(arg1, s8 *, 0x78) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E2C68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E2D38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E2F08);
