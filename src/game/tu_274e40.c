/* Translation unit tu_274e40 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00274F58();
extern s32 D_003C09E0;
extern void func_00274F08();
extern s32 (*D_00449544)();

s32 func_00274E40(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 0) = 0;
    return func_00274F58(arg0, 4);
}

/* Assembly between the functions: func_00274E68 (64 bytes) */

void func_00274EA8(void *arg0)
{
  s32 temp_4;
  int new_var2;
  s32 *new_var;
  new_var = (s32 *) (((s8 *) arg0) + 4);
  if (arg0 == D_003C09E0)
  {
    func_00274F08();
  }
  temp_4 = *new_var;
  if (temp_4 != 0)
  {
    new_var2 = 4;
    D_00449544(temp_4);
    *((s32 *) (((s8 *) arg0) + new_var2)) = 0;
  }
 do { M2C_FIELD(arg0, s8 *, 0) = 0; M2C_FIELD(arg0, s32 *, 8) = 0; } while (0);
  M2C_FIELD(arg0, s32 *, 0xC) = 0;
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
}
