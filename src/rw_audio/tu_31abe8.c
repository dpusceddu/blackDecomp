#include "auto/prelude.h"

void func_0031ABE8(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x40);
    if (temp_3 != NULL) {
        *M2C_FIELD(arg0, void ***, 0x44) = temp_3;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x44);
    }
}
