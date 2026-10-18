#ifdef NONMATCHING
// Unmatched: stack aggregate pointer and float-register allocation; full-body score 84.
#include "animation/sampling_pipeline.h"
extern SamplingPair *func_0034FE70(SamplingPair *);
extern SamplingPair *func_0034FE88(SamplingPair *, s32, f32, f32, f32);
extern SamplingPair *func_0034FFA0(SamplingPair *, s32, f32, f32, f32);
extern SamplingSpan *func_0034F360(SamplingSpan *, s32, s32, s32);
extern s32 func_0034F980(SamplingPipeline *, SamplingPoseHeader *, s32, s32);
extern s32 func_0034FAF8(SamplingPipeline *, SamplingPoseHeader *, SamplingPoseHeader *, SamplingPoseHeader *);
extern s32 func_0034FA60(SamplingPipeline *, SamplingPoseHeader *, SamplingPoseHeader *, s32, s32);
extern s32 func_0034FC80(SamplingPipeline *, SamplingPoseHeader *, SamplingPoseHeader *, const SamplingPair *, s32);
extern SamplingPoseHeader *func_0034FB58(SamplingPipeline *, SamplingPoseHeader *, const SamplingPair *, s32);
extern void func_00343A30(SamplingPoseHeader *, const SamplingPoseHeader *, const SamplingPoseHeader *, const SamplingPoseHeader *, const SamplingPoseHeader *, s32);
extern void func_0034FE10(SamplingPipeline *, SamplingPoseHeader *);

SamplingPoseHeader *func_0034F430(SamplingPipeline *context, f32 current, f32 previous, f32 rate, s32 count, f32 weight, s32 flags) {
    SamplingPair root, current_pair, previous_pair;
    SamplingSpan span;
    SamplingPoseHeader *out;
    func_0034FE70(&root);
    func_0034FE70(&current_pair);
    func_0034FE70(&previous_pair);
    func_0034FE88(&root, count, current, rate, weight);
    func_0034FFA0(&current_pair, count, current, rate, weight);
    func_0034FFA0(&previous_pair, count, previous, rate, weight);
    func_0034F360(&span, current_pair.first, previous_pair.first, count);
    if (!func_0034F980(context, &span.headers[0], span.first, flags)) return NULL;
    if (!func_0034FAF8(context, &span.headers[3], &span.headers[0], &span.headers[0])) return NULL;
    if (!func_0034FA60(context, &span.headers[4], &span.headers[0], span.second, flags)) return NULL;
    if (!func_0034FC80(context, &span.headers[1], &span.headers[0], &current_pair, flags)) return NULL;
    out = func_0034FB58(context, &span.headers[0], &root, flags);
    if (out == NULL) return NULL;
    if (current == 0.0f && previous == 0.0f) func_00344020(out, &span.headers[1]);
    else {
        if (!func_0034FC80(context, &span.headers[2], &span.headers[0], &previous_pair, flags)) return NULL;
        func_00343A30(out, &span.headers[1], &span.headers[2], &span.headers[3], &span.headers[4], 0);
    }
    func_0034FE10(context, out);
    return out;
}
#endif
