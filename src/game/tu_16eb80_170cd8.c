#include "ps2/prelude.h"

extern void *D_0040F4D0;
extern s32 func_00170740();

void func_00170CD8(void *arg0)
{
  f32 new_var;
  if ((M2C_FIELD(arg0, s32 *, 0x7C)) == 3)
  {
    new_var = (f32) (M2C_FIELD(D_0040F4D0, f32 *, 0x20));
 dummy_label_91248: ;
    *((s32 *) ((0, ((s8 *) arg0) + 0x7C))) = 4;
    M2C_FIELD(arg0, f32 *, 0x74) = new_var;
    return;
  }
  func_00170740(arg0, arg0);
}
