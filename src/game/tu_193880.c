#include "ps2/prelude.h"

extern s32 func_00173690();

void func_00193880(void *arg0)
{
  s8 *new_var2;
  s8 *new_var;
  new_var2 = (s8 *) arg0;
  func_00173690(arg0 + 4);
  new_var = (s8 *) (new_var2 + 9);
  *((s8 *) (new_var2 + 8)) = (*new_var = 0);
  *((f32 *) (new_var2 + 0)) = -1.0f;
}
