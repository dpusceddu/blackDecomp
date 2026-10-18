#include "auto/prelude.h"

extern s32 (*D_00451280)();

void func_00373348(s32 arg0, void *arg1) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg1, s32 *, 8);
    if (temp_4 != 0) {
        D_00451280(temp_4);
    }
}
