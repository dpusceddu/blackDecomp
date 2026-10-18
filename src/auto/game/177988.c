#include "auto/prelude.h"

extern s32 func_001779D0();

void * func_00177988(void *arg0) {
    if (func_001779D0() != 0) {
        return NULL;
    }
    return arg0 + (M2C_FIELD(arg0, s32 *, 0x960) * 8);
}
