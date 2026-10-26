#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/playback_state_pool.h"

s32 func_001D96E8(void) {
    return 1;
}

void func_001D96F0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8_1d96e8", func_001D96F8);
Recovered_PlaybackState* PlaybackStatePool_Acquire(Recovered_PlaybackStatePool* self, u64 key) {
    s32 i;
    for (i = 0; i < self->stateCount; i++) {
        Recovered_PlaybackState* state = &self->states[i];
        if (state->poolKey == key && !state->claimed) {
            state->claimed = 1;
            return state;
        }
    }
    return 0;
}

void PlaybackStatePool_Release(Recovered_PlaybackStatePool* self, Recovered_PlaybackState* state) {
    state->claimed = 0;
}

Recovered_PlaybackState* PlaybackStatePool_AcquireExtended(Recovered_PlaybackStatePool* self, u64 key) {
    s32 i;
    for (i = 0; i < self->extendedStateCount; i++) {
        Recovered_ExtendedPlaybackState* state = &self->extendedStates[i];
        if (state->state.poolKey == key && !state->state.claimed) {
            state->state.claimed = 1;
            return &state->state;
        }
    }
    return 0;
}

void PlaybackStatePool_ReleaseExtended(Recovered_PlaybackStatePool* self, Recovered_PlaybackState* state) {
    state->claimed = 0;
}
