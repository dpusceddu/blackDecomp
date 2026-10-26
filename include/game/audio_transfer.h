#ifndef GAME_AUDIO_TRANSFER_H
#define GAME_AUDIO_TRANSFER_H
#include "ps2/prelude.h"

/* Existing matched channel helpers confirm handle/state, input-null testing,
 * alternating buffer index/stride, blockSize and the pending byte. UNVERIFIED:
 * format identities, remaining field names/units until matched consumers, and
 * the meaning of numeric states and completion flags. The leading bytes may
 * include a library object; no common object identity is inferred here. */
typedef struct {
    u8 unk_00[0xA8];
    void* target;
    s32 unk_AC;
    s32 handle;
    s32 state;
    s32 format;
    u8* decoded;
    s32 unk_C0;
    u8* input;
    s32 inputBytes;
    s32 outputBytes;
    s32 bufferIndex;
    s32 lastBuffer;
    s32 bufferStride;
    s32 unk_DC;
    s32 blockSize;
    s32 submitted;
    s32 unk_E8;
    s32 unk_EC;
    s32 completed;
    u8 unk_F4[4];
    u8 pending;
    u8 unk_F9;
    u8 final;
    u8 finalSubmitted;
    u8 unk_FC;
} Recovered_AudioTransferChannel;

/* Partial views of the paired transfer family. Matched group accessors confirm
 * slot blockIndex at 0x04, data at 0x10, blockBytes at 0x14 and blockCount at
 * 0x24. UNVERIFIED: original identities, size units, slot/count bounds, other
 * group fields until their consumers match, and all unaccessed storage/extents. */
typedef struct {
    Recovered_AudioTransferChannel* channel;
    s32 blockIndex;
} Recovered_AudioTransferSlot;

typedef struct {
    Recovered_AudioTransferSlot slots[2];
    u8* data;
    s32 blockBytes;
    s32 dataBytes;
    s32 channelCount;
    s32 current;
    s32 blockCount;
    s32 unk_28;
    s32 state;
    u8 final;
} Recovered_AudioTransferGroup;

typedef char AudioTransferSlotStride[sizeof(Recovered_AudioTransferSlot) == 8 ? 1 : -1];
typedef char AudioTransferGroupDataOffset[(u32) & ((Recovered_AudioTransferGroup*)0)->data == 0x10 ? 1 : -1];
typedef char AudioTransferChannelHandleOffset[(u32) & ((Recovered_AudioTransferChannel*)0)->handle == 0xB0 ? 1 : -1];
typedef char AudioTransferChannelInputOffset[(u32) & ((Recovered_AudioTransferChannel*)0)->input == 0xC4 ? 1 : -1];
typedef char AudioTransferChannelPendingOffset[(u32) & ((Recovered_AudioTransferChannel*)0)->pending == 0xF8 ? 1 : -1];
#endif
