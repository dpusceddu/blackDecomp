/* Translation unit tu_1d97d0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_001DACE0(void *arg0);
extern s32 func_001DAD08(void *arg0);
extern s32 func_0031D528();
extern s32 func_00284298(s32);
extern s32 func_002842E8(s32);

s32 func_001D9C68(s32 arg0, s32 arg1)
{
  unsigned int new_var;
  s32 temp_3;
  if (func_001D9D00(arg0, arg1) != 0)
  {
    return 0;
  }
  temp_3 = M2C_FIELD(arg0, s32 *, 0x14);
  new_var = (arg1 ^ 0) * 8;
  return ((M2C_FIELD(arg0, s32 *, 0x10)) + (temp_3 * (*((s32 *) (((s8 *) (arg0 + new_var)) + 4))))) + ((temp_3 * (M2C_FIELD(arg0, s32 *, 0x24))) * arg1);
}

/* Assembly between the functions: func_001D9CD0 (48 bytes) */

s32 func_001D9D00(void *arg0, s32 arg1)
{
  s32 *new_var;
  s8 *new_var2;
  new_var = &(M2C_FIELD(arg0, s32 *, 0x24));
  new_var2 = (s8 *) (arg0 + (arg1 * 8));
  return (*((s32 *) (new_var2 + 4))) == (*new_var);
}

/* Assembly between the functions: func_001D9D20 (56 bytes), func_001D9D58 (104 bytes), func_001D9DC0 (120 bytes), func_001D9E38 (8 bytes), func_001D9E40 (104 bytes) */

void func_001D9EA8(void **arg0) {
    func_001DACE0(*arg0);
}

/* Assembly between the functions: func_001D9EC8 (120 bytes) */

void func_001D9F40(void **arg0) {
    func_001DAD08(*arg0);
}

s32 func_001D9F60(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x24) * M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0xE0);
}

/* Assembly between the functions: func_001D9F78 (592 bytes), func_001DA1C8 (1024 bytes), func_001DA5C8 (640 bytes), func_001DA848 (144 bytes), func_001DA8D8 (104 bytes), func_001DA940 (128 bytes), func_001DA9C0 (168 bytes) */

void func_001DAA68(void *arg0) {
    func_0031D528(arg0 + 0x18, M2C_FIELD(arg0, s32 *, 0xD0) * M2C_FIELD(arg0, s32 *, 0xDC), M2C_FIELD(arg0, s32 *, 0xC0), M2C_FIELD(arg0, s32 *, 0xD8));
    M2C_FIELD(arg0, s8 *, 0xF8) = 1;
    M2C_FIELD(arg0, s32 *, 0xD0) = (s32) ((M2C_FIELD(arg0, s32 *, 0xD0) + 1) % 2);
}

s32 func_001DAAD0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC4) == 0;
}

/* Assembly between the functions: func_001DAAE0 (64 bytes), func_001DAB20 (400 bytes) */

void func_001DACB0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xFA) = 0;
    M2C_FIELD(arg0, s8 *, 0xFB) = 0;
    M2C_FIELD(arg0, s8 *, 0xFC) = 0;
    func_00284298(M2C_FIELD(arg0, s32 *, 0xB0));
}

s32 func_001DACE0(void *arg0) {
    s32 temp_4;
    s32 var_2;

    temp_4 = M2C_FIELD(arg0, s32 *, 0xB0);
    var_2 = 0;
    if (temp_4 != 0) {
        var_2 = func_002842E8(temp_4);
    }
    return var_2;
}

s32 func_001DAD08(void *arg0)
{
  int new_var;
  s32 temp_5;
  s32 var_3;
  var_3 = 0;
  if (((u32) ((M2C_FIELD(arg0, s32 *, 0xB4)) - 6)) < 4U)
  {
    temp_5 = M2C_FIELD(arg0, s32 *, 0xF0);
    if (temp_5 >= 2)
    {
      var_3 = ((((s32) (temp_5 + (((u32) temp_5) >> 0x1F))) >> 1) * (new_var = 2)) * (M2C_FIELD(arg0, s32 *, 0xE0));
    }
    if ((M2C_FIELD(arg0, s32 *, 0xB0)) != 0)
    {
      var_3 += M2C_FIELD(arg0, s32 *, 0xE8);
    }
  }
  return var_3;
}

void func_001DAD60(void *arg0, s32 arg1) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0xA8);
    if (arg1 != 0) {
        M2C_FIELD(temp_4, s32 *, 0x54) = (s32) (M2C_FIELD(temp_4, s32 *, 0x54) | 2);
        return;
    }
    M2C_FIELD(temp_4, s32 *, 0x54) = (s32) (M2C_FIELD(temp_4, s32 *, 0x54) & 0xFFFFFFFD);
}
