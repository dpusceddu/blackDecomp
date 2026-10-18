#include "auto/prelude.h"

extern s32 func_0031D268(void *, M2C_UNK, M2C_UNK);

void * func_00377C80(void *arg0, s32 arg1, s16 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s16 *, 4) = arg2;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 8) = 0;
    M2C_FIELD(arg0, s16 *, 0xA) = 0;
    return (func_0031D268(arg0 + 0xC, 1, 1) == 0) ? NULL : arg0;
}
