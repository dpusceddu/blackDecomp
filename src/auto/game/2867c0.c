#include "auto/prelude.h"

s32 func_002867C0(s32 arg0, s32 arg1, s32 arg2)
{
  s32 *temp_2_2;
  s32 *temp_5;
  void *temp_2;
  temp_2_2 = *((s32 **) (((s8 *) (arg0 ^ 0)) + 0x286C));
  *temp_2_2 = arg1;
  temp_2 = temp_2_2;
  temp_2 = temp_2 + 4;
  temp_5 = *((s32 **) (((s8 *) arg0) + 0x2868));
  *((s32 **) (((s8 *) arg0) + 0x286C)) = (s32 *) (temp_2 - (-(arg2 * 4)));
  *temp_5 += 1;
  return (s32) temp_2;
}
