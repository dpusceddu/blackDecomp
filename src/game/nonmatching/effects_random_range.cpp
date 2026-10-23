// Unmatched: VU broadcast construction register allocation.
#ifdef NONMATCHING
#include "game/effects/vector.h"
extern s128 D_00415B80[2];
static inline s128 Splat(f32 scalar) {s128 t,r;__asm__("pextlw tmpv, fr, fr":"=r tmpv"(t):"r fr"(scalar));__asm__("pextlw outv, fr, tmpv":"=r outv"(r):"r fr"(scalar),"r tmpv"(t));return r;}
extern "C" void func_001BEC18(void) {
 s128 low=Splat(0.1f),high=Splat(1.1f);volatile s128 temporary;
 temporary=low;D_00415B80[1]=BkEffectSubPS2(high,low);temporary=high;D_00415B80[0]=high;
}

#endif // NONMATCHING
