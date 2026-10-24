#include "ps2/prelude.h"

extern s32 func_00322C70();

void func_00374EE8(s32 arg0, s32 arg1, s32 arg2)
{
  void *temp_2;
  void *temp_3;
  temp_2 = arg0 + 0x40;
  do
  {
  }
  while (0);
  temp_3 = *((void **) (temp_2 + 0x44));
  (*((M2C_UNK (**)(s32, s32)) (((s8 *) temp_3) + 4)))(M2C_FIELD(temp_2, s32 *, 0x7C), M2C_FIELD(temp_3, s32 *, 8));
  func_00322C70(arg0, arg1, arg2);
}
