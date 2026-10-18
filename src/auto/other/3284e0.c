#include "auto/prelude.h"

void * func_003284E0(void *arg0, s32 arg1, s32 *arg2) {
    void *temp_3;
    void *temp_4;

    if (*arg2 != 0) {
        temp_3 = M2C_FIELD(arg0, void **, 0x30);
        M2C_FIELD(temp_3, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_3, s32 *, 0x1C) | 1);
    } else {
        temp_4 = M2C_FIELD(arg0, void **, 0x30);
        M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFFFFFFFE);
    }
    return arg0;
}
