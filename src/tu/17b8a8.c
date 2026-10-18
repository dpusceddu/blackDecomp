#include "auto/prelude.h"

extern s32 *func_0017B6F8();
extern s32 func_00179650();
extern void *D_0040F4D4;
extern s32 func_00174228();
extern s32 func_001742B8();

s32 func_0017B8A8(void)
{
  s32 *temp_2;
  temp_2 = func_0017B6F8();
  if (temp_2 != NULL)
  {
    if (temp_2)
    {
      return func_00179650(D_0040F4D4, *temp_2);
    }
    else
    {
      return func_00179650(D_0040F4D4, *temp_2);
    }
  }
  return 0;
}

void func_0017B8E8(void) {
    func_00174228();
}

void func_0017B908(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, s32 *, 0xC) == arg1) {
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
    }
    func_001742B8();
}
