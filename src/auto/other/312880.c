#include "auto/prelude.h"

extern s32 func_00312AD0();
extern M2C_UNK D_00455FD0;

s32 func_00312880(s32 arg0) {
    s32 temp_2;

    if (M2C_FIELD(arg0, s32 *, 4) != 1) {
        goto block_6;
    }
    temp_2 = func_00312AD0((s32) &D_00455FD0, M2C_FIELD(arg0, s32 *, 0));
    if (temp_2 == 0) {
        goto block_3;
    }
    M2C_FIELD(arg0, s32 *, 0) = temp_2;
    goto block_5;
block_3:
    return 0;
block_5:
    M2C_FIELD(arg0, s32 *, 4) = 0;
block_6:
    return arg0;
}
