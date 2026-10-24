#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_0010F6D8(s32 *arg0) {
    s32 *var_4;
    s32 temp_3;
    s32 var_6;
    u32 var_5;

    var_4 = arg0;
    var_6 = 0;
    var_5 = 0;
    do {
        temp_3 = *var_4;
        var_5 += 1;
        var_4 = (s32 *) (((s8 *) var_4) + 4);
        var_6 += temp_3;
    } while (var_5 < 0x1DCU);
    return var_6;
}
