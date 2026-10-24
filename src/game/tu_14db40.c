#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_0014DB40(void *arg0) {
    s32 var_5;
    s32 var_6;
    void *temp_3;

    var_6 = 0;
    if (M2C_FIELD(arg0, s32 *, 4) > 0) {
        var_5 = 0;
        do {
            var_6 += 1;
            M2C_FIELD((var_5 + M2C_FIELD(arg0, s32 *, 0)), s8 *, 0x1D0) = 0;
            temp_3 = var_5 + M2C_FIELD(arg0, s32 *, 0);
            M2C_FIELD(temp_3, s8 *, 0x13D) = 0;
            M2C_FIELD(temp_3, s32 *, 0x120) = 0;
            M2C_FIELD(temp_3, s32 *, 0x11C) = 0;
            var_5 += 0x1E0;
        } while (var_6 < M2C_FIELD(arg0, s32 *, 4));
    }
    return 1;
}
