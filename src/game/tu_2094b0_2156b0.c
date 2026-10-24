#include "ps2/prelude.h"

extern void func_00105258();
extern void *D_0040F0E0;
extern s32 func_0010B1C8();
extern s32 D_0040F4F0;
extern s32 D_003BE84C;
extern s32 func_0010B270();

void func_002156B0(void)
{
  func_00105258(0x20220 + D_0040F0E0);
  func_0010B1C8(D_0040F4F0);
  D_003BE84C = 1;
}

void func_002156F8(void)
{
  func_00105258(D_0040F0E0 + 0x20220);
  func_0010B270(D_0040F4F0);
  D_003BE84C = 3;
}
