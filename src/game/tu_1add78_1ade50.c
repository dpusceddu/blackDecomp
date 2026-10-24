#include "ps2/prelude.h"

s32 func_001ADE50(void *arg0, s32 arg1, s32 arg2) {
    s32 *temp_7;
    s32 temp_2;
    s32 temp_5;

    temp_5 = arg1 * 4;
    temp_7 = temp_5 + M2C_FIELD(arg0, s32 *, 4);
    temp_2 = (*temp_7 + 0xF) & 0xFFFFFFF0;
    *temp_7 = temp_2 + arg2;
    return ((u32) (M2C_FIELD((temp_5 + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0) + M2C_FIELD(arg0, s32 *, 0xC)) < (u32) M2C_FIELD((temp_5 + M2C_FIELD(arg0, s32 *, 4)), u32 *, 0)) ? 0 : temp_2;
}
