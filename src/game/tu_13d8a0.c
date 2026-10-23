#include "auto/prelude.h"

extern s32 func_00189B90(s32, s32);

void func_0013D8A0(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x1F98) == 0) {
        M2C_FIELD(arg0, s32 *, 0x1F98) = arg1;
    }
}

void func_0013D8B8(s32 arg0, void *arg1) {
    func_00189B90(arg0 + 0x150, M2C_FIELD(arg1, s32 *, 0x30));
}
