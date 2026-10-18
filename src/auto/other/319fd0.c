#include "auto/prelude.h"

extern s32 func_00310768();
extern s32 func_00317340();

s32 func_00319FD0(s32 arg0) {
    M2C_UNK var_17;
    s32 temp_4;
    void *temp_16;

    temp_16 = arg0 + 0x28;
    if (M2C_FIELD(temp_16, u8 *, 0x62) & 2) {
        temp_4 = M2C_FIELD(temp_16, s32 *, 0x38);
        var_17 = 2;
        if (temp_4 != 0) {
            var_17 = (func_00310768(temp_4, 8, 2, 0) == 0) ? 1 : 2;
        }
        func_00317340(temp_16, var_17);
    }
    M2C_FIELD(temp_16, u8 *, 0x62) = (u8) (M2C_FIELD(temp_16, u8 *, 0x62) & 0xDF);
    return arg0;
}
