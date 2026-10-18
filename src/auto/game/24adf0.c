#include "auto/prelude.h"

extern s32 func_00386EC8();
extern M2C_UNK D_003E22B8;
extern s32 func_00253FF0();

s32 func_0024ADF0(s32 arg0, s32 arg1) {
    func_00386EC8(arg0, 1);
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E22B8;
    func_00253FF0(arg0 + 8, arg1);
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    return arg0;
}
