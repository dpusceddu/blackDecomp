#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00209FF8(s32);
extern s32 D_0040F544;

void func_001F1E90(void) {
    func_00209FF8(D_0040F544 + 0x13A8);
}

void func_001F1EB8(void) {
    func_00209FF8(D_0040F544 + 0x1C6C);
}
