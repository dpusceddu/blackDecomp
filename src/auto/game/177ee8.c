#include "auto/prelude.h"

void func_00177EE8(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_3;

    temp_3 = 1 << arg1;
    if (arg2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x64) = (s32) (M2C_FIELD(arg0, s32 *, 0x64) | temp_3);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x64) = (s32) (M2C_FIELD(arg0, s32 *, 0x64) & ~temp_3);
}
