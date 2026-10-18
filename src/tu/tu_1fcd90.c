/* Translation unit tu_1fcd90 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_001FD440();
extern s32 func_001FD648(void *);
extern s32 func_001FBA78(void *);
extern s32 func_001F1C08();
extern s32 func_001F1F08();
extern s32 func_001F1E20();
extern M2C_UNK D_003F9DD8;

void func_001FD3E8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2DB) == 0) {
        func_001FD440();
    }
    if (M2C_FIELD(arg0, u8 *, 0x2D9) == 0) {
        func_001FD648(arg0);
    }
    func_001FBA78(arg0 + 0xE0);
}

s32 func_001FD438(void) {
    return 1;
}

/* Assembly between the functions: func_001FD440 (520 bytes), func_001FD648 (600 bytes) */

void func_001FD8A0(void *arg0)
{
  void *new_var3;
  void *new_var;
  void *new_var2;
  s32 *temp_3;
  u32 var_4;
  func_001F1C08();
  var_4 = 0;
  do
  {
    new_var3 = (new_var = arg0 + 0x70);
    new_var2 = new_var3 + (var_4 * 4);
    temp_3 = new_var2;
    var_4 = (var_4 + 1) & 0xFF;
    *temp_3 = 0;
  }
  while (var_4 < 2U);
  M2C_FIELD(arg0, s32 *, 0x78) = 0;
}

/* Assembly between the functions: func_001FD8F0 (136 bytes) */

void func_001FD978(void) {
    func_001F1F08();
}

s32 func_001FD998(s32 arg0) {
    func_001F1E20(arg0, (s32) &D_003F9DD8);
    return 1;
}
