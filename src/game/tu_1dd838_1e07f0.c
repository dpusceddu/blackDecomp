#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_001E07F0(void *arg0, s32 *arg1) {
    s32 *var_4;
    s32 var_3;

    var_4 = (s32 *) (((s8 *) arg0) + 0x30);
    var_3 = 0;
loop_1:
    if (*var_4 != arg1) {
        var_3 += 1;
        var_4 = (s32 *) (((s8 *) var_4) + 4);
        if (var_3 >= 8) {
            return -1;
        }
        goto loop_1;
    }
    return var_3;
}
