#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_003E41B0;

void * func_00389BD0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E41B0;
    return arg0;
}
