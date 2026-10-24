/* Translation unit rwa_ee/tu_3168c8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00312C70();
extern s32 func_00317C20(M2C_UNK *, s32 *);
extern M2C_UNK D_00456448;
extern s32 D_00458480;
extern s32 func_00319928();
extern s32 func_00324948();
extern void func_003249E8();
extern s32 func_00318D28();
extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_004584D8;
extern M2C_UNK D_00458500;
extern M2C_UNK D_00458528;
extern s32 func_00310978();
extern M2C_UNK D_00458550;
extern s32 func_00317340(void *, M2C_UNK);
extern s32 func_00310768();
extern s32 func_00317340();
extern s32 func_003106F0(s32, M2C_UNK, M2C_UNK, f32);

volatile unsigned int func_00318250(s32 arg0, s32 arg1)
{
  s32 var_6;
  void *var_3;
  if (arg0)
  {
  }
  var_3 = *((void **) (((s8 *) arg0) + 4));
  var_6 = 0;
  if (var_3 == arg0)
  {
 goto dummy_label_525197; dummy_label_525197: ;
    do
    {
    }
    while (0);
    goto block_7;
  }
  loop_2:
  if ((M2C_FIELD(var_3, s32 *, 8)) == arg1)
  {
    goto block_4;
  }

  var_3 = *((void **) (((s8 *) var_3) + 4));
  goto block_6;
  block_4:
  return var_6;

  block_6:
  var_6 += 1;

  if (var_3 != arg0)
  {
    goto loop_2;
  }
  block_7:
  return -1;

}

/* Assembly between the functions: func_00318288 (64 bytes), func_003182C8 (120 bytes), func_00318340 (128 bytes) */

s32 func_003183C0(s32 arg0) {
    s32 var_2;
    void *var_3;

    var_3 = M2C_FIELD(arg0, void **, 4);
    var_2 = 0;
    if (var_3 != arg0) {
        do {
            var_3 = M2C_FIELD(var_3, void **, 4);
            var_2 += 1;
        } while (var_3 != arg0);
    }
    return var_2;
}

/* Assembly between the functions: func_003183F8 (8 bytes), func_00318400 (80 bytes), func_00318450 (40 bytes), func_00318478 (216 bytes), func_00318550 (176 bytes), func_00318600 (176 bytes), func_003186B0 (64 bytes), func_003186F0 (264 bytes), func_003187F8 (136 bytes), func_00318880 (208 bytes), func_00318950 (208 bytes), func_00318A20 (8 bytes) */

s32 func_00318A28(void *arg0) {
    return *M2C_FIELD(arg0, s32 **, 8) == M2C_FIELD(arg0, s32 *, 0xC);
}

/* Assembly between the functions: func_00318A40 (200 bytes), func_00318B08 (88 bytes), func_00318B60 (96 bytes) */

void func_00318BC0(void) {
    func_00312C70();
}

/* Assembly between the functions: func_00318BE0 (96 bytes), func_00318C40 (80 bytes), func_00318C90 (88 bytes) */


/* Assembly between the functions: func_00318D20 (8 bytes), func_00318D28 (344 bytes), func_00318E80 (1000 bytes), func_00319268 (112 bytes), func_003192D8 (144 bytes), func_00319368 (168 bytes) */

void func_00319410(void *arg0)
{
  int new_var;
  void *new_var2;
  s32 temp_4;
  func_00319480();
  new_var2 = arg0 + 4;
  temp_4 = new_var2;
  new_var = D_00458480 == temp_4;
  if (new_var)
  {
    func_00319928(temp_4);
  }
  if (((*(*((s32 **) (((s8 *) arg0) + 0)))) == 2) && (func_00324948(M2C_FIELD(arg0, s32 *, 0x5C)) != 0))
  {
    func_003249E8(M2C_FIELD(arg0, s32 *, 0x5C));
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
  }
}

void func_00319480(void) {
    func_00318D28();
}

/* Assembly between the functions: func_003194A0 (56 bytes), func_003194D8 (160 bytes), func_00319578 (88 bytes), func_003195D0 (64 bytes) */

s32 func_00319610(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

/* Assembly between the functions: func_00319618 (16 bytes), func_00319628 (128 bytes), func_003196A8 (48 bytes), func_003196D8 (336 bytes), func_00319828 (256 bytes), func_00319928 (40 bytes), func_00319950 (112 bytes) */

void func_003199C0(void) {
    func_00311CA0(&D_004584D8);
}

/* Assembly between the functions: func_003199E0 (112 bytes) */

void func_00319A50(void) {
    func_00311CA0(&D_00458500);
}

/* Assembly between the functions: func_00319A70 (112 bytes) */

void func_00319AE0(void) {
    func_00311CA0(&D_00458528);
}

/* Assembly between the functions: func_00319B00 (368 bytes) */

s32 func_00319C70(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_00310978((s32) &D_00458550, arg0, arg2, arg1, arg3, arg4);
}

/* Assembly between the functions: func_00319CA8 (64 bytes), func_00319CE8 (184 bytes), func_00319DA0 (64 bytes), func_00319DE0 (72 bytes), func_00319E28 (136 bytes), func_00319EB0 (32 bytes), func_00319ED0 (176 bytes) */

void func_00319F80(void *arg0) {
    void *temp_3;

    func_00317340(arg0 + 0x28, 1);
    temp_3 = M2C_FIELD(arg0, void **, 0x28);
    if (temp_3 != NULL) {
        *M2C_FIELD(arg0, void ***, 0x2C) = temp_3;
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x28), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x2C);
    }
}

s32 func_00319FD0(s32 arg0) {
    M2C_UNK var_17;
    s32 temp_4;
    void *temp_16;

    temp_16 = arg0 + 0x28;
    if (M2C_FIELD(temp_16, u8 *, 0x62) & 2) {
        temp_4 = M2C_FIELD(temp_16, s32 *, 0x38);
        var_17 = 2;
        if (temp_4 != 0) {
            var_17 = (func_00310768(temp_4, 8, 2, 0) == 0) ? 1 : 2;
        }
        func_00317340(temp_16, var_17);
    }
    M2C_FIELD(temp_16, u8 *, 0x62) = (u8) (M2C_FIELD(temp_16, u8 *, 0x62) & 0xDF);
    return arg0;
}

s32 func_0031A058(s32 arg0, s32 *arg1) {
    *arg1 = 0;
    return arg0;
}

/* Assembly between the functions: func_0031A068 (40 bytes), func_0031A090 (40 bytes), func_0031A0B8 (40 bytes), func_0031A0E0 (40 bytes), func_0031A108 (88 bytes), func_0031A160 (40 bytes), func_0031A188 (88 bytes), func_0031A1E0 (40 bytes), func_0031A208 (88 bytes), func_0031A260 (40 bytes), func_0031A288 (88 bytes), func_0031A2E0 (40 bytes) */

void * func_0031A308(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x7C) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 4, 1, *arg2);
    }
    return arg0;
}

s32 func_0031A350(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x7C);
    return arg0;
}

void * func_0031A360(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x80) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 5, 1, *arg2);
    }
    return arg0;
}

s32 func_0031A3A8(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x80);
    return arg0;
}

void * func_0031A3B8(void *arg0, s32 arg1, f32 *arg2) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
    M2C_FIELD(arg0, f32 *, 0x78) = (f32) *arg2;
    if (temp_4 != 0) {
        func_003106F0(temp_4, 6, 1, *arg2);
    }
    return arg0;
}

s32 func_0031A400(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, f32 *, 0) = (f32) M2C_FIELD(arg0, f32 *, 0x78);
    return arg0;
}
