#ifndef BLACK_EFFECTS_GEOMETRY_H
#define BLACK_EFFECTS_GEOMETRY_H
#include "game/effects/vector.h"
/* PS2 access views; complete allocation sizes remain unknown. */
typedef struct {
 BkEffectVectorPS2 normal,points[4];BkEffectUVPS2 uv[4];BkEffectVectorPS2 transform[4],velocity,gravity,unknownD0,direction;
 void *material;f32 elapsed,size,unknownFC,lifetime,area;u16 tag,frames;s8 vertexCount;u8 pass,flags,padding;
} BkEffectGeometryPS2;
typedef struct BkEffectGeometryBucketPS2 {
 u8 count,padding[3];BkEffectGeometryPS2 *records[32];struct BkEffectGeometryBucketPS2 *next;
} BkEffectGeometryBucketPS2;
static inline BkEffectVectorPS2 BkEffectTransformPS2(const BkEffectVectorPS2 *m,BkEffectVectorPS2 v) {
 BkEffectVectorPS2 r;
 __asm__("vmulax.xyz ACC, mx, pointvx\n\tvmadday.xyz ACC, my, pointvy\n\tvmaddaz.xyz ACC, mz, pointvz\n\tvmaddw.xyz outv, mt, vf0w":"=j outv"(r):"j mx"(m[0]),"j my"(m[1]),"j mz"(m[2]),"j mt"(m[3]),"j pointv"(v));return r;
}
static inline BkEffectVectorPS2 BkEffectRotatePS2(const BkEffectVectorPS2 *m,BkEffectVectorPS2 v) {
 BkEffectVectorPS2 r;
 __asm__("vmulax.xyz ACC, mx, pointvx\n\tvmadday.xyz ACC, my, pointvy\n\tvmaddz.xyz outv, mz, pointvz":"=j outv"(r):"j mx"(m[0]),"j my"(m[1]),"j mz"(m[2]),"j pointv"(v));return r;
}
#endif

