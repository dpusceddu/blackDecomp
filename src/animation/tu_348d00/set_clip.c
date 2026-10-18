#include "animation/channel_state.h"
extern AnimationChannelState *func_00348E30(AnimationChannelState *, s32);
extern void func_00350570(AnimationChannelState *, s32, f32, s32);
s32 func_00348E88(f32 time, AnimationChannelState *state, s32 clip, s32 flags, s32 index) {
    s32 result = 0;
    if (clip != -1) {
        func_00350570(func_00348E30(state, index), clip, time, flags);
        result = 1;
        state->flags &= 0xffdfffff;
    }
    state->flags &= 0xedfffffe;
    return result;
}
