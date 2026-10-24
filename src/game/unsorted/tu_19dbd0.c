#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern s32 func_001880D8();
extern s32 func_001823B0();
extern s32 func_001829A8();
extern s32 func_001829E8();
extern s32 func_00181028();
extern s32 func_00180FE0();
extern s32 func_00193A28();
extern f32 func_001891A8();
extern s32 func_001863A0();
extern s32 func_0019DFE8();
extern s32 func_0019DF50();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019DBD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019DD08);

void func_0019DF10(void **arg0)
{
  int new_var2;
  void *temp_3;
  int new_var;
  func_00193988();
  new_var = 0;
  new_var2 = 0x290;
  temp_3 = *arg0;
  if ((*((u8 *) (temp_3 + new_var2))) != new_var)
  {
    func_001880D8(temp_3 + new_var2);
  }
}

s32 func_0019DF50(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x44) != 0) {
        M2C_FIELD(arg0, s8 *, 0x45) = 0;
        return 1;
    }
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x694), s8 *, 0x30) = 0;
    if ((func_001823B0(M2C_FIELD(arg0, void **, 0) + 0x810, M2C_FIELD(arg0, s128 *, 0x10), 0) == 0) || (func_001829A8(M2C_FIELD(arg0, void **, 0) + 0x810) == 0) || (func_001829E8(M2C_FIELD(arg0, void **, 0) + 0x810) != 0)) {
        M2C_FIELD(arg0, s8 *, 0x45) = 0;
        M2C_FIELD(arg0, u8 *, 0x44) = 1U;
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019DFE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019E060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019E2E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019E318);

void func_0019E380(void **arg0)
{
  unsigned char new_var2;
  void *temp_3;
  s8 *new_var;
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
  new_var2 = func_00181028((*arg0) + 0x140) != 0;
  if (new_var2)
  {
    func_00180FE0((*arg0) + 0x140);
  }
  func_00193A28(arg0, 3, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019E3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019E510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019EA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019EC00);

void func_0019EE30(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x45) != 0) {
        if (func_001891A8(M2C_FIELD(arg0, s32 *, 0) + 0x150) < 2.0f) {
            goto block_3;
        }
    } else {
block_3:
        func_001863A0(M2C_FIELD(arg0, s32 *, 0) + 0x90);
        func_0019DFE8(arg0);
    }
    func_0019DF50(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019EEA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019EF08);
