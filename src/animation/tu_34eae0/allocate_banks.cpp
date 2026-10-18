#include "animation/playback_state.h"

extern "C" void *func_00350060(void *);
extern "C" void *func_00351A40(void *);
extern "C" s32 func_0034EB88(PlaybackState *state, PlaybackAllocator *allocator) {
    void *memory;
    u8 *row;
    s32 i;

    memory = allocator->vtable->allocate((u8 *)allocator + allocator->vtable->allocate_adjust, 0x11c, PlaybackAllocationInit());
    if (memory == NULL) return 0;
    state->bank = func_00350060(memory);

    memory = allocator->vtable->allocate((u8 *)allocator + allocator->vtable->allocate_adjust, 0x11c, PlaybackAllocationInit());
    if (memory == NULL) return 0;
    state->scratch_bank = func_00350060(memory);
    if (state->blend_weights == NULL) {

        memory = allocator->vtable->allocate((u8 *)allocator + allocator->vtable->allocate_adjust, 0x84, PlaybackAllocationInit());
        if (memory == NULL) return 0;
        state->blend_weights = func_00351A40(memory);
    }
    row = (u8 *)&state->history[0].bank;
    for (i = 0; i < 8; ++i) {

        memory = allocator->vtable->allocate((u8 *)allocator + allocator->vtable->allocate_adjust, 0x11c, PlaybackAllocationInit());
        if (memory == NULL) return 0;
        *(void **)row = func_00350060(memory);
        row += sizeof(PlaybackHistory);
    }
    return 1;
}
