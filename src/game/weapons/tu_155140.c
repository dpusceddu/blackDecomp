#include "include_asm.h"
#include "ps2/prelude.h"

u16 func_00155140(s32 arg0, s32 arg1, s32 arg2)
{
  u16 *temp_4;
  u16 temp_2;
  u16 temp_3;
  u16 temp_6;
  temp_6 = arg2 & 0xFF;
  temp_4 = arg0 + (arg1 * 2);
  ;
  if ((*temp_4) < temp_6)
  {
    temp_2 = *temp_4;
    *temp_4 = 0;
    return temp_2 ^ 0;
  }
  *temp_4 = (*temp_4) - temp_6;
  return temp_6 & 0xFF;
}
