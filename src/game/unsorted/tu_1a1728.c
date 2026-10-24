#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern s32 func_00181028();
extern s32 func_00180FE0();
extern s32 func_001880D8();
extern s32 func_00193A28();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A1728);

void func_001A1888(void **arg0)
{
  s8 *new_var;
  void *temp_3;
  func_00193988();
  if (func_00181028((*arg0) + 0x140) != 0)
  {
    temp_3 = (*arg0) + 0x140;
    func_00180FE0(temp_3);
  }
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A18E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A1A08);

void func_001A1B28(void **arg0)
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A1B90);
