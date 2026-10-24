#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_001EAB60(void *arg0) {
    s32 *var_3;
    s32 temp_2;
    s32 var_5;
    s32 var_6;

    var_6 = 0;
    var_3 = (s32 *) (((s8 *) arg0) + 4);
    var_5 = 7;
    do {
        temp_2 = *var_3 - 1;
        *var_3 = temp_2;
        if (temp_2 > 0) {
            var_6 += 1;
        } else {
            *var_3 = 0;
        }
        var_5 -= 1;
        var_3 = (s32 *) (((s8 *) var_3) + 8);
    } while (var_5 >= 0);
    M2C_FIELD(arg0, s32 *, 0x44) = var_6;
    return temp_2;
}
