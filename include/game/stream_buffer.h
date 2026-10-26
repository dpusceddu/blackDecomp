#ifndef GAME_STREAM_BUFFER_H
#define GAME_STREAM_BUFFER_H
#include "ps2/prelude.h"

/* Partial native stream-buffer views. Accesses without a full-image matched
 * consumer remain UNVERIFIED, as do original class
 * identities, record meanings, numeric state meanings, unaccessed storage and
 * full extents. Initialization converts byte capacity to 2048-byte blocks;
 * the allocator packs three arguments and reads a 32-bit reply through the
 * platform service. Its address space and ownership contract remain unknown. */
typedef struct {
    u16 unk_00;
    u16 blockCount;
    u32 unk_04;
    s32 id;
    u32 unk_0C;
    u8 unk_10, unk_11, unk_12, unk_13;
    s32 unk_14;
} Recovered_StreamRecord;

typedef struct {
    u64 key;
    void* data;
    Recovered_StreamRecord* record;
    s32 unk_10;
    s32 state;
    s32 remaining;
    s32 unk_1C;
    s16 blockCapacity;
    s16 firstBlock;
    u8 readPending;
    u8 mode;
    u8 claimed;
    u8 unk_27;
} Recovered_StreamBuffer;

/* The native pool constructor copies 64 slot pointers to slotCopy and walks
 * eight records with a 24-byte stride. Input count bounds and slotCopy's role
 * beyond that copy remain UNVERIFIED. */
typedef struct {
    u8 buffersAllocated;
    u8 unk_01[3];
    Recovered_StreamBuffer* slots[64];
    Recovered_StreamBuffer* slotCopy[64];
    u32 unk_204;
    Recovered_StreamRecord records[8];
    u32 unk_2C8, unk_2CC;
    s32 bufferCount;
    s32 unk_2D4;
} Recovered_StreamBufferPool;

typedef char StreamBufferSize[sizeof(Recovered_StreamBuffer) == 0x28 ? 1 : -1];
typedef char StreamRecordSize[sizeof(Recovered_StreamRecord) == 0x18 ? 1 : -1];
typedef char StreamBufferCapacityOffset[(u32) & ((Recovered_StreamBuffer*)0)->blockCapacity == 0x20 ? 1 : -1];
typedef char StreamBufferClaimedOffset[(u32) & ((Recovered_StreamBuffer*)0)->claimed == 0x26 ? 1 : -1];
typedef char StreamPoolRecordsOffset[(u32) & ((Recovered_StreamBufferPool*)0)->records == 0x208 ? 1 : -1];
typedef char StreamPoolCountOffset[(u32) & ((Recovered_StreamBufferPool*)0)->bufferCount == 0x2D0 ? 1 : -1];

void StreamBuffer_Initialize(Recovered_StreamBuffer* self, void* data, s32 bytes) __asm__("func_001D7BE0");
s32 StreamBuffer_Prepare(Recovered_StreamBuffer* self, u64 key, Recovered_StreamRecord* record, s16 firstBlock,
                         s32 value, s32 mode);
s32 StreamBuffer_TryReset(Recovered_StreamBuffer* self);
Recovered_StreamRecord* StreamBufferPool_FindRecord(Recovered_StreamBufferPool* self, s32 id);
Recovered_StreamBuffer* StreamBufferPool_Acquire(Recovered_StreamBufferPool* self);
void StreamBufferPool_Release(Recovered_StreamBufferPool* self, Recovered_StreamBuffer* buffer);
void StreamBufferPool_AllocateBuffers(Recovered_StreamBufferPool* self);
#endif
