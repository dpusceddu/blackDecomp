#include "auto/prelude.h"

extern s32 func_00347858();

void func_001A7450(void *arg0) {
    void *temp_4;

    if (M2C_FIELD(arg0, u8 *, 0xB9) != 0) {
        temp_4 = M2C_FIELD(arg0, void **, 0x54);
        if (M2C_FIELD(temp_4, s32 *, 4) != 0) {
            func_00347858(temp_4, arg0 + 0x10);
            M2C_FIELD(arg0, u8 *, 0xB9) = 0U;
        }
    }
}
