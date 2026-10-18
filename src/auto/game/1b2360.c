#include "auto/prelude.h"

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
