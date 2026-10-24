#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00193980();
extern s32 func_0019B6D8();
extern s32 func_00193988();
extern s32 func_00181028();
extern s32 func_00180FE0();
extern s32 func_001880D8();

s32 func_0019B3B8(s32 arg0) {
    void **temp_16;

    temp_16 = arg0;
    func_00193980();
    M2C_FIELD(M2C_FIELD(*temp_16, void **, 0x694), s8 *, 0x35) = 1;
    return func_0019B6D8((s32) temp_16);
}

void func_0019B3F8(void **arg0)
{
  s8 *new_var;
  void *temp_3;
  func_00193988();
  if (func_00181028((*arg0) + 0x140) != 0)
  {
    temp_3 = (*arg0) + 0x140;
    func_00180FE0(temp_3);
  }
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019B458);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019B580);
