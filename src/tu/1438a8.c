#include "auto/prelude.h"

extern s32 func_00143908();

s32 func_001438A8(void) {
    return func_00143908() != 0;
}

s32 func_001438C8(s32 arg0) {
    return func_00143908(arg0, 0) != 0;
}

s32 func_001438E8(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x80);
    if (M2C_FIELD(temp_4, s32 *, 0x1C) == 9) {
        M2C_FIELD(temp_4, s32 *, 0x1C) = 0;
    }
    return 1;
}
