/* Translation unit animation/tu_34b498 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00347430(s32, s32, s32);
extern s32 func_0034B910();
extern s32 func_0034E220(s32, void *, void *, M2C_UNK, f32);
extern f32 * func_003500E0(void *arg0, s32 arg1);
extern f32 func_0034E530();
extern s32 func_0034DE98();
extern f32 func_00348A38();
extern f32 * func_003500E0();
extern f32 *func_003500E0();

s32 func_0034B5A8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x14);
}

/* Assembly between the functions: func_0034B5B0 (304 bytes), func_0034B6E0 (560 bytes), func_0034B910 (320 bytes), func_0034BA50 (480 bytes), func_0034BC30 (904 bytes), func_0034BFB8 (48 bytes), func_0034BFE8 (224 bytes), func_0034C0C8 (96 bytes), func_0034C128 (1712 bytes), func_0034C7D8 (192 bytes), func_0034C898 (48 bytes), func_0034C8C8 (160 bytes) ... */

s32 func_0034CBF8(void) {
    return 0;
}

/* Assembly between the functions: func_0034CC00 (544 bytes), func_0034CE20 (544 bytes), func_0034D040 (112 bytes), func_0034D0B0 (304 bytes), func_0034D1E0 (288 bytes), func_0034D300 (560 bytes), func_0034D530 (520 bytes), func_0034D738 (256 bytes), func_0034D838 (184 bytes) */

s32 func_0034D8F0(void *arg0)
{
  s32 (*temp_2)();
  s32 new_var;
  temp_2 = *((s32 (**)()) (((s8 *) arg0) + 0x9C0));
  if (temp_2 == NULL)
  {
    return 0;
  }
  if (arg0)
  {
    new_var = temp_2();
    return new_var;
  }
  else
  {
    new_var = temp_2();
    return new_var;
  }
}

void func_0034D920(s32 arg0, s32 arg1) {
    func_00347430(arg0, func_0034B910(), arg1);
}

/* Assembly between the functions: func_0034D960 (80 bytes), func_0034D9B0 (584 bytes), func_0034DBF8 (56 bytes), func_0034DC30 (56 bytes), func_0034DC68 (96 bytes), func_0034DCC8 (112 bytes), func_0034DD38 (152 bytes), func_0034DDD0 (200 bytes), func_0034DE98 (56 bytes), func_0034DED0 (160 bytes), func_0034DF70 (240 bytes), func_0034E060 (248 bytes) ... */

void func_0034E328(s32 arg0, void *arg1, void *arg2) {
    func_0034E220(arg0, arg1, arg2, 1, *func_003500E0(arg2, M2C_FIELD(M2C_FIELD(arg1, void **, 8), s32 *, 0xC)));
}

/* Assembly between the functions: func_0034E388 (40 bytes) */

f32 func_0034E3B0(void) {
    return 1.0f;
}

/* Assembly between the functions: func_0034E3C0 (88 bytes) */

f32 func_0034E418(s32 *arg0, void *arg1, s32 *arg2) {
    f32 temp_f20;

    if (M2C_FIELD(arg1, s8 *, 1) <= 0) {
        return 1.0f;
    }
    temp_f20 = func_0034E530(arg0, M2C_FIELD(arg1, s32 **, 0x10), arg2);
    if (M2C_FIELD(arg1, s8 *, 1) >= 2) {
        func_0034E530(arg0, M2C_FIELD(arg1, s32 **, 0x14), arg2);
    }
    return temp_f20;
}

void func_0034E4A8(s32 arg0, void *arg1, void *arg2) {
    func_0034E220(arg0, arg1, arg2, 0, *func_003500E0(arg2, M2C_FIELD(M2C_FIELD(arg1, void **, 8), s32 *, 0xC)));
}

f32 func_0034E508(void) {
    func_0034DE98();
    return 1.0f;
}

/* Assembly between the functions: func_0034E530 (144 bytes), func_0034E5C0 (408 bytes) */

void func_0034E758(void *arg0, void *arg1, s32 *arg2) {
    f32 temp_f20;
    void *temp_16;

    temp_16 = M2C_FIELD(arg1, void **, 8);
    temp_f20 = func_00348A38(M2C_FIELD(temp_16, s32 *, 0), arg0);
    *func_003500E0(arg2, M2C_FIELD(temp_16, s32 *, 0xC)) = (temp_f20 - M2C_FIELD(temp_16, f32 *, 4)) / M2C_FIELD(temp_16, f32 *, 8);
}

void func_0034E7C0(void *arg0, void *arg1, s32 *arg2) {
    f32 temp_f20;
    void *temp_16;

    temp_16 = M2C_FIELD(arg1, void **, 8);
    temp_f20 = func_00348A38(M2C_FIELD(temp_16, s32 *, 0), arg0);
    *func_003500E0(arg2, M2C_FIELD(temp_16, s32 *, 0xC)) = (temp_f20 - M2C_FIELD(temp_16, f32 *, 4)) / M2C_FIELD(temp_16, f32 *, 8);
}

/* Assembly between the functions: func_0034E828 (224 bytes) */

void func_0034E908(void *arg0, void *arg1, s32 *arg2) {
    f32 temp_f20;
    void *temp_16;

    temp_16 = M2C_FIELD(arg1, void **, 8);
    temp_f20 = func_00348A38(M2C_FIELD(temp_16, s32 *, 0), arg0);
    *func_003500E0(arg2, M2C_FIELD(temp_16, s32 *, 0xC)) = (temp_f20 - M2C_FIELD(temp_16, f32 *, 4)) / M2C_FIELD(temp_16, f32 *, 8);
    if (*func_003500E0(arg2, M2C_FIELD(temp_16, s32 *, 0xC)) < 0.0f) {
        *func_003500E0(arg2, M2C_FIELD(temp_16, s32 *, 0xC)) = 0.0f;
    }
    if (*func_003500E0(arg2, M2C_FIELD(temp_16, s32 *, 0xC)) > 1.0f) {
        *func_003500E0(arg2, M2C_FIELD(temp_16, s32 *, 0xC)) = 1.0f;
    }
}

/* Assembly between the functions: func_0034E9E0 (192 bytes) */

f32 func_0034EAA0(void *arg0, void *arg1)
{
  s16 temp_5;
  temp_5 = M2C_FIELD(arg0, s16 *, 2);
  if (temp_5 >= 0x46)
  {
    if (arg1)
    {
      return M2C_FIELD(arg0, f32 *, 4);
    }
    else
    {
      return M2C_FIELD(arg0, f32 *, 4);
    }
  }
  return *func_003500E0(arg1, (s32) temp_5);
}
