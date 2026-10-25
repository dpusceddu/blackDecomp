#include "include_asm.h"
#include "ps2/prelude.h"

u8 func_001ADBF0(s32 arg0, void *arg1)
{
  void *temp_2;
  void *new_var;
  temp_2 = (new_var = *((void **) (((s8 *) arg1) + 0x2A4)));
  if (temp_2 != NULL)
  {
    if (temp_2 || arg1)
    {
      return (long long) (*((u8 *) (((s8 *) new_var) + (0x106 & 0xFFFFFFFFFFFFFFFFu))));
    }
    else
    {
      return (long long) (*((u8 *) (((s8 *) new_var) + (0x106 & 0xFFFFFFFFFFFFFFFFu))));
    }
  }
  return 0U;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a83a0_1adbf0", func_001ADC10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a83a0_1adbf0", func_001ADC30);
