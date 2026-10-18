#include "auto/prelude.h"

extern s32 func_00193980();
extern s32 func_00187FE0(s32, M2C_UNK);
extern s32 func_00181A90(s32, M2C_UNK);

void func_0019A4F0(void *arg0) {
    func_00193980();
    func_00187FE0(M2C_FIELD(arg0, s32 *, 0) + 0x290, 0);
    M2C_FIELD(arg0, s32 *, 8) = func_00181A90(M2C_FIELD(arg0, s32 *, 0) + 0xEC0, 0x37);
}
