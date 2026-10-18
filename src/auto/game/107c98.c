#include "auto/prelude.h"

extern s32 func_00107CC8();
extern s32 func_00107D20();

s32 func_00107C98(s32 arg0, s32 arg1) {
    func_00107CC8(arg0, M2C_FIELD(arg1, s32 *, 4));
    return func_00107D20(M2C_FIELD(arg1, s32 *, 0));
}
