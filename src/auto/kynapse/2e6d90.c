#include "auto/prelude.h"

extern s32 func_002E5358();
extern M2C_UNK D_003E9C08;

s32 func_002E6D90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    func_002E5358(arg0, arg2);
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E9C08;
    return arg0;
}
