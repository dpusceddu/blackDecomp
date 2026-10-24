/* Translation unit physics/tu_33a260 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_0033A260();
extern s32 func_0033A260(M2C_UNK, M2C_UNK);

void *func_0033A3B0(void *arg0, s32 arg1, s32 arg2)
{
  s8 *new_var2;
  int new_var;
  new_var2 = ((s8 *) arg0) + 4;
  *((s32 *) new_var2) = 0x10;
  new_var = (arg1 << 7) + 0x100;
  M2C_FIELD(arg0, s32 *, 0) = (s32) (((new_var + (arg2 << 7)) + (arg2 * 0x60)) + 0x27E0);
  return arg0;
}

/* Assembly between the functions: func_0033A3E8 (8 bytes), func_0033A3F0 (80 bytes), func_0033A440 (8 bytes) */

void func_0033A448(void) {
    func_0033A260(1, 0xFFFF);
}

void func_0033A468(void) {
    func_0033A260(0, 0xFFFF);
}
