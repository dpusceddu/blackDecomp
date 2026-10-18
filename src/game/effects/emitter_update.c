#include "game/effects/emitter.h"
extern char *D_0040F4D0;extern u8 D_0040D9F1;
extern void *func_001C0760(void *,void *,f32);
extern int func_001BF918(BkEffectEmitterRecordPS2 *,BkEffectEmitterNodePS2 **,f32);
extern void func_001BFEA0(BkEffectEmitterRecordPS2 *);
// Unmatched: pool list recycling, paired u16 indices and callback return widths.
#ifdef NONMATCHING
void func_001C02A0(BkEffectEmittersPS2 *pool) {
 f32 now=*(f32 *)(D_0040F4D0+0x20);BkEffectEmitterNodePS2 *node=(BkEffectEmitterNodePS2 *)pool->count0;void *pending=0;u16 i;u16 remaining,*cursor;
 if(node) {while(node->next)node=node->next;if(node) {node->next=pool->freeHead;pool->freeHead=(BkEffectEmitterNodePS2 *)pool->count0;}}
 pool->count0=pool->count1;
 for(i=0;i<pool->emitterCount;i++)pending=func_001C0760((char *)pool->emitters+i*0xc,pending,now);
 pool->count1=(u32)pending;remaining=pool->activeCount;cursor=pool->indices;
 if(remaining) {
  D_0040D9F1=1;
  do {
   u16 index=*cursor;BkEffectEmitterRecordPS2 *record=pool->records+index;u8 alive=0;
   if(now<=record->birthTime+record->expiry) {alive=1;if(record->lastUpdate<now)alive=func_001BF918(record,&pool->freeHead,now);}
   if(!alive) {
    u16 last,slot,replacement;func_001BFEA0(record);last=pool->activeCount-1;slot=pool->reverseIndices[index];replacement=pool->indices[last];pool->indices[slot]=replacement;pool->reverseIndices[index]=last;pool->indices[last]=index;pool->reverseIndices[replacement]=slot;pool->activeCount--;
   }else cursor++;
   remaining--;
  }while(remaining);
  D_0040D9F1=0;
 }
}
#endif // NONMATCHING
