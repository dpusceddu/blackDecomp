#include "mod/animation/sampling.h"
s32 func_0034F980(SamplingPipeline *context, SamplingPoseHeader *header, s32 index, s32 flags) {
    SamplingClip *clip = context->clip;
    s32 root = clip->root_track;
    s32 result;
    if (root >= 0) result = func_00347558(header, context->owner, clip, (f32)index, flags, root);
    else result = func_00344008(header);
    return result;
}
