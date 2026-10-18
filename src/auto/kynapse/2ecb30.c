#include "auto/prelude.h"

extern s32 D_003E8420;
extern s32 func_002EC8A0(M2C_UNK, M2C_UNK);

void func_002ECB30(void) {
    D_003E8420 = 0;
}

void func_002ECB40(void) {
    func_002EC8A0(1, 0xFFFF);
}

void func_002ECB60(void) {
    func_002EC8A0(0, 0xFFFF);
}
