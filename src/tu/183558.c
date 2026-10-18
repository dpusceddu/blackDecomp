#include "auto/prelude.h"

extern s32 func_00160E70();
extern s32 func_00165BC8(s32, s32);

s128 func_00183558(void *arg0, void *arg1) {
    if (M2C_FIELD(arg1, s32 *, 0xC4) == 2) {
        return M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s128 *, 0x30);
    }
    return M2C_FIELD(arg1, s128 *, 0xA0);
}

void func_00183578(s32 arg0, s32 arg1) {
    func_00160E70();
    func_00165BC8(arg0, arg1);
}
