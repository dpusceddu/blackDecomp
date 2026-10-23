#include "auto/prelude.h"
f32 func_002A76C0(const f32 *vector) {f32 squared=vector[0]*vector[0]+vector[1]*vector[1],length;__asm__("sqrt.s %0, %1" : "=f"(length):"f"(squared));return length;}
