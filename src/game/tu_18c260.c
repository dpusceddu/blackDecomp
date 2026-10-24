#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018C368();

void func_0018C260(void *arg0)
{
  void *new_var;
  s32 temp_3;
  void *temp_16;
  void *temp_3_2;
  void *temp_3_3;
  temp_3 = M2C_FIELD(arg0, s32 *, 0xF8);
  if (temp_3 < 2)
  {
    new_var = arg0 + (temp_3 * 4);
    temp_16 = *((void **) (((s8 *) new_var) + 0xF0));
    temp_3_2 = *((void **) (((s8 *) temp_16) + 4));
    (*((M2C_UNK (**)(void *)) (((s8 *) temp_3_2) + 0x14)))(temp_16 + (M2C_FIELD(temp_3_2, s16 *, 0x10)));
    temp_3_3 = *((void **) (((s8 *) temp_16) + 4));
    if ((*((s32 (**)(void *)) (((s8 *) temp_3_3) + 0x34)))(temp_16 + (M2C_FIELD(temp_3_3, s16 *, 0x30))) != 0)
    {
      func_0018C368(arg0);
    }
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C2D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C2E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C368);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C3C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C408);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C688);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C878);

s32 func_0018C8D8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x34) == 3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C8E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018C938);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018CC20);
