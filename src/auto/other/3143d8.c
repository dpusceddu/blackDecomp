#include "auto/prelude.h"

void func_003143D8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_17;
    s32 temp_4;
    void *var_16;

    temp_17 = arg0 + 0xC;
    var_16 = M2C_FIELD(arg0, void **, 0x10);
    if (var_16 != temp_17) {
loop_1:
        temp_4 = M2C_FIELD(var_16, s32 *, 8);
        var_16 = M2C_FIELD(var_16, void **, 4);
        if (((s32 (*)(s32, s32)) arg1)(temp_4, arg2) != 0) {
            if (var_16 != temp_17) {
                goto loop_1;
            }
        }
    }
}
