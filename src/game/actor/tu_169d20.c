#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00169D88();
extern s32 func_00165B00();

s32 func_00169D20(void) {
    return 0;
}

void func_00169D28(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x11C) != 0) {
        M2C_FIELD(arg0, u8 *, 0x11C) = 0U;
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x11C) = 1U;
}

void func_00169D48(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x120) == 2) {
        func_00169D88();
        return;
    }
    func_00165B00();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_169d20", func_00169D88);
