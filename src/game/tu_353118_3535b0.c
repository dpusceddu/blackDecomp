#include "ps2/prelude.h"

extern s32 func_00353518();

void func_003535B0(s32 arg0, void *arg1, s32 arg2) {
    M2C_FIELD(arg1, s32 *, 4) = (s32) (arg2 | 1);
    M2C_FIELD(arg1, void **, 0xC) = arg1;
    M2C_FIELD(arg1, void **, 8) = arg1;
    M2C_FIELD((arg1 + arg2), s32 *, 0) = arg2;
    func_00353518();
}
