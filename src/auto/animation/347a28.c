#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00347A28(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s128 arg4, s128 arg5) {
    s32 *var_4;
    s32 var_2;

    var_4 = (s32 *) (((s8 *) arg0) + 0x80);
    var_2 = 3;
    do {
        *var_4 = 0;
        var_2 -= 1;
        var_4 = (s32 *) (((s8 *) var_4) + -4);
    } while (var_2 >= 0);
    return var_2;
}
