#include "auto/prelude.h"

extern s32 func_001A2CD8(s32);

void func_00188B68(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x3A8);
    if (temp_4 != 0) {
        func_001A2CD8(temp_4);
    }
}

void func_00188B90(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x130) = arg1;
}
