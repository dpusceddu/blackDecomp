#include "auto/prelude.h"

extern s32 func_00215250();
extern s32 func_0020E8C8();

void func_00105268(void *arg0)
{
  s32 temp_3;
  int new_var;
  new_var = 0;
  temp_3 = M2C_FIELD(arg0, s32 *, 0x44);
  if ((temp_3 != new_var) && (temp_3 == 1))
  {
    func_00215250(arg0 + 0x38);
  }
  func_0020E8C8();
}
