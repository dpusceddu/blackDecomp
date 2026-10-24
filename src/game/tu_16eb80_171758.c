#include "ps2/prelude.h"

extern s32 func_0028B2A8(void *, s32);
extern void * D_0040F4D4;
extern s32 func_002F4620(s32, s32, s32);
extern s32 func_0028B1F0(void *, s32);
extern s32 func_002F47B0(s32, s32, s32);

s32 func_00171758(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x7C);
    if (((u32) (temp_3 - 3) < 2U) || (temp_3 == 1)) {
        return 0;
    }
    return 1;
}

void func_00171788(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        func_0028B2A8(D_0040F4D4 + 0x13D0, arg2);
    }
    func_002F4620(arg0, arg1, arg2);
}

void func_001717E8(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        func_0028B1F0(D_0040F4D4 + 0x13D0, arg2);
    }
    func_002F47B0(arg0, arg1, arg2);
}
