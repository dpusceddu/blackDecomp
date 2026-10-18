#include "auto/prelude.h"

extern M2C_UNK D_003E2098;
extern s32 func_00387020();
extern s32 func_00385298();

s32 func_00385240(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E2098;
    var_2 = func_00387020(arg0, 0);
    if (arg1 & 1) {
        var_2 = func_00385298(arg0, 0xC);
    }
    return var_2;
}
