#include "ps2/prelude.h"

void * func_0011D1D0(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x18);
    if (temp_3 != NULL) {
        M2C_FIELD(arg0, void **, 0x18) = (void *) M2C_FIELD(temp_3, void **, 0x90);
    }
    return temp_3;
}

void func_0011D1F0(void *arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x90) = (void *) M2C_FIELD(arg0, void **, 0x18);
    M2C_FIELD(arg0, void **, 0x18) = arg1;
}
