/* Translation unit kynapse/CSoundManager_30d160 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern M2C_UNK D_003F1220;
extern s32 func_0030DFC0();

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

/* Assembly between the functions: func_0030D228 (328 bytes), func_0030D370 (648 bytes), func_0030D5F8 (376 bytes), func_0030D770 (352 bytes), func_0030D8D0 (472 bytes), func_0030DAA8 (384 bytes), func_0030DC28 (448 bytes), func_0030DDE8 (472 bytes), func_0030DFC0 (96 bytes), func_0030E020 (224 bytes), func_0030E100 (40 bytes) */

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

/* Assembly between the functions: func_0030E180 (248 bytes) */

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

/* Assembly between the functions: func_0030E320 (224 bytes), func_0030E400 (184 bytes), func_0030E4B8 (152 bytes) */

s32 func_0030E550(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x48);
}

s32 func_0030E558(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x44);
}

/* Assembly between the functions: func_0030E560 (64 bytes), func_0030E5A0 (280 bytes), func_0030E6B8 (112 bytes), func_0030E728 (112 bytes), func_0030E798 (320 bytes), func_0030E8D8 (176 bytes) */

void func_0030E988(void) {
    func_0030DFC0(1, 0xFFFF);
}

void func_0030E9A8(void) {
    func_0030DFC0(0, 0xFFFF);
}
