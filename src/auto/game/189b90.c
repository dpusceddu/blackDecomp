#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_0018A2C8();
extern s32 func_00181AD0();

s32 func_00189B90(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_3;
    s32 var_5;

    var_5 = arg0;
    temp_3 = var_5 + 0x120;
loop_1:
    if (M2C_FIELD(var_5, s32 *, 0) != arg1) {
        var_5 += 0x60;
        temp_2 = var_5 < temp_3;
        if (temp_2 == 0) {
            return temp_2;
        }
        goto loop_1;
    }
    func_0018A2C8(arg0, var_5);
    return func_00181AD0(M2C_FIELD(arg0, s32 *, 0x130) + 0xEC0, 3);
}
