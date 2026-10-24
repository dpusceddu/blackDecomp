#include "ps2/prelude.h"

void func_0013DB10(void *arg0, s32 arg1, s128 arg2, f32 fparg0) {
    if ((arg1 >= M2C_FIELD(arg0, s32 *, 0x1F9C)) && (M2C_FIELD(arg0, s32 *, 0x4C) == 0)) {
        M2C_FIELD(arg0, f32 *, 0x1FA0) = fparg0;
        M2C_FIELD(arg0, s32 *, 0x1F9C) = arg1;
        M2C_FIELD(arg0, s128 *, 0x1FB0) = arg2;
    }
}
