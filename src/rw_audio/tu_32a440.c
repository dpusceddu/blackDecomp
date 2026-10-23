#include "auto/prelude.h"

void * func_0032A440(void *arg0, s32 arg1, void *arg2) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 0x54C);
    if (temp_5 != 0) {
        M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(((M2C_FIELD(arg2, s32 *, 8) * 4) + M2C_FIELD(((M2C_FIELD(arg2, s32 *, 4) * 0xC) + temp_5), s32 *, 4)), s32 *, 0);
    } else {
        M2C_FIELD(arg2, s32 *, 0) = 0;
    }
    return arg0;
}
