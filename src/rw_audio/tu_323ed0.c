#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_00458DC0;
extern s32 func_0036CD08(M2C_UNK, s32, M2C_UNK);
extern void func_00324E38(s32 arg0, s32 arg1);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00323ED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003240D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003242B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003245C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324640);

s32 func_00324650(void) {
    return D_00458DC0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324660);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003246E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003247A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003248A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324900);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324948);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324968);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003249E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324A88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324CB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00324D98);

s32 func_00324DE8(s32 arg0) {
    s32 temp_2;

    temp_2 = func_0036CD08(0, arg0, 0);
    func_00324E38(temp_2, arg0);
    return temp_2;
}
