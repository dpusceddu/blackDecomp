#include "auto/prelude.h"

extern s32 D_0049BB70;
extern s32 D_0049BB30;
extern s32 func_003909A8();
extern s32 func_00370168();
extern M2C_UNK D_00407418;
extern M2C_UNK D_0049BBB0;
extern M2C_UNK D_003EC990;

s32 * func_00390498(void) {
    if (D_0049BB70 == 0) {
        if (D_0049BB30 == 0) {
            func_003909A8();
            func_00370168(&D_0049BB30, &D_00407418, &D_0049BBB0);
        }
        func_00370168(&D_0049BB70, "Q24Kaim17CSphereConstraint", &D_0049BB30);
    }
    return &D_0049BB70;
}

void *func_00390520(void *arg0)
{
  void *temp_3;
  int new_var;
  temp_3 = arg0 + 4;
  M2C_FIELD(arg0, s32 *, 4) = 0;
  new_var = 0;
  *((M2C_UNK **) (((s8 *) arg0) + new_var)) = &D_003EC990;
  M2C_FIELD(temp_3, s32 *, 4) = 0;
  M2C_FIELD(temp_3, s32 *, 8) = 0;
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
  return arg0;
}
