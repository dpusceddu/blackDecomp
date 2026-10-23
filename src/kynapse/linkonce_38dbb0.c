#include "auto/prelude.h"

extern M2C_UNK D_003E0040;
extern s32 func_002E5D90();
extern s32 (*D_003C87E0)();
extern s32 D_0049B9E0;
extern s32 func_0038D760();
extern s32 func_00370168();
extern M2C_UNK D_0049B9A0;

s32 func_0038DBB0(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, M2C_UNK **, 0x28) = &D_003E0040;
    var_2 = func_002E5D90(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

s32 * func_0038DC08(void) {
    if (D_0049B9E0 == 0) {
        func_0038D760();
        func_00370168(&D_0049B9E0, "Q24Kaim14CFreeListBlock", &D_0049B9A0);
    }
    return &D_0049B9E0;
}
