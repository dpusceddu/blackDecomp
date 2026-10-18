#include "auto/prelude.h"

extern s32 func_002DFF10();
extern M2C_UNK D_003E32D0;

void * func_002D39D0(void *arg0) {
    func_002DFF10();
    M2C_FIELD(arg0, s8 *, 0x10) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E32D0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    return arg0;
}
