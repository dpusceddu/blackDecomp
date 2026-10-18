#include "auto/prelude.h"

extern M2C_UNK D_003E1258;
extern s32 func_00250198();
extern s32 D_0043DEE0;
extern s32 func_00240798();
extern M2C_UNK D_003E12F8;
extern s32 func_002486D8();
extern s32 func_00107D48();

s32 func_00233C60(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 var_2;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E1258;
    if (M2C_FIELD(arg0, s32 *, 0x2C) == 1) {
        func_00250198(D_0043DEE0, M2C_FIELD(arg0, s32 *, 8), 0x3C);
    }
    func_00240798(arg0 + 0x24, 2);
    temp_4 = M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    if (temp_4 != 0) {
        func_002486D8(temp_4, 3);
    }
    var_2 = arg1 & 1;
    if (var_2 != 0) {
        var_2 = func_00107D48(arg0);
    }
    return var_2;
}
