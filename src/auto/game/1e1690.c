#include "auto/prelude.h"

extern f32 func_001ED820(s32);
extern void * D_0040F510;
extern s8 func_00281120();
extern f32 D_003BD390;

void func_001E1690(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        M2C_FIELD(arg0, f32 *, 0x242C) = func_001ED820(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x2C));
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x242C) = 0.0f;
}

void func_001E16E0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x18) = func_00281120();
}

f32 func_001E1708(s32 arg0, s32 arg1) {
    return (&D_003BD390)[arg1];
}
