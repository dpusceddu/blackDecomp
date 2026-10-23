#include "game/effects/emitter.h"
extern void func_001C08F0(BkEffectLightPS2 *);
void func_001C1578(BkEffectLightsPS2 *pool) {
 BkEffectLightPS2 *entry=pool->lights,*end=pool->lights+256;
 do {func_001C08F0(entry);entry++;}while(entry<end);
 pool->activeCount=0;pool->definitions=0;
}
