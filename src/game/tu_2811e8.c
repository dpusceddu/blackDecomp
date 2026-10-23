#include "auto/prelude.h"

extern char D_0049A858;

void *func_002811E8(s32 arg0)
{
  return (arg0 * 8) + (&D_0049A858);
 dummy_label_769319: ;
}

void func_00281200(void *arg0, f32 fparg0)
{
  s8 *new_var;
  new_var = ((s8 *) arg0) + 0x30;
  if (fparg0 > 0.0f)
  {
    M2C_FIELD(arg0, f32 *, 0x1C) = (M2C_FIELD(arg0, f32 *, 0x20) = fparg0);
    *((u16 *) new_var) = (u16) ((*((u16 *) new_var)) | 4);
  }
}
