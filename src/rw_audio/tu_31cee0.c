#include "include_asm.h"
#include "ps2/prelude.h"

void * func_0031CEE0(void *arg0, void *arg1) {
    u32 temp_3;
    u32 temp_6;

    temp_6 = M2C_FIELD(arg1, u32 *, 0);
    if (temp_6 != M2C_FIELD(arg0, u32 *, 0x84)) {
        M2C_FIELD(arg1, s32 *, 8) = 0;
        temp_3 = M2C_FIELD(arg0, u32 *, 0x84);
        if (temp_6 < temp_3) {
            M2C_FIELD(arg1, u32 *, 0) = temp_3;
        }
    }
    return arg0;
}
