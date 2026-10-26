#ifndef GAME_ALIGNED_BUFFER_H
#define GAME_ALIGNED_BUFFER_H
#include "ps2/prelude.h"

/* Partial native view. Allocation advances an aligned cursor within a bound
 * range. The original class identity and lifecycle-byte meaning are UNVERIFIED. */
typedef struct {
    u8 unk_00;
    void* ownedBuffer;
    u8* begin;
    u8* end;
    u8* cursor;
    u32 alignment;
    void* lastAllocation;
} Recovered_AlignedBuffer;

typedef char AlignedBufferSize[sizeof(Recovered_AlignedBuffer) == 0x1C ? 1 : -1];
typedef char AlignedBufferCursor[(u32)&((Recovered_AlignedBuffer*)0)->cursor == 0x10 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif
void AlignedBuffer_Initialize(Recovered_AlignedBuffer* self) __asm__("func_00274E40");
s32 AlignedBuffer_Bind(Recovered_AlignedBuffer* self, void* buffer, u32 bytes);
void AlignedBuffer_RestoreAllocatorHooks(void);
void* AlignedBuffer_Allocate(Recovered_AlignedBuffer* self, u32 bytes);
void AlignedBuffer_SetAlignment(Recovered_AlignedBuffer* self, u32 alignment) __asm__("func_00274F58");
#ifdef __cplusplus
}
#endif
#endif
