/* Translation unit tu_378d90 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00311CA0(M2C_UNK *);
extern M2C_UNK D_0048EC20;
extern s32 func_0037B988();
extern s32 func_003230C0();
extern s32 func_0037B608();
extern s32 func_003110B0();
extern s32 func_00323188();

s32 func_00378D90(s32 arg0)
{
 do { } while (0);
  func_0037B2D0(arg0 + 0x104, arg0 + 0x16C);
  return arg0;
  if (((!arg0) && (!arg0)) && (!arg0))
  {
  }
}

/* Assembly between the functions: func_00378DC0 (8 bytes), func_00378DC8 (1232 bytes), func_00379298 (56 bytes), func_003792D0 (96 bytes), func_00379330 (112 bytes) */

void func_003793A0(void) {
    func_00311CA0(&D_0048EC20);
}

/* Assembly between the functions: func_003793C0 (360 bytes), func_00379528 (304 bytes), func_00379658 (1072 bytes), func_00379A88 (880 bytes), func_00379DF8 (872 bytes), func_0037A160 (792 bytes), func_0037A478 (2496 bytes), func_0037AE38 (920 bytes), func_0037B1D0 (80 bytes), func_0037B220 (104 bytes), func_0037B288 (72 bytes) */

s32 func_0037B2D0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_2;

    temp_2 = func_0037B988(arg0, arg1, M2C_FIELD(arg2, s32 *, 4));
    return func_003230C0((s32) temp_2, M2C_FIELD(temp_2, s32 *, 0x80), 2, arg2);
}

/* Assembly between the functions: func_0037B310 (8 bytes), func_0037B318 (312 bytes) */

void func_0037B450(void) {
    func_0037B608();
}

/* Assembly between the functions: func_0037B470 (168 bytes), func_0037B518 (240 bytes), func_0037B608 (312 bytes), func_0037B740 (360 bytes) */

s32 func_0037B8A8(s32 arg0, s32 arg1) {
    *M2C_FIELD(arg0, void ***, 0x48) = M2C_FIELD(arg0, void **, 0x44);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), void ***, 4) = (void **) M2C_FIELD(arg0, void ***, 0x48);
    return func_003110B0(arg0, M2C_FIELD(arg1, s32 *, 0x54), M2C_FIELD(arg1, s32 *, 0x58));
}

s32 func_0037B8E8(s32 arg0, s32 arg1) {
    return func_00323188(arg0, M2C_FIELD(arg0, s32 *, 0x40), 2, arg1);
}
