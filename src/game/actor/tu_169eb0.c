#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00125E40();

void func_00169EB0(void) {

}

s32 func_00169EB8(void) {
    func_00125E40();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_169eb0", func_00169ED8);
