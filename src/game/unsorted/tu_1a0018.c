#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001880D8();
extern s32 func_00193988();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a0018", func_001A0018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a0018", func_001A0360);

void func_001A0468(void **arg0)
{
  void *temp_3;
  s8 *new_var2;
  int new_var;
  temp_3 = *arg0;
  new_var2 = ((s8 *) temp_3) + 0x290;
  new_var = 0;
  if ((*((u8 *) new_var2)) != new_var)
  {
    func_001880D8(temp_3 + 0x290);
  }
  func_00193988(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a0018", func_001A04A8);
