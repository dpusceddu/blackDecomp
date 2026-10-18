#include "auto/prelude.h"

extern M2C_UNK D_003E3428;
extern s32 (*D_003C87E0)();
extern s32 func_002DFF98();

s32 func_002D50E8(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 temp_4_2;
    s32 var_2;

    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E3428;
    temp_4 = M2C_FIELD(arg0, s32 *, 0x40);
    if (temp_4 != 0) {
        D_003C87E0(temp_4);
    }
    temp_4_2 = M2C_FIELD(arg0, s32 *, 0x44);
    if (temp_4_2 != 0) {
        D_003C87E0(temp_4_2);
    }
    func_002DFF98(arg0, 0);
    var_2 = arg1 & 1;
    if (var_2 != 0) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

s32 func_002D5178(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x10) != 0) {
        return M2C_FIELD(arg0, s32 *, 0xC) != 0;
    }
    return 0;
}
