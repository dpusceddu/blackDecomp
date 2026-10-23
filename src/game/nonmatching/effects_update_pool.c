// Unmatched: indexed-pool aliases and register allocation.
#ifdef NONMATCHING
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

#endif // NONMATCHING
