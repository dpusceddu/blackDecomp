#ifdef NONMATCHING
// Unmatched: callback argument lifetime adds a context move; full-body score 6.
#include "animation/sampling_pipeline.h"
extern s32 func_0034FA60(SamplingPipeline *, SamplingPoseHeader *, SamplingPoseHeader *, s32, s32);
extern s32 func_00344178(SamplingPoseHeader *, const SamplingPoseHeader *, const SamplingPoseHeader *, f32);
static __inline__ f32 Sampling_Abs(f32 value) { f32 result; __asm__("abs.s %0,%1":"=f"(result):"f"(value)); return result; }
s32 func_0034FC80(SamplingPipeline *context, SamplingPoseHeader *out, SamplingPoseHeader *root, const SamplingPair *pair, s32 flags) {
    SamplingPoseHeader first_header, second_header;
    s32 first, second;
    if (pair->first == pair->second) return func_0034FA60(context, out, root, pair->second, flags);
    if (Sampling_Abs(0.0f - pair->weight) < 0.001f) return func_0034FA60(context, out, root, pair->first, flags);
    if (Sampling_Abs(1.0f - pair->weight) < 0.001f) return func_0034FA60(context, out, root, pair->second, flags);
    func_00343FC8(&first_header);
    func_00343FC8(&second_header);
    first = func_0034FA60(context, &first_header, root, pair->first, flags) != 0;
    second = func_0034FA60(context, &second_header, root, pair->second, flags) != 0;
    if (first) {
        if (second) return func_00344178(out, &first_header, &second_header, pair->weight);
        return func_00344020(out, &first_header);
    }
    if (second) return func_00344020(out, &second_header);
    return 0;
}
#endif
