#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_003106F0(s32, M2C_UNK, M2C_UNK, f32);

void * func_0031A308(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 4, 1, *arg2);
    }
    return arg0;
}

s32 func_0031A350(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x7C);
    return arg0;
}

void * func_0031A360(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x80) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 5, 1, *arg2);
    }
    return arg0;
}

s32 func_0031A3A8(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
    return arg0;
}

void * func_0031A3B8(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x78) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 6, 1, *arg2);
    }
    return arg0;
}

s32 func_0031A400(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    return arg0;
}
