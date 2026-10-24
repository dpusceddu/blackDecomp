#include "include_asm.h"
#include "ps2/prelude.h"

void func_001794A0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x70) = 0;
    M2C_FIELD(arg0, s8 *, 0x74) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001794B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001795A0);
