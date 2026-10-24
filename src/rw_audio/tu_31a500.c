#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00310640(s32, M2C_UNK, M2C_UNK, s32);

void * func_0031A500(void *arg0, s32 arg1, s32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, s32 *, 0x6C) = (s32) *arg2;
    if (temp_4 != 0) {
        func_00310640(temp_4, 9, 1, *arg2);
    }
    return arg0;
}
