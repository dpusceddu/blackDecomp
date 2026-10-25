#include "include_asm.h"
#include "ps2/prelude.h"

void func_001084F8(s32 arg0, s32 arg1, s16 arg2)
{
  s32 var_2;
  s32 var_3;
  void *var_4;
  var_4 = arg0 + 0xD40;
  var_3 = 0;
  loop_1:
  var_3 += 1;

  if ((*((s32 *) (((s8 *) var_4) + (-4)))) == arg1)
  {
    var_2 = var_3 < 0x11;
    if ((M2C_FIELD(var_4, s16 *, 4)) == arg2)
    {
      M2C_FIELD(var_4, s32 *, 0) = 0;
      return;
    }
    goto block_5;
  }
  block_5:
  var_4 += 0xC;

  var_2 = var_3 < 0x11;
  if (!var_2)
  {
    return;
  }
  goto loop_1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_105bc0_1084f8", func_00108540);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_105bc0_1084f8", func_00108668);
