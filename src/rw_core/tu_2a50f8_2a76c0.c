#include "include_asm.h"

#include "ps2/prelude.h"

f32 func_002A76C0(const f32 *vector) {f32 squared=vector[0]*vector[0]+vector[1]*vector[1],length;__asm__("sqrt.s %0, %1" : "=f"(length):"f"(squared));return length;}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A76E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A7790);
