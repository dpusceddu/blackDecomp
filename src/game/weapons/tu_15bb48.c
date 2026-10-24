#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00154FD8();

s32 func_0015BB48(s32 arg0, s32 arg1)
{
  s8 *new_var;
  M2C_FIELD(arg0, s32 *, 0x1C) = 0;
  M2C_FIELD(arg0, f32 *, 0x2C) = 1.0f;
  M2C_FIELD(arg0, s32 *, 0x24) = 0;
  M2C_FIELD(arg0, s32 *, 0x28) = 0;
  M2C_FIELD(arg0, s32 *, 0x20) = 0;
  M2C_FIELD(arg0, s8 *, 0x45) = 0;
 do { new_var = ((s8 *) arg0) + 0x3C; M2C_FIELD(arg0, s8 *, 0x46) = 0; *((s32 *) new_var) = 0; M2C_FIELD(arg0, s8 *, 0x42) = 0; return func_00154FD8(arg0); } while (0);
}
