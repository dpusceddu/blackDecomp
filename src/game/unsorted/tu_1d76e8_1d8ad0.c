#include "game/audio_playback_control.h"

extern s32 func_001D9100(Recovered_PlaybackRequest*, u64, Recovered_StreamRange*);

s32 AudioPlaybackControl_PollFinished(Recovered_AudioPlaybackControl* self) {
    switch (self->state) {
        case 4:
            if (!func_001D9100(self->request, self->descriptor->key,
                               self->descriptor->variantData + self->variantIndex))
                break;
            self->state = 5;
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
            if (self->request && !self->request->vtable->pollComplete.function(
                                     (u8*)self->request + self->request->vtable->pollComplete.thisAdjustment))
                break;
            self->state = 8;
        case 8: {
            s32 remaining = 1;
            void** channel = &self->channels[1];
            do {
                *channel = 0;
                remaining--;
                channel--;
            } while (remaining >= 0);
        }
            self->channelCount = 0;
            self->mode = 0;
            self->descriptor = 0;
            goto complete;
        default: break;
    }
    return 0;
complete:
    return 1;
}
