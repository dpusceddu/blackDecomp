#include "mod/animation/sampling.h"
extern SamplingPoseHeader *func_0034F730(SamplingPipeline *, SamplingPoseHeader *, f32, f32, f32, s32, f32, s32);
SamplingPoseHeader *func_0034F668(SamplingPipeline *context, f32 current, f32 previous, f32 rate, s32 count, f32 weight, s32 flags) {
    SamplingPoseHeader temporary;
    SamplingPoseHeader *result = NULL;
    func_00343FC8(&temporary);
    if (func_0034F730(context, &temporary, current, previous, rate, count, weight, flags)) {
        result = (SamplingPoseHeader *)func_003461F0();
        if (result != NULL) func_00344020(result, &temporary);
    }
    return result;
}
