#include "ps2/prelude.h"

extern s32 func_00280B10();

s32 func_001EED58(void *arg0) {
    func_00280B10();
    M2C_FIELD(arg0, s8 *, 0x291) = 0;
    M2C_FIELD(arg0, s32 *, 0x250) = 2;
    return 1;
}
