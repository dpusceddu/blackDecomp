#include "auto/prelude.h"

s32 func_00178FC8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4) == 3;
}

s32 func_00178FD8(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    var_4 = 0;
    if ((temp_3 == 0) || (temp_3 == 3)) {
        var_4 = 1;
    }
    return var_4;
}

s32 func_00179000(s32 *arg0) {
    return 1 << *arg0;
}

void func_00179010(void) {

}
