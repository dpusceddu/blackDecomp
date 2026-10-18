/* Translation unit physics/tu_33a488 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_0033A488();
extern s32 func_0033AC48(M2C_UNK, M2C_UNK);

void *func_0033AD90(void *arg0, s32 arg1, s32 arg2)
{
  int new_var;
  new_var = 0x110;
  M2C_FIELD(arg0, s32 *, 4) = 0x10;
  M2C_FIELD(arg0, s32 *, 0) = (s32) (((((((arg1 << 5) << 2) + new_var) + (arg2 << 7)) + (arg2 * 0x60)) + (arg2 * 0xD0)) + 0x2880);
  return arg0;
}

/* Assembly between the functions: func_0033ADD0 (104 bytes), func_0033AE38 (8 bytes) */

s32 func_0033AE40(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x100) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
    return func_0033A488(arg0, arg1, arg2);
}

/* Assembly between the functions: func_0033AE68 (64 bytes) */

void func_0033AEA8(void) {
    func_0033AC48(1, 0xFFFF);
}

void func_0033AEC8(void) {
    func_0033AC48(0, 0xFFFF);
}
