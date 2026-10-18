#include "auto/prelude.h"

extern s32 func_001F1F08();
extern s32 func_001F1E20();
extern M2C_UNK D_003F9DD8;

void func_001FD978(void) {
    func_001F1F08();
}

s32 func_001FD998(s32 arg0) {
    func_001F1E20(arg0, (s32) &D_003F9DD8);
    return 1;
}
