#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002810A0(void *);

void func_001E31A8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x260) != 0) {
        func_002810A0(arg0 + 0x250);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E31D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E32B8);
