#include "ps2/prelude.h"

extern s32 func_002789C0(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK);
extern s32 D_003BC5E0;

void func_00109FB0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    func_002789C0(arg0 + 0x20, 2, 0x28, 0x28, D_003BC5E0, 0x2000);
}
