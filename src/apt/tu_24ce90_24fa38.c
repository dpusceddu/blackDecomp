#include "ps2/prelude.h"

extern s32 * func_00250058();
extern u8 D_0040EB63;

s32 * func_0024FA38(void) {
    s32 *temp_3;

    temp_3 = func_00250058();
    if (D_0040EB63 == 4) {
        M2C_FIELD(temp_3, s32 *, 4) = (s32) (M2C_FIELD(temp_3, s32 *, 4) | 1);
    } else if (D_0040EB63 == 0) {
        M2C_FIELD(temp_3, s32 *, 0) |= 1;
    }
    return temp_3;
}
