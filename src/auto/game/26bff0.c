#include "auto/prelude.h"

extern s32 func_0026BAF8();
extern f32 func_0026BEC0(s32, f32);
extern s32 func_0029CB50();
extern f32 func_0026BF10(s32, f32);

s32 func_0026BFF0(void *arg0)
{
  void *new_var;
  new_var = arg0;
  if (func_0026BAF8() != 0)
  {
    if (new_var || arg0)
    {
      *((s32 *) (((s8 *) new_var) - -4)) = 4;
      return 1;
    }
    else
    {
      *((s32 *) (((s8 *) new_var) - -4)) = 4;
      return 1;
    }
  }
  return 0;
}

void func_0026C030(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s8 *new_var;
  *((f32 *) (new_var = ((s8 *) (arg0 + (arg1 * 4))) + 0x4C)) = func_0026BEC0(arg0, ((f32) func_0029CB50(arg3, arg4)) / 255.0f);
}

void func_0026C098(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s8 *new_var;
  *((f32 *) (new_var = ((s8 *) (arg0 + (arg1 * 4))) + 0x4C)) = func_0026BF10(arg0, ((f32) func_0029CB50(arg3, arg4)) / 255.0f);
}
