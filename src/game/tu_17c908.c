#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0017E770();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017C908);

void func_0017C9F0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x44) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017C9F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017CAF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017D4B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017D7A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017DAD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017DB10);

void func_0017DB18(void *arg0) {
    if (func_0017E770() == 0) {
        M2C_FIELD(arg0, s8 *, 0x7E) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017DB50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017DB98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017DE50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017E428);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017E488);
