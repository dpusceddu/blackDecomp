#ifndef BLACK_ANIMATION_JOINT_OVERRIDES_H
#define BLACK_ANIMATION_JOINT_OVERRIDES_H
#include "animation/instance.h"

/* The exact append establishes the 12-byte stride and three field offsets.
 * UNVERIFIED: the pose/bone/flags meanings inferred from lookup/removal;
 * pose ownership and the individual flag bits remain unknown. */
typedef struct AnimationJointOverride {
    BkAnimationPoseHeaderPS2* pose;
    int bone;
    unsigned flags;
} AnimationJointOverride;

typedef char AnimationJointOverrideSize[sizeof(AnimationJointOverride) == 12 ? 1 : -1];
typedef char AnimationJointOverrideBoneOffset[(unsigned)&((AnimationJointOverride*)0)->bone == 4 ? 1 : -1];
typedef char AnimationJointOverrideFlagsOffset[(unsigned)&((AnimationJointOverride*)0)->flags == 8 ? 1 : -1];
#endif
