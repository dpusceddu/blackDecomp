#include "auto/prelude.h"

void func_003298D8(void *arg0, s32 *arg1, s32 arg2, u32 arg3, s32 arg4, s32 *arg5) {
    u32 temp_3;
    u8 temp_10;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x14);
    temp_10 = M2C_FIELD(arg0, u8 *, 8);
    *arg5 = ((*arg1 & ((1 << temp_10) - 1)) + ((u32) ((arg2 - arg4) + temp_3) / temp_3)) | ((arg3 / temp_3) << temp_10);
}
