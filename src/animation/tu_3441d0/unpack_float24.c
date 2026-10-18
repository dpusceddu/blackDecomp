#ifdef NONMATCHING
// Unmatched: GPR and FPU scheduling for packed float bit reconstruction.
#include "animation/packed_tracks.h"
static __inline__ f32 Track_FloatBits(u32 bits) { f32 value; __asm__("mtc1 %1,%0" : "=f"(value) : "r"(bits)); return value; }
const u8 *func_003441D0(const u8 *bytes, TrackVector *out) {
    u32 first = *(const u32 *)bytes;
    u32 second, third;
    out->x = Track_FloatBits(first << 8);
    second = *(const u32 *)(bytes + 4);
    out->y = Track_FloatBits(((first >> 16) & 0xff00) | (second << 16));
    third = *(const u32 *)(bytes + 8);
    out->w = Track_FloatBits(third & 0xffffff00);
    out->z = Track_FloatBits(((second & 0xffff0000) >> 8) | (third << 24));
    return bytes + 12;
}
#endif
