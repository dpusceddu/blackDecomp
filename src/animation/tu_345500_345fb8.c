#include "auto/prelude.h"

s32 func_00345FB8(void *arg0)
{
  if ((M2C_FIELD(arg0, s32 *, 0x20)) != 0)
  {
    if (arg0)
    {
      M2C_FIELD(arg0, s32 *, 0x20) = 0;
      return 1;
    }
    else
    {
      M2C_FIELD(arg0, s32 *, 0x20) = 0;
      return 1;
    }
  }
  return 0;
}
