#include "auto/prelude.h"

extern s32 func_00118810();

s32 func_00117800(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s8 *, 0xA0) = 1;
    return func_00118810(arg0 + 4);
}
