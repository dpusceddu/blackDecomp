#ifndef BLACK_EFFECTS_VECTOR_H
#define BLACK_EFFECTS_VECTOR_H
#include "ps2/prelude.h"
typedef s128 BkEffectVectorPS2;
typedef struct { f32 x,y,z,w; } __attribute__((aligned(16))) BkEffectPointPS2;
typedef struct { f32 u,v; } BkEffectUVPS2;
static inline BkEffectVectorPS2 BkEffectSubPS2(BkEffectVectorPS2 a,BkEffectVectorPS2 b) {
 BkEffectVectorPS2 r;__asm__("vsub.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b));return r;
}
static inline BkEffectPointPS2 BkEffectSpillPS2(BkEffectVectorPS2 v) { BkEffectPointPS2 r;*(BkEffectVectorPS2 *)&r=v;return r; }
#endif
