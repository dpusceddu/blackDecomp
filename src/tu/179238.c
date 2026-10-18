#include "auto/prelude.h"

s32 func_00179238(s32 *arg0, s32 arg1) {
    s32 temp_3;

    temp_3 = 1 << arg1;
    return (temp_3 & *arg0) == temp_3;
}

void * func_00179258(void *arg0, void *arg1) {
    return arg0 + (((s32) arg1 * 0xC) + 4);
}
