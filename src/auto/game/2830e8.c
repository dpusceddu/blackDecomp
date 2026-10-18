#include "auto/prelude.h"

void func_002830E8(void *arg0, f32 fparg0) {
    void *temp_3;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), f32 *, 0x80) = fparg0;
    temp_3 = M2C_FIELD(arg0, void **, 0x14);
    M2C_FIELD(temp_3, s32 *, 0x88) = (s32) (M2C_FIELD(temp_3, s32 *, 0x88) | 0x20);
}
