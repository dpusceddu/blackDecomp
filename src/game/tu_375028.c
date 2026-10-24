#include "ps2/prelude.h"

extern s32 func_00322DA8();
extern M2C_UNK D_003D0660;

s32 func_00375028(s32 arg0, void *arg1)
{
  func_00322DA8();
  M2C_FIELD(arg1, s32 *, 4) = (M2C_FIELD(arg1, s32 *, 0) = 1);
  *((M2C_UNK **) (((s8 *) arg1) + 0x1C)) = &D_003D0660;
  return arg0;
}
