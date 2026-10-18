#include "auto/prelude.h"

extern s32 func_00355B40();
extern s32 func_0026F908();

s32 func_0026F508(s32 arg0, s32 arg1)
{
  unsigned char new_var;
  new_var = 0;
  if (func_00355B40(*((s32 *) (((s8 *) arg0) + (0x54 ^ new_var))), arg1, 0, 1, arg0 + 0x94, arg0 + 0xCC) == 0)
  {
    return 1;
    do
    {
      arg0++;
      arg0--;
    }
    while (new_var);
  }
  func_0026F908(arg0, 0xD);
  return 0;
}
