#include "include_asm.h"

#include "game/effects/pool.h"
extern int func_001B7A70(BkEffectPoolPS2 *,void *,void *,int);

#ifdef NON_MATCHING
// Unmatched: indexed-pool aliases and register allocation.
#include "game/effects/pool.h"
extern char *D_0040F4D0;
extern void func_001B7B80(BkEffectPoolPS2 *,void *,f32),func_001B1518(BkEffectEntryPS2 *);
extern int func_001B1340(BkEffectEntryPS2 *,void *,f32,f32);
void func_001B7758(BkEffectPoolPS2 *pool) {
 f32 now=*(f32 *)(D_0040F4D0+0x20);u16 remaining,*cursor;
 func_001B7B80(pool,D_0040F4D0,pool->time);
 remaining=(pool->activeCount-1)&0xffff;cursor=pool->indices;
 while(remaining!=0xffff) {
  u16 index=*cursor;BkEffectEntryPS2 *entry=&pool->entries[index];
  if(func_001B1340(entry,pool->owner,now,pool->time))cursor++;
  else {
   u16 last,slot,replacement;
   func_001B1518(entry);last=(pool->activeCount-1)&0xffff;slot=pool->reverseIndices[index];replacement=pool->indices[last];
   pool->indices[slot]=replacement;pool->reverseIndices[index]=last;pool->indices[last]=index;pool->reverseIndices[replacement]=slot;pool->activeCount--;
  }
  remaining=(remaining-1)&0xffff;
 }
 pool->time=now;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/dispatch", func_001B7758);
#endif

#ifdef NON_MATCHING
// Unmatched: large-offset aliases and return scheduling.
#include "game/effects/pool.h"
extern void func_001B1518(BkEffectEntryPS2 *);
int func_001B78D8(BkEffectPoolPS2 *pool) {
 u16 index=0;
 do {
  BkEffectEntryPS2 *entry=pool->entries+index;
  if(entry->resource)func_001B1518(entry);
  index=(index+1)&0xffff;
 }while(index<0x300);
 pool->resource=0;pool->activeCount=0;return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/dispatch", func_001B78D8);
#endif

void func_001B7968(BkEffectPoolPS2 *pool,void *transform,u32 index) {
 BkEffectResourcePS2 *resource=pool->resource;
 if(index<resource->effectCount) {
  void *effect=resource->effects[index];
  if(effect)func_001B7A70(pool,effect,transform,1);
 }
}
