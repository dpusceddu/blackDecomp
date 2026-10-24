#include "ps2/prelude.h"

#include "types_ghidra.h"
extern M2C_UNK D_003E0040;
extern s32 func_003842A0();

s32 func_00383C70(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E0040;
    M2C_FIELD(arg0, u32 *, 0) = &D_003E0040;
    if (arg1 & 1) {
        var_2 = func_003842A0();
    }
    return (s32) var_2;
}
