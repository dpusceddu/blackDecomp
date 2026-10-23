#include "auto/prelude.h"
#include "mod/animation/instance.h"
#include "types_ghidra.h"

extern s32 func_00347CA0();
extern s32 func_003461E0();
extern s32 func_0034F080();
extern s32 *func_003489A8();
extern s32 func_003511D0();

s32 func_00347D48(s32 arg0, s32 arg1) {
    return func_00347CA0(arg0, arg1, 1);
}

void func_00347D68(void *arg0)
{
  s32 temp_17;
  s8 *new_var2;
  f32 *new_var;
  if ((((BkModAnimationInstancePS2*)arg0)->graph) != 0)
  {
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((M2C_FIELD(arg0, s32 *, 0)) | 0x800000);
    func_003461E0();
    temp_17 = func_0034F080(arg0, 0);
    new_var2 = ((s8 *) arg0) + 0;
    *((s32 *) new_var2) = (s32) ((*((s32 *) new_var2)) & 0xFF7FFFFF);
    new_var = &((BkModAnimationInstancePS2*)arg0)->root.quaternion[3];
    if (temp_17 != 0)
    {
      ((BkModAnimationInstancePS2*)arg0)->root.translation[0] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.translation[1] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.translation[2] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.quaternion[0] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.quaternion[1] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.quaternion[2] = 0.0f;
      ((BkModAnimationInstancePS2*)arg0)->root.translation[3] = 1.0f;
      *new_var = 1.0f;
      if (func_003489A8(arg0) != NULL)
      {
        func_003511D0(arg0, temp_17);
      }
    }
  }
}
