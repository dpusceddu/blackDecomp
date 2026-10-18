#include "auto/prelude.h"

extern s32 func_001AFCC8();
extern s32 func_00125E40();
extern s32 func_001B6CF8();
extern s32 D_0040F4D8;
extern s32 func_001B37C8();

s32 func_00150738(void *arg0)
{
  u16 temp_3;
  func_001AFCC8(0x1A0 + arg0);
  func_00125E40(arg0);
  func_001B6CF8(D_0040F4D8 + 0x66290, arg0, 0);
  ;
  if ((M2C_FIELD(arg0, u16 *, 0x1BC)) != 0xFFFF)
  {
    func_001B37C8(D_0040F4D8 + 0x33C40, M2C_FIELD(arg0, u16 *, 0x1BC));
    temp_3 = M2C_FIELD(arg0, u16 *, 0x1BC);
  }
  return 1;
}
