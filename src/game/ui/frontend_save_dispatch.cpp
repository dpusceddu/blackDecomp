#include "include_asm.h"

#include "game/frontend_resources.hpp"
extern "C" {
extern FrontendSaveState *D_0040F4F0;
int func_0010B2A8(FrontendSaveState *);
int func_0010B238(FrontendSaveState *);
int func_0010B270(FrontendSaveState *);
int func_0010B2C0(FrontendSaveState *, int);
int func_0010B2D8(FrontendSaveState *);
}

extern "C" void func_0010C2F8(int command) {
  switch (command) {
  case 1:
    func_0010B2A8(D_0040F4F0);
    return;
  case 3:
    func_0010B238(D_0040F4F0);
    return;
  case 4:
    func_0010B270(D_0040F4F0);
    return;
  case 5:
    func_0010B2C0(D_0040F4F0, 0);
    return;
  case 9:
    func_0010B2D8(D_0040F4F0);
  default:
    return;
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010C398);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010C8E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010CF18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010D9F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010E0F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010E498);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010E5F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010E720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010E740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010EAC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010EAF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0010EBC0);
