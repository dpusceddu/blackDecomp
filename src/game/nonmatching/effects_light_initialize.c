#include "game/effects/emitter.h"
typedef struct {s64 id;void *resource;u32 unknown;} BkEffectNamedEntryPS2;
typedef struct {u32 prefix[2];int count;BkEffectNamedEntryPS2 *entries;} BkEffectNameMapPS2;
typedef struct {u8 prefix[0x14];BkEffectNameMapPS2 *map;u8 unknown18[0x14];char *definitions;u8 unknown30[8];u16 count;} BkEffectLightResourcePS2;
extern char D_00415BA0[];
extern void func_001D0A68(void),func_001D0AA8(void),func_001D14E0(void *,void *,void *),func_001D1A30(void *),func_001C1548(BkEffectLightPS2 *);
extern int func_00360838(const char *,const char *);
// Unmatched: named light-definition lookup and resource loop register allocation.
#ifdef NONMATCHING
int func_001C15D0(BkEffectLightsPS2 *pool,BkEffectLightResourcePS2 *resource) {
 u16 index=0;BkEffectLightPS2 *light;func_001D0A68();func_001D0AA8();pool->resource=resource;pool->definitions=D_00415BA0;pool->definitionCount=resource->count;
 if(pool->definitionCount)do {
  BkEffectNameMapPS2 *map=resource->map;int i;void *asset=0;
  for(i=0;i<map->count;i++) {
   asset=map->entries[i].resource;
   if(func_00360838((char *)asset+0xa8,resource->definitions+index*0xc0)==0)break;
   asset=0;
  }
  func_001D14E0(pool->definitions+index*0x90,resource->definitions+index*0xc0,asset);
  func_001D1A30(pool->definitions+index*0x90);index++;
 }while(index<pool->definitionCount);
 light=pool->lights;do {if(light->resource)func_001C1548(light);light++;}while(light<pool->lights+256);
 pool->activeCount=0;return 1;
}
#endif // NONMATCHING
