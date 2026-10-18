#include "auto/prelude.h"

extern s32 func_00319DE0(s32, M2C_UNK);
extern s32 func_00319E28(s32, s32);

s32 func_00285190(void *arg0) {
    func_00319DE0(M2C_FIELD(arg0, s32 *, 0x34), 0);
    func_00319E28(M2C_FIELD(arg0, s32 *, 0x34), 0);
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) (M2C_FIELD(arg0, u16 *, 0x30) & 1);
    return 1;
}
