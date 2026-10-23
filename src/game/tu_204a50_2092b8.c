#include "auto/prelude.h"

extern s32 func_00208D00(M2C_UNK, M2C_UNK);
extern s32 D_003BE718;
extern s32 func_0020D188(s32);
extern s32 D_0040F544;

void func_002092B8(void) {
    func_00208D00(1, 0xFFFF);
}

void func_002092D8(s32 arg0) {
    D_003BE718 = arg0;
}

void func_002092E8(void) {
    func_0020D188(D_0040F544 + 0xE90);
}
