#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_001B0F50(s32 arg0, s32 arg1) {
    s32 *temp_2;
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x40);
    temp_2 = arg0 + (temp_3 * 4);
    *temp_2 = arg1;
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (temp_3 + 1);
    return (s32) temp_2;
}
