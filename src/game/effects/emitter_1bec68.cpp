#include "include_asm.h"

#include "game/effects/mod_emitter_methods.hpp"

#ifdef NON_MATCHING
// Unmatched: VU broadcast construction register allocation.
#include "game/effects/vector.h"
extern s128 D_00415B80[2];
static inline s128 Splat(f32 scalar) {s128 t,r;__asm__("pextlw tmpv, fr, fr":"=r tmpv"(t):"r fr"(scalar));__asm__("pextlw outv, fr, tmpv":"=r outv"(r):"r fr"(scalar),"r tmpv"(t));return r;}
extern "C" void func_001BEC18(void) {
 s128 low=Splat(0.1f),high=Splat(1.1f);volatile s128 temporary;
 temporary=low;D_00415B80[1]=BkEffectSubPS2(high,low);temporary=high;D_00415B80[0]=high;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BEC18);
#endif

int ModEffects::Flights::Clear() {
    u32 i = 0, j;
    do {
        BkModAttachedEffectPS2 *record = records + i;
        record->active = 0;
        j = 0;
        BkModEffectChildrenPS2 *child = &record->children;
        do {
            child->items[j] = 0;
            j = (j + 1) & 0xFFFF;
        } while (j < 8);
        i = (i + 1) & 0xFFFF;
        child->resource = 0;
    } while (i < 44);
    return 1;
}
