#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0027C410();
extern s32 D_003C0DFC;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C410);

s32 func_0027C460(s32 arg0, s32 arg1) {
    return M2C_FIELD(func_0027C410(), s32 *, 0x10C) + (arg1 * 0x70);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C778);

s8 *func_0027C860(s8 *arg0)
{
  s8 *var_5;
  u32 var_6;
  var_5 = arg0;
  var_6 = 0;
 do { } while (0);
  if ((*var_5) == 0x3A)
  {
    var_5 += 1;
  }
  else
  {
    loop_3:
    var_6 += 1;

    if (var_6 < 4U)
    {
 do { } while (0);
      if (!((*(var_5 + var_6)) == 0x3A))
      {
        goto loop_3;
      }
      else
      {
        var_5 += var_6 + 1;
      }
    }
  }
  return var_5;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C8B0);

void func_0027C990(s32 arg0) {
    D_003C0DFC = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027C9A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CAB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CBC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CBE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CC78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CCA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CCF8);

s32 func_0027CD48(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x60);
    return M2C_FIELD(temp_3, s64 *, 0x10) >= M2C_FIELD(temp_3, s64 *, 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CD60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c410", func_0027CE50);
