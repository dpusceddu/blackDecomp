#include "auto/prelude.h"

void * func_0023F020(void *arg0) {
    void *temp_3;
    void *temp_3_2;

    temp_3 = M2C_FIELD(arg0, void **, 0x4C);
    if (temp_3 != NULL) {
        M2C_FIELD(temp_3, void **, 0x50) = (void *) M2C_FIELD(arg0, void **, 0x50);
    }
    temp_3_2 = M2C_FIELD(arg0, void **, 0x50);
    if (temp_3_2 != NULL) {
        M2C_FIELD(temp_3_2, void **, 0x4C) = (void *) M2C_FIELD(arg0, void **, 0x4C);
    }
    M2C_FIELD(arg0, void **, 0x4C) = NULL;
    M2C_FIELD(arg0, void **, 0x50) = NULL;
    return arg0;
}
