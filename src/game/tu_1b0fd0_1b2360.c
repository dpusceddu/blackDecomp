#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_001B2E08();

s32 func_001B2360(s32 arg0, s32 arg1) {
    s32 var_2;
    u8 temp_6;

    var_2 = M2C_FIELD(arg1, s32 *, 0x28) & 0x40000000;
    if (var_2 == 0) {
        temp_6 = (u8) M2C_FIELD(arg1, s32 *, 0x28);
        var_2 = M2C_FIELD(arg0, s32 *, 0x873F0);
        if (temp_6 != M2C_FIELD(var_2, u16 *, 0x3A)) {
            var_2 = func_001B2E08(arg0 + 0x33C40, arg1, (s32) M2C_FIELD((M2C_FIELD(var_2, s32 *, 0x1C) + temp_6), u8 *, 0));
        }
    }
    return var_2;
}

s32 func_001B23C0(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 var_6;
    void *temp_2;
    void *var_3;

    temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x873F0), void **, 8);
    temp_4 = M2C_FIELD(temp_2, s32 *, 8);
    var_6 = 0;
    if (temp_4 <= 0) {
        goto block_5;
    }
    var_3 = M2C_FIELD(temp_2, void **, 0xC);
loop_2:
    var_6 += 1;
    if (M2C_FIELD(var_3, s64 *, 0) != arg1) {
        goto block_4;
    }
    return M2C_FIELD(var_3, s32 *, 8);
block_4:
    var_3 += 0x10;
    if (var_6 < temp_4) {
        goto loop_2;
    }
block_5:
    return 0;
}
