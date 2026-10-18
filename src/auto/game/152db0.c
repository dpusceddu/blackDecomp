#include "auto/prelude.h"

extern void * func_001AFD80();

s32 func_00152DB0(void *arg0) {
    void *temp_2;

    temp_2 = func_001AFD80(arg0 + 0x1A0, M2C_FIELD(arg0, s32 *, 0x118));
    if (temp_2 == NULL) {
        return 0;
    }
    return M2C_FIELD(temp_2, s32 *, 0x54) == 8;
}
