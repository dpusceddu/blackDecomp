#ifndef BLACK_ANIMATION_SAMPLING_PIPELINE_H
#define BLACK_ANIMATION_SAMPLING_PIPELINE_H
#include "auto/prelude.h"

/* Inferred sampling views; offsets and temporary extents follow the PS2 callers. */
typedef struct SamplingClip {
    u8 unknown_00[12];
    s32 bone_count, root_track;
    u8 unknown_14[0x4c];
    f32 scale;
} SamplingClip;
typedef struct SamplingPipeline { void *owner; SamplingClip *clip; } SamplingPipeline;
typedef struct SamplingPoseHeader { u8 storage[32]; } __attribute__((aligned(16))) SamplingPoseHeader;
typedef struct SamplingPair { s32 first, second; f32 weight; s32 reserved; } SamplingPair;
typedef struct SamplingSpan {
    s32 first, second, count, reserved;
    SamplingPoseHeader headers[5];
} SamplingSpan;
extern SamplingPoseHeader *func_00343FC8(SamplingPoseHeader *);
extern s32 func_00344008(SamplingPoseHeader *);
extern s32 func_00344020(SamplingPoseHeader *, const SamplingPoseHeader *);
extern s32 func_003438E0(SamplingPoseHeader *, const SamplingPoseHeader *, const SamplingPoseHeader *, s32);
extern void *func_003461F0(void);
extern void *func_0034F950(SamplingPipeline *, s32, s32);
extern s32 func_00347558(SamplingPoseHeader *, void *, SamplingClip *, f32, s32, s32);
#endif
