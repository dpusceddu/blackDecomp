#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002050B0();
extern s32 func_00278F00();
extern void * D_003BDCC8;
extern s32 func_00204FF0();
extern s32 func_00276728();
extern s32 func_00208D00(M2C_UNK, M2C_UNK);
extern s32 D_003BE718;
extern s32 func_0020D188(s32);
extern s32 D_0040F544;

s32 func_00206F08(void) {
    func_002050B0();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00206F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00206F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00207020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00207110);

void func_002071C0(void) {

}

s32 func_002071C8(void *arg0) {
    func_00278F00(D_003BDCC8, 0, M2C_FIELD(arg0, s32 *, 0x18));
    return 1;
}

void func_002071F8(void) {
    func_00204FF0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00207218);

void func_002072A0(void *arg0) {
    func_00276728(M2C_FIELD(arg0, s32 *, 0x84), arg0 + 0x40, arg0 + 0x50, arg0 + 0x58, M2C_FIELD(arg0, s128 *, 0x20), M2C_FIELD(arg0, s32 *, 0x88), arg0 + 0x68, arg0 + 0x70, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002072E0);

void func_002075F0(void) {
    func_00204FF0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00207610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002076A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002076F8);

s32 func_00207938(void *arg0)
{
  s8 *new_var;
  new_var = (s8 *) arg0;
  func_002050B0();
  func_00278F00(*((void **) (new_var + 8)), *((s32 *) (new_var + 0x64)), *((s32 *) (new_var + 0x7C)));
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00207970);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00207978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00207B80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00208140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00208AF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00208BF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00208C58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00208C60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00208D00);

void func_002092B8(void) {
    func_00208D00(1, 0xFFFF);
}

void func_002092D8(s32 arg0) {
    D_003BE718 = arg0;
}

void func_002092E8(void) {
    func_0020D188(D_0040F544 + 0xE90);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00209310);
