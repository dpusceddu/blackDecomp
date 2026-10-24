#include "ps2/prelude.h"

void func_00391180(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
}

s32 func_00391188(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x14);
}

s32 func_00391190(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 8);
}

s32 func_00391198(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

f32 func_003911A0(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x10);
}

void func_003911A8(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = fparg0;
}
