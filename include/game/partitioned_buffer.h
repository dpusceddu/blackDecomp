#ifndef GAME_PARTITIONED_BUFFER_H
#define GAME_PARTITIONED_BUFFER_H
#include "game/aligned_buffer.h"

/* One root range owns two independently advancing subranges. The original
 * class identity and the wider meaning of the state values are UNVERIFIED. */
typedef struct {
    Recovered_AlignedBuffer storage;
    Recovered_AlignedBuffer first;
    Recovered_AlignedBuffer second;
    s32 state;
} Recovered_PartitionedBuffer;

typedef char PartitionedBufferSize[sizeof(Recovered_PartitionedBuffer) == 0x58 ? 1 : -1];
typedef char PartitionedBufferState[(u32)&((Recovered_PartitionedBuffer*)0)->state == 0x54 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
void PartitionedBuffer_Initialize(Recovered_PartitionedBuffer* self, void* buffer, u32 bytes, u32 firstBytes,
                                  u32 secondBytes, u32 alignment);
#ifdef __cplusplus
}
#endif
#endif
