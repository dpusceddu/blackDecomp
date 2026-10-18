#include "auto/prelude.h"

void func_00366510(void *arg0, void *arg1) {
    s32 temp_4;

    if (arg1 != NULL) {
        temp_4 = M2C_FIELD(arg1, s32 *, 4) * 4;
        M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD((temp_4 + M2C_FIELD(arg0, s32 *, 0x4C)), s32 *, 0);
        M2C_FIELD((temp_4 + M2C_FIELD(arg0, s32 *, 0x4C)), u32 *, 0) = arg1;
    }
}
