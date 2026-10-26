#ifndef RW_AUDIO_SAMPLE_H
#define RW_AUDIO_SAMPLE_H
#include "ps2/prelude.h"

/* Accessed native prefixes; full allocation sizes and format identifier names
 * remain unknown. The frame count preserves each format's native rounding. */
typedef struct {
    u8 unk_00[8];
    u8 indexBits;
    u8 unk_09[3];
    u8* storage;
    u8 unk_10[4];
    u32 stride;
} Recovered_AudioHandlePool;

/* UNVERIFIED: the frame-count function remains a draft. */
typedef struct {
    u8 unk_00[4];
    void* format;
    u32 encodedBytes;
    u8 bitsPerSample;
    u8 channels;
} Recovered_AudioSample;

typedef char AudioPoolIndexOffset[(u32) & ((Recovered_AudioHandlePool*)0)->indexBits == 8 ? 1 : -1];
typedef char AudioPoolStrideOffset[(u32) & ((Recovered_AudioHandlePool*)0)->stride == 0x14 ? 1 : -1];
typedef char AudioSampleChannelsOffset[(u32) & ((Recovered_AudioSample*)0)->channels == 0xD ? 1 : -1];
/* UNVERIFIED: native 20-byte default descriptor. Only the leading bit-depth byte is used
 * here; the representation and meanings of the other words are UNVERIFIED. */
typedef struct {
    u8 bitsPerSample;
    u8 unk_01[3];
    u32 unk_04[4];
} Recovered_AudioFormat;
typedef char AudioFormatDescriptorSize[sizeof(Recovered_AudioFormat) == 20 ? 1 : -1];

void* AudioHandle_Resolve(u32 handle);
u32 AudioSample_FrameCount(Recovered_AudioSample* sample);
#endif
