#include "auto/prelude.h"

extern s32 func_002DFF10();
extern M2C_UNK D_003E3130;

void * func_002D3520(void *arg0) {
    func_002DFF10();
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E3130;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    return arg0;
}
