#ifndef GAME_AUDIO_PLAYBACK_CONTROL_H
#define GAME_AUDIO_PLAYBACK_CONTROL_H
#include "game/playback_request.h"

/* Matched controller consumers confirm these access views. Original identities,
 * numeric lifecycle-state meanings, channel ownership, unused storage and total
 * extents remain UNVERIFIED. The native initializer clears
 * two channel slots; no additional input bounds are implied by this view. */
typedef struct {
    u64 key;
    u8 unk_08[0x10];
    Recovered_StreamRange* variantData; // Eight-byte selection stride confirmed by the matched poll.
} Recovered_AudioPlaybackDescriptor;

typedef struct {
    u8 unk_00[0x50];
    void* channels[2];
    s32 channelCount;
    s32 unk_5C, unk_60;
    s32 mode;
    s32 state;
    s32 pendingState;
    s32 variantIndex;
    s32 index;
    u8 unk_78[8];
    f32 gain;
    Recovered_PlaybackRequest* request;
    Recovered_AudioPlaybackDescriptor* descriptor;
    u8 unk_8C, unk_8D;
} Recovered_AudioPlaybackControl;

typedef char AudioPlaybackChannelsOffset[(u32) & ((Recovered_AudioPlaybackControl*)0)->channels == 0x50 ? 1 : -1];
typedef char AudioPlaybackStateOffset[(u32) & ((Recovered_AudioPlaybackControl*)0)->state == 0x68 ? 1 : -1];
typedef char AudioPlaybackRequestOffset[(u32) & ((Recovered_AudioPlaybackControl*)0)->request == 0x84 ? 1 : -1];
typedef char AudioPlaybackDescriptorOffset[(u32) & ((Recovered_AudioPlaybackControl*)0)->descriptor == 0x88 ? 1 : -1];
typedef char AudioPlaybackVariantsOffset[(u32) & ((Recovered_AudioPlaybackDescriptor*)0)->variantData == 0x18 ? 1 : -1];

void AudioPlaybackControl_Initialize(Recovered_AudioPlaybackControl* self);
s32 AudioPlaybackControl_Begin(Recovered_AudioPlaybackControl* self, const u32* values, s32 count,
                               Recovered_AudioPlaybackDescriptor* descriptor);
s32 AudioPlaybackControl_PollFinished(Recovered_AudioPlaybackControl* self);
void AudioPlaybackControl_RequestState2(Recovered_AudioPlaybackControl* self);
void AudioPlaybackControl_ClearChannelState(Recovered_AudioPlaybackControl* self);
#endif
