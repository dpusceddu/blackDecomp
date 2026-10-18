#include "auto/prelude.h"

extern s32 func_001B6CF8();
extern s32 D_0040F4D8;
extern s32 func_001B37C8();

void func_00152148(void *arg0)
{
  u16 temp_3;
  func_001B6CF8(D_0040F4D8 + 0x66290, arg0, 1);
  ;
  if ((M2C_FIELD(arg0, u16 *, 0x1BC)) != 0xFFFF)
  {
    func_001B37C8(D_0040F4D8 + 0x33C40, M2C_FIELD(arg0, u16 *, 0x1BC));
  }
}
