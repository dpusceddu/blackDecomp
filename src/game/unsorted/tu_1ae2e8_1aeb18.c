#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001AF6D0();
extern s32 func_001B86D0();
extern s32 D_0040F4D8;

void func_001AEB18(s32 actor_address)
{
  func_001AF6D0(actor_address + 0x14);
  D_0040F4D8 += 0;
  func_001B86D0(D_0040F4D8 + 0x54AB0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ae2e8_1aeb18", func_001AEB50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ae2e8_1aeb18", func_001AEBB0);
