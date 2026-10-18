#include "auto/prelude.h"

extern s32 D_0049A9C8;
extern s32 func_00389908();
extern s32 func_00370168();
extern M2C_UNK D_0049A9D8;
extern M2C_UNK D_003E3D10;

s32 func_00389828(s32 arg0) {
    return arg0 + 0x10;
}

s32 func_00389830(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x28);
}

u8 func_00389838(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x2C);
}

s32 * func_00389840(void) {
    if (D_0049A9C8 == 0) {
        func_00389908();
        func_00370168(&D_0049A9C8, "Q24Kaim19CActionAcceleration", &D_0049A9D8);
    }
    return &D_0049A9C8;
}

void * func_00389890(void *arg0) {
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E3D10;
    return arg0;
}
