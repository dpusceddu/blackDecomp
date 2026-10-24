#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E7610();
extern M2C_UNK D_004525B8;
extern M2C_UNK func_002F4BC0;
extern M2C_UNK * D_004526C8;
extern M2C_UNK D_003E5E40;

void func_002F5760(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_004525B8, "CPathObjectManager", &func_002F4BC0, 0, 0, 0);
            return;
        }
        D_004526C8 = &D_003E5E40;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F57C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F5868);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F58E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F5968);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F5A40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F5AE0);

void func_002F5BD0(void) {
    func_002F5760(1, 0xFFFF);
}

void func_002F5BF0(void) {
    func_002F5760(0, 0xFFFF);
}
