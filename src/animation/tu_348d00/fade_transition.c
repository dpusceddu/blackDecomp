#include "animation/channel_state.h"
typedef struct ChannelTransition {
    u8 unknown_000[0x20];
    f32 duration_frames;
    u8 unknown_024[4];
    s32 mode;
} ChannelTransition;
extern AnimationChannelState *func_00348E30(AnimationChannelState *, s32);
extern void func_00350570(AnimationChannelState *, s32, s32, f32);
extern ChannelTransition *func_003507C0(AnimationChannelState *, s32);

s32 func_00348F28(f32 time, AnimationChannelState *state, s32 clip, s32 fade, s32 flags, s32 index) {
    s32 result = 0;
    state = func_00348E30(state, index);
    if (state != NULL) {
        if (clip != -1) {
            func_00350570(state, clip, flags, time);
            result = 1;
            state->flags &= ~0x80;
            state->playback_time = -1.0f;
            if (fade != 0) {
                s32 old_direction = state->fade_direction;
                f32 old_time = state->fade_time;
                ChannelTransition *transition;
                state->fade_direction = 1;
                transition = func_003507C0(state, clip);
                if (transition != NULL) {
                    state->fade_duration = transition->duration_frames / 59.94f;
                    state->fade_mode = transition->mode;
                } else {
                    state->fade_mode = 0;
                    state->fade_duration = 0.3f;
                }
                if (clip == state->clip && old_direction < 0) {
                    state->fade_time = state->fade_duration * (1.0f - old_time / 0.3f);
                    if (state->fade_time < 0.0f) state->fade_time = 0.0f;
                } else {
                    state->fade_time = 0.0f;
                }
            }
            state->flags &= 0xffdfffff;
        }
        state->flags &= 0xedfffffe;
    }
    return result;
}
