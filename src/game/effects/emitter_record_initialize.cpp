#include "game/effects/emitter.h"
extern "C" void func_001B1038(...);extern int D_003BD1C8;
struct BkEmitterConfigPS2 {u32 type;f32 frequency,lifetime,minSpeed,maxSpeed,minScale,maxScale,minEmission,maxEmission,unknown24,width,fade;u8 alternate;};
// Unmatched: partial vector-lane construction and record initializer stack objects.
#ifdef NONMATCHING
extern "C" int func_001BF740(BkEffectEmitterRecordPS2 *record,void *context,char *asset,void *owner,const s128 *transform) {
 func_001B1038(record,context,asset,transform);record->flags=0;record->owner=owner;record->ranges[4]=transform[3];
 BkEmitterConfigPS2 *config=(BkEmitterConfigPS2 *)record->resource;
 BkEffectPointPS2 high={config->maxEmission,config->maxSpeed,6.2831855f,1},low={config->minEmission,config->minSpeed,0,config->alternate?-1.0f:0.0f};
 s128 delta;__asm__("vsub.xyzw outv, av, bv":"=j outv"(delta):"j av"(*(s128 *)&high),"j bv"(*(s128 *)&low));record->ranges[1]=delta;record->ranges[0]=*(s128 *)&high;
 BkEffectPointPS2 top={config->maxScale,1.0f+config->width,0,0},bottom={config->minScale,1.0f-config->width,0,0};record->ranges[2]=*(s128 *)&top;record->ranges[3]=BkEffectSubPS2(*(s128 *)&top,*(s128 *)&bottom);
 record->rate=asset[0x68]?0.0f:8.0f/config->frequency;
 record->expiry=config->lifetime+((BkEffectPointPS2 *)*(void **)owner)[6].y;
 if(D_003BD1C8==-1)D_003BD1C8=0;return 1;
}
#endif // NONMATCHING
