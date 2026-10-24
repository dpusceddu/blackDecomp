#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003EFCC0;
extern M2C_UNK D_003EFCD0;
extern M2C_UNK D_003EFD20;
extern M2C_UNK D_003EFD70;
extern M2C_UNK D_003EFDC0;

#include "ps2/recovered_types.h"
extern s32 func_002E27F8(void *, void *, s32, s32, f32);

s32 func_00305110(void *arg0, s32 arg1) {
    return func_002E27F8(arg0 + 0xF4, arg1, M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x14), 2, M2C_FIELD(M2C_FIELD(arg0, void **, 0x160), f32 *, 4));
}

s32 func_00305148(void) {
    return 1;
}

#include "ps2/recovered_types.h"
extern s32 func_002E27F8(void *, void *, s32, s32, f32);

s32 func_00305150(void *arg0, s32 arg1) {
    return func_002E27F8(arg0 + 0xF4, arg1, M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x14), 2, M2C_FIELD(M2C_FIELD(arg0, void **, 0x160), f32 *, 4));
}

s32 func_00305188(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00305190);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00305200);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00305250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003052A0);

#include "ps2/recovered_types.h"
extern s32 func_002FB9D0(void *, void *, void *, s32, s32, f32);

s32 func_00305340(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    return func_002FB9D0(M2C_FIELD(arg0, void **, 0x64), arg1, M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x14), arg2 & 0xFF, arg3 & 0xFF, M2C_FIELD(arg0, f32 *, 0x38));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00305378);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003053C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003053F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00305428);

void func_00305438(void) {
    D_003EFCC0 = 0;
}

void func_00305448(void)
{
  M2C_UNK *new_var;
  new_var = &D_003EFCD0;
  M2C_FIELD(new_var, s32 *, 0x40) = 0;
  M2C_FIELD(new_var, s8 *, 0x44) = 0;
}

void func_00305460(void)
{
  M2C_UNK *new_var;
  new_var = &D_003EFD20;
  M2C_FIELD(new_var, s32 *, 0x40) = 0;
  M2C_FIELD(new_var, s8 *, 0x44) = 0;
}

void func_00305478(void)
{
  M2C_UNK *new_var;
  new_var = &D_003EFD70;
  M2C_FIELD(new_var, s32 *, 0x40) = 0;
  M2C_FIELD(new_var, s8 *, 0x44) = 0;
}

void func_00305490(void)
{
  M2C_UNK *new_var;
  new_var = &D_003EFDC0;
  M2C_FIELD(new_var, s32 *, 0x40) = 0;
  M2C_FIELD(new_var, s8 *, 0x44) = 0;
}
