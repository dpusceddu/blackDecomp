#include "ps2/prelude.h"

void func_002AF7D8(void *arg0) {
    void **temp_2;
    void *temp_3;

    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        temp_3 = M2C_FIELD(arg0, void **, 8);
        temp_2 = M2C_FIELD(arg0, void ***, 0xC);
        *temp_2 = temp_3;
        M2C_FIELD(temp_3, void ***, 4) = temp_2;
    }
}
