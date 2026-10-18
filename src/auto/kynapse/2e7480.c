#include "auto/prelude.h"

extern s32 D_003E6428;
extern s32 D_003EA768;
extern s32 func_002E72F0(M2C_UNK, M2C_UNK);

void func_002E7480(void) {
    D_003E6428 = 0;
}

void func_002E7490(void) {
    D_003EA768 = 0;
}

void func_002E74A0(void) {
    func_002E72F0(1, 0xFFFF);
}

void func_002E74C0(void) {
    func_002E72F0(0, 0xFFFF);
}
