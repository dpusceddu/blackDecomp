#include "auto/prelude.h"

extern s32 func_002867F0();

s32 func_00286558(s32 arg0) {
    s32 temp_3;
    s32 var_2;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x2870);
    var_2 = temp_3 < 2;
    if (temp_3 >= 0) {
        if (var_2 == 0) {
            var_2 = temp_3 < 4;
            if (var_2 != 0) {
                var_2 = func_002867F0(arg0, 0);
            }
        }
    }
    return var_2;
}
