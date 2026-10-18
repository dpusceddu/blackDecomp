#include "auto/prelude.h"

extern s32 func_001080F0();
extern s32 func_00274F80(s32, s32);
extern s32 func_0035E7D8(s32);

void func_00107C20(M2C_UNK *arg0, s32 arg1) {
    if ((M2C_FIELD(arg0, u8 *, 0x3B8) != 0) || (func_001080F0() != 0)) {
        func_00274F80(M2C_FIELD(arg0, s32 *, 0x3AC), arg1);
        return;
    }
    func_0035E7D8(arg1);
}

s32 func_00107C80(s32 arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x24) + arg0), s32 *, 0x24);
}
