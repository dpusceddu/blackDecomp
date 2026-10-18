// Unmatched: short-loop assembler padding.
#ifdef NONMATCHING
#include "game/effects/pool.h"
void func_001B7F28(BkEffectBucketPS2 *buckets) {
 int i=7;BkEffectBucketPS2 *bucket=buckets+7;
 do {bucket->material=0;--i;--bucket;}while(i>=0);
}

#endif // NONMATCHING
