#include "auto/prelude.h"

extern M2C_UNK D_003DB9E0;

s32 func_00383B00(void) {
    return 8;
}

void * func_00383B08(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x10) = &D_003DB9E0;
    return arg0;
}
