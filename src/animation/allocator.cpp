#include "include_asm.h"
#include "animation/playback_state.h"
#include "animation/graph.h"

extern PlaybackAllocator* AnimationAllocator_Current __asm__("D_003D1B7C");

void AnimationAllocator_Set(PlaybackAllocator*) ANIMATION_FUNCTION(00343ED0);
#ifdef NON_MATCHING
// Unmatched: adjusted callback dispatch uses different temporary registers.
void AnimationAllocator_Set(PlaybackAllocator* allocator) {
    if (AnimationAllocator_Current) {
        AnimationAllocator_Current->vtable->on_remove((u8*)AnimationAllocator_Current +
                                                      AnimationAllocator_Current->vtable->remove_adjust);
    }
    AnimationAllocator_Current = allocator;
    if (allocator) { allocator->vtable->on_install((u8*)allocator + allocator->vtable->install_adjust); }
}

#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/allocator", func_00343ED0);

PlaybackAllocator* AnimationAllocator_Get(void) ANIMATION_FUNCTION(00343F38);
PlaybackAllocator* AnimationAllocator_Get(void) { return AnimationAllocator_Current; }

void* AnimationAllocator_Allocate(int) ANIMATION_FUNCTION(00343F48);
void* AnimationAllocator_Allocate(int size) {
    return AnimationAllocator_Current->vtable->allocate((u8*)AnimationAllocator_Current +
                                                            AnimationAllocator_Current->vtable->allocate_adjust,
                                                        size, PlaybackAllocationInit());
}

void AnimationAllocator_Free(void*) ANIMATION_FUNCTION(00343F90);
void AnimationAllocator_Free(void* memory) {
    PlaybackAllocator* allocator = AnimationAllocator_Current;
    allocator->vtable->free((u8*)allocator + allocator->vtable->free_adjust, memory, 0);
}
