#include "ps2/prelude.h"

extern s32 D_00452150;
extern s32 func_00390BA8();
extern M2C_UNK D_003ED620;
extern s32 func_0035E690();
extern M2C_UNK func_002F3398;

M2C_UNK * func_00390BC8(void) {
    if (D_00452150 == 0) {
        func_00390BA8(&D_003ED620);
        D_00452150 = 1;
        func_0035E690(&func_002F3398);
    }
    return &D_003ED620;
}
