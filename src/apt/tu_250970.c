#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern M2C_UNK D_003E1E78;
extern void func_002486D8();
extern s32 func_00387020();
extern s32 func_0024FA98();
extern s32 D_0043DEE4;

void func_00250970(void *arg0, s32 arg1)
{
  *((M2C_UNK **) (arg0 + 4)) = &D_003E1E78;
  func_002486D8(arg0 + 8, 2);
  func_00387020(arg0, 0);
  if (arg1 & 1)
  {
    func_0024FA98(D_0043DEE4, arg0, 0x24);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_250970", func_002509E0);
