#include "auto/prelude.h"

extern M2C_UNK D_003E23C8;
extern s32 func_00107D48();

s32 func_00387020(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E23C8;
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E23C8;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}
