#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_001D96E8(void) {
    return 1;
}

void func_001D96F0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D96F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D9700);

void func_001D9760(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x66) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D9768);

void func_001D97C8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x66) = 0;
}
