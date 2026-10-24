#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00164DF0();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00164BC0);

void func_00164D30(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x195) == 0) {
        func_00164DF0();
        M2C_FIELD(arg0, u8 *, 0x195) = 1U;
    }
}
