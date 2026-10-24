#include "ps2/prelude.h"

extern s32 func_00280528();
extern s32 func_003178B8(M2C_UNK);
extern s32 func_00280628();
extern s32 func_003110B0(s32, M2C_UNK, M2C_UNK);

s32 func_00282EF8(void *arg0) {
    func_00280528();
    if (M2C_FIELD(arg0, s32 *, 8) == 1) {
        func_003178B8(2);
    } else {
        func_003178B8(3);
    }
    return 1;
}

void func_00282F48(void *arg0) {
    func_00280628();
    func_003110B0(M2C_FIELD(arg0, s32 *, 0x14), 0, 0);
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
}
