#include "auto/prelude.h"

void func_00353518(void *arg0) {
    void *temp_5;

    if (M2C_FIELD(arg0, void **, 0x474) != NULL) {
        temp_5 = M2C_FIELD(arg0, void **, 0x440);
        if (temp_5 != NULL) {
            M2C_FIELD(arg0, void **, 0x474) = (void *) (temp_5 + ((u32) (M2C_FIELD(temp_5, s32 *, 4) & 0x7FFFFFF8) >> 1));
        }
    }
}
