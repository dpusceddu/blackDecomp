#include "include_asm.h"
#include "ps2/prelude.h"

void func_00200A68(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x64) = 0;
    M2C_FIELD(arg0, s32 *, 0x70) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00200A78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00200AD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00200B50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00200BB0);
