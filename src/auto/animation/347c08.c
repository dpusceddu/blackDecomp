#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00350570();

s32 func_00347C08(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_7;

    var_7 = 0;
    if (arg1 != -1) {
        func_00350570(arg0, arg1, arg2);
        var_7 = 1;
        M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFDFFFFF);
    }
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xEDFFFFFE);
    return var_7;
}
