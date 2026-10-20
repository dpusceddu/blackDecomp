#include "mod/animation/sampling.h"
void *func_0034F9D0(SamplingPipeline *context, SamplingPoseHeader *header, s32 index, s32 flags) {
    u8 *pose = (u8 *)func_0034F950(context, index, flags);
    SamplingClip *clip;
    s32 root;
    if (pose == NULL) return NULL;
    clip = context->clip;
    root = clip->root_track;
    if (root < 0) func_00344008((SamplingPoseHeader *)pose);
    else func_003438E0((SamplingPoseHeader *)pose, (SamplingPoseHeader *)(pose + 0x20 + root * 0x20), header, clip->bone_count);
    return pose;
}
