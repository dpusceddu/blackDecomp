#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00391658(s32 arg0) {
    return arg0 + 0x5C;
}

s32 func_00391660(s32 arg0) {
    return arg0 + 0x64;
}

s32 func_00391668(s32 arg0) {
    return arg0 + 0x78;
}

f32 func_00391670(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 8);
}

void func_00391678(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 8) = fparg0;
}

void func_00391680(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x54) = arg1;
}

void func_00391688(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x58) = arg1;
}

s32 func_00391690(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x54);
}

s32 func_00391698(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x58);
}

s32 func_003916A0(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xC);
    if (temp_2 == 0) {
        return 0;
    }
    return temp_2 - 1;
}

s32 func_003916C0(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x28);
    if (temp_2 == 0) {
        return 0;
    }
    return temp_2 - 1;
}

s32 func_003916E0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4) & 1;
}
