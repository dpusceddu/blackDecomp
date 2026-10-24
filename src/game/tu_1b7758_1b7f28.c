#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_001B7F28(void *arg0) {
    s32 *var_4;
    s32 var_2;

    var_4 = (s32 *) (((s8 *) arg0) + 0x188);
    var_2 = 7;
    do {
        *var_4 = 0;
        var_2 -= 1;
        var_4 = (s32 *) (((s8 *) var_4) + -0x38);
    } while (var_2 >= 0);
    return var_2;
}
