#include "ps2/prelude.h"

extern s32 func_00158E80();
extern void *D_0040F4D0;

void func_00135C08(void *arg0)
{
  f32 *new_var;
  M2C_FIELD(arg0, s8 *, 0x3B2) = 0;
  func_00158E80(M2C_FIELD(arg0, s32 *, 0x2A4));
  new_var = (f32 *) (((s8 *) D_0040F4D0) + 0x20);
  M2C_FIELD(arg0, f32 *, 0x300) = (f32) (*new_var);
  M2C_FIELD(arg0, f32 *, 0x258) = 1.0f;
}
