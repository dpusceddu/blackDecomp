#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_003E1208;
extern s32 func_00244CE8();
extern void func_00244CF8();
extern void func_00233C60();
extern s32 func_00250198();
extern s32 D_0043DEE0;
extern s32 func_00241128(s32, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00230710);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00230B70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00230BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00230C00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00230C40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_002311F0);

void func_00231288(u16 *arg0, s32 arg1) {
    u16 *temp_4;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E1208;
    temp_4 = M2C_FIELD(arg0, u16 **, 0x34);
    if (temp_4 != NULL) {
        if (func_00244CE8(temp_4) == 0) {
            func_00244CF8(M2C_FIELD(arg0, u16 **, 0x34));
        }
    }
    func_00233C60(arg0, 0);
    if (arg1 & 1) {
        func_00250198(D_0043DEE0, arg0, 0x38);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00231308);

void func_00231338(s32 arg0) {
    func_00241128(arg0 + 0x24, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00231358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_002315B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_002317B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_002317B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00231B48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00231C50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00231F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00231FA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232180);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232230);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232370);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232490);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232638);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232878);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232A00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232AA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232B78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232C48);

s32 func_00232E00(void *arg0)
{
  s32 temp_3;
  temp_3 = ((s32) (((M2C_FIELD(arg0, s32 *, 8)) - (M2C_FIELD(arg0, s32 *, 4))) * 0xCCCCCCCD)) >> 2;
  if (temp_3 < 0)
  {
    if (temp_3)
    {
      return temp_3 + (M2C_FIELD(arg0, s32 *, 0x10));
    }
    else
    {
      return temp_3 + (M2C_FIELD(arg0, s32 *, 0x10));
    }
  }
  if (!temp_3)
  {
  }
  return temp_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232E40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/apt/tu_230710", func_00232E90);
