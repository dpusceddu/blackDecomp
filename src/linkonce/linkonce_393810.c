#include "include_asm.h"
#include "ps2/prelude.h"

f32 func_00393810(void *arg0)
{
  f32 temp_f0;
  f32 temp_f1;
  float new_var;
  temp_f1 = M2C_FIELD(arg0, f32 *, 8);
  temp_f0 = M2C_FIELD(arg0, f32 *, 0);
  new_var = ((float) (temp_f0 * temp_f0)) + (temp_f1 * temp_f1);
  return ((float) (temp_f0 * temp_f0)) + (temp_f1 * temp_f1);
}
