#include "auto/prelude.h"

extern f32 func_0034E530();

f32 func_0034E418(s32 *arg0, void *arg1, s32 *arg2) {
    f32 temp_f20;

    if (M2C_FIELD(arg1, s8 *, 1) <= 0) {
        return 1.0f;
    }
    temp_f20 = func_0034E530(arg0, M2C_FIELD(arg1, s32 **, 0x10), arg2);
    if (M2C_FIELD(arg1, s8 *, 1) >= 2) {
        func_0034E530(arg0, M2C_FIELD(arg1, s32 **, 0x14), arg2);
    }
    return temp_f20;
}
