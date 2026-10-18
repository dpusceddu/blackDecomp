#include "auto/prelude.h"

void func_00387058(s32 *arg0, s32 arg1)
{
  int new_var;
  new_var = (arg1 != 0) & 0xFFFFFFFF;
  *arg0 = ((*arg0) & 0xFEFFFFFF) | ((new_var << 0x18) ^ 0);
}
