#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_003E1E78;
extern s32 func_002486D8();
extern s32 func_00387020();
extern s32 func_0024FA98();
extern s32 D_0043DEE4;
extern M2C_UNK D_003E1258;
extern s32 func_00250198();
extern s32 D_0043DEE0;
extern s32 func_00240798();
extern M2C_UNK D_003E12F8;
extern s32 func_00107D48();
extern s32 func_00241228(s32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00232F90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002330D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002330D8);

void func_00233150(void *arg0, s32 arg1)
{
  s32 *new_var;
  *((M2C_UNK **) (((s8 *) arg0) + ((unsigned short) 4))) = &D_003E1E78;
  func_002486D8(arg0 + 8, 2);
  new_var = &D_0043DEE4;
 do { } while (0);
  func_00387020(arg0, 0);
  if (arg1 & 1)
  {
    func_0024FA98(*new_var, arg0, 0x2C);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002331C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00233278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00233300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002333E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002334A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002334E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002334F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00233670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002337E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00233818);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00233890);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002339F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00233A80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00233B30);

s32 func_00233C60(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 var_2;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E1258;
    if (M2C_FIELD(arg0, s32 *, 0x2C) == 1) {
        func_00250198(D_0043DEE0, M2C_FIELD(arg0, s32 *, 8), 0x3C);
    }
    func_00240798(arg0 + 0x24, 2);
    temp_4 = M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    if (temp_4 != 0) {
        func_002486D8(temp_4, 3);
    }
    var_2 = arg1 & 1;
    if (var_2 != 0) {
        var_2 = func_00107D48(arg0);
    }
    return var_2;
}

void func_00233CF8(s32 arg0) {
    func_00241228(arg0 + 0x24);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00233D18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002340D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00234398);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00234468);
