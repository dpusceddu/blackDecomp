#include "auto/prelude.h"

extern s32 D_003EC8F0;
extern s32 func_002F1EB0(M2C_UNK, M2C_UNK);

void func_002F23E8(void) {
    D_003EC8F0 = 0;
}

void func_002F23F8(void) {
    func_002F1EB0(1, 0xFFFF);
}

void func_002F2418(void) {
    func_002F1EB0(0, 0xFFFF);
}
