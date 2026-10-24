#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_003E3F30;

void * func_00389A40(void *arg0) {
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E3F30;
    return arg0;
}
