#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003D2B00;
extern s32 D_003D2B04;

void func_00348A10(s32 arg0, s32 arg1) {
    D_003D2B00 = arg0;
    D_003D2B04 = arg1;
}

s32 func_00348A28(void) {
    return D_003D2B04;
}
