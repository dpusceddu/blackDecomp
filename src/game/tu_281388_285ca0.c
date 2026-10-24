#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00285CA0(void *arg0, s32 arg1) {
    s32 var_2;
    s32 var_5;

    var_5 = arg1;
    var_2 = 0;
    if (var_5 > 0) {
        do {
            var_5 -= 1;
            var_2 = (var_2 * 2) | 1;
        } while (var_5 != 0);
    }
    return var_2;
}
