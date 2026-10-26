#include "animation/joint_overrides.h"
#include "animation/graph.h"

static inline AnimationJointOverride* Overrides(BkAnimationInstancePS2* instance) {
    return (AnimationJointOverride*)instance->jointOverrides;
}

void AnimationInstance_AppendOverride(BkAnimationInstancePS2*, BkAnimationPoseHeaderPS2*, int, unsigned)
    ANIMATION_FUNCTION(003477F0);
void AnimationInstance_AppendOverride(BkAnimationInstancePS2* instance, BkAnimationPoseHeaderPS2* pose, int bone,
                                      unsigned flags) {
    if (instance->jointOverrideCount < 9) {
        Overrides(instance)[instance->jointOverrideCount].pose = pose;
        Overrides(instance)[instance->jointOverrideCount].bone = bone;
        Overrides(instance)[instance->jointOverrideCount].flags = flags;
        ++instance->jointOverrideCount;
    }
}

void AnimationInstance_RemoveOverride(BkAnimationInstancePS2*, BkAnimationPoseHeaderPS2*) ANIMATION_FUNCTION(00347858);
void AnimationInstance_RemoveOverride(BkAnimationInstancePS2* instance, BkAnimationPoseHeaderPS2* pose) {
    int index;
    for (index = 0; index < instance->jointOverrideCount; ++index) {
        AnimationJointOverride* records = Overrides(instance);
        if (records[index].pose == pose) {
            if (instance->jointOverrideCount >= 2 && index != instance->jointOverrideCount - 1)
                records[index] = records[instance->jointOverrideCount - 1];
            --instance->jointOverrideCount;
            return;
        }
    }
}

void AnimationInstance_FindOverride(BkAnimationInstancePS2*, int, BkAnimationPoseHeaderPS2**, unsigned*)
    ANIMATION_FUNCTION(003478F0);
void AnimationInstance_FindOverride(BkAnimationInstancePS2* instance, int bone, BkAnimationPoseHeaderPS2** pose,
                                    unsigned* flags) {
    int index;
    for (index = 0; index < instance->jointOverrideCount; ++index) {
        if (Overrides(instance)[index].bone == bone) {
            *pose = Overrides(instance)[index].pose;
            *flags = Overrides(instance)[index].flags;
            return;
        }
    }
    *pose = 0;
}
