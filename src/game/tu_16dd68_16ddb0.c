#include "ps2/prelude.h"

s32 func_0016DDB0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x22BBC) != 0;
}

s32 func_0016DDC8(s32 arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x22BBC);
    M2C_FIELD(arg0, void **, 0x22BBC) = (void *) M2C_FIELD(temp_2, void **, 0x1EF0);
    return (s32) temp_2;
}

void func_0016DDE0(void *arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1EF0) = (void *) M2C_FIELD(arg0, void **, 0x22BBC);
    M2C_FIELD(arg0, void **, 0x22BBC) = arg1;
}
