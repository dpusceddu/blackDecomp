#include "auto/prelude.h"

void func_001624A0(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x24);
    M2C_FIELD(arg0, void **, 0x20) = temp_3;
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_3, s32 *, 0x37C);
    M2C_FIELD(arg0, u16 *, 0x28) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x50), u16 *, 0x2C);
}
