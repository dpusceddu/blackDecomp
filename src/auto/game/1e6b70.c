#include "auto/prelude.h"

s32 func_001E6B70(s32 arg0, void *arg1) {
    s32 var_2;

    var_2 = 0;
    if (arg1 != NULL) {
        var_2 = M2C_FIELD(arg1, s32 *, 0x348) != 0;
    }
    return var_2;
}
