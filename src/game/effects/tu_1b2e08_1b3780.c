#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001B3AE8();

void func_001B3780(s32 arg0) {
    u32 var_5;
    void *temp_3;

    var_5 = 0;
    do {
        temp_3 = arg0 + (var_5 * 0x10);
        var_5 = (var_5 + 1) & 0xFFFF;
        M2C_FIELD(temp_3, s8 *, 0xD) = 0;
    } while (var_5 < 0x1CU);
}

void func_001B37B0(s32 arg0, s32 arg1)
{
  s8 *new_var;
  new_var = ((s8 *) (arg0 + ((arg1 & 0xFFFF) * 0x10))) + 0xD;
  *((s8 *) new_var) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B37C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B3818);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B38F8);

s32 func_001B3A10(s32 arg0, s32 arg1)
{
  arg0 = func_001B3AE8(arg0, 0, 8, 0, 0x100, arg1, 0xFF);
  M2C_FIELD(arg1, s16 *, 0xD8) = arg0;
  return (s32) arg0;
}
