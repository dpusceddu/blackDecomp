#include "auto/prelude.h"

extern void func_00181AD0(void *arg0, s32 arg1);

void func_001834B0(s32 *arg0) {
    func_00181AD0(*arg0 + 0xEC0, 0xD);
}

void func_001834D8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x30) = arg1;
}

s32 func_001834E0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x30);
}

s32 func_001834E8(void *arg0) {
    s32 var_2;

    var_2 = M2C_FIELD(arg0, s32 *, 4);
    if (var_2 < 0) {
        var_2 = M2C_FIELD(arg0, s32 *, 8);
    }
    return var_2;
}

s32 func_00183500(void *arg0)
{
  void *temp_2;
  temp_2 = *((void **) (((s8 *) arg0) + 0x30));
  if (temp_2 == NULL)
  {
    return 0;
  }
  if (arg0 || temp_2)
  {
    return *((s32 *) (((s8 *) temp_2) + (0x10 & 0xFFFFFFFFFFFFFFFFu)));
  }
  else
  {
    return M2C_FIELD(temp_2, s32 *, 0x10);
  }
}
