#include "auto/prelude.h"

extern s32 func_00129240(void *, s32, M2C_UNK);
extern void * D_0040F4D0;

void func_00143550(void *arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_5 != 0) {
        func_00129240(D_0040F4D0, temp_5, 0);
        M2C_FIELD(arg0, s32 *, 4) = 0;
    }
}
