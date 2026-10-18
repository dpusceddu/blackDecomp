#include "auto/prelude.h"

extern s32 D_004549C4;
extern s32 func_003071A8();

s32 func_0030B7A8(s32 arg0)
{
  s32 *var_2;
  var_2 = &D_004549C4;
  if ((M2C_FIELD(arg0, s32 *, 0x1C)) & D_004549C4)
  {
    var_2 = func_003071A8();
    return (s32) var_2;
    var_2 = &D_004549C4;
  }
}
