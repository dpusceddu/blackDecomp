#include "animation/channel_state.h"

extern s32 func_00348E88(AnimationChannelState *, s32, s32, s32, f32);
extern s32 func_00348F28(AnimationChannelState *, s32, s32, s32, s32, f32);

s32 func_00349128(AnimationChannelState *state, s32 clip, s32 index) {
    if (state != NULL) return func_00348E88(state, clip, 0, index, 0.0f);
    return 0;
}

s32 func_003491E8(AnimationChannelState *state, s32 clip, s32 index, s32 unused, s32 flags) {
    if (state != NULL) return func_00348F28(state, clip, flags, 0, index, 0.0f);
    return 0;
}
