#include "ps2/vu0_micro.hpp"
#include "mod/animation/instance.h"

// Descriptive names; the original pose class identity is unverified.
extern "C" BkModAnimationPoseHeaderPS2 *func_00344178(
    BkModAnimationPoseHeaderPS2 *output, const BkModAnimationPoseHeaderPS2 *a,
    const BkModAnimationPoseHeaderPS2 *b, float weight)
{
    BlackPS2::AnimationMicro::Slerp(output->quaternion, a->quaternion, b->quaternion, weight);
    BlackPS2::AnimationMicro::InterpolateXYZ(output->translation, a->translation,
                                          b->translation, weight);
    return output;
}
