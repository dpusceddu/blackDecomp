#include "auto/prelude.h"

extern s32 func_001AF6D0();
extern s32 func_001B86D0();
extern s32 D_0040F4D8;

void func_001AEB18(s32 actor_address)
{
  func_001AF6D0(actor_address + 0x14);
  D_0040F4D8 += 0;
  func_001B86D0(D_0040F4D8 + 0x54AB0);
}
