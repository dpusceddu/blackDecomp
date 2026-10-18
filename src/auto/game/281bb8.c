#include "auto/prelude.h"

#include "types_ghidra.h"

s32 func_00281BB8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 var_3;
    s32 var_5;
    s32 var_7;

    var_5 = arg1;
    M2C_FIELD(arg0, s32 *, 0xC0) = arg2;
    var_7 = 0;
    if (arg2 > 0) {
        var_3 = arg0;
        do {
            temp_2 = M2C_FIELD(var_5, s32 *, 0);
            var_7 += 1;
            M2C_FIELD(var_3, s32 *, 4) = 0;
            var_5 += 4;
            M2C_FIELD(var_3, s32 *, 0) = temp_2;
            var_3 += 0xC;
        } while (var_7 < M2C_FIELD(arg0, s32 *, 0xC0));
    }
    return 1;
}
