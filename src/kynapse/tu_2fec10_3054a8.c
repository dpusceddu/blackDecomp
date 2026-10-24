#include "ps2/prelude.h"

extern s32 D_003EC8F0;
extern s32 func_003039D8(M2C_UNK, M2C_UNK);
extern s32 D_004548B8;
extern s32 D_00455AD0;
extern s32 D_00455BE8;

void func_003054A8(void) {
    D_003EC8F0 = 0;
}

void func_003054B8(void) {
    func_003039D8(1, 0xFFFF);
}

void func_003054D8(void) {
    func_003039D8(0, 0xFFFF);
}

s32 func_003054F8(void) {
    if ((D_004548B8 == -1) || (D_00455AD0 == -1) || (D_00455BE8 == -1)) {
        return 0;
    }
    return 1;
}
