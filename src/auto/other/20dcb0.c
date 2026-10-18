#include "auto/prelude.h"

extern s32 func_0020DB90();

s32 func_0020DCB0(s32 arg0) {
    M2C_FIELD(arg0, s16 **, 4) = NULL;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = -1;
    func_0020DB90(arg0, 0x10);
    *M2C_FIELD(arg0, s16 **, 4) = 0;
    return 1;
}
