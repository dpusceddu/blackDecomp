#include "auto/prelude.h"

extern u8 D_003EA770;
extern s32 D_004513D4;
extern M2C_UNK D_003EA368;
extern s32 func_0035E690(M2C_UNK *);
extern M2C_UNK func_002E7490;

M2C_UNK * func_0038E090(M2C_UNK *arg0) {
    if (D_003EA770 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003EA770 = 0;
    return arg0;
}

M2C_UNK * func_0038E0B0(void) {
    if (D_004513D4 == 0) {
        func_0038E090(&D_003EA368);
        D_004513D4 = 1;
        func_0035E690(&func_002E7490);
    }
    return &D_003EA368;
}
