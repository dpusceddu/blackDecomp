#include "ps2/prelude.h"

extern s32 D_00414D54;
extern s32 func_001AAF10();
extern s32 func_00137AE0();
extern M2C_UNK D_003F6A88;
extern M2C_UNK D_0040D9C8;

void func_001A8E30(s8 *arg0, s32 arg1, s32 arg2) {
    s32 var_3;
    s8 temp_3;

    temp_3 = *arg0;
    if (temp_3 == -1) {
        var_3 = 0;
    } else {
        var_3 = M2C_FIELD(((temp_3 * 4) + D_00414D54), s32 *, 0);
    }
    if (var_3 == 0xA) {
        func_001AAF10(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), &D_003F6A88, &D_0040D9C8, arg2);
        return;
    }
    func_001AAF10(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), "U_SHO", &D_003F6A88, arg2);
}
