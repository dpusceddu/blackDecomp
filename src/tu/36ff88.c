#include "auto/prelude.h"
#include "types_ghidra.h"

extern M2C_UNK D_0040BEA0;
extern s32 func_00107D48();
extern M2C_UNK D_0040BE88;

s32 func_0036FF88(void **arg0) {
    return *M2C_FIELD(*arg0, s32 *(**)(), 4)();
}

s32 func_0036FFB0(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_0040BEA0;
    M2C_FIELD(arg0, u32 *, 0) = &D_0040BEA0;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

M2C_UNK ** func_0036FFE0(M2C_UNK **arg0) {
    *arg0 = &D_0040BE88;
    return arg0;
}
