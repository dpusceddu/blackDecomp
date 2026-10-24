#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00193980();
extern u8 func_00180BC0();
extern s32 func_00173690();
extern s32 func_00193988();

void func_00193CC8(RecoveredAIActionHeader *arg0) {
    func_00193980();
    if (func_00180BC0(arg0->brain + 0xB30) == 0) {
        func_00193A28(arg0, 0xCU, 0);
    }
    func_00173690(&arg0->phase);
}

void func_00193D18(void) {
    func_00193988();
}

void func_00193D38(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193D40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00193FE8);
