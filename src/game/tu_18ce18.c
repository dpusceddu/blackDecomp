#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_001A73F0();
extern s32 func_00182318();
extern s32 func_00188148();

void func_0018CE18(void **arg0) {
    func_001A73F0(M2C_FIELD(M2C_FIELD(*arg0, void **, 0x7C), void **, 0x330));
    func_00182318(*arg0 + 0x810, 1);
    func_00188148(*arg0 + 0x290, 0);
}
