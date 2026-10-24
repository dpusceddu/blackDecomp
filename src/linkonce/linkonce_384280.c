#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_00414F50;

M2C_UNK * func_00384280(void) {
    return &D_00414F50;
}

void func_00384290(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xC) = 1;
}
