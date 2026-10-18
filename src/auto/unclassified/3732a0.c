#include "auto/prelude.h"

extern s32 func_002E3918();
extern s32 (*D_0045127C)();
extern M2C_UNK D_0040C418;

s32 func_003732A0(s32 arg0, void *arg1) {
    s32 temp_2;
    s32 temp_2_2;

    temp_2 = func_002E3918(arg1);
    if (temp_2 != 0) {
        temp_2_2 = D_0045127C(temp_2, &D_0040C418);
        if (temp_2_2 != 0) {
            M2C_FIELD(arg1, s32 *, 8) = temp_2_2;
            return 1;
        }
    }
    M2C_FIELD(arg1, s32 *, 8) = 0;
    return 0;
}
