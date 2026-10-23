#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00149120(s32 *arg0, s32 arg1) {
    s32 var_3;
    s32 var_5;

    var_5 = arg1;
    var_3 = 0;
    if (var_5 != -1) {
        do {
            var_5 = M2C_FIELD(((var_5 * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x118), s32 *, 0x58)), s32 *, 0);
            var_3 += 1;
        } while (var_5 != -1);
    }
    return var_3;
}
