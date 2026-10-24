#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_0028C4F8(s32 arg0, s32 arg1) {
    s32 var_2;
    s32 var_4;

    var_4 = arg0;
    var_2 = -1;
    if (var_4 != 0) {
        do {
            var_4 = (s32) ((u32) var_4 >> 1);
            var_2 += 1;
        } while (var_4 != 0);
    }
    return var_2;
}
