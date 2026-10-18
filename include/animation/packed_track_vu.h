#ifndef BLACK_ANIMATION_PACKED_TRACK_VU_H
#define BLACK_ANIMATION_PACKED_TRACK_VU_H
#include "animation/packed_tracks.h"

/* Inferred VU primitives; masked xyz operations retain the destination's w lane. */
#define TRACK_VU_HELPERS(suffix, lanes, initial, access) \
static __inline__ void Track_Add##suffix(TrackVector *out, const TrackVector *left, const TrackVector *right) { \
    s128 result initial, a = *(const s128 *)left, b = *(const s128 *)right; \
    __asm__("vadd." lanes " resultv, leftv, rightv" : access(result) : "j leftv"(a), "j rightv"(b)); \
    *(s128 *)out = result; \
} \
static __inline__ void Track_Sub##suffix(TrackVector *out, const TrackVector *left, const TrackVector *right) { \
    s128 result initial, a = *(const s128 *)left, b = *(const s128 *)right; \
    __asm__("vsub." lanes " resultv, leftv, rightv" : access(result) : "j leftv"(a), "j rightv"(b)); \
    *(s128 *)out = result; \
} \
static __inline__ void Track_Mul##suffix(TrackVector *out, const TrackVector *left, const TrackVector *right) { \
    s128 result initial, a = *(const s128 *)left, b = *(const s128 *)right; \
    __asm__("vmul." lanes " resultv, leftv, rightv" : access(result) : "j leftv"(a), "j rightv"(b)); \
    *(s128 *)out = result; \
} \
static __inline__ void Track_Madd##suffix(TrackVector *out, const TrackVector *base, const TrackVector *gradient, f32 time) { \
    s128 result initial, a = *(const s128 *)base, b = *(const s128 *)gradient, scale; \
    __asm__("qmtc2.ni timebits, scalev" : "=j scalev"(scale) : "r timebits"(time)); \
    __asm__("vaddax." lanes " ACC, basev, vf0x\n\tvmaddx." lanes " resultv, gradientv, scalevx" \
        : access(result) : "j basev"(a), "j gradientv"(b), "j scalev"(scale)); \
    *(s128 *)out = result; \
}
TRACK_VU_HELPERS(3, "xyz", = *(s128 *)out, "+j resultv")
TRACK_VU_HELPERS(4, "xyzw", , "=j resultv")
#undef TRACK_VU_HELPERS
static __inline__ void Track_Copy3(TrackVector *out, const TrackVector3 *in) {
    out->x = in->x; out->y = in->y; out->z = in->z;
}
#endif
