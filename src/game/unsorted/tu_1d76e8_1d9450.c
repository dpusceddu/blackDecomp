#include "game/playback_state_pool.h"
void PlaybackState_SetBuffers(Recovered_PlaybackState* self, Recovered_StreamBuffer** buffers, s32 count) {
    s32 i;
    if (!count || !buffers) {
        for (i = 0; i < self->bufferCount; i++) {
            StreamBuffer_TryReset(self->buffers[i]);
            self->buffers[i] = 0;
        }
        self->bufferCount = 0;
    } else {
        self->bufferCount = count;
        for (i = 0; i < self->bufferCount; i++) self->buffers[i] = *buffers++;
    }
}

extern void* func_0036CD08(s32, s32, void*);
extern void* func_00107D20(u32);
/* Native call-site view; the initializer's returned value is discarded. */
extern void func_001DCDC0(Recovered_PlaybackState*, u64, u32, s32, s32, void*, s32, s8, s8, u8);
void PlaybackStatePool_Initialize(Recovered_PlaybackStatePool* self, const Recovered_PlaybackStateDefinition* first,
                                  s32 count, const Recovered_PlaybackStateDefinition* second, s32 extendedCount) {
    s32 bytes = 0;
    s32 i;
    self->extendedStateCount = extendedCount;
    self->stateCount = count;
    for (i = 0; i < count; i++) {
        s32 required = first[i].dataSize;
        if (first[i].unk_0C == 5) required = (required / 19) * 64;
        if (bytes < required) bytes = required;
    }
    for (i = 0; i < self->extendedStateCount; i++) {
        s32 required = second[i].dataSize;
        if (second[i].unk_0C == 5) required = (required / 19) * 64;
        if (bytes < required) bytes = required;
    }
    self->scratchBytes = bytes;
    self->scratch = func_0036CD08(0, bytes, 0);
    self->unk_18 = 0;
    self->states = func_00107D20(self->stateCount * sizeof(Recovered_PlaybackState));
    for (i = 0; i < self->stateCount; i++) {
        const Recovered_PlaybackStateDefinition* definition = &first[i];
        func_001DCDC0(&self->states[i], definition->key, definition->unk_08, definition->unk_0C, definition->dataSize,
                      self->scratch, self->unk_18, definition->unk_14, definition->unk_15, definition->unk_16);
    }
    self->extendedStates = func_00107D20(self->extendedStateCount * sizeof(Recovered_ExtendedPlaybackState));
    for (i = 0; i < self->extendedStateCount; i++) {
        const Recovered_PlaybackStateDefinition* definition = &second[i];
        func_001DCDC0(&self->extendedStates[i].state, definition->key, definition->unk_08, definition->unk_0C,
                      definition->dataSize, self->scratch, self->unk_18, definition->unk_14, definition->unk_15,
                      definition->unk_16);
    }
}
