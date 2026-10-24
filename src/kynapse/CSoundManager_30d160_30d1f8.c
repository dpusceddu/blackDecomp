#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern M2C_UNK D_003F1220;

void *func_0030D1F8(void *arg0)
{
  M2C_FIELD(arg0, s32 *, 0x48) = -1;
  *((M2C_UNK **) (((s8 *) arg0) + 0)) = &D_003F1220;
  M2C_FIELD(arg0, s32 *, 4) = 0;
  M2C_FIELD(arg0, s32 *, 8) = 0;
  M2C_FIELD(arg0, s32 *, 0x44) = -1;
  M2C_FIELD(arg0, s32 *, 0x48) = -1;
  M2C_FIELD(arg0, s32 *, 0x4C) = 0;
  return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030D228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030D370);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030D5F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030D770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030D8D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030DAA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030DC28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030DDE8);

#include "ps2/recovered_types.h"
extern void * func_002E7610(void *, s8 *, s32, s32, s32, s32);
extern M2C_UNK D_00455D00;
extern void * func_0030D160();
extern M2C_UNK D_003E5E40;
extern M2C_UNK * D_00455E10;

void * func_0030DFC0(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = (M2C_UNK *)0xFFFF;
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            return func_002E7610(&D_00455D00, "CSoundManager", (s32) func_0030D160, 0, 1, 0);
        }
        var_2 = &D_003E5E40;
        D_00455E10 = &D_003E5E40;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_2;
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E100);

s32 func_0030E128(void *arg0)
{
  s32 temp_8;
  temp_8 = M2C_FIELD(arg0, s32 *, 8);
  if (temp_8 > 0)
  {
    if (arg0)
    {
      return temp_8 >= (((((((M2C_FIELD(arg0, s32 *, 0xC)) + (M2C_FIELD(arg0, s32 *, 0x10))) + (M2C_FIELD(arg0, s32 *, 0x14))) + (M2C_FIELD(arg0, s32 *, 0x18))) + (M2C_FIELD(arg0, s32 *, 0x1C))) + (M2C_FIELD(arg0, s32 *, 0x20))) + (M2C_FIELD(arg0, s32 *, 0x24)));
    }
    else
    {
      return temp_8 >= (((((((M2C_FIELD(arg0, s32 *, 0xC)) + (M2C_FIELD(arg0, s32 *, 0x10))) + (M2C_FIELD(arg0, s32 *, 0x14))) + (M2C_FIELD(arg0, s32 *, 0x18))) + (M2C_FIELD(arg0, s32 *, 0x1C))) + (M2C_FIELD(arg0, s32 *, 0x20))) + (M2C_FIELD(arg0, s32 *, 0x24)));
      if (!arg0)
      {
      }
    }
  }
  return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E180);

void func_0030E278(void *arg0, s32 arg1, s32 arg2) {
    s32 *temp_2;
    s32 temp_3;
    s32 temp_5;

    if (arg2 != -1) {
        temp_5 = M2C_FIELD(arg0, s32 *, 4);
        M2C_FIELD(((arg2 * 0x24) + temp_5), s32 *, 0x20) = (s32) M2C_FIELD(((arg1 * 0x24) + temp_5), s32 *, 0x20);
    } else {
        M2C_FIELD(arg0, s32 *, 0x48) = (s32) M2C_FIELD(((arg1 * 0x24) + M2C_FIELD(arg0, s32 *, 4)), s32 *, 0x20);
    }
    temp_3 = arg1 * 0x24;
    M2C_FIELD((temp_3 + M2C_FIELD(arg0, s32 *, 4)), s32 *, 0x20) = (s32) M2C_FIELD(arg0, s32 *, 0x44);
    M2C_FIELD(arg0, s32 *, 0x44) = arg1;
    temp_2 = func_0030E6B8(arg0, M2C_FIELD((temp_3 + M2C_FIELD(arg0, s32 *, 4)), u32 *, 0x14));
    if (temp_2 != NULL) {
        *temp_2 -= 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E400);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E4B8);

s32 func_0030E550(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x48);
}

s32 func_0030E558(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x44);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E5A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E6B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E8D8);

void func_0030E988(void) {
    func_0030DFC0(1, 0xFFFF);
}

void func_0030E9A8(void) {
    func_0030DFC0(0, 0xFFFF);
}
