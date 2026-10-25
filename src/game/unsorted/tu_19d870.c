#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001880D8();
extern s32 func_00181028();
extern s32 func_00180FE0();
extern s32 func_00193A28();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19d870", func_0019D870);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19d870", func_0019D990);

void func_0019DAA0(void **arg0)
{
  unsigned char new_var2;
  void *temp_3;
  s8 *new_var;
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
  new_var2 = func_00181028((*arg0) + 0x140) != 0;
  if (new_var2)
  {
    func_00180FE0((*arg0) + 0x140);
  }
  func_00193A28(arg0, 3, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_19d870", func_0019DB08);
