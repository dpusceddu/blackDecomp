#include "include_asm.h"

#include "game/frontend_resources.hpp"
extern "C" {
extern char *D_0040F0E0;
extern void *D_0040F4E8;
signed char func_001228E0(void *, int);
void func_00103990(int);
}

extern "C" void func_00103930() {
  D_0040F0E0[0x2020c] = func_001228E0(D_0040F4E8, 0);
  D_0040F0E0[0x2020d] = 1;
  D_0040F0E0[0x2020e] = 1;
  func_00103990(0);
}
