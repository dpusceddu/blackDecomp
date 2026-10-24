#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_001A1D20();

void func_001A1CB0(void) {
    func_001A1D20();
}

s32 func_001A1CD0(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg1, s32 *, 0);
    if (temp_5 == 0xA) {
        func_00193A28((RecoveredAIActionHeader *) arg0, 0x16U, 0);
        return 1;
    }
    if (temp_5 == 0xB) {
        func_001A1D20(arg0);
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A1D20);
