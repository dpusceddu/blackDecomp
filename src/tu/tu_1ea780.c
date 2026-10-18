/* Translation unit tu_1ea780 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_001EBFC0(s32);
extern void * D_0040F510;
extern s32 func_0035C6EC();
extern s32 D_003C0E04;
extern s32 D_003BD9D8;
extern s32 D_003BD9D0;

s32 func_001EA7C0(void) {
    return 1;
}

/* Assembly between the functions: func_001EA7C8 (208 bytes), func_001EA898 (72 bytes), func_001EA8E0 (80 bytes), func_001EA930 (240 bytes), func_001EAA20 (168 bytes) */

void func_001EAAC8(void) {
    func_001EBFC0(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x24));
}

s32 func_001EAAF8(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = -1;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    return func_0035C6EC(arg0, 0, 0x40);
}

s32 func_001EAB30(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x40) = arg2;
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
    func_0035C6EC(arg0, 0, 0x40);
    return 1;
}

/* Assembly between the functions: func_001EAB60 (64 bytes) */

s32 func_001EABA0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = -1;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    func_0035C6EC(arg0, 0, 0x40);
    return 1;
}

void func_001EABD8(void *arg0, s32 arg1, s32 arg2)
{
  s8 *new_var;
  s32 var_8;
  void *var_4;
  void *var_7;
  var_4 = arg0;
  var_7 = (void *) 0;
  var_8 = 0;
  loop_1:
  var_7 = ((M2C_FIELD(var_4, s32 *, 4)) == 0) ? (var_4) : (var_7);

  if ((M2C_FIELD(var_4, s32 *, 0)) != arg1)
  {
    var_8 += 1;
    var_4 += 8;
    if (var_8 >= 8)
    {
      if (var_7 != NULL)
      {
        new_var = (s8 *) var_7;
        *((s32 *) (new_var + 0)) = arg1;
 do { } while (0);
        M2C_FIELD(var_7, s32 *, 4) = arg2;
      }
    }
    else
    {
      goto loop_1;
    }
  }
}

/* Assembly between the functions: func_001EAC18 (304 bytes), func_001EAD48 (1864 bytes) */

void func_001EB490(void) {
    if ((u32) (D_003C0E04 - D_003BD9D8) >= 2U) {
        D_003BD9D0 = D_003C0E04;
    }
    D_003BD9D8 = D_003C0E04;
}
