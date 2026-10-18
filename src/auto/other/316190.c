#include "auto/prelude.h"

s32 func_00316190(void *arg0) {
    s32 (*temp_2)();

    temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), s32 (**)(), 0x1C);
    if (temp_2 == NULL) {
        return 0;
    }
    return temp_2();
}
