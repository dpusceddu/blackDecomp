#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 (*D_0043DA70)();
extern s32 * func_00248C78();
extern s32 D_003BFAB8;
extern s32 D_003BFABC;
extern s32 *func_00248C78();
extern s32 func_002488D0();
extern s32 func_0024F770();
extern s32 func_0024F790();

void func_0024FE68(void) {
    D_0043DA70();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_0024FE90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_0024FEA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_00250010);

s32 func_00250018(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_2 == 0) {
        return 0;
    }
    return temp_2 + 8;
}

s32 func_00250038(s32 arg0, void *arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg1, s32 *, -8);
    if (temp_2 == 0) {
        return 0;
    }
    return temp_2 + 8;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_00250058);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_00250198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_00250260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_002502D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_00250370);

s32 * func_002503A8(s32 arg0, s32 arg1, u16 **arg2) {
    s32 *temp_2;

    temp_2 = func_00248C78(D_003BFAB8 + 8, arg2);
    if ((temp_2 != NULL) && (((((s32) *temp_2 >> 4) & 1) ^ 1) == 0)) {
        return temp_2;
    }
    return func_00248C78(D_003BFABC + 8, arg2);
}

s32 func_00250418(s32 arg0, s32 arg1, u16 **arg2, s32 arg3)
{
  if (func_00248C78(D_003BFAB8 + 8, arg2) == NULL)
  {
    func_002488D0(8 + arg0, arg2, arg3);
  }
  if (arg3 || arg2)
  {
    return 1;
  }
  else
  {
    return 1;
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_00250480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_002504D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_00250518);

void func_00250550(void) {
    func_0024F770();
}

void func_00250570(void) {
    func_0024F790();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_00250590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_00250618);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_002506A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_24ce90_24fe68", func_002507F0);
