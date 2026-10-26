#include "game/audio_playback_control.h"

extern void func_001D9250(Recovered_PlaybackRequest*);

void AudioPlaybackControl_RequestState2(Recovered_AudioPlaybackControl* self) {
    switch (self->state) {
        case 0:
        case 1:
        case 2:
        case 8:
        case 9:
        case 10: break;
        case 4:
        case 5: self->pendingState = 2; break;
        case 6:
        case 7: func_001D9250(self->request);
        case 3:
            self->index = -1;
            self->state = 2;
            break;
    }
}
