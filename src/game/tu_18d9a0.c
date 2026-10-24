#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D9A0);

void func_0018D9E8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
}

void func_0018D9F0(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = fparg0;
}

f32 func_0018D9F8(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    if ((temp_3 >= 0x1D) && ((temp_3 < 0x20) || (temp_3 == 0x2A))) {
        return 4.5f;
    }
    return 6.51999f;
}
