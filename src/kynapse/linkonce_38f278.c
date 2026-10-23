#include "auto/prelude.h"

extern M2C_UNK D_003EBB48;
extern s32 func_00107D48();

s32 func_0038F278(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003EBB48;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EBB48;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}
