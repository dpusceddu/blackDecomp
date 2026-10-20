#include "mod/animation/sampling.h"
extern s32 func_0034F980(SamplingPipeline *, SamplingPoseHeader *, s32, s32);
s32 func_0034FA60(SamplingPipeline *context, SamplingPoseHeader *out, SamplingPoseHeader *root, s32 index, s32 flags) {
    SamplingPoseHeader sample;
    s32 result;
    func_00343FC8(&sample);
    if (func_0034F980(context, &sample, index, flags)) result = func_003438E0(out, &sample, root, context->clip->bone_count);
    else result = 0;
    return result;
}
