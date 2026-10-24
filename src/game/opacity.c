#include "ps2/prelude.h"
void func_001AEBD0(char *actor,float opacity) {
 __asm__("max.s %0, %0, %1":"+f"(opacity):"f"(0.0f));
 __asm__("min.s %0, %0, %1":"+f"(opacity):"f"(1.0f));
 M2C_FIELD(actor+0x8000,float *,0x5560)=opacity;
}
