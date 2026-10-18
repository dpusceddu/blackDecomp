#include "auto/prelude.h"

extern s32 func_00312C70();

void func_003153C0(M2C_UNK **arg0, M2C_UNK *arg1, s32 arg2) {
    M2C_UNK *temp_4;

    if (M2C_FIELD(arg0, s32 *, 0x58) & 1) {
        temp_4 = M2C_FIELD(arg0, M2C_UNK **, 0x38);
        if (temp_4 != NULL) {
            func_00312C70(temp_4);
        }
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & 0xFFFFFFFE);
    }
    M2C_FIELD(arg0, M2C_UNK **, 0x38) = arg1;
    M2C_FIELD(arg0, s32 *, 0x34) = arg2;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
}
