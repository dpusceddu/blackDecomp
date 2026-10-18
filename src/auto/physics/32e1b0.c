#include "auto/prelude.h"

s32 func_0032E1B0(void *arg0, u32 *arg1) {
    s32 var_8;
    u32 temp_6;

    var_8 = 0;
    if (arg1 != NULL) {
        temp_6 = *arg1;
        if ((temp_6 < (u32) M2C_FIELD(arg0, u32 *, 0x28)) && (M2C_FIELD(((temp_6 * 4) + M2C_FIELD(arg0, s32 *, 0x44)), s32 *, 0) == arg1)) {
            var_8 = ((u32) M2C_FIELD((((temp_6 >> 5) * 4) + M2C_FIELD(arg0, s32 *, 0x60)), u32 *, 0) >> (temp_6 & 0x1F)) & 1;
        }
    }
    return var_8;
}
