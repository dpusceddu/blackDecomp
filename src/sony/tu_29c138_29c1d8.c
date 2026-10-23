#include "auto/prelude.h"

#include "types_ghidra.h"
extern void * D_003C1588;

void func_0029C1D8(s8 *arg0, s32 arg1) {
    s32 var_2;
    s8 *var_4;

    var_4 = arg0;
    var_2 = arg1 - 1;
    if (arg1 != 0) {
        do {
            *var_4 = 0;
            var_2 -= 1;
            var_4 += 1;
        } while (var_2 != -1);
    }
}

void * func_0029C210(u32 arg0) {
    if (arg0 < 0xAU) {
        return (&D_003C1588)[arg0];
    }
    return NULL;
}
