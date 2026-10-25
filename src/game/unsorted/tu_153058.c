#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0014B8A0();
extern s32 func_0014B948();
extern s32 func_0014BA80();
extern s32 func_0014BA58();

void func_00153058(void) {
    func_0014B8A0();
}

s32 func_00153078(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0014B948(arg0, arg1, arg2 & 0xFF, arg3);
    return 1;
}

void func_00153098(void) {
    func_0014BA80();
}

s32 func_001530B8(void) {
    func_0014BA58();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_153058", func_001530D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_153058", func_001530E0);

void func_001531B8(void) {

}

s32 func_001531C0(void) {
    return 1;
}
