#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001E8120();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9958);

void func_001E9AC8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9AD0);

void func_001E9B30(void *arg0) {
    func_001E8120();
    M2C_FIELD(arg0, s32 *, 0x1B4) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9B58);
