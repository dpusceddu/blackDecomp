#include "auto/prelude.h"

extern s32 func_0015A938(void *arg0);

s32 func_00158078(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xD8) == 4;
}

s32 func_00158088(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xD8) == 1;
}

s32 func_00158098(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 0xD8);
    var_4 = 0;
    if ((temp_3 == 1) || (temp_3 == 8)) {
        var_4 = 1;
    }
    return var_4;
}

void func_001580C0(void *arg0) {
    func_0015A938(M2C_FIELD(arg0, void **, 0xF4));
}

s16 func_001580E0(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0xF4), s16 *, 0x18);
}
