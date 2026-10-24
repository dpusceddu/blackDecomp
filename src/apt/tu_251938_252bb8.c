#include "ps2/prelude.h"

extern u16 * func_00250058();
extern void * D_0043DEE0;
extern u16 D_003BFAF8;

u16 ** func_00252BB8(u16 **arg0, s32 arg1) {
    s32 temp_16;
    u16 *temp_2;

    if (arg1 != 0) {
        temp_16 = (arg1 + 0xC) & 0xFFFFFFFC;
        temp_2 = func_00250058(D_0043DEE0, temp_16);
        *arg0 = temp_2;
        *temp_2 = 1;
        M2C_FIELD(*arg0, s16 *, 4) = (s16) (temp_16 - 9);
        M2C_FIELD(*arg0, s16 *, 2) = 0;
        M2C_FIELD(*arg0, s16 *, 6) = 0;
        M2C_FIELD(*arg0, s8 *, 8) = 0;
    } else {
        *arg0 = &D_003BFAF8;
        D_003BFAF8 += 1;
    }
    return arg0;
}
