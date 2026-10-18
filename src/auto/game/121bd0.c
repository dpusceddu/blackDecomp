#include "auto/prelude.h"

extern s32 func_0020F920(s32);
extern s32 func_002105F8(s32);
extern s32 func_00107D20(M2C_UNK);

s32 func_00121BD0(s32 arg0) {
    func_0020F920(arg0 + 8);
    func_002105F8(arg0 + 0xC);
    return 1;
}

void func_00121C08(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x3C) = func_00107D20(0x40);
}
