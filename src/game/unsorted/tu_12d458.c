#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00103860(s32);
extern s32 D_0040F0E0;
extern s32 func_00103848(s32);

void func_0012D458(void) {
    if (func_00103860(D_0040F0E0) != 0) {
        func_00103848(D_0040F0E0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012D490);

s16 func_0012D508(void *arg0) {
    return (s16) ((s8) M2C_FIELD(arg0, u8 *, 0x5AAC) | (M2C_FIELD(arg0, u8 *, 0x5CA0) << 8));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0012D530);
