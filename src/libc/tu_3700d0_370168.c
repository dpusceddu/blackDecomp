/* Translation unit libstdcxx_typeinfo/tu_3700d0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern M2C_UNK D_0040BF00;
extern M2C_UNK D_0040BF18;
extern M2C_UNK D_0040BEE8;

void func_00370168(void *arg0, void *arg1, void *arg2) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, void **, 8) = arg2;
        M2C_FIELD(arg0, void **, 0) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = &D_0040BF00;
    }
}

void func_00370188(void *arg0, void *arg1) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, void **, 0) = arg1;
        M2C_FIELD(arg0, M2C_UNK **, 4) = &D_0040BF18;
    }
}

/* Assembly between the functions: func_003701A8 (48 bytes), func_003701D8 (152 bytes), func_00370270 (472 bytes) */

void *func_00370448(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  int new_var;
  new_var = 0;
  do
  {
  }
  while (new_var);
  M2C_FIELD(arg0, s32 *, 0) = arg1;
  M2C_FIELD(arg0, s32 *, 8) = arg2;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_0040BEE8;
  M2C_FIELD(arg0, s32 *, 0xC) = arg3;
  return arg0;
}
