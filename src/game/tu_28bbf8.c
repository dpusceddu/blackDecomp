#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_0028BD68();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028BBF8);

s32 func_0028BC10(s32 arg0)
{
  s32 temp_2;
  s32 var_18;
  u32 var_17;
  temp_2 = M2C_FIELD(arg0, s32 *, 0x14);
  if (temp_2 != 0)
  {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (temp_2 + arg0);
  }
  ;
  temp_2 = M2C_FIELD(arg0, u16 *, 0x10);
  var_17 = 0;
  if (temp_2 != 0)
  {
    var_18 = 0;
    do
    {
      if (temp_2)
      {
        var_17 += 1;
        func_0028BD68((M2C_FIELD(arg0, s32 *, 0x14)) + var_18);
        do
        {
          temp_2 = var_17 < ((u16) (M2C_FIELD(arg0, u16 *, 0x10)));
        }
        while (0);
        var_18 += 0x18;
      }
      else
      {
        var_17 += 1;
        func_0028BD68((M2C_FIELD(arg0, s32 *, 0x14)) + var_18);
        temp_2 = var_17 < ((u16) (M2C_FIELD(arg0, u16 *, 0x10)));
        var_18 += 0x18;
      }
    }
    while (temp_2 != 0);
  }
  return (s32) temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028BC80);
