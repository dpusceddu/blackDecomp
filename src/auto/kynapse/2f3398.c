#include "auto/prelude.h"

extern s32 D_003EDA20;
extern s32 func_002F2E28();

void func_002F3398(void) {
    D_003EDA20 = 0;
}

void func_002F33A8(void) {
    func_002F2E28(1, 0xFFFF);
}

void func_002F33C8(void) {
    func_002F2E28(0, 0xFFFF);
}
