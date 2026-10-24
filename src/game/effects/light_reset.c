#include "include_asm.h"

#include "game/effects/emitter.h"
extern void func_001C08F0(BkEffectLightPS2 *);

void func_001C1578(BkEffectLightsPS2 *pool) {
 BkEffectLightPS2 *entry=pool->lights,*end=pool->lights+256;
 do {func_001C08F0(entry);entry++;}while(entry<end);
 pool->activeCount=0;pool->definitions=0;
}

#ifdef NON_MATCHING
#include "game/effects/emitter.h"
typedef struct {s64 id;void *resource;u32 unknown;} BkEffectNamedEntryPS2;
typedef struct {u32 prefix[2];int count;BkEffectNamedEntryPS2 *entries;} BkEffectNameMapPS2;
typedef struct {u8 prefix[0x14];BkEffectNameMapPS2 *map;u8 unknown18[0x14];char *definitions;u8 unknown30[8];u16 count;} BkEffectLightResourcePS2;
extern char D_00415BA0[];
extern void func_001D0A68(void),func_001D0AA8(void),func_001D14E0(void *,void *,void *),func_001D1A30(void *),func_001C1548(BkEffectLightPS2 *);
extern int func_00360838(const char *,const char *);
// Unmatched: named light-definition lookup and resource loop register allocation.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C15D0);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C1740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C1810);
