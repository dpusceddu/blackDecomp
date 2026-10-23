#include "auto/prelude.h"

extern s32 func_002F4A48();
extern M2C_UNK D_003DD198;

void * func_00171110(void *arg0) {
    func_002F4A48();
    M2C_FIELD(arg0, s32 *, 0x70) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003DD198;
    M2C_FIELD(arg0, s32 *, 0x74) = 0;
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
    M2C_FIELD(arg0, s32 *, 0x80) = 0;
    return arg0;
}

s32 func_00171158(void) {
    return 1;
}

s32 func_00171160(void) {
    return 0;
}
