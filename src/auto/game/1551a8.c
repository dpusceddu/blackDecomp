#include "auto/prelude.h"

s32 func_001551A8(void *arg0)
{
  u16 temp_3;
  temp_3 = M2C_FIELD(arg0, u16 *, 0xE);
  do
  {
    if (temp_3 != 0)
    {
      if (temp_3)
      {
        temp_3 = M2C_FIELD(arg0, u16 *, 0xE);
        M2C_FIELD(arg0, u16 *, 0xE) = (u16) (temp_3 - 1);
        return 1;
      }
      else
      {
        temp_3 = M2C_FIELD(arg0, u16 *, 0xE);
        M2C_FIELD(arg0, u16 *, 0xE) = (u16) (temp_3 - 1);
        return 1;
      }
    }
  }
  while (0);
  return 0;
}
