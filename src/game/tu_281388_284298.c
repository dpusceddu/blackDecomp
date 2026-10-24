#include "ps2/prelude.h"

extern s32 func_00328140(void *, s32);

s32 func_00284298(void *arg0) {
    *M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 **, 0x30) = 1;
    func_00328140(M2C_FIELD(arg0, void **, 0x38), 0);
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) (M2C_FIELD(arg0, u16 *, 0x30) & 1);
    return 1;
}
