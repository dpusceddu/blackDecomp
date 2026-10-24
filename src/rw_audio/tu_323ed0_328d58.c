#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00329370(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_0045C120;
extern M2C_UNK D_0045C138;
extern s32 func_003299E8(M2C_UNK *, s32, s32, M2C_UNK);
extern s32 func_00329958(M2C_UNK *);

void func_00328D58(void) {
    func_00329370(0, 0x200000, 0x80, &D_0045C120, &D_0045C138);
    func_003299E8(&D_0045C120, 0, 0x5400, 1);
}

void func_00328DB0(void) {
    func_003299E8(&D_0045C120, 0, 0x5400, 0);
    func_00329958(&D_0045C120);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00328DF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00328DF8);
