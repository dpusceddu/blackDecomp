#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/audio_playback_control.h"
#include "game/stream_buffer.h"

extern void* func_0036CD08(s32 mode, s32 size, void* address);

extern void func_00280908(void*, s32);

extern s32 func_00324F98();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D76E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D7A60);

s32 func_001D7B98(void) {
    return func_00324F98() != 0;
}

#include "ps2/recovered_types.h"
extern void * func_0027FCF8(void *, void *, s32);

void * func_001D7BB8(void *arg0, s32 arg1) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s64 *)(sp + 0) = (s64) arg1;
    return func_0027FCF8(M2C_FIELD(arg0, void **, 0x88), sp, 0);
}

#ifdef NON_MATCHING
// Unmatched: independent field stores are scheduled differently.
void StreamBuffer_Initialize(Recovered_StreamBuffer* self, void* data, s32 bytes) {
    self->data = data;
    self->readPending = 0;
    self->state = 1;
    self->blockCapacity = bytes / 2048;
    self->remaining = 0;
    self->mode = 0;
    self->claimed = 0;
    self->unk_1C = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D7BE0);
#endif
#ifdef NON_MATCHING
// Unmatched: clamped-count reload and return joins differ.
s32 StreamBuffer_Prepare(Recovered_StreamBuffer* self, u64 key, Recovered_StreamRange* record, s16 firstBlock,
                         s32 value, s32 mode) {
    switch (self->state) {
        case 1:
            self->key = key;
            self->unk_10 = value;
            self->mode = mode;
            self->record = record;
            self->firstBlock = firstBlock;
            {
                s32 count = record->blockCount - firstBlock;
                s32 capacity = self->blockCapacity;
                self->state = 3;
                if (capacity >= count) capacity = count;
                self->remaining = capacity;
            }
            if (self->remaining != 0) break;
            self->state = 4;
        case 4: return 1;
        case 3: break;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D7C20);
#endif
#ifdef NON_MATCHING
// Unmatched: reset-field stores are scheduled differently.
s32 StreamBuffer_TryReset(Recovered_StreamBuffer* self) {
    switch (self->state) {
        case 3:
            if (self->remaining != 0) {
                if (self->readPending) break;
                self->remaining = 0;
            }
        case 4:
            self->key = 0;
            self->state = 1;
            self->record = 0;
            self->firstBlock = 0;
            self->mode = 0;
        case 1: return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D7CC0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D7D40);
s32 func_001D7EC8(Recovered_StreamBufferPool* self) {
    self->unk_2CC = 0;
    self->unk_2D4 = 2;
    self->unk_2C8 = 0;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D7EE0);
/* UNVERIFIED: only the record ID of this input is known. */
typedef struct Recovered_StreamRecordInput {
    u8 unk_00[0x10];
    s32 id;
} Recovered_StreamRecordInput;

void func_001D83D0(Recovered_StreamRecordInput* self, Recovered_StreamBufferPool* pool) {
    s32 id = self->id;
    Recovered_StreamRecord* record = StreamBufferPool_FindRecord(pool, id);
    record->unk_10 = 0;
}
#ifdef NON_MATCHING
// Unmatched: return-address reload is scheduled before the first byte store.
void func_001D83F8(Recovered_StreamRecordInput* self, Recovered_StreamBufferPool* pool) {
    s32 id = self->id;
    Recovered_StreamRecord* record = StreamBufferPool_FindRecord(pool, id);
    record->unk_11 = 0;
    record->unk_12 = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D83F8);
#endif
Recovered_StreamRecord* StreamBufferPool_FindRecord(Recovered_StreamBufferPool* self, s32 id) {
    Recovered_StreamRecord* result = 0;
    s32 i;
    for (i = 0; i < 8; i++) {
        if (id == self->records[i].id) {
            result = &self->records[i];
            break;
        }
    }
    return result;
}
Recovered_StreamBuffer* StreamBufferPool_Acquire(Recovered_StreamBufferPool* self) {
    s32 i;
    for (i = 0; i < self->bufferCount; i++) {
        if (!self->slots[i]->claimed) {
            self->slots[i]->claimed = 1;
            return self->slots[i];
        }
    }
    return 0;
}

void StreamBufferPool_Release(Recovered_StreamBufferPool* self, Recovered_StreamBuffer* buffer) { buffer->claimed = 0; }

void StreamBufferPool_AllocateBuffers(Recovered_StreamBufferPool* self) {
    if (!self->buffersAllocated) {
        s32 i;
        for (i = 0; i < self->bufferCount; i++) {
            void* data = func_0036CD08(0, 0x8000, 0);
            StreamBuffer_Initialize(self->slots[i], data, 0x8000);
        }
        self->buffersAllocated = 1;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D8728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D8BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8", func_001D8BC0);
s32 func_001D8D68(void) {
    return 0;
}

void AudioPlaybackControl_ClearChannelState(Recovered_AudioPlaybackControl* self) {
    if (self->mode == 1) {
        s32 i;
        for (i = 0; i < self->channelCount; i++) func_00280908(self->channels[i], 0);
    }
}

void func_001D8DE8(void) {

}

void func_001D8DF0(void) {

}

void func_001D90F8(void) {

}
