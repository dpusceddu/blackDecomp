// Unmatched: bucket pointer scheduling.
#ifdef NONMATCHING
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

#endif // NONMATCHING
