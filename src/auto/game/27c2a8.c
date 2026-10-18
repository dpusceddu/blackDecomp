#include "auto/prelude.h"

#include "types_ghidra.h"
extern M2C_UNK D_003C09F0;

s32 func_0027C2A8(s8 *arg0, s32 arg1) {
    s32 var_4;
    s32 var_5;
    s8 *var_6;
    s8 temp_2;

    var_5 = arg1;
    var_6 = arg0;
    var_4 = -1;
    if (var_5 > 0) {
        do {
            temp_2 = *var_6;
            var_6 += 1;
            var_5 -= 1;
            var_4 = (var_4 >> 8) ^ M2C_FIELD((((temp_2 ^ (var_4 & 0xFF)) * 4) + ((s32) &D_003C09F0)), s32 *, 0);
        } while (var_5 != 0);
    }
    return var_4;
}
