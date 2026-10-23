// Unmatched: loop register allocation and repeated material binding.
#ifdef NONMATCHING
#include "game/effects/pool.h"
extern void func_001C45C0(void),func_001C4148(void *),func_001C41D0(BkEffectEntryPS2 *);
void func_001B7FC8(BkEffectBucketPS2 *buckets,u32 pass) {
 int bucketIndex=0;BkEffectBucketPS2 *bucket=buckets;
 do {
  int batchIndex;u8 bound=0;
  if(!bucket->material)return;
  for(batchIndex=0;batchIndex<bucket->count;batchIndex++) {
   BkEffectBatchPS2 *batch=bucket->batches[batchIndex];
   if(((batch->flags>>1)&1)!=pass) {
    int i,offset;
    if(!bound) { bound=1;func_001C45C0();func_001C4148(bucket->material); }
    for(i=0,offset=0;i<batch->entryCount;i++,offset+=0x70) {
     if((batch->enabled[i/8]>>(i%8))&1)func_001C41D0((BkEffectEntryPS2 *)((char *)batch->entries+offset));
    }
   }
  }
  bucketIndex++;bucket=buckets+bucketIndex;
 }while(bucketIndex<8);
}

#endif // NONMATCHING
