/* Translation unit apt/tu_230710 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern M2C_UNK D_003E1208;
extern s32 func_00244CE8();
extern void func_00244CF8();
extern void func_00233C60();
extern s32 func_00250198();
extern s32 D_0043DEE0;
extern s32 func_00241128(s32, M2C_UNK);

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

/* Assembly between the functions: func_00231308 (48 bytes) */

void func_00231338(s32 arg0) {
    func_00241128(arg0 + 0x24, 0);
}

/* Assembly between the functions: func_00231358 (600 bytes), func_002315B0 (512 bytes), func_002317B0 (8 bytes), func_002317B8 (912 bytes), func_00231B48 (264 bytes), func_00231C50 (728 bytes), func_00231F28 (120 bytes), func_00231FA0 (416 bytes), func_00232140 (64 bytes), func_00232180 (176 bytes), func_00232230 (320 bytes), func_00232370 (288 bytes) ... */

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
