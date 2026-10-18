#include "auto/prelude.h"

s32 func_001438E8(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x80);
    if (M2C_FIELD(temp_4, s32 *, 0x1C) == 9) {
        M2C_FIELD(temp_4, s32 *, 0x1C) = 0;
    }
    return 1;
}
