#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00201108();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F42C8);

void func_001F43F0(void *arg0, f32 fparg0)
{
  f32 temp_f0;
  void *temp_2;
  if ((M2C_FIELD(arg0, u8 *, 0x248)) != 0)
  {
    temp_f0 = (M2C_FIELD(arg0, f32 *, 0x244)) + fparg0;
    M2C_FIELD(arg0, f32 *, 0x244) = temp_f0;
    if (temp_f0 > 1.0f)
    {
      temp_2 = arg0 + 0x20;
      M2C_FIELD(arg0, u8 *, 0x248) = 0U;
      M2C_FIELD(temp_2, f32 *, 0x7C) = (M2C_FIELD(temp_2, f32 *, 0x78) = 0.3f);
    }
  }
  func_00201108(arg0 + 0x20);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F4458);
