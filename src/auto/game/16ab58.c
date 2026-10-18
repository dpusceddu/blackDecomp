#include "auto/prelude.h"

extern s32 func_00107D20();

s32 func_0016AB58(s32 arg0, s32 arg1)
{
  s32 temp_2;
  temp_2 = func_00107D20(arg1 * 0xC);
  M2C_FIELD(arg0, s16 *, 4) = (s16) arg1;
  temp_2++;
  temp_2--;
  M2C_FIELD(arg0, s32 *, 0) = temp_2;
 do { M2C_FIELD(arg0, s16 *, 6) = 0; } while (0);
  return temp_2;
}
