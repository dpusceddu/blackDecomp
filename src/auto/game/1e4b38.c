#include "auto/prelude.h"

s32 func_001E4B38(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    var_4 = 0;
    if ((temp_3 == 1) || (temp_3 == 3) || (temp_3 == 2) || (temp_3 == 4)) {
        var_4 = 1;
    }
    return var_4;
}
