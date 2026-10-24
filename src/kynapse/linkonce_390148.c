#include "ps2/prelude.h"

extern u8 D_003EC8F8;
extern s32 D_00451770;
extern M2C_UNK D_003EC4F0;
extern s32 func_0035E690(M2C_UNK *);
extern M2C_UNK func_002F23E8;

M2C_UNK * func_00390148(M2C_UNK *arg0) {
    if (D_003EC8F8 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003EC8F8 = 0;
    return arg0;
}

M2C_UNK * func_00390168(void) {
    if (D_00451770 == 0) {
        func_00390148(&D_003EC4F0);
        D_00451770 = 1;
        func_0035E690(&func_002F23E8);
    }
    return &D_003EC4F0;
}
