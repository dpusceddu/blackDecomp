#include "ps2/prelude.h"

extern M2C_UNK D_003EA790;
extern s32 func_00107D48();

s32 func_0038E5C8(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003EA790;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EA790;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}
