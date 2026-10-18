#include "auto/prelude.h"

extern s32 func_002E41D8();
extern M2C_UNK D_003EE090;

void * func_002F4A48(void *arg0) {
    func_002E41D8();
    M2C_FIELD(arg0, s32 *, 0x6C) = 0x19;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003EE090;
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = 0;
    M2C_FIELD(arg0, s32 *, 0x68) = 0;
    return arg0;
}
