#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_003111A8();
extern s32 func_00317C20();
extern s32 func_00318950();
extern s32 func_00312C70();

s32 func_0031E320(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 temp_17;
    s32 temp_3;
    s32 temp_4;
    s32 temp_5;
    s32 var_16;
    s32 var_2;

    var_16 = arg0;
    temp_5 = M2C_FIELD(var_16, s32 *, 0x1C);
    var_2 = temp_5 & 8;
    temp_17 = M2C_FIELD(var_16, s32 *, 0);
    if (var_2 != 0) {
        var_16 = M2C_FIELD(var_16, s32 *, -4);
    } else {
        var_2 = temp_5 & 0x10;
        if (var_2 != 0) {
            var_2 = var_16 + func_003111A8(temp_17, temp_5 & 7, (s32) sp);
            var_16 = M2C_FIELD(var_2, s32 *, 0);
        }
    }
    temp_3 = M2C_FIELD(temp_17, s32 *, 0x48);
    if ((temp_3 != 0) && ((arg1 == 0) || (var_2 = M2C_FIELD(arg0, s32 *, 0x1C) & 0x20, (var_2 == 0)))) {
        temp_4 = M2C_FIELD(temp_17, s32 *, 0xC);
        if (temp_4 & 0x40) {
            return func_00317C20(temp_3, var_16);
        }
        if (temp_4 & 0x80) {
            return func_00318950(temp_3, var_16);
        }
        return func_00312C70(var_16);
    }
    if (arg1 != 0) {
        var_2 = ((s32 (*)(s32, s32)) arg1)(var_16, arg2);
    }
    return var_2;
}
