#include "auto/prelude.h"

s32 func_003151D8(void *arg0) {
    s32 var_6;

    var_6 = (M2C_FIELD(arg0, s32 *, 4) != 0) ? 0x2C : 0x1C;
    if (M2C_FIELD(arg0, s32 *, 0x10) != 0) {
        var_6 += M2C_FIELD(arg0, s32 *, 0x14);
    }
    return var_6;
}
