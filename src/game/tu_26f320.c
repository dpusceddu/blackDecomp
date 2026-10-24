#include "ps2/prelude.h"

s32 func_0026F320(s32 arg0)
{
  int new_var;
  if (arg0)
  {
  }
  arg0 = arg0 & 0xFF;
  new_var = 4;
  return (arg0 & 0xF) + (((arg0 >> new_var) & 0xFFFF) * 0xA);
}
