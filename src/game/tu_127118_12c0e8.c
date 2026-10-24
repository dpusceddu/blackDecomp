#include "ps2/prelude.h"

extern s32 func_0012C118(s32, s32);

s32 func_0012C0E8(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_4 != 0) {
        func_0012C118(temp_4, arg2);
    }
    return 1;
}
