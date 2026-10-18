#include "auto/prelude.h"

extern s32 func_0035E7D8(s32);

void func_00170798(void *arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = func_0035E7D8(arg1 * 0x10);
    M2C_FIELD(arg0, s32 *, 0x6C) = arg1;
    M2C_FIELD(arg0, s32 *, 0x60) = temp_2;
}
