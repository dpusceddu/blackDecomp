#include "include_asm.h"
#include "ps2/prelude.h"

extern void * func_0011D498();
extern s32 func_001A7188();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358", func_0011D358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358", func_0011D3C8);

void func_0011D430(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x44) = arg1;
    M2C_FIELD(arg0, s32 *, 0) = 0;
}

s32 func_0011D440(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
    return 1;
}

void func_0011D450(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x48) = 0;
    M2C_FIELD(func_0011D498(), s8 *, 0x3AF) = 0;
    func_001A7188(M2C_FIELD(func_0011D498(arg0), s32 *, 0x330));
}

void func_0011D490(void) {

}

void * func_0011D498(void **arg0) {
    return M2C_FIELD(*arg0, void **, 0x7C);
}

s32 func_0011D4A8(s32 *arg0) {
    return *arg0 + 0xA0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358", func_0011D4B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358", func_0011D5A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358", func_0011D848);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358", func_0011D948);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358", func_0011DA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358", func_0011DC80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_11d358", func_0011DD48);
