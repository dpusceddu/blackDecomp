#include "auto/prelude.h"

s32 func_002F4330(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s8 *temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 8) + ((arg1 * M2C_FIELD(arg0, s32 *, 0xC)) + arg2);
    *temp_2 = (s8) arg3;
    return (s32) temp_2;
}
