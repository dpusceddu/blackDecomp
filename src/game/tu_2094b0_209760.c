#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0027C278(s32);

s32 func_00209760(void *arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_4;
    s32 var_3;
    void *var_16;

    var_16 = arg0;
    temp_4 = func_0027C278(arg1);
    var_3 = 0;
loop_1:
    temp_2 = M2C_FIELD(var_16, s32 *, 0);
    if (temp_2 != temp_4) {
        var_3 += 1;
        temp_2_2 = var_3 < 0x6E;
        var_16 = (void *) (((s8 *) var_16) + 8);
        if (temp_2_2 == 0) {
            return temp_2_2;
        }
        goto loop_1;
    }
    M2C_FIELD(var_16, s32 *, 4) = 0;
    M2C_FIELD(var_16, s32 *, 0) = 0;
    return temp_2;
}
