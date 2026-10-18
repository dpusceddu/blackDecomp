#ifndef BLACK_EFFECTS_INVERSE_H
#define BLACK_EFFECTS_INVERSE_H
#include "game/effects/geometry.h"
/* UNVERIFIED: transpose/inverse candidate; no whole matching caller yet. */
static inline void BkEffectInverseLocalPS2(const s128 *world,s128 *matrix) {
 BkEffectPointPS2 a=BkEffectSpillPS2(world[0]),b=BkEffectSpillPS2(world[1]),c=BkEffectSpillPS2(world[2]);
 BkEffectPointPS2 rows[4]={{a.x,b.x,c.x,0},{a.y,b.y,c.y,0},{a.z,b.z,c.z,0},{0,0,0,0}};
 s128 inverse[4],result[4];for(int i=0;i<4;i++)inverse[i]=*(s128 *)&rows[i];inverse[3]=BkEffectSubPS2(0,BkEffectRotatePS2(inverse,world[3]));
 for(int i=0;i<3;i++)result[i]=BkEffectRotatePS2(inverse,matrix[i]);result[3]=BkEffectTransformPS2(inverse,matrix[3]);for(int i=0;i<4;i++)matrix[i]=result[i];
}
#endif
