#include "game/audio_playback_control.h"

extern void* func_00107CF8(s32 size);
extern const Recovered_PlaybackRequestVtable D_003E08D0;
extern void func_00384700(Recovered_AudioPlaybackControl*, f32);
// This native call forwards arguments to a matched no-op producer; its result is unused.
extern s32 PlaybackControl_Notify(Recovered_AudioPlaybackControl*, Recovered_AudioPlaybackControl*, s32,
                                  s32) __asm__("func_001D8D68");

void AudioPlaybackControl_Initialize(Recovered_AudioPlaybackControl* self) {
    Recovered_PlaybackRequest* request = func_00107CF8(0x30);
    const Recovered_PlaybackRequestVtable* vtable = &D_003E08D0;
    self->request = request;
    request->vtable = vtable;
    vtable->initialize.function((u8*)request + vtable->initialize.thisAdjustment);
    self->descriptor = 0;
    self->pendingState = 0;
    self->index = -1;
    func_00384700(self, 1.0f);
    self->unk_8D = 0;
    self->unk_60 = 0;
    self->mode = 0;
    {
        s32 remaining = 1;
        void** channel = &self->channels[1];
        do {
            *channel = 0;
            remaining--;
            channel--;
        } while (remaining >= 0);
    }
    self->channelCount = 0;
    self->state = 0;
}

s32 AudioPlaybackControl_Begin(Recovered_AudioPlaybackControl* self, const u32* values, s32 count,
                               Recovered_AudioPlaybackDescriptor* descriptor) {
    switch (self->state) {
        case 0:
        case 8: {
            Recovered_PlaybackRequest* request = self->request;
            if (!request->vtable->prepare.function((u8*)request + request->vtable->prepare.thisAdjustment, values,
                                                   count, 0xB936093923CCD843ULL))
                return 0;
        }
            if (self->unk_8D) PlaybackControl_Notify(self, self, self->unk_5C, self->unk_60);
            self->descriptor = descriptor;
            self->index = -1;
            if (count > 0) {
                const u32* source = values;
                void** channel = self->channels;
                s32 remaining = count;
                do {
                    *channel = (void*)*source;
                    remaining--;
                    source++;
                    channel++;
                } while (remaining != 0);
            }
            self->channelCount = count;
            self->state = 1;
            self->mode = 0;
            break;
        case 1: self->mode = 0; break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            self->mode = 0;
            AudioPlaybackControl_RequestState2(self);
            break;
    }
    return 1;
}
