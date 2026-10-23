#include "animation/channel_state.h"
// A scoped view adds methods without asserting historical inheritance.
struct AnimationChannelView : AnimationChannelState { float FadeWeight(float); static AnimationChannelState* Lookup(AnimationChannelState*,int); };


#ifdef NONMATCHING
// Unmatched: two division hazard NOPs are absent from the compiler output.
extern "C" f32 func_003527E8(f32);
extern "C" void func_003492E0(AnimationChannelState *);
f32 AnimationChannelView::FadeWeight(f32 fade_out_duration) {
    AnimationChannelState* state=this;
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

#endif

AnimationChannelState *AnimationChannelView::Lookup(AnimationChannelState *state, s32 index) {
    s32 position;
    if (state == 0 || index < 0) return 0;
    state = state->next;
    for (position = 0; position < index; ++position) {
        state = state->next;
        if (state == 0) break;
    }
    return state;
}
