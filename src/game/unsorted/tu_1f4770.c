#include "include_asm.h"
#include "ps2/prelude.h"

extern void * D_0040F0E0;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F4770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F4CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F4D30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F4D88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F4DE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F4E38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F5410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F5418);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F5498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F5770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F5850);

void func_001F5928(void *arg0) {
    if (M2C_FIELD(D_0040F0E0, s32 *, 0x2014C) != 0) {
        M2C_FIELD(arg0, s8 *, 0x19A4) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F5950);
