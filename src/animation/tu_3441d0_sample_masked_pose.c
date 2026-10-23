#ifdef NONMATCHING
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
#endif
