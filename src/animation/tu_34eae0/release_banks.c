#include "animation/playback_state.h"
s32 func_0034ECD8(PlaybackState *state, PlaybackAllocator *allocator) {
    s32 result = 0;
    u8 *row;
    if (state->bank != NULL) {
        result = 1;
        allocator->vtable->free((u8 *)allocator + allocator->vtable->free_adjust, state->bank, 0);
        state->bank = NULL;
    }
    row = (u8 *)&state->history[0].bank;
    do {
        if (*(void **)row != NULL) {
            allocator->vtable->free((u8 *)allocator + allocator->vtable->free_adjust, *(void **)row, 0);
            *(void **)row = NULL;
        }
        row += sizeof(PlaybackHistory);
    } while ((s32)row < (s32)&state->history[8].bank);
    return result;
}
