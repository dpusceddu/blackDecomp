#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FCF8);

s32 func_0027FE68(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FE70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FF00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_0027FF78);

s32 func_00280100(s32 arg0, void *arg1)
{
  s32 temp_2;
  void *temp_3;
  temp_2 = M2C_FIELD(arg1, s32 *, 0x1024);
  if (temp_2 == 0)
  {
    temp_3 = *((void **) (((s8 *) arg1) + 0x1030));
    (*((M2C_UNK (**)(void *)) (((s8 *) temp_3) + 0x24)))(arg1 + (M2C_FIELD(temp_3, s16 *, 0x20)));
    M2C_FIELD(arg1, s8 *, 0x102E) = (M2C_FIELD(arg1, s8 *, 0x102D) = 0);
  }
  else
  {
    M2C_FIELD(arg1, s32 *, 0x1024) = (s32) (temp_2 - 1);
  }
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_00280158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_00280160);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_00280200);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_002802A8);

void func_00280320(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x102D) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27fcf8", func_00280328);
