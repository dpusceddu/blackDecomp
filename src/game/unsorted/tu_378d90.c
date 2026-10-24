#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_0048EC20;
extern s32 func_0037B988();
extern s32 func_003230C0();
extern s32 func_0037B608();
extern s32 func_003110B0();
extern s32 func_00323188();

s32 func_00378D90(s32 arg0)
{
 do { } while (0);
  func_0037B2D0(arg0 + 0x104, arg0 + 0x16C);
  return arg0;
  if (((!arg0) && (!arg0)) && (!arg0))
  {
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00378DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00378DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00379298);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003792D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00379330);

void func_003793A0(void) {
    func_00311CA0(&D_0048EC20);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003793C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00379528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00379658);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00379A88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00379DF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037A160);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037A478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037AE38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B1D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B220);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B288);

s32 func_0037B2D0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_2;

    temp_2 = func_0037B988(arg0, arg1, M2C_FIELD(arg2, s32 *, 4));
    return func_003230C0((s32) temp_2, M2C_FIELD(temp_2, s32 *, 0x80), 2, arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B310);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B318);

void func_0037B450(void) {
    func_0037B608();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B518);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B740);

s32 func_0037B8A8(s32 arg0, s32 arg1) {
    *M2C_FIELD(arg0, void ***, 0x48) = M2C_FIELD(arg0, void **, 0x44);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x48);
    return func_003110B0(arg0, M2C_FIELD(arg1, s32 *, 0x54), M2C_FIELD(arg1, s32 *, 0x58));
}

s32 func_0037B8E8(s32 arg0, s32 arg1) {
    return func_00323188(arg0, M2C_FIELD(arg0, s32 *, 0x40), 2, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037B988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037BA00);
