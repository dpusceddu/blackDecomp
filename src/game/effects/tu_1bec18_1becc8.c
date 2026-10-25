#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001D0010(s32);

s32 func_001BECC8(void) {
    return 1;
}


#ifdef NON_MATCHING
#include "game/effects/emitter.h"
extern char D_00418598[];
extern void func_001CFF78(void),func_001C0740(void *,void *),func_001C08B0(BkEffectEmitterNodePS2 *),func_001BFEA0(BkEffectEmitterRecordPS2 *);
// Unmatched: emitter pool initialization aliases and loop register allocation.
int func_001BFFE0(BkEffectEmittersPS2 *pool,BkEffectEmitterResourcePS2 *resource) {
 u16 index=0;u32 i;BkEffectEmitterNodePS2 *node;BkEffectEmitterRecordPS2 *record;
 func_001CFF78();pool->resource=resource;pool->emitters=D_00418598;pool->emitterCount=resource->emitterCount;
 if(pool->emitterCount)do {func_001C0740((char *)pool->emitters+index*0xc,(char *)resource->emitterDefs+index*0xf0);index++;}while(index<pool->emitterCount);
 for(i=0;i<256;i++)func_001C08B0(&pool->nodes[i]);
 node=pool->nodes;for(i=0;i<255;i++)node[i].next=&node[i+1];pool->nodes[255].next=0;pool->freeHead=pool->nodes;
 i=1;do {((u32 *)&pool->count0)[i]=0;}while((s32)--i>=0);
 record=pool->records;do {if(record->resource)func_001BFEA0(record);record++;}while(record<pool->records+1024);
 index=0;if(pool->capacity)do {pool->indices[index]=index;pool->reverseIndices[index]=index;index++;}while(index<pool->capacity);
 pool->activeCount=0;return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_1bec18_1becc8", func_001BFFE0);
#endif


#ifdef NON_MATCHING
#include "game/effects/emitter.h"
extern char *D_0040F4D0;extern u8 D_0040D9F1;
extern void *func_001C0760(void *,void *,f32);
extern int func_001BF918(BkEffectEmitterRecordPS2 *,BkEffectEmitterNodePS2 **,f32);
extern void func_001BFEA0(BkEffectEmitterRecordPS2 *);
// Unmatched: pool list recycling, paired u16 indices and callback return widths.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/tu_1bec18_1becc8", func_001C02A0);
#endif


void func_001C05D8(s32 arg0, s32 arg1) {
    func_001D0010(arg1);
}

void func_001C05F8(void) {

}
