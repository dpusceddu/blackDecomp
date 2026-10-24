#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00310698();

void *func_0031A7F8(void *arg0, s32 arg1, s32 arg2)
{
  s32 temp_4;
  M2C_FIELD(arg0, s32 *, 0x68) = arg2;
  temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
  if (temp_4 != 0)
  {
 do { } while (0);
    func_00310698(temp_4, 0xE, 1, arg2);
  }
  return arg0;
}
