#include "auto/prelude.h"

void func_0023EAC8(s32 arg0, void *arg1, void *arg2) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg1, void **, 8);
    M2C_FIELD(arg2, void **, 0xC) = arg1;
    M2C_FIELD(arg2, void **, 8) = temp_2;
    if (temp_2 != NULL) {
        M2C_FIELD(temp_2, void **, 0xC) = arg2;
    }
    M2C_FIELD(M2C_FIELD(arg2, void **, 0xC), void **, 8) = arg2;
}
