#include "auto/prelude.h"

void *func_00181A90(void *arg0, s32 arg1)
{
  void *new_var;
  if (arg1 != 0x4A)
  {
    new_var = (s8 *) (arg0 + ((2 * arg1) * 2));
    return *((void **) (0x718 + new_var));
  }
  if (arg1 || arg0)
  {
    new_var = (void *) 0;
    return (void *) 0;
  }
  else
  {
    return new_var;
  }
}
