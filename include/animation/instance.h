#ifndef BLACK_MOD_ANIMATION_INSTANCE_H
#define BLACK_MOD_ANIMATION_INSTANCE_H
#include "ps2/ee_types.h"
/* Access view only: no original class identity, inheritance or allocation claim.
   Keep legacy instance/playback/channel semantic views separate. Unknown fields
   and prototype order must not be inferred from an Xbox layout. */
typedef struct BkModAnimationPoseHeaderPS2 {
    float quaternion[4], translation[4];
} BkModAnimationPoseHeaderPS2 __attribute__((aligned(16)));
typedef struct BkModAnimationInstancePS2 {
    EeS32 flags;
    void *collection;
    EeS16 skeleton; EeU8 unknown0a[2];
    void *graph;
    EeU32 graphHash;
    float current, previous, span;
    EeU8 unknown20[0x10];
    BkModAnimationPoseHeaderPS2 root;
    /* Override instruction view3478F0: 12-byte records {pose pointer,bone s32,
       flags u32}; no native control yet proves that complete record contract. */
    void *selectedMatrices, *matrixBase, *jointOverrides;
    EeS16 jointOverrideCount, maximumBones;
    float rootScale, inverseRootScale;
    void *auxiliary;
    EeU8 unknown6c[4];
    void *jointCache;
    EeU8 unknown74[0x10];
    void *owner84_unverified;
    EeU8 history88[8][0x28];
    EeS16 cursor;
    EeU8 unknown1ca[0x7ba];
    void *selectedClip, *scratchBank, *bank;
    EeS32 unknown990;
    void *blendWeights;
    EeS32 evaluationFlags;
    EeU8 unknown99c[0x10];
    struct BkModAnimationInstancePS2 *next;
    void *eventStorage;
    EeU8 unknown9b4[8], eventsActive;
} BkModAnimationInstancePS2;
static inline int BkModAnimationHasNextPS2(const BkModAnimationInstancePS2 *instance) { return instance->next!=0; }
typedef char BkModPoseSize20[sizeof(BkModAnimationPoseHeaderPS2)==0x20?1:-1];
typedef char BkModInstanceRoot30[(unsigned)&((BkModAnimationInstancePS2*)0)->root==0x30?1:-1];
typedef char BkModInstanceFlags998[(unsigned)&((BkModAnimationInstancePS2*)0)->evaluationFlags==0x998?1:-1];
typedef char BkModInstanceNext9AC[(unsigned)&((BkModAnimationInstancePS2*)0)->next==0x9ac?1:-1];
#endif
