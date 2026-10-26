#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/resource_pool.hpp"

extern char D_0049A858;

Recovered_FloatPair* FloatPairOutput_At(s32 index) {
    return (Recovered_FloatPair*)((index * 8) + &D_0049A858);
}

void func_00281200(void *arg0, f32 fparg0)
{
  s8 *new_var;
  new_var = ((s8 *) arg0) + 0x30;
  if (fparg0 > 0.0f)
  {
    M2C_FIELD(arg0, f32 *, 0x1C) = (M2C_FIELD(arg0, f32 *, 0x20) = fparg0);
    *((u16 *) new_var) = (u16) ((*((u16 *) new_var)) | 4);
  }
}
