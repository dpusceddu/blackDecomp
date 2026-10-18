#include "auto/prelude.h"

extern s32 func_002703D0();
extern M2C_UNK D_00440280;
extern s32 (*D_003BFB2C)();

s32 func_00270188(s32 arg0, s32 arg1, s32 arg2) {
    func_002703D0(&D_00440280);
    return D_003BFB2C(arg0, arg1, arg2) != 0;
}
