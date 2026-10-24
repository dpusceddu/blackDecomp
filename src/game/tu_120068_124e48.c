#include "ps2/prelude.h"

extern s32 func_0026BBC0(s32, s32);
extern s32 D_003BCAA0;
extern volatile char D_003BC850;

void func_00124E48(void *arg0, s32 arg1) {
    func_0026BBC0(M2C_FIELD(arg0, s32 *, 0xC), (&D_003BCAA0)[arg1]);
}

void *func_00124E78(s32 arg0)
{
  return (arg0 * 0x94) + (&D_003BC850);
}
