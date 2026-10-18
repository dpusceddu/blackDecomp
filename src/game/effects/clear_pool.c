// Unmatched: large-offset aliases and return scheduling.
#ifdef NONMATCHING
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

#endif // NONMATCHING
