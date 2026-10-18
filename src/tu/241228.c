#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_00241128();
extern s32 func_00241AD8();
extern s32 func_002405E8();

s32 func_00241228(s32 arg0) {
    s32 temp_4;
    s32 var_v0;

    var_v0 = func_00241128(arg0, 0);
    temp_4 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_4 != 0) {
        var_v0 = func_00241AD8(temp_4, 3);
    }
    M2C_FIELD(arg0, s32 *, 0) = 0;
    return var_v0;
}

s32 func_00241268(s32 *arg0) {
    return *arg0;
}

s32 func_00241270(s32 arg0, s32 arg1, s32 arg2) {
    return func_002405E8(arg0, arg2);
}
