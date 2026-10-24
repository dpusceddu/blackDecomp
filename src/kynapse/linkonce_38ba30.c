#include "ps2/prelude.h"

extern s32 D_00451210;
extern s32 func_0038BA10();
extern M2C_UNK D_003E7148;
extern s32 func_0035E690();
extern M2C_UNK func_002E0130;

void * func_0038BA30(void) {
    if (D_00451210 == 0) {
        func_0038BA10(&D_003E7148);
        D_00451210 = 1;
        func_0035E690(&func_002E0130);
    }
    return &D_003E7148;
}
