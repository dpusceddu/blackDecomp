#include "auto/prelude.h"

extern s32 func_001A6840(s32, M2C_UNK, M2C_UNK);

u8 func_0017FA58(void *arg0) {
    u8 var_5;
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x44);
    var_5 = 0;
    if (M2C_FIELD(temp_4, s32 *, 0x80) == 1) {
        var_5 = M2C_FIELD(temp_4, u8 *, 0x84A);
    }
    return var_5;
}

void func_0017FA78(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x44);
    if ((M2C_FIELD(temp_3, u8 *, 0x3B) != 0) && (func_001A6840(M2C_FIELD(M2C_FIELD(temp_3, void **, 0x7C), s32 *, 0x330), 0, 1) != 0)) {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), u8 *, 0x3B) = 0U;
    }
}
