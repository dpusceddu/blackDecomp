#ifdef NONMATCHING
// Unmatched: endpoint callback argument lifetime; full-body score 5.
#include "animation/sampling_pipeline.h"
extern void *func_0034F9D0(SamplingPipeline *, SamplingPoseHeader *, s32, s32);
extern void *func_00346230(void *, void *, void *, s32, f32);
static __inline__ f32 Sampling_Abs(f32 value) { f32 result; __asm__("abs.s %0,%1":"=f"(result):"f"(value)); return result; }
void *func_0034FB58(SamplingPipeline *context, SamplingPoseHeader *header, const SamplingPair *pair, s32 flags) {
    void *first, *second;
    if (pair->first == pair->second) return func_0034F9D0(context, header, pair->first, flags);
    if (Sampling_Abs(0.0f - pair->weight) < 0.001f) return func_0034F9D0(context, header, pair->first, flags);
    else if (Sampling_Abs(1.0f - pair->weight) < 0.001f) return func_0034F9D0(context, header, pair->second, flags);
    first = func_0034F9D0(context, header, pair->first, flags);
    second = func_0034F9D0(context, header, pair->second, flags);
    if (first == NULL) return second;
    if (second == NULL) return first;
    return func_00346230(context->owner, first, second, flags, pair->weight);
}
#endif
