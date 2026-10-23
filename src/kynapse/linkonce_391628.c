#include "auto/prelude.h"

s32 func_00391628(s32 arg0, s32 arg1) {
    s32 *temp_2;

    if ((u32) arg1 >= (u32) M2C_FIELD(arg0, u32 *, 0x28)) {
        goto block_2;
    }
    goto block_4;
block_2:
    return 0;
block_4:
    temp_2 = (arg1 * 8) + M2C_FIELD(arg0, s32 *, 0x34);
    return (s32) ((~*temp_2 == 0) ? NULL : temp_2);
}
