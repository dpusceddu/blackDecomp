/* Translation unit tu_17b0e0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00174210();
extern s32 func_00174218();
extern void func_0017B3C0(void *arg0);
extern s32 func_0017B930();
extern s32 func_0017B998(s32);
extern s32 *func_0017B6F8();
extern s32 func_00179650();
extern void *D_0040F4D4;
extern s32 func_00174228();
extern s32 func_001742B8();
extern s32 func_00174320();

s32 func_0017B668(s32 arg0) {
    return func_00174210(arg0, 0x20);
}

s32 func_0017B688(void *arg0) {
    func_00174218();
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    func_0017B3C0(arg0 + 0x10);
    return 1;
}

void func_0017B6C0(s32 arg0) {
    func_0017B930();
    func_0017B998(arg0);
}

s32 func_0017B6F0(void) {
    return 1;
}

/* Assembly between the functions: func_0017B6F8 (216 bytes), func_0017B7D0 (216 bytes) */

s32 func_0017B8A8(void)
{
  s32 *temp_2;
  temp_2 = func_0017B6F8();
  if (temp_2 != NULL)
  {
    if (temp_2)
    {
      return func_00179650(D_0040F4D4, *temp_2);
    }
    else
    {
      return func_00179650(D_0040F4D4, *temp_2);
    }
  }
  return 0;
}

void func_0017B8E8(void) {
    func_00174228();
}

void func_0017B908(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, s32 *, 0xC) == arg1) {
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
    }
    func_001742B8();
}

/* Assembly between the functions: func_0017B930 (104 bytes), func_0017B998 (104 bytes) */

void func_0017BA00(void *arg0, s32 arg1) {
    s32 *temp_2;

    temp_2 = M2C_FIELD(arg0, s32 **, 0xC);
    if ((temp_2 != NULL) && (*temp_2 == arg1)) {
        M2C_FIELD(arg0, s32 **, 0xC) = NULL;
    }
    func_00174320();
}

void func_0017BA38(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xC) != 0) {
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
    }
    func_0017B3C0(arg0 + 0x10);
}
