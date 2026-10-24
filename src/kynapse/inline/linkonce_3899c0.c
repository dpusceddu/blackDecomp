#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_003E3D38;
extern s32 func_00107D48();

s32 func_003899C0(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E3D38;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E3D38;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}
