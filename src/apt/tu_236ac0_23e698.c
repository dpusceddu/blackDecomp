#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0021ADB8();

void func_0023E698(void *arg0)
{
  unsigned int temp_2;
  temp_2 = (M2C_FIELD(arg0, u16 *, 0x58)) - 1;
  M2C_FIELD(arg0, u16 *, 0x58) = temp_2;
  if (!(temp_2 & 0xFFFF))
  {
    func_0021ADB8(0);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023E6D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0023E6D8);
