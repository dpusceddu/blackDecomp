#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern void * D_003C1588;
extern s32 func_0029C1B0();
extern s32 func_0029C138();

void func_0029C1D8(s8 *arg0, s32 arg1) {
    s32 var_2;
    s8 *var_4;

    var_4 = arg0;
    var_2 = arg1 - 1;
    if (arg1 != 0) {
        do {
            *var_4 = 0;
            var_2 -= 1;
            var_4 += 1;
        } while (var_2 != -1);
    }
}

void * func_0029C210(u32 arg0) {
    if (arg0 < 0xAU) {
        return (&D_003C1588)[arg0];
    }
    return NULL;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C238);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C318);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C4F0);

void func_0029C4F8(s32 *arg0, s32 arg1)
{
  s32 temp_17;
  temp_17 = func_0029C1B0(arg1);
  func_0029C138(arg0);
  if (arg0 && arg0)
  {
 arg0++; arg0--; } if ((M2C_FIELD(arg0, s32 *, 0x30)) != 0xFFFFFFFF) {
    M2C_FIELD(arg0, s32 *, 0x30) = temp_17;
  }
  M2C_FIELD(arg0, s32 *, 0x20) = 0;
  M2C_FIELD(arg0, s32 *, 0) = ((M2C_FIELD(arg0, s32 *, 0)) & (~0xC)) | 0x105;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C5D8);

s32 func_0029C5E8(u32 *arg0, s32 arg1) {
    if (arg1 == 1) {
        return ((u32) *arg0 >> 8) & 1;
    }
    func_0029C138();
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C620);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_29c138_29c1d8", func_0029C6C0);
