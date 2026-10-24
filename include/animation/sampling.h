#ifndef BLACK_ANIMATION_SAMPLING_PIPELINE_H
#define BLACK_ANIMATION_SAMPLING_PIPELINE_H
#include "ps2/prelude.h"

/* Inferred sampling views; offsets and temporary extents follow the PS2 callers. */
typedef struct SamplingClip {
    u8 unknown_00[12];
    /* Legacy bone_count spelling is retained for compatibility. PS2 passes
       this field as extraction flags to3438E0; it is not a joint count. */
    s32 bone_count, root_track;
    u8 unknown_14[0x4c];
    f32 scale; /* Unverified: ScaleRoot34FE10 reads OWNER+60, not clip+60. */
} SamplingClip;
typedef struct SamplingPipeline { void *owner; SamplingClip *clip; } SamplingPipeline;
typedef struct SamplingPoseHeader { u8 storage[32]; } __attribute__((aligned(16))) SamplingPoseHeader;
typedef struct SamplingPair { s32 first, second; f32 weight; u8 wrapped, unknown0d[3]; } SamplingPair;
typedef struct SamplingSpan {
    s32 first, second, count, reserved;
    SamplingPoseHeader headers[5];
} SamplingSpan;
/* 34FE70 clears only the byte at pair+C; 34FE88/34FFA0 use it as a wrap flag.
   The trailing three bytes and span padding are unverified payload.
   Do not substitute the Xbox 12-byte pair. */
typedef char ModSamplingPipeline8[sizeof(SamplingPipeline)==8?1:-1];
typedef char ModSamplingPair16[sizeof(SamplingPair)==16?1:-1];
typedef char ModSamplingSpan176[sizeof(SamplingSpan)==176?1:-1];
typedef char ModSamplingPose32[sizeof(SamplingPoseHeader)==32?1:-1];
#ifdef __cplusplus
extern "C" {
#endif
extern SamplingPoseHeader *func_00343FC8(SamplingPoseHeader *);
extern s32 func_00344008(SamplingPoseHeader *);
extern s32 func_00344020(SamplingPoseHeader *, const SamplingPoseHeader *);
extern s32 func_003438E0(SamplingPoseHeader *, const SamplingPoseHeader *, const SamplingPoseHeader *, s32);
extern void *func_003461F0(void);
extern void *func_0034F950(SamplingPipeline *, s32, s32);
extern s32 func_00347558(SamplingPoseHeader *, void *, SamplingClip *, f32, s32, s32);
extern SamplingPair *func_0034FE70(SamplingPair *);
extern SamplingSpan *func_0034F360(SamplingSpan *, s32, s32, s32);
extern SamplingPipeline *func_0034F420(SamplingPipeline *, void *, SamplingClip *);
#ifdef __cplusplus
}
#endif
#endif
