#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_002763B0();
extern s32 func_00274138();

void func_00276258(void *arg0) {
    func_002763B0();
    func_00274138(M2C_FIELD(arg0, s32 *, 0x48) + 0x40, arg0 - 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275128_276258", func_00276290);
