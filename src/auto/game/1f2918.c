#include "auto/prelude.h"

extern s32 func_001F44B8();
extern void *D_0040F518;
extern s32 func_001F76E8();

void func_001F2918(s32 arg0, s8 arg1, s32 arg2)
{
  int new_var;
  new_var = arg1 * 0xA8;
  func_001F44B8(*((s32 *) (((s8 *) (D_0040F518 + new_var)) + 0x20)), arg2);
}

void func_001F2958(s32 arg0, s8 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  func_001F76E8(*((s32 *) (((s8 *) (D_0040F518 - (-(arg1 * 0xA8)))) + 0xC)), arg2, arg3 & 0xFF, arg4);
}
