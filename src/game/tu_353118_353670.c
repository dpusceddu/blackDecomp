#include "ps2/prelude.h"

extern s32 func_00353610();

s32 func_00353670(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (arg1 | arg2);
    M2C_FIELD(arg0, s32 *, 0) = 0;
    func_00353610(arg0, 0);
    return arg0;
}
