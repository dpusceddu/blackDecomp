#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00312C70();

void func_0037BE10(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x4C);
    if (temp_3 != NULL) {
        *M2C_FIELD(arg0, void ***, 0x50) = temp_3;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x4C), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x50);
    }
    func_00312C70();
}
