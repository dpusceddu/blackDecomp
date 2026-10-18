#include "auto/prelude.h"

extern s32 D_003BD140;

s32 func_00137AE0(void *arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x2A4);
    if (temp_2 != NULL) {
        return M2C_FIELD(M2C_FIELD(temp_2, void **, 0xE8), s32 *, 0xC) + 0x10;
    }
    return D_003BD140;
}
