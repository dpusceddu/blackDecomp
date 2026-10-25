#include "include_asm.h"

#include "animation/packed_tracks.h"
extern void Track_EvaluateAt(const u8 **, f32, TrackVector *) __asm__("func_003443E0");

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_3441d0_sample_bone", func_003441D0);
#endif

#ifdef NON_MATCHING
// Unmatched: switch body folding, loop padding and jump-table layout.
#include "animation/packed_tracks.h"
const u8 *func_00344240(const u8 *bytes) {
    s32 length;
    const u8 *cursor;
    s32 remaining;
    switch (bytes[0]) {
    case 0: length = Track_Count(bytes) * 4; break;
    case 6: length = Track_Count(bytes) * 12; break;
    case 7: length = (Track_Count(bytes) * 3 + 27) & 0xfffffffc; break;
    case 8: length = (Track_Count(bytes) * 6 + 27) & 0xfffffffc; break;
    case 9: case 17: return bytes + 4;
    case 2: case 10: return bytes + 16;
    case 3: case 11: return bytes + 28;
    case 4: case 12: return bytes + 40;
    case 5: case 13: return bytes + 52;
    case 14: length = (((const volatile u8 *)bytes)[1] + (((const volatile u8 *)bytes)[2] << 8)) * 12; break;
    case 15: length = (Track_Count(bytes) * 4 + 27) & 0xfffffffc; break;
    case 16: length = (Track_Count(bytes) * 8 + 27) & 0xfffffffc; break;
    case 1:
        cursor = bytes + 4;
        remaining = Track_Count(bytes);
        if (remaining != 0) {
            do { --remaining; cursor = func_00344240(cursor); } while (remaining != 0);
        }
        return cursor;
    default: return NULL;
    }
    return bytes + length + 4;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_3441d0_sample_bone", func_00344240);
#endif

#ifdef NON_MATCHING
// Unmatched: VU register allocation, temporary layout and jump-table ownership; full body score 781.
#include "animation/packed_track_vu.h"
void func_003443E0(const u8 **stream, TrackVector *out, f32 time) {
    const u8 *track = *stream;
    const u8 *cursor = track + 4;
    TrackVector a, b, c, d;
    s32 frame, count, i;
    f32 fraction;
    switch (track[0]) {
    case 0: {
        const f32 *samples = (const f32 *)cursor;
        frame = (s32)time;
        fraction = time - (f32)frame;
        out->x = samples[frame];
        if (fraction >= 0.01f) out->x += fraction * (samples[frame + 1] - out->x);
        cursor += Track_Count(track) * 4;
        break;
    }
    case 1:
        count = Track_Count(track);
        i = 0;
        if (count != 0) {
            do {
                f32 span = (f32)Track_Count(cursor) - 1.0f;
                if (time <= span) {
                    func_003443E0(&cursor, out, time);
                    ++i;
                    while (i < count) { cursor = func_00344240(cursor); ++i; }
                    break;
                }
                ++i;
                cursor = func_00344240(cursor);
                time -= span;
            } while (i < count);
        }
        break;
    case 2:
        Track_Copy3(out, (const TrackVector3 *)cursor);
        cursor += 12;
        break;
    case 3:
        Track_Copy3(&a, (const TrackVector3 *)cursor);
        Track_Copy3(&b, (const TrackVector3 *)(cursor + 12));
        Track_Madd3(out, &b, &a, time);
        cursor += 24;
        break;
    case 4:
        Track_Copy3(&a, (const TrackVector3 *)cursor);
        Track_Copy3(&b, (const TrackVector3 *)(cursor + 12));
        Track_Copy3(&c, (const TrackVector3 *)(cursor + 24));
        Track_Madd3(&b, &b, &a, time);
        Track_Madd3(out, &c, &b, time);
        cursor += 36;
        break;
    case 5:
        Track_Copy3(&a, (const TrackVector3 *)cursor);
        Track_Copy3(&b, (const TrackVector3 *)(cursor + 12));
        Track_Copy3(&c, (const TrackVector3 *)(cursor + 24));
        Track_Copy3(&d, (const TrackVector3 *)(cursor + 36));
        Track_Madd3(&b, &b, &a, time);
        Track_Madd3(&c, &c, &b, time);
        Track_Madd3(out, &d, &c, time);
        cursor += 48;
        break;
    case 6: {
        const TrackVector3 *samples = (const TrackVector3 *)cursor;
        frame = (s32)time;
        fraction = time - (f32)frame;
        Track_Copy3(&a, samples + frame);
        if (fraction < 0.01f) Track_Copy3(out, (const TrackVector3 *)&a);
        else {
            Track_Copy3(&b, samples + frame + 1);
            Track_Sub3(&b, &b, &a);
            Track_Madd3(out, &a, &b, fraction);
        }
        cursor += Track_Count(track) * 12;
        break;
    }
    case 7: {
        const u8 *samples = cursor + 24;
        frame = (s32)time * 3;
        fraction = time - (f32)(s32)time;
        Track_Copy3(&a, (const TrackVector3 *)cursor);
        Track_Copy3(&b, (const TrackVector3 *)(cursor + 12));
        c.x = (f32)samples[frame]; c.y = (f32)samples[frame + 1]; c.z = (f32)samples[frame + 2];
        Track_Mul3(&c, &c, &b);
        Track_Add3(&c, &c, &a);
        if (fraction >= 0.01f) {
            d.x = (f32)samples[frame + 3]; d.y = (f32)samples[frame + 4]; d.z = (f32)samples[frame + 5];
            Track_Mul3(&d, &d, &b);
            Track_Add3(&d, &d, &a);
            Track_Sub4(&d, &d, &c);
            Track_Madd3(&c, &c, &d, fraction);
        }
        Track_Copy3(out, (const TrackVector3 *)&c);
        cursor += 24 + ((Track_Count(track) * 3 + 3) & ~3);
        break;
    }
    case 8: {
        const u16 *samples = (const u16 *)(cursor + 24);
        frame = (s32)time * 3;
        fraction = time - (f32)(s32)time;
        Track_Copy3(&a, (const TrackVector3 *)cursor);
        Track_Copy3(&b, (const TrackVector3 *)(cursor + 12));
        c.x = (f32)samples[frame]; c.y = (f32)samples[frame + 1]; c.z = (f32)samples[frame + 2];
        Track_Mul3(&c, &c, &b);
        Track_Add3(&c, &c, &a);
        if (fraction >= 0.01f) {
            d.x = (f32)samples[frame + 3]; d.y = (f32)samples[frame + 4]; d.z = (f32)samples[frame + 5];
            Track_Mul3(&d, &d, &b);
            Track_Add3(&d, &d, &a);
            Track_Sub4(&d, &d, &c);
            Track_Madd3(&c, &c, &d, fraction);
        }
        Track_Copy3(out, (const TrackVector3 *)&c);
        cursor += 24 + ((Track_Count(track) * 6 + 3) & ~3);
        break;
    }
    case 9:
        out->z = 0.0f; out->x = 0.0f; out->y = 0.0f;
        break;
    case 10:
        cursor = func_003441D0(cursor, out);
        break;
    case 11:
        cursor = func_003441D0(cursor, &a);
        cursor = func_003441D0(cursor, &b);
        Track_Madd4(out, &b, &a, time);
        break;
    case 12:
        cursor = func_003441D0(cursor, &a);
        cursor = func_003441D0(cursor, &b);
        cursor = func_003441D0(cursor, &c);
        Track_Madd4(&b, &b, &a, time);
        Track_Madd4(out, &c, &b, time);
        break;
    case 13:
        cursor = func_003441D0(cursor, &a);
        cursor = func_003441D0(cursor, &b);
        cursor = func_003441D0(cursor, &c);
        cursor = func_003441D0(cursor, &d);
        Track_Madd4(&b, &b, &a, time);
        Track_Madd4(&c, &c, &b, time);
        Track_Madd4(out, &d, &c, time);
        break;
    case 14: {
        const u8 *next;
        frame = (s32)time;
        fraction = time - (f32)frame;
        next = func_003441D0(cursor + frame * 16, &a);
        if (fraction < 0.01f) *out = a;
        else {
            func_003441D0(next, &b);
            Track_Sub4(&b, &b, &a);
            Track_Madd4(out, &a, &b, fraction);
        }
        cursor += Track_Count(track) * 12;
        break;
    }
    case 15: {
        const u8 *samples;
        cursor = func_003441D0(cursor, &a);
        cursor = func_003441D0(cursor, &b);
        samples = cursor;
        frame = (s32)time * 4;
        fraction = time - (f32)(s32)time;
        c.x = (f32)samples[frame]; c.y = (f32)samples[frame + 1]; c.z = (f32)samples[frame + 2]; c.w = (f32)samples[frame + 3];
        Track_Mul4(&c, &c, &b);
        Track_Add4(&c, &c, &a);
        if (fraction >= 0.01f) {
            d.x = (f32)samples[frame + 4]; d.y = (f32)samples[frame + 5]; d.z = (f32)samples[frame + 6]; d.w = (f32)samples[frame + 7];
            Track_Mul4(&d, &d, &b);
            Track_Add4(&d, &d, &a);
            Track_Sub4(&d, &d, &c);
            Track_Madd4(&c, &c, &d, fraction);
        }
        *out = c;
        cursor += Track_Count(track) * 4;
        break;
    }
    case 16: {
        const u16 *samples;
        cursor = func_003441D0(cursor, &a);
        cursor = func_003441D0(cursor, &b);
        samples = (const u16 *)cursor;
        frame = (s32)time * 4;
        fraction = time - (f32)(s32)time;
        c.x = (f32)samples[frame]; c.y = (f32)samples[frame + 1]; c.z = (f32)samples[frame + 2]; c.w = (f32)samples[frame + 3];
        Track_Mul4(&c, &c, &b);
        Track_Add4(&c, &c, &a);
        if (fraction >= 0.01f) {
            d.x = (f32)samples[frame + 4]; d.y = (f32)samples[frame + 5]; d.z = (f32)samples[frame + 6]; d.w = (f32)samples[frame + 7];
            Track_Mul4(&d, &d, &b);
            Track_Add4(&d, &d, &a);
            Track_Sub4(&d, &d, &c);
            Track_Madd4(&c, &c, &d, fraction);
        }
        *out = c;
        cursor += Track_Count(track) * 8;
        break;
    }
    case 17:
        out->x = 0.0f; out->w = 1.0f; out->y = 0.0f; out->z = 0.0f;
        break;
    default:
        out->x = 0.0f;
        break;
    }
    *stream = cursor;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_3441d0_sample_bone", func_003443E0);
#endif

#ifdef NON_MATCHING
// Unmatched: masked-loop pointer, index and callback register allocation.
#include "animation/packed_tracks.h"
extern void Track_EvaluateAt(f32, const u8 **, TrackVector *) __asm__("func_003443E0");
void func_003452B0(TrackPose *out, const u8 *bytes, s32 count, f32 time) {
    const u8 *cursor = bytes;
    s32 i, limit;
    TrackVector *rotation, *translation;
    if (D_003D20D8 == NULL) {
        rotation = &out->bones[0].rotation;
        translation = &out->bones[0].translation;
        if (count > 0) {
            s32 remaining = count;
            do {
                Track_EvaluateAt(time, &cursor, rotation);
                Track_EvaluateAt(time, &cursor, translation);
                rotation = (TrackVector *)((u8 *)rotation + 32); translation = (TrackVector *)((u8 *)translation + 32);
                --remaining;
            } while (remaining != 0);
        }
        return;
    }
    limit = D_003D20DC < count ? D_003D20DC : count;
    i = 0;
    rotation = &out->bones[0].rotation;
        translation = &out->bones[0].translation;
    if (limit > 0) {
        do {
            if (D_003D20D8[i]) {
                Track_EvaluateAt(time, &cursor, rotation);
                Track_EvaluateAt(time, &cursor, translation);
            } else {
                cursor = func_00344240(cursor);
                cursor = func_00344240(cursor);
                rotation->x = 0.0f;
                rotation->y = 0.0f;
                rotation->z = 0.0f;
                rotation->w = 1.0f;
                translation->x = 0.0f;
                translation->y = 0.0f;
                translation->z = 0.0f;
                translation->w = 0.0f;
            }
            ++i; rotation = (TrackVector *)((u8 *)rotation + 32); translation = (TrackVector *)((u8 *)translation + 32);
        } while (i < limit);
    }
    if (i < count) {
        s32 remaining = count - i;
        do {
            rotation->x = 0.0f;
            rotation->y = 0.0f;
            rotation->z = 0.0f;
            rotation->w = 1.0f;
            translation->x = 0.0f;
            translation->y = 0.0f;
            translation->z = 0.0f;
            translation->w = 0.0f;
            rotation = (TrackVector *)((u8 *)rotation + 32); translation = (TrackVector *)((u8 *)translation + 32); --remaining;
        } while (remaining != 0);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_3441d0_sample_bone", func_003452B0);
#endif

void func_00345480(TrackBone *out, const u8 *bytes, s32 index, f32 time) {
    const u8 *cursor = bytes;
    if (index > 0) {
        s32 remaining = index;
        do {
            --remaining;
            cursor = func_00344240(cursor);
            cursor = func_00344240(cursor);
        } while (remaining != 0);
    }
    Track_EvaluateAt(&cursor, time, &out->rotation);
    Track_EvaluateAt(&cursor, time, &out->translation);
}
