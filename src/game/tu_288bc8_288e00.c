#include "ps2/prelude.h"

s32 func_00288E00(s32 arg0, s32 arg1) {
    s32 *temp_2;
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x20);
    temp_2 = (temp_3 * 4) + M2C_FIELD(arg0, s32 *, 0x18);
    *temp_2 = arg1;
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (temp_3 + 1);
    return (s32) temp_2;
}
