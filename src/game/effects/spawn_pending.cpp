#include "game/effects/pool.h"
#include "game/effects/vector.h"
extern "C" {
extern char *D_0040F4C0,*D_0040F4C4,*D_0040F510;
extern void func_001B1168(f32,BkEffectEntryPS2 *,void *,void *,int);
extern s64 func_00108120(void *);
extern void func_001BE7F0(...),func_001B0C10(...),func_001BEBA0(...),func_0014EBE0(...),func_001BEF70(...),func_001EC158(...),func_001EC060(...);
}
// Unmatched: pending effect resource ownership and vector-valued callback signatures.
#ifdef NONMATCHING
extern "C" void func_001B7B80(BkEffectPoolPS2 *pool,void *,f32 time) {
 u16 remaining=pool->pendingCount;
 while(remaining--) {
  char *pending=(char *)pool+0x15000+remaining*0x50;
  char *definition=*(char **)(pending+0x40);
  u16 index=pool->activeCount;
  BkEffectPointPS2 transform[6];
  if((u16)(pool->capacity-index)==0)break;
  pool->activeCount=index+1;
  BkEffectEntryPS2 *entry=pool->entries+pool->indices[index];
  func_001B1168(time,entry,pending,definition,0);
  /* The 64-bit sound identifier and 128-bit position are independent arguments. */
  if(*(s64 *)(definition+0x280)) {
   s64 sound=func_00108120(D_0040F4C4);
   func_001BE7F0(*(void **)(definition+0x290),0,*(u32 *)(definition+0x294),*(u32 *)(definition+0x298),*(u32 *)(definition+0x29c),(char *)pool->owner+0x83720,sound,pending);
  }
  if(definition[0x2a0])func_001B0C10(*(u32 *)(definition+0x2a4),*(u32 *)(definition+0x2a8),0,D_0040F4C0+0xd290,*(s64 *)(definition+0x2b0));
  if(definition[0x242])func_001BEBA0(0,10.0f,(char *)pool->owner+0x83d24,entry,definition);
  u16 slot=*(u16 *)(definition+0x240);
  if(slot!=9999) {
   char *table=*(char **)((char *)pool->resource+0x20)+slot*0x48;
   if(*(s64 *)table!=(s64)0x9b5db9da662d3b18ULL) {
    func_0014EBE0(transform,pending,table);
   }else func_001BEF70((char *)pool->owner+0x83fb0,*(s128 *)(pending+0x30));
  }
  s8 category=definition[0x270];void *service=*(void **)(*(char **)(D_0040F510+0xcbd8)+0x24);
  if(category>0)func_001EC158(service,category,*(s128 *)(pending+0x30));
  if(*(f32 *)(definition+0x278)>0)func_001EC060(*(u32 *)(definition+0x274),service,*(s128 *)(pending+0x30),0,0);
 }
 pool->pendingCount=0;
}
#endif // NONMATCHING
