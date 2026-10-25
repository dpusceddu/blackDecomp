#include "include_asm.h"
#include "ps2/prelude.h"

extern s64 D_0040DFD0;
extern s64 D_0040EB28;
extern s32 func_001C2D90();
extern s32 func_001C2E30();
extern s32 func_001D5370(M2C_UNK, M2C_UNK);

void func_001D4068(void) {

}

s32 func_001D4070(void) {
    return 1;
}

s32 func_001D4078(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D4080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D4268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D4328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D4330);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001D43B0);

void func_001D4C78(void) {
    D_0040DFD0 = D_0040EB28;
}


void func_001D5028(void) {
    func_001C2D90();
}

s32 func_001D5048(void) {
    func_001C2E30();
    return 1;
}


void func_001D5808(void) {
    func_001D5370(1, 0xFFFF);
}
