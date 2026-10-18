#include "game/effects/emitter.h"
extern char D_00418598[];
extern void func_001CFF78(void),func_001C0740(void *,void *),func_001C08B0(BkEffectEmitterNodePS2 *),func_001BFEA0(BkEffectEmitterRecordPS2 *);
// Unmatched: emitter pool initialization aliases and loop register allocation.
#ifdef NONMATCHING
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
#endif // NONMATCHING
