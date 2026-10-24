#include "ps2/prelude.h"

extern unsigned long D_003E18F8;
extern void func_00387328();
extern M2C_UNK D_003E1E78;
extern s32 func_002486D8();
extern s32 func_00387020();
extern s32 func_0024FA98();
extern s32 D_0043DEE4;

void func_00386100(void *arg0, s32 arg1)
{
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E18F8;
  func_00387328(arg0 + 0x20, 2);
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
  func_002486D8(arg0 + 8, 2);
  func_00387020(arg0, 0);
  if ((arg1 & 1) != 0U)
  {
    func_0024FA98(D_0043DEE4, arg0, 0x40);
  }
}
