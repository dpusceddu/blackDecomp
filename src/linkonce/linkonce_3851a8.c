#include "ps2/prelude.h"

extern M2C_UNK D_003E2120;
extern s32 func_00387020();
extern s32 func_00250198(s32, void *, s32);
extern s32 D_0043DEE0;

s32 func_003851A8(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E2120;
    var_2 = func_00387020(arg0, 0);
    if (arg1 & 1) {
        var_2 = func_00385200(arg0, 0xC);
    }
    return var_2;
}

void func_00385200(void *arg0, s32 arg1) {
    func_00250198(D_0043DEE0, arg0, arg1);
}
