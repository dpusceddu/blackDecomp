#ifndef RWA_EE_VOICE_H
#define RWA_EE_VOICE_H
#include "rw_audio/sound.h"

/* Inferred PS2 playback access views; verification requires matching users. */
typedef struct RwaPlayback {u32 mode;u32 fields04[4];u32 position;u32 step;} RwaPlayback;
typedef struct RwaChannel {
    u8 fields00[0x30];
    RwaPlayback *playback;
    u8 fields34[0x28];
    u16 flags;
    u8 fields5e[0x3a];
    f32 value98;
    u32 field9c;
    f32 valuea0;
    u8 fieldsa4[0x2c];
} RwaChannel;
typedef struct RwaVoice {u8 fields00[0x60];RwaChannel channel;} RwaVoice;
typedef struct RwaRingBlock {u32 state,kind,offset,mode,field10,ready;} RwaRingBlock;
typedef struct RwaRequest {u32 flags;u8 *data;u32 field08;RwaIdBytes *tag;} RwaRequest;
typedef struct RwaPlaybackState {
    u8 fields00[0x44];
    u32 chunk_size;
    RwaRequest *request;
    u32 ring_count;
    RwaRingBlock *ring;
    u32 filled_channels,source_channels,output_chunk,ring_size,position;
    u32 write_index,read_index,queued_bytes;
    u32 field74,field78,field7c,field80,field84;
    RwaRequest fallback;
    union {u64 bits;struct {u32 low,high;} words;} status;
    u32 saved_read,active_ring;
    RwaVoice *voices;
    u32 voice_count,frame_bytes,voice_bytes,next_voice;
    f32 gain;
    RwaLink *owners;
    struct {RwaLink *previous,*next;} owner_link;
    u32 epoch,advance,fieldd4,fieldd8;
} RwaPlaybackState;
typedef struct RwaDriverContext {u8 fields00[0x20];RwaPlaybackState *state;u8 fields24[0x44];u32 status;} RwaDriverContext;
#endif
