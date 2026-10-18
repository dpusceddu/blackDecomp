#include "auto/prelude.h"

extern M2C_UNK D_003E1E78;
extern s32 func_002486D8();
extern s32 func_00387020();
extern s32 func_0024FA98();
extern void *D_0043DEE4;

void func_00251F70(void *arg0, s32 arg1)
{
  int new_var;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
  new_var = 0x30;
  func_002486D8(arg0 + 8, 2);
  if ((arg1 && arg1) && arg1)
  {
  }
 do { } while (0);
  func_00387020(arg0, 0);
  if (arg1 & 1)
  {
    func_0024FA98(D_0043DEE4, arg0, new_var);
  }
}
