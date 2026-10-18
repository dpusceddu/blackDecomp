#include "auto/prelude.h"

extern s32 D_00482DA8;
extern s32 func_00367F20();

s32 func_00365D48(s32 *arg0, s32 arg1) {
    s32 temp_2;

    D_00482DA8 = 0;
    temp_2 = func_00367F20(arg1);
    if ((temp_2 == -1) && (D_00482DA8 != 0)) {
        *arg0 = D_00482DA8;
    }
    return temp_2;
}
