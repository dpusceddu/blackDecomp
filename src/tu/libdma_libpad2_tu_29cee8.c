/* Translation unit libdma_libpad2/tu_29cee8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern u8 func_0029D138();
extern u8 func_0029D108();
extern s32 func_0029D228();

void func_0029D158(void *arg0) {
    M2C_FIELD(arg0, u8 *, 7) = func_0029D138(M2C_FIELD(arg0, u8 *, 7));
    M2C_FIELD(arg0, u8 *, 6) = func_0029D138(M2C_FIELD(arg0, u8 *, 6));
    M2C_FIELD(arg0, u8 *, 5) = func_0029D138(M2C_FIELD(arg0, u8 *, 5));
    M2C_FIELD(arg0, u8 *, 3) = func_0029D138(M2C_FIELD(arg0, u8 *, 3));
    M2C_FIELD(arg0, u8 *, 2) = func_0029D138(M2C_FIELD(arg0, u8 *, 2));
    M2C_FIELD(arg0, u8 *, 1) = func_0029D138(M2C_FIELD(arg0, u8 *, 1));
}

void func_0029D1C0(void *arg0) {
    M2C_FIELD(arg0, u8 *, 7) = func_0029D108(M2C_FIELD(arg0, u8 *, 7));
    M2C_FIELD(arg0, u8 *, 6) = func_0029D108(M2C_FIELD(arg0, u8 *, 6));
    M2C_FIELD(arg0, u8 *, 5) = func_0029D108(M2C_FIELD(arg0, u8 *, 5));
    M2C_FIELD(arg0, u8 *, 3) = func_0029D108(M2C_FIELD(arg0, u8 *, 3));
    M2C_FIELD(arg0, u8 *, 2) = func_0029D108(M2C_FIELD(arg0, u8 *, 2));
    M2C_FIELD(arg0, u8 *, 1) = func_0029D108(M2C_FIELD(arg0, u8 *, 1));
}

/* Assembly between the functions: func_0029D228 (184 bytes), func_0029D2E0 (168 bytes) */

short func_0029D388(void *arg0)
{
  unsigned int temp_3;
  temp_3 = M2C_FIELD(arg0, u8 *, 3);
  temp_3 = temp_3 + 1;
  M2C_FIELD(arg0, u8 *, 3) = temp_3;
  if ((temp_3 & 0xFF) == 0x18)
  {
    M2C_FIELD(arg0, u8 *, 3) = 0U;
    func_0029D228(arg0, arg0);
  }
}
