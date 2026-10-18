#include "auto/prelude.h"

extern s32 func_0013EE28();

s32 func_00131078(void *arg0)
{
  void *new_var;
  if (func_0013EE28())
  {
    if (arg0)
    {
      *((s8 *) (((s8 *) (new_var = arg0)) + 0x102)) = 0;
      M2C_FIELD(arg0, s32 *, 0xB0) = 0;
      return 1;
    }
    else
    {
      M2C_FIELD(arg0, s8 *, 0x102) = 0;
      M2C_FIELD(arg0, s32 *, 0xB0) = 0;
      return 1;
    }
  }
  return 0;
}
