#include "auto/prelude.h"

void func_002740D8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

s32 func_002740E8(s32 arg0, s32 arg1) {
    M2C_UNK *temp_2;
    M2C_UNK *temp_2_2;
    M2C_UNK *temp_3;
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0);
    temp_3 = M2C_FIELD(temp_5, M2C_UNK **, 0x10);
    if (temp_3 == NULL) {
        goto block_2;
    }
    goto block_4;
block_2:
    return 0;
block_4:
    M2C_FIELD(temp_5, M2C_UNK **, 0x10) = (M2C_UNK *) *temp_3;
    temp_2 = *temp_3;
    if (temp_2 == NULL) {
        goto block_6;
    }
    M2C_FIELD(temp_2, s32 *, 4) = 0;
block_6:
    temp_2_2 = M2C_FIELD(arg0, M2C_UNK **, 4);
    if (temp_2_2 == NULL) {
        goto block_8;
    }
    *temp_3 = temp_2_2;
    goto block_10;
block_8:
    *temp_3 = NULL;
    goto block_11;
block_10:
    M2C_FIELD(temp_2_2, M2C_UNK **, 4) = temp_3;
block_11:
    M2C_FIELD(arg0, M2C_UNK **, 4) = temp_3;
    return (s32) temp_3;
}
