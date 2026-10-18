#ifdef NONMATCHING
// Unmatched: global ordering and float stores differ; ABI-correct opaque variant reaches score 8.
#include "animation/playback_state.h"
extern f32 D_003D4460, D_003D4464;
extern void *func_00350F28(PlaybackState *, void *, void *, f32, f32, s32, s16);
extern void func_00343C28(void *, void *);
extern void func_00351030(PlaybackState *, void *, void *);
void *func_0034F080(PlaybackState *state, void *optional_pose) {
    s32 flags, evaluation;
    f32 coordinate;
    f32 *scale;
    void *pose;
    D_003D4460 = 0.0f;
    D_003D4464 = 0.0f;
    flags = state->flags;
    evaluation = (flags >> 6) & 1;
    if (flags & 0x800) evaluation |= 0x80;
    if (flags & 0x1000) evaluation |= 4;
    if (state->current < state->span) evaluation |= 0x10;
    state->skeleton = -1;
    scale = state->scale;
    scale[0] = 1.0f;
    scale[2] = 1.0f;
    scale[1] = 1.0f;
    state->evaluated_revision = state->revision;
    pose = func_00350F28(state, state->graph, state->bank, state->current, state->previous, evaluation, state->cursor);
    if (state->skeleton == -1) state->skeleton = 0;
    func_00343C28(optional_pose, pose);
    func_00351030(state, state->graph, state->bank);
    if (state->current != state->previous) state->current -= D_003D4460;
    coordinate = state->current + D_003D4464;
    state->previous = coordinate;
    state->current = coordinate;
    return pose;
}
#endif
