#include "auto/prelude.h"

extern s32 func_001DD6C0();

void func_001EC690(void *arg0)
{
  s32 temp_3;
  temp_3 = M2C_FIELD(arg0, s32 *, 0x28);
  if (temp_3 < 4)
  {
    if (temp_3 < 2)
    {
      if (temp_3 != 1)
      {
        if (temp_3)
        {
        }
        return;
      }
      goto block_5;
    }
  }
  else
    if (temp_3 == 4)
  {
    block_5:
    func_001DD6C0(M2C_FIELD(arg0, s32 *, 0x1C));

    M2C_FIELD(arg0, s32 *, 0x28) = 2;
  }
}
