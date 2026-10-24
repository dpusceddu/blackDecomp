#include "include_asm.h"
#include "ps2/prelude.h"

void func_001A10E0(void *arg0, s32 arg1) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0xC);
    if ((temp_2 != NULL) && (M2C_FIELD(temp_2, s32 *, 0x380) == arg1)) {
        M2C_FIELD(arg0, void **, 0xC) = NULL;
    }
}
