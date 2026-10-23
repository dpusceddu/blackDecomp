#include "auto/prelude.h"

extern s32 func_002486D8(s32, M2C_UNK);
extern void func_00387020(void *arg0, s32 arg1);
extern s32 func_0024FA98(s32, void *, M2C_UNK);
extern s32 D_0043DEE4;

void func_00385338(void *arg0, s32 arg1) {
    func_002486D8(arg0 + 8, 2);
    func_00387020(arg0, 0);
    if (arg1 & 1) {
        func_0024FA98(D_0043DEE4, arg0, 0x1C);
    }
}
