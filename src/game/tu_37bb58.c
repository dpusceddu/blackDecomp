#include "ps2/prelude.h"

extern s32 func_00323188(void *, s32, s32, s32);

void func_0037BB58(void *arg0, void *arg1) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
    func_00323188(temp_4, M2C_FIELD(temp_4, s32 *, 0x80), 1, M2C_FIELD(arg1, s32 *, 0x14));
}
