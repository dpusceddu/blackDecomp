#include "ps2/prelude.h"

extern void *D_0040F4D0;

s16 func_0012DFF0(void *arg0)
{
  return (s16) (((M2C_FIELD(D_0040F4D0, s8 *, 0x5AAC)) | ((M2C_FIELD(arg0, u16 *, 4)) << 8)) ^ 0);
}

s16 func_0012E018(void *arg0)
{
  int new_var;
  int new_var2;
  new_var2 = 0x5AAC;
  new_var = (*((s8 *) (((s8 *) D_0040F4D0) + new_var2))) | ((M2C_FIELD(arg0, u16 *, 8)) << 8);
  return (s16) new_var;
}

s16 func_0012E040(void *arg0)
{
  int new_var;
  new_var = ((M2C_FIELD(D_0040F4D0, s8 *, 0x5AAC)) | ((M2C_FIELD(arg0, u16 *, 4)) << 7)) | ((M2C_FIELD(D_0040F4D0, s8 *, 0x5AAD)) << 0xB);
  return (s16) new_var;
}

s16 func_0012E070(void *arg0)
{
  int new_var;
  u16 *new_var3;
  int new_var2;
  new_var3 = (u16 *) (((s8 *) arg0) + 8);
  new_var = (M2C_FIELD(D_0040F4D0, s8 *, 0x5AAC)) | (((*new_var3) & 0xFFFFu) << 7);
  new_var2 = 0xB;
  return (s16) (new_var | ((M2C_FIELD(D_0040F4D0, s8 *, 0x5AAD)) << new_var2));
}
