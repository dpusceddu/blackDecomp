#include "auto/prelude.h"

extern s32 func_003700D0();
extern M2C_UNK D_0040BF00;

void func_003704B8(void) {
    func_003700D0();
}

void *func_003704D8(void *arg0, s32 arg1, s32 arg2)
{
  M2C_FIELD(arg0, s32 *, 0) = arg1;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_0040BF00;
  M2C_FIELD(arg0, s32 *, 8) = arg2;
  return arg0;
}
