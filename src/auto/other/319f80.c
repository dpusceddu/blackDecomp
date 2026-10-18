#include "auto/prelude.h"

extern s32 func_00317340(void *, M2C_UNK);

void func_00319F80(void *arg0) {
    void *temp_3;

    func_00317340(arg0 + 0x28, 1);
    temp_3 = M2C_FIELD(arg0, void **, 0x28);
    if (temp_3 != NULL) {
        *M2C_FIELD(arg0, void ***, 0x2C) = temp_3;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x28), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x2C);
    }
}
