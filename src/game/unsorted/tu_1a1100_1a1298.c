#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern s32 func_001829A8();
extern s32 func_00182550(s32, M2C_UNK);

void func_001A1298(s32 *arg0) {
    func_00193988();
    if (func_001829A8(*arg0 + 0x810) == 0) {
        func_00182550(*arg0 + 0x810, 0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A12E0);
