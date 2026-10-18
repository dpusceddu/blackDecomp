#include "auto/prelude.h"

void func_001B37B0(s32 arg0, s32 arg1)
{
  s8 *new_var;
  new_var = ((s8 *) (arg0 + ((arg1 & 0xFFFF) * 0x10))) + 0xD;
  *((s8 *) new_var) = 1;
}
