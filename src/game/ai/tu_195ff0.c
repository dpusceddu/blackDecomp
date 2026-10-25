#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern s32 func_001880D8();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_195ff0", func_00195FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_195ff0", func_001960C8);

void func_00196128(void **arg0)
{
  int new_var2;
  void *temp_3;
  int new_var;
  func_00193988();
  new_var = 0;
  new_var2 = 0x290;
  temp_3 = *arg0;
  if ((*((u8 *) (temp_3 + new_var2))) != new_var)
  {
    func_001880D8(temp_3 + new_var2);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_195ff0", func_00196168);
