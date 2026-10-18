#include "auto/prelude.h"

extern s32 func_00282170();

s32 func_00282100(void *arg0) {
    s32 temp_16;

    temp_16 = M2C_FIELD(arg0, s32 *, 0x54);
    if (temp_16 != 1) {
        if (temp_16 < 2) {
            if (temp_16 != 0) {
                return 0;
            }
            goto block_7;
        }
        if (temp_16 != 2) {
            return 0;
        }
        goto block_7;
    }
    func_00282170(arg0);
    M2C_FIELD(arg0, s32 *, 0x54) = temp_16;
block_7:
    return 1;
}
