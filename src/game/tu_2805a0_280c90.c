#include "ps2/prelude.h"

#include "types_ghidra.h"

s32 func_00280C90(s32 arg0, s32 arg1) {
    s32 var_2;
    s32 var_6;
    s32 var_7;

    var_2 = M2C_FIELD(arg0, s32 *, 0x240);
    var_7 = 0;
    if (var_2 > 0) {
        var_6 = arg0;
        do {
            var_7 += 1;
            M2C_FIELD(M2C_FIELD(var_6, u32 *, 0), s8 *, 0x35) = (s8) arg1;
            var_2 = var_7 < M2C_FIELD(arg0, s32 *, 0x240);
            var_6 += 0xC;
        } while (var_2 != 0);
    }
    return var_2;
}
