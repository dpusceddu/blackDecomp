#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_004512A0;
extern M2C_UNK * func_0038CF00(M2C_UNK *arg0);
extern M2C_UNK D_0049B0E0;
extern s32 func_0035E690(M2C_UNK *);
extern M2C_UNK func_002E4E18;

M2C_UNK * func_0038CC20(void) {
    if (D_004512A0 == 0) {
        func_0038CF00(&D_0049B0E0);
        D_004512A0 = 1;
        func_0035E690(&func_002E4E18);
    }
    return &D_0049B0E0;
}
