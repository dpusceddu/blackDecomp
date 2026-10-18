#include "auto/prelude.h"

extern s32 func_001B3AE8();

s32 func_001B3A10(s32 arg0, s32 arg1)
{
  arg0 = func_001B3AE8(arg0, 0, 8, 0, 0x100, arg1, 0xFF);
  M2C_FIELD(arg1, s16 *, 0xD8) = arg0;
  return (s32) arg0;
}
