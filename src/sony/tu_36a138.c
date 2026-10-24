#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_0036A138(s32 arg0, s32 arg1) {
    s32 *temp_2;

    temp_2 = (M2C_FIELD(arg0, s32 *, 0x10) * 4) + M2C_FIELD(arg1, s32 *, 0x1C);
    *temp_2 = M2C_FIELD(arg0, s32 *, 0x14);
    return (s32) temp_2;
}
