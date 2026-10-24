#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 * func_001EAAF8(s32 *);

s32 func_001EA780(s32 arg0) {
    s32 temp_17;
    s32 temp_2;
    s32 var_16;

    var_16 = arg0;
    temp_17 = var_16 + 0x260;
    do {
        func_001EAAF8((s32 *) var_16);
        var_16 += 0x4C;
        temp_2 = var_16 < temp_17;
    } while (temp_2 != 0);
    return temp_2;
}
