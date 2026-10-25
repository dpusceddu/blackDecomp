#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00230B70();
extern s32 (*D_0043DA98)();
extern s32 func_00244CE8();
extern s32 func_00244CF8();

void func_00243060(s32 arg0, void **arg1, s32 arg2, void *arg3, s32 arg4)
{
  s32 temp_2;
  s32 temp_2_2;
  void *temp_3;
  void *temp_4;
  if (arg2 != 0)
  {
    temp_2 = M2C_FIELD(arg3, s32 *, 0x14);
    if (temp_2 != 0)
    {
      M2C_FIELD(arg3, s32 *, 0x14) = (s32) (arg2 + temp_2);
    }
    func_00230B70((M2C_FIELD(arg3, s32 *, 0x14)) + 8, arg2, arg3, arg4);
    temp_3 = *arg1;
    M2C_FIELD(temp_3, s32 *, 0x10) = (s32) (M2C_FIELD(arg3, s32 *, 0x14));
    M2C_FIELD(temp_3, s32 *, 0x14) = arg4;
    M2C_FIELD(temp_3, s32 *, 0xC) = arg2;
    *((s32 *) (((s8 *) (*arg1)) + 8)) = 3;
    temp_2 = M2C_FIELD(arg3, s32 *, 0x14);
    temp_2_2 = temp_2;
    if (temp_2_2 != 0)
    {
      M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_2_2 - arg2);
    }
    D_0043DA98(arg3);
  }
  temp_4 = *arg1;
  if ((temp_4 != NULL) && (func_00244CE8(temp_4) == 0))
  {
    func_00244CF8(*arg1);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_241ea0_243060", func_00243138);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_241ea0_243060", func_00243140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_241ea0_243060", func_00243BF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_241ea0_243060", func_00244108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_241ea0_243060", func_00244B90);
