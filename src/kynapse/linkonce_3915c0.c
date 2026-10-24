#include "ps2/prelude.h"

void func_003915C0(void) {

}

void func_003915C8(void) {

}

s32 func_003915D0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

s32 func_003915D8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x14);
}

s32 * func_003915E0(void *arg0, u32 arg1) {
    s32 *temp_2;

    if (arg1 >= (u32) M2C_FIELD(arg0, u32 *, 0xC)) {
        return NULL;
    }
    temp_2 = (arg1 * 0x14) + M2C_FIELD(arg0, s32 *, 0x18);
    return (~*temp_2 == 0) ? NULL : temp_2;
}

s32 func_00391618(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x2C);
}

s32 func_00391620(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x30);
}
