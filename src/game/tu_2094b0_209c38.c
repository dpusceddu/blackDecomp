#include "auto/prelude.h"

extern s32 func_0020D910(s32);
extern void func_00209CF0();

void func_00209C38(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = 5;
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) + 1);
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
}

s32 func_00209C60(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

s32 func_00209C68(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

s32 func_00209C70(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

s32 func_00209C78(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

s32 func_00209C80(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

void func_00209C88(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x10) = arg1;
}

void func_00209C90(void *arg0, s32 arg1) {
    s32 temp_2;

    M2C_FIELD(arg0, s32 *, 4) = arg1;
    temp_2 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_2 != 0) {
        func_0020D910(temp_2);
    }
}

void func_00209CC0(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xC) - 1;
    M2C_FIELD(arg0, s32 *, 0xC) = temp_2;
    if (temp_2 <= 0) {
        func_00209CF0();
    }
}
