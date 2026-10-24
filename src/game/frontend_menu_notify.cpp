#include "include_asm.h"

#include "game/frontend_resources.hpp"
extern "C" {
extern unsigned char D_0040EAE0;
extern void *D_0040F0E0;
extern void *D_0040EADC;
void func_001034B0(void *, void *);
}

extern "C" void func_00103DB0(int conditional) {
  if (!conditional || D_0040EAE0)
    func_001034B0(D_0040F0E0, D_0040EADC);
}
