#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00108DB8();

s32 func_00107E10(s32 *arg0) {
    *arg0 = 0;
    return 1;
}

void func_00107E20(void) {

}

void func_00107E28(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107E30);

s32 func_00107F60(s32 arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xC88) != 1) {
        goto block_4;
    }
    if (func_00108DB8(arg0) != 0) {
        goto block_3;
    }
    return 0;
block_3:
    M2C_FIELD(arg0, s32 *, 0xC88) = 0x1C;
block_4:
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107FB0);
