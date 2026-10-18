#include "auto/prelude.h"

void func_0010B608(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x500) = arg1;
}

u8 func_0010B610(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x515);
}

void func_0010B618(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x516) = arg1;
}

s32 func_0010B620(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x4F8);
    M2C_FIELD(arg0, s32 *, 0x4F8) = 0;
    return temp_2;
}
