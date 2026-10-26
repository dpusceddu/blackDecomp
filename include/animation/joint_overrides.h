#ifndef BLACK_ANIMATION_JOINT_OVERRIDES_H
#define BLACK_ANIMATION_JOINT_OVERRIDES_H
#include "animation/instance.h"

/* Exact append, lookup and removal confirm this 12-byte record and its fields.
 * UNVERIFIED: pose ownership and the individual flag meanings. */
typedef struct AnimationJointOverride {
    BkAnimationPoseHeaderPS2* pose;
    int bone;
    unsigned flags;
} AnimationJointOverride;

typedef char AnimationJointOverrideSize[sizeof(AnimationJointOverride) == 12 ? 1 : -1];
typedef char AnimationJointOverrideBoneOffset[(unsigned)&((AnimationJointOverride*)0)->bone == 4 ? 1 : -1];
typedef char AnimationJointOverrideFlagsOffset[(unsigned)&((AnimationJointOverride*)0)->flags == 8 ? 1 : -1];
#endif
