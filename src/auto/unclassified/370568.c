#include "auto/prelude.h"

extern M2C_UNK D_0040BF18;

s32 func_00370568(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_0040BF18;
    return arg0;
}
