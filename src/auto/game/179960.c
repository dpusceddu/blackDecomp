#include "auto/prelude.h"

extern s32 func_00177A98();
extern s32 func_00177AD0();

void func_00179960(void *arg0, s32 arg1) {
    s32 var_17;
    s32 var_18;

    var_18 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x28) > 0) {
        var_17 = 0;
        do {
            if (func_00177A98(M2C_FIELD(arg0, s32 *, 0x2C) + var_17) == arg1) {
                func_00177AD0(M2C_FIELD(arg0, s32 *, 0x2C) + var_17);
            }
            var_18 += 1;
            var_17 += 0x50;
        } while (var_18 < M2C_FIELD(arg0, s32 *, 0x28));
    }
}
