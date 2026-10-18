#include "auto/prelude.h"

void func_0010B2A8(void *arg0)
{
  s8 *new_var;
  M2C_FIELD(arg0, s8 *, 0x515) = 0;
  M2C_FIELD(arg0, s32 *, 0xC) = 1;
  arg0 += 0;
  new_var = (s8 *) arg0;
 do { *((s32 *) (new_var + 0x10)) = 0; } while (0);
}

void func_0010B2C0(void *arg0, s8 arg1)
{
  M2C_FIELD(arg0, s8 *, 0x517) = arg1;
  if ((arg1 && arg1) && arg1)
  {
  }
  M2C_FIELD(arg0, s32 *, 0xC) = 5;
 M2C_FIELD(arg0, s32 *, 0x1C) = 0; M2C_FIELD(arg0, s8 *, 0x515) = 0;
}

void func_0010B2D8(void *arg0)
{
  M2C_FIELD(arg0, s8 *, 0x515) = 0;
  M2C_FIELD(arg0, s32 *, 0x28) = 0;
  M2C_FIELD(arg0, s32 *, 0xC) = 9;
}

void func_0010B2F0(void *arg0)
{
  M2C_FIELD(arg0, s8 *, 0x515) = 0;
  M2C_FIELD(arg0, s32 *, 0x2C) = 0;
  *((s32 *) (0xC + ((s8 *) arg0))) = 6;
}

void func_0010B308(void *arg0)
{
  s8 *new_var;
  new_var = ((s8 *) arg0) + 0x515;
  M2C_FIELD(arg0, s32 *, 0x30) = (*((s8 *) new_var) = 0);
  M2C_FIELD(arg0, s32 *, 0xC) = 7;
}
