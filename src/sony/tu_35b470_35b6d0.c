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
