#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00179258();
extern s32 D_0040F4D4;
extern s32 func_00178F18();
extern s32 func_00176310();

s32 func_001893B8(s32 arg0, s32 arg1) {
    s32 temp_21;
    s32 temp_2;
    s32 temp_5;
    s32 var_17;
    s32 var_20;

    var_20 = 0;
    if (arg1 != 0) {
        var_17 = arg0;
        temp_21 = var_17 + 0x120;
        do {
            temp_5 = M2C_FIELD(var_17, s32 *, 0);
            if (temp_5 != -1) {
                temp_2 = func_00179258(D_0040F4D4 + 0xFA8, temp_5);
                if ((func_00178F18(temp_2) != 0) && (func_00176310(D_0040F4D4 + 0xFA0, M2C_FIELD(temp_2, s32 *, 8), arg1) != 0)) {
                    var_20 = (var_20 + 1) & 0xFF;
                }
            }
            var_17 += 0x60;
        } while (var_17 < temp_21);
    }
    return var_20;
}
