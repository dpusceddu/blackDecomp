#ifndef BLACK_EFFECTS_FRACTURE_H
#define BLACK_EFFECTS_FRACTURE_H
#include "game/effects/vu_math.h"
#include "game/effects/random.h"
/* Inferred geometry allocation and fracture callback signatures. */
struct BkEffectFracturePoolPS2 {s32 count;u8 pad[12];BkEffectGeometryPS2 records[255];};
extern "C" void func_001B9198(BkEffectGeometryPS2 *,s128,s128,s8,s16,void *,u8,u8,s128,f32,f32);
extern "C" s128 func_001BCA30(void *,s128,f32),func_001BC880(void);
extern "C" void func_001BC548(void *,s128,s128,int,int,int,f32,f32);
static inline BkEffectGeometryPS2 *BkEffectAllocateGeometryPS2(BkEffectFracturePoolPS2 *pool) {if(pool->count>=254)return 0;return pool->records+pool->count++;}
static inline s128 BkEffectLerpPS2(s128 a,s128 b,f32 fraction) {return BkEffectAddPS2(BkEffectScalePS2(a,fraction),BkEffectScalePS2(b,1-fraction));}
#endif
