#include "animation/packed_tracks.h"
extern void Track_EvaluateAt(const u8 **, f32, TrackVector *) __asm__("func_003443E0");
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
