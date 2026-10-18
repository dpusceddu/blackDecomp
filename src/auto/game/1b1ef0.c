#include "auto/prelude.h"

extern void *D_0040F4CC;
extern s32 func_001DE6F0();
extern s32 func_0016B7A0();

void func_001B1EF0(void)
{
  u8 sp[8];
  s32 temp_17;
  void *temp_16;
  temp_17 = M2C_FIELD(D_0040F4CC, s32 *, 0x8B00);
  temp_16 = D_0040F4CC + 0x2980;
  func_001DE6F0(sp, temp_16, temp_17);
 do { } while (0);
  func_0016B7A0(temp_16, temp_17);
}
