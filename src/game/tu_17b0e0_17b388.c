#include "ps2/prelude.h"

extern s32 func_00179650();
extern void *D_0040F4D4;

s32 func_0017B388(void *arg0)
{
  s32 *temp_5;
  s32 *new_var;
  temp_5 = *((s32 **) (((s8 *) arg0) + 0x20));
  if (temp_5 != NULL)
  {
    if (temp_5 || arg0)
    {
      return func_00179650(D_0040F4D4, *(new_var = temp_5));
    }
    else
    {
      return func_00179650(D_0040F4D4, *new_var);
    }
  }
  return 0;
}
