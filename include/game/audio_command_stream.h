#ifndef GAME_AUDIO_COMMAND_STREAM_H
#define GAME_AUDIO_COMMAND_STREAM_H
#include "ps2/prelude.h"

/* Native command-packet and client storage. The original class identity,
 * unaccessed bytes, full extents and meanings of raw configuration values are
 * UNVERIFIED. Only offsets used by the recovered command path are modeled. */
typedef struct {
    u8 unk_00[0x2400];
    u32 firstValues[6];
    u32 unk_2418;
    u32 secondValues[6];
    u32 chunkSize;
    u8 unk_2438[8];
    u32 packet[256];
    u8 client[0x28];
    u32* commandCount;
    u32* writeCursor;
    s32 state;
    u32 unk_2874, unk_2878, unk_287C;
    u8 unk_2880[12];
    u8 unk_288C, unk_288D, wide, unk_288F;
} Recovered_AudioCommandStream;

typedef struct {
    u32 pairs[6][2];
    u32 firstValue, secondValue, thirdValue;
    u8 wide;
} Recovered_AudioStreamConfiguration;

typedef char AudioCommandPacketOffset[(u32)&((Recovered_AudioCommandStream*)0)->packet == 0x2440 ? 1 : -1];
typedef char AudioCommandClientOffset[(u32)&((Recovered_AudioCommandStream*)0)->client == 0x2840 ? 1 : -1];
typedef char AudioCommandCountOffset[(u32)&((Recovered_AudioCommandStream*)0)->commandCount == 0x2868 ? 1 : -1];
typedef char AudioCommandStateOffset[(u32)&((Recovered_AudioCommandStream*)0)->state == 0x2870 ? 1 : -1];
typedef char AudioCommandWideOffset[(u32)&((Recovered_AudioCommandStream*)0)->wide == 0x288E ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
u32* AudioCommandStream_Append(Recovered_AudioCommandStream* self, u32 operation, u32 payloadWords);
u32* AudioCommandStream_SetValues(Recovered_AudioCommandStream* self, u32 firstValue, u32 secondValue,
                                  u32 thirdValue, u32 wide);
// UNVERIFIED: original return contract; the recovered command wrappers discard it.
void AudioCommandStream_Submit(Recovered_AudioCommandStream* self, s32 synchronous) __asm__("func_002867F0");
#ifdef __cplusplus
}
#endif
#endif
