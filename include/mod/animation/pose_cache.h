#ifndef BLACK_MOD_ANIMATION_POSE_CACHE_H
#define BLACK_MOD_ANIMATION_POSE_CACHE_H
#include "mod/animation/sampling.h"
/* Instruction-only arena layout3461F0/347738:28slots,0x670 stride,
   root+50Pose headers followed by16unknown bytes. Slot identity and tail
   semantics are unverified. Existing source controls verify the globals only. */
typedef struct BkModPoseCacheSlotPS2 {
    SamplingPoseHeader root,samples[50]; u8 unknown660[16];
} BkModPoseCacheSlotPS2;
/* Exact3487D0/E0/E8 prove frameCount14 and skeletonIndex18. Other clip
   fields remain instruction-only346668/347558/3489A8 views. */
typedef struct BkModSourceClipPS2 {
    u32 hash; u8 unknown04[4]; u32 flags,extractionFlags; s32 rootTrack,frameCount,skeletonIndex; u32 trackFormat; void *tracks;
} BkModSourceClipPS2;
#ifdef __cplusplus
extern "C" {
#endif
extern u8 D_003D20D0;
extern s32 D_003D20D4,D_003D20E0,D_0046A500;
extern u8 *D_003D20D8;
extern s32 D_003D20DC;
#ifdef __cplusplus
}
#endif
static inline void BkModPoseCacheEnablePS2(s8 enabled){D_003D20D0=enabled;}
static inline void BkModPoseCacheClearPS2(void){D_0046A500=0;}
static inline void BkModPoseCacheForceBonePS2(s32 bone){D_003D20E0=bone;}
typedef char PoseCacheSlot670[sizeof(BkModPoseCacheSlotPS2)==0x670?1:-1];
typedef char SourceClipFrame14[(unsigned)&((BkModSourceClipPS2*)0)->frameCount==0x14?1:-1];
typedef char SourceClipSkeleton18[(unsigned)&((BkModSourceClipPS2*)0)->skeletonIndex==0x18?1:-1];
typedef char SourceClipFormat1c[(unsigned)&((BkModSourceClipPS2*)0)->trackFormat==0x1c?1:-1];
typedef char SourceClipTracks20[(unsigned)&((BkModSourceClipPS2*)0)->tracks==0x20?1:-1];
/* ps2/vu0_micro.hpp provides the scoped AnimationMicro::Slerp contract for
   microcall330: inputsVF18/19 andVF28.x, outputVF20, reviewed clobbers and VNOP.
   Keep its per-recipe evidence limits.347558 retains the unused owner/flags
   and original frame/time argument-bank order. */
#endif
