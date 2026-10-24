#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 (*D_003C0E34)();

void func_00292000(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00292008);

void func_00292060(void) {
    D_003C0E34();
}

s32 func_00292088(void) {
    return D_003C0E34() + 8;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002920B0);
