#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0018C0C0(s32 *, void *, s32);

s32 func_00181B08(void *arg0, s32 *arg1) {
    s32 *var_3;
    s32 temp_6;
    s32 var_2;
    s32 var_5;

    temp_6 = M2C_FIELD(arg0, s32 *, 0x710);
    var_5 = 0;
    if (temp_6 > 0) {
        var_3 = (s32 *) (((s8 *) arg0) + 0x4C4);
loop_2:
        var_2 = *var_3;
        if (*arg1 != var_2) {
            var_5 += 1;
            var_3 = (s32 *) (((s8 *) var_3) + 0x1C);
            if (var_5 >= temp_6) {
                goto block_4;
            }
            goto loop_2;
        }
    } else {
block_4:
        var_2 = func_0018C0C0(arg1, (void *) (((s8 *) arg0) + ((M2C_FIELD(arg0, s32 *, 0x710) * 0x1C) + 0x4C4)), temp_6);
        if (var_2 != 0) {
            var_2 = M2C_FIELD(arg0, s32 *, 0x710) + 1;
            M2C_FIELD(arg0, s32 *, 0x710) = var_2;
        }
    }
    return var_2;
}
