#include "include_asm.h"
#include "ps2/prelude.h"

extern s8 D_0040EAD8;

void func_001AD070(void *arg0) {
    if (D_0040EAD8 != 0) {
        M2C_FIELD(arg0, f32 *, 0x9C8) = 1.0f;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AD098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AD0D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AD2E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AD360);
