#include "auto/prelude.h"

void func_001C2798(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2)
{
  s8 *new_var;
  s8 *new_var2;
  new_var2 = (s8 *) arg0;
  if ((M2C_FIELD(arg0, s32 *, 0x34)) == 0)
  {
    new_var = (s8 *) arg0;
    M2C_FIELD(arg0, f32 *, 0x24) = fparg2;
    *((s32 *) (new_var2 + 0x34)) = 1;
    *((f32 *) (new_var + 0x18)) = 1.0f;
    *((f32 *) (new_var + 0x1C)) = fparg0;
    *((s32 *) (new_var + 0x14)) = 0;
    *((f32 *) (new_var + 0x20)) = fparg1;
    *((s32 *) (new_var + 0x38)) = 0;
  }
}
