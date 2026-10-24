#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0023E830();
extern M2C_UNK *func_00250058();
extern s32 D_0043DEE0;

void *func_0023E8B8(void *arg0, s32 *arg1, long arg2, s32 arg3, M2C_UNK *arg4)
{
  M2C_FIELD(arg0, s32 *, 0x10) = arg3;
  *((s32 **) (((s8 *) arg0) + 0)) = arg1;
 if ((arg1 != NULL) && ((*arg1) == 3)) { *((M2C_UNK **) (((s8 *) arg0) + 4)) = func_0023E830(func_00250058(D_0043DEE0, 0x1C), arg1, arg2, arg4);
  }
  else
  {
    *((M2C_UNK **) (((s8 *) arg0) + 4)) = (void *) 0;
  }
  if (arg1)
  {
  }
  M2C_FIELD(arg0, s32 *, 8) = 0;
  M2C_FIELD(arg0, s32 *, 0xC) = 0;
  return arg0;
}
