#include "game/effects/pool.h"
typedef struct { s64 id;void *effect;u32 unknown; } BkEffectIdPS2;
typedef struct { u32 prefix[2];s32 count;BkEffectIdPS2 *entries; } BkEffectLookupPS2;
int func_001B7A70(BkEffectPoolPS2 *,void *,void *,int);
void func_001B7A00(BkEffectPoolPS2 *pool,void *transform,s64 id,int mode) {
 if(id) {
  BkEffectLookupPS2 *lookup=*(BkEffectLookupPS2 **)((char *)pool->resource+8);
  BkEffectIdPS2 *entry;int i=0,count=lookup->count;void *effect;
  if(count>0) {
   entry=lookup->entries;
   do {
    ++i;
    if(entry->id==id) {effect=entry->effect;goto found;}
    ++entry;
   }while(i<count);
  }
  effect=0;
 found:
  func_001B7A70(pool,effect,transform,mode);
 }
}
