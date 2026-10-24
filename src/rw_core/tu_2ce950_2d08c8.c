#include "ps2/prelude.h"

#include "types_ghidra.h"
extern M2C_UNK D_0040A991;

s32 func_002D08C8(void *arg0) {
    s32 var_5;
    s8 temp_3;

    var_5 = 0;
    if ((arg0 != NULL) && ((temp_3 = M2C_FIELD(arg0, s8 *, 0), (temp_3 == 0x5C)) || ((M2C_FIELD((temp_3 + ((s32) &D_0040A991)), u8 *, 0) & 3) && (M2C_FIELD(arg0, s8 *, 1) == 0x3A)))) {
        var_5 = 1;
    }
    return var_5;
}
