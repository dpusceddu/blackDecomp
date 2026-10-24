#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_001B7F28(void *arg0) {
    s32 *var_4;
    s32 var_2;

    var_4 = (s32 *) (((s8 *) arg0) + 0x188);
    var_2 = 7;
    do {
        *var_4 = 0;
        var_2 -= 1;
        var_4 = (s32 *) (((s8 *) var_4) + -0x38);
    } while (var_2 >= 0);
    return var_2;
}

#ifdef NON_MATCHING
// Unmatched: bucket pointer scheduling.
#include "game/effects/pool.h"
void func_001B7F50(BkEffectBucketPS2 *buckets,BkEffectBatchPS2 *batch) {
 BkEffectBucketPS2 *bucket=buckets,*end=buckets+8;
 do {
  if(!bucket->material) {bucket->count=1;bucket->material=batch->material;bucket->batches[0]=batch;return;}
  if(bucket->material==batch->material) {
   if(bucket->count<12) {bucket->batches[bucket->count]=batch;bucket->count++;}
   return;
  }
  bucket++;
 }while(bucket<end);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B7F50);
#endif

#ifdef NON_MATCHING
// Unmatched: loop register allocation and repeated material binding.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B7FC8);
#endif
