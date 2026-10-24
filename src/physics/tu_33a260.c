#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0033A260();
extern s32 func_0033A260(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033A260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033A3A8);

void *func_0033A3B0(void *arg0, s32 arg1, s32 arg2)
{
  s8 *new_var2;
  int new_var;
  new_var2 = ((s8 *) arg0) + 4;
  *((s32 *) new_var2) = 0x10;
  new_var = (arg1 << 7) + 0x100;
  M2C_FIELD(arg0, s32 *, 0) = (s32) (((new_var + (arg2 << 7)) + (arg2 * 0x60)) + 0x27E0);
  return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033A3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033A3F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0033A440);

void func_0033A448(void) {
    func_0033A260(1, 0xFFFF);
}

void func_0033A468(void) {
    func_0033A260(0, 0xFFFF);
}
