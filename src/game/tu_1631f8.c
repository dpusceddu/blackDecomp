#include "ps2/prelude.h"

extern s32 func_001F2A60(s32, s8, M2C_UNK, M2C_UNK, M2C_UNK);
extern s32 D_0040F51C;
extern s32 func_00160E70();

void func_001631F8(void *arg0) {
    func_001F2A60(D_0040F51C, *M2C_FIELD(arg0, s8 **, 0x20), 0, 0, 1);
}

void func_00163230(void) {
    func_00160E70();
}
