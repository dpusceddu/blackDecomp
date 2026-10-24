#include "ps2/prelude.h"

s32 func_003892A0(s32 arg0) {
    return arg0 + 0x34;
}

void func_003892A8(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x68) = fparg0;
}

f32 func_003892B0(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x68);
}

void func_003892B8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x74) = arg1;
}

s32 func_003892C0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x74);
}

void func_003892C8(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x78) = arg1;
}

u8 func_003892D0(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x78);
}

s32 func_003892D8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}
