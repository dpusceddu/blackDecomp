/* Translation unit libmc2/tu_35b470 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 D_0047EA08;

s32 func_0035B6D0(s32 arg0, s32 arg1, s32 arg2)
{
  void *temp_7;
  temp_7 = ((s32) (&D_0047EA08)) + (arg0 * 0x24);
  *((s32 *) (((s8 *) (((s32) (&D_0047EA08)) + (arg0 * 0x24))) + 0x1C)) = arg1;
  *((s32 *) (((s8 *) (((s32) (&D_0047EA08)) + (arg0 * 0x24))) + 0x20)) = arg2;
  return 1;
}

/* Assembly between the functions: func_0035B6F8 (64 bytes), func_0035B738 (472 bytes), func_0035B910 (256 bytes), func_0035BA10 (216 bytes), func_0035BAE8 (240 bytes), func_0035BBD8 (312 bytes), func_0035BD10 (264 bytes), func_0035BE18 (408 bytes), func_0035BFB0 (32 bytes), func_0035BFD0 (400 bytes), func_0035C160 (8 bytes), func_0035C168 (304 bytes) ... */

s32 func_0035C470(s32 arg0) {
    s32 temp_4;

    temp_4 = arg0 * 0x24;
    if (M2C_FIELD((temp_4 + ((s32) &D_0047EA08)), s32 *, 0) == 0) {
        return -1;
    }
    return M2C_FIELD((((s32) &D_0047EA08) + temp_4), s32 *, 4);
}
