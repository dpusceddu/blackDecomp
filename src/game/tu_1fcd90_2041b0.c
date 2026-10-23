#include "auto/prelude.h"

extern s32 func_00201AD0(M2C_UNK, M2C_UNK);
extern s32 func_001F1C08();

void func_002041B0(void) {
    func_00201AD0(1, 0xFFFF);
}

void func_002041D0(void *arg0) {
    func_001F1C08();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
}
