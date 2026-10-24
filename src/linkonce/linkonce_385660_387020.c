#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern M2C_UNK D_003E23C8;
extern s32 func_00107D48();
extern u16 D_003BFAF8;
extern s32 func_00253FF0();
extern s32 func_00250198();
extern s32 D_0043DEE0;
extern s32 func_0035CA74(s32);
extern s32 func_00250058(s32, s32);
extern s32 func_0035C6EC(s32, M2C_UNK, s32);
extern M2C_UNK D_003E2450;
extern s32 func_002486D8();
extern s32 func_0024FA98();
extern void *D_0043DEE4;

s32 func_00387020(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E23C8;
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E23C8;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387050);

void func_00387058(s32 *arg0, s32 arg1)
{
  int new_var;
  new_var = (arg1 != 0) & 0xFFFFFFFF;
  *arg0 = ((*arg0) & 0xFEFFFFFF) | ((new_var << 0x18) ^ 0);
}

u32 func_00387080(u32 *arg0) {
    return (u32) *arg0 >> 0x19;
}

void func_00387090(s32 *arg0, u32 arg1) {
    u32 var_5;

    var_5 = arg1;
    if (var_5 >= 0x1000U) {
        var_5 = 0xFFF;
        *arg0 = (*arg0 & 0xFEFFFFFF) | 0x01000000;
    }
    *arg0 = (*arg0 & 0xFFFC003F) | ((var_5 & 0xFFF) << 6);
}

void func_003870E0(s32 *arg0, s32 arg1) {
    *arg0 = (*arg0 & 0x01FFFFFF) | (arg1 << 0x19);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387120);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387140);

void func_00387170(s32 *arg0) {
    *arg0 |= 4;
}

void func_00387180(s32 *arg0) {
    *arg0 &= ~4;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387198);

s32 func_003871C0(s32 *arg0) {
    return (((s32) *arg0 >> 4) & 1) ^ 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003871D8);

s32 func_003872A8(s32 *arg0) {
    return *arg0 == (s32) &D_003BFAF8;
}

u16 ** func_003872C0(u16 **arg0) {
    *arg0 = &D_003BFAF8;
    D_003BFAF8 += 1;
    return arg0;
}

s32 func_003872E0(s32 arg0) {
    func_00253FF0();
    return arg0;
}

u16 ** func_00387308(u16 **arg0, u16 **arg1) {
    u16 *temp_6;

    temp_6 = *arg1;
    *arg0 = temp_6;
    *temp_6 += 1;
    return arg0;
}

void func_00387328(u16 **arg0, s32 arg1)
{
  u16 *temp_5;
  u16 temp_2;
  int new_var2;
  s8 *new_var;
  new_var2 = 4;
  temp_5 = *arg0;
  new_var = (s8 *) temp_5;
  temp_2 = (*((u16 *) (new_var + 0)) = (0, (*((u16 *) (new_var + 0))) - 1));
  if (!(temp_2 & 0xFFFF))
  {
    temp_2 = *((u16 *) (new_var + new_var2));
    func_00250198(D_0043DEE0, temp_5, temp_2 + 9);
  }
  if (arg1 & 1)
  {
    func_00107D48(arg0);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387398);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387410);

s32 func_00387458(s32 *arg0) {
    return func_0035CA74(*arg0 + 8) == 0;
}

s32 func_00387480(s32 *arg0) {
    return func_0035CA74(*arg0 + 8) != 0;
}

void func_003874A8(u16 **arg0)
{
  u16 *temp_5;
  s8 *new_var2;
  s8 *new_var;
  int new_var3;
  u16 temp_2;
  temp_5 = *arg0;
  new_var2 = ((s8 *) temp_5) - -0;
  new_var = (s8 *) temp_5;
  temp_2 = (*((u16 *) new_var2) = (*((u16 *) (new_var + ((0, 0))))) - 1);
  if (!(temp_2 & 0xFFFF))
  {
    new_var3 = (M2C_FIELD(temp_5, u16 *, 4)) + 9;
    func_00250198(D_0043DEE0, temp_5, new_var3);
  }
  *arg0 = &D_003BFAF8;
  D_003BFAF8 += 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003875D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003875E8);

void func_00387C70(void *arg0) {
    s32 temp_2;

    temp_2 = func_00250058(D_0043DEE0, M2C_FIELD(arg0, s32 *, 0) * 8);
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    func_0035C6EC(temp_2, 0, M2C_FIELD(arg0, s32 *, 0) * 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387CC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00387D08);

void func_00387D50(void *arg0, s32 arg1)
{
  s32 new_var;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E2450;
  new_var = arg1;
  do
  {
    *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E2450;
 do { func_002486D8(arg0 + 8, 2); } while (0);
  }
  while (0);
  func_00387020(arg0, 0);
  if ((new_var & 1) != 0U)
  {
    func_0024FA98(D_0043DEE4, arg0, 0x20);
  }
}

s32 func_00387DC0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_4 < M2C_FIELD(arg0, s32 *, 0)) {
        temp_2_2 = M2C_FIELD(arg0, s32 *, 8);
        M2C_FIELD(((temp_4 * 4) + temp_2_2), s32 *, 0) = arg1;
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_4 + 1);
        return temp_2_2;
    }
    temp_2 = M2C_FIELD(arg1, s32 *, 0) & ~4;
    M2C_FIELD(arg1, s32 *, 0) = temp_2;
    return temp_2;
}
