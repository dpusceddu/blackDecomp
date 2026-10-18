#ifndef BLACK_ANIMATION_PACKED_TRACKS_H
#define BLACK_ANIMATION_PACKED_TRACKS_H
#include "auto/prelude.h"

/* Inferred packed-track kinds; the four-byte prefix and widths follow the PS2 switches. */
typedef struct TrackVector { f32 x, y, z, w; } __attribute__((aligned(16))) TrackVector;
typedef struct TrackVector3 { f32 x, y, z; } TrackVector3;
typedef struct TrackBone { TrackVector rotation, translation; } TrackBone;
typedef struct TrackPose { u8 header[32]; TrackBone bones[1]; } TrackPose;
static __inline__ s32 Track_Count(const u8 *track) { return track[1] + (track[2] << 8); }
extern const u8 *func_003441D0(const u8 *, TrackVector *);
extern const u8 *func_00344240(const u8 *);
extern void func_003443E0(const u8 **, TrackVector *, f32);
extern const u8 *D_003D20D8;
extern s32 D_003D20DC;
#endif
