#include "auto/prelude.h"

extern s32 func_0025C4C8();
extern s32 func_00136F10();
extern s32 func_0025C798();

s32 func_0025C2C8(s32 arg0, s32 arg1) {
    s32 temp_5;
    s32 temp_v0;

    temp_5 = M2C_FIELD(arg1, s32 *, 0x350);
    if (temp_5 != 0) {
        func_0025C4C8(arg0, temp_5);
    }
    func_00136F10(arg1, 1);
    temp_v0 = func_0025C798(arg0, M2C_FIELD(arg1, s32 *, 0xB4));
    M2C_FIELD(arg1, s32 *, 0xB4) = 0;
    return temp_v0;
}
