#include "auto/prelude.h"

#include "types_ghidra.h"

s32 func_00293350(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_4;
    s32 var_8;
    u32 temp_3;
    u32 temp_4_2;
    u32 var_10;
    u32 var_9;
    void *var_2;

    var_8 = arg0;
    var_2 = M2C_FIELD(var_8, u32 *, 0);
    var_9 = M2C_FIELD(arg2, u32 *, 0);
    var_10 = M2C_FIELD(arg3, u32 *, 0);
    if (var_2 != NULL) {
        do {
            if ((M2C_FIELD(var_8, s32 *, 4) != 0) && (M2C_FIELD(var_8, u32 *, 8) != 0)) {
                temp_4 = M2C_FIELD(arg1, s32 *, 4);
                M2C_FIELD(((temp_4 * 4) + M2C_FIELD(arg1, s32 *, 0)), s32 *, 0) = var_8;
                M2C_FIELD(arg1, s32 *, 4) = (s32) (temp_4 + 1);
                temp_3 = M2C_FIELD(var_8, u32 *, 8);
                temp_4_2 = temp_3 + M2C_FIELD(var_8, s32 *, 0xC);
                var_9 = (temp_3 < var_9) ? temp_3 : var_9;
                var_10 = (var_10 < temp_4_2) ? temp_4_2 : var_10;
            }
            var_2 = var_8 + M2C_FIELD(var_8, s32 *, 0);
            var_8 = (s32) (var_2 + 4);
        } while (M2C_FIELD(var_2, s32 *, 4) != 0);
    }
    M2C_FIELD(arg2, u32 *, 0) = var_9;
    M2C_FIELD(arg3, u32 *, 0) = var_10;
    return (s32) var_2;
}
