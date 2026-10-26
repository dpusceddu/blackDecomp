#include "include_asm.h"
#include "game/audio_command_stream.h"

u32* AudioCommandStream_SetValues(Recovered_AudioCommandStream* self, u32 firstValue, u32 secondValue, u32 thirdValue,
                                  u32 wide) {
    u32* payload = AudioCommandStream_Append(self, 0x8050, 4);

    payload[3] = wide;
    payload[0] = firstValue;
    payload[1] = secondValue;
    payload[2] = thirdValue;
    self->unk_2418 = firstValue;
    self->unk_2874 = secondValue;
    self->unk_2878 = thirdValue;
    self->wide = wide;
    self->unk_288D = 0;
    self->unk_288C = 0;
    return payload;
}

// Start/Stop are descriptive state-flow names; native command meanings are UNVERIFIED.
// State 2 -> 3 sends operation 0x8020 synchronously; state 3 -> 2 sends 0x30.
void AudioCommandStream_Start(Recovered_AudioCommandStream* self) {
    s32 requiredState = 2;

    if (self->state == requiredState) {
        AudioCommandStream_Append(self, 0x8020, 0);
        AudioCommandStream_Submit(self, 1);
        self->state = 3;
    }
}

void AudioCommandStream_Stop(Recovered_AudioCommandStream* self) {
    s32 requiredState = 3;

    if (self->state == requiredState) {
        AudioCommandStream_Append(self, 0x30, 0);
        AudioCommandStream_Submit(self, 1);
        self->state = 2;
    }
}
#ifdef NON_MATCHING
extern s32 func_0036B300(void* client);
extern s32 func_0036B100(void* client, u32 operation, s32 asynchronous, void* packet, u32 bytes, void* output,
                         u32 outputBytes, void* callback, void* callbackArgument);

// Unmatched: call-argument scheduling differs; the native return contract is UNVERIFIED.
void AudioCommandStream_Submit(Recovered_AudioCommandStream* self, s32 synchronous) {
    s32 asynchronous = synchronous == 0;
    if (*self->commandCount) {
        void* client = self->client;

        func_0036B300(client);
        func_0036B100(client, 0x101079, asynchronous, self->packet, 0x400, 0, 0, 0, 0);
        *self->commandCount = 0;
        self->writeCursor = &self->packet[1];
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286698", func_002867F0);
#endif
extern f64 func_0029D5B0(f64 angle);

// Write 48 kHz samples, retaining the unsigned phase for the next buffer.
// UNVERIFIED: caller policy for nonfinite or out-of-range conversions.
u32 AudioCommandStream_GenerateTone(Recovered_AudioCommandStream* self, s16* output, s32 count, u32 phase,
                                    f32 frequency) {
    f32 angularFrequency;
    f32 sampleRate = 48000.0f;

    if (frequency > 24000.0f) { frequency = 24000.0f; }
    if (count > 0) {
        s32 remaining = count;
        angularFrequency = frequency * 6.28318530717958647692f;
        do {
            f32 angle = angularFrequency * (f32)phase / sampleRate;
            --remaining;
            phase++;
            *output++ = (s32)(func_0029D5B0((f64)angle) * (0.7f * 32767.0f));
        } while (remaining);
    }
    return phase;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286698", func_00286990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286698", func_00286C10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_286698", func_00286CA0);
