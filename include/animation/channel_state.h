#ifndef BLACK_ANIMATION_CHANNEL_STATE_H
#define BLACK_ANIMATION_CHANNEL_STATE_H
#include "ps2/prelude.h"

/* Inferred channel view; offsets are the USA PS2 accesses. */
typedef struct AnimationChannelState {
    s32 flags;
    u8 unknown_004[12];
    s32 clip;
    u8 unknown_014[4];
    f32 playback_time;
    u8 unknown_01c[0x980];
    s32 fade_direction;
    f32 fade_time;
    f32 fade_duration;
    s32 fade_mode;
    struct AnimationChannelState *next;
} AnimationChannelState;
typedef char AnimationChannelFadeOffset[(unsigned)&((AnimationChannelState *)0)->fade_direction == 0x99c ? 1 : -1];
typedef char AnimationChannelNextOffset[(unsigned)&((AnimationChannelState *)0)->next == 0x9ac ? 1 : -1];
#endif
