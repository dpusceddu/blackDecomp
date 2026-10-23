#include "animation/channel_state.h"

#ifdef NONMATCHING
// Unmatched: two division hazard NOPs are absent from the compiler output.
extern f32 func_003527E8(f32);
extern void func_003492E0(AnimationChannelState *);
f32 func_00348D00(AnimationChannelState *state, f32 fade_out_duration) {
    f32 weight = 0.0f;
    if (state->fade_direction != 0) {
        if (state->fade_direction > 0) {
            weight = state->fade_time / state->fade_duration;
            if (weight < 1.0f) weight = func_003527E8(weight * 3.1415927f * 0.5f);
            if (weight >= 1.0f) state->fade_direction = 0;
        } else {
            if (fade_out_duration > 0.0f) {
                weight = 1.0f - state->fade_time / fade_out_duration;
                if (weight > 0.0f) weight = func_003527E8(weight * 3.1415927f * 0.5f);
            }
            if (weight <= 0.0f) func_003492E0(state);
        }
    }
    return weight;
}

// Unmatched: assembler moves the short-loop hazard NOP before the branch.
AnimationChannelState *func_00348E30(AnimationChannelState *state, s32 index) {
    s32 position;
    if (state == NULL || index < 0) return NULL;
    state = state->next;
    for (position = 0; position < index; ++position) {
        state = state->next;
        if (state == NULL) break;
    }
    return state;
}

#endif
