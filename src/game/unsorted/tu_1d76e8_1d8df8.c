#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/playback_request.h"

extern Recovered_PlaybackServices* D_0040F510;
extern Recovered_PlaybackState* func_001D9768(void*, s32);
extern void* func_001D8478(void*);
extern void func_001D97C8(void*, Recovered_PlaybackState*);
extern void func_001D84C8(void*, void*);
extern void func_001DD158(Recovered_PlaybackState*, Recovered_PlaybackParameters*);
extern s32 func_001DD728(Recovered_PlaybackState*);
extern s32 func_001DD3E0(Recovered_PlaybackState*);
extern void func_001DD6C0(Recovered_PlaybackState*);
extern void func_001D9450(Recovered_PlaybackState*, void**, s32);
extern s32 func_001D92A0(Recovered_PlaybackState*, u64, s32, u32*, s32, s32);
extern void func_001DD5D8(Recovered_PlaybackState*, Recovered_PlaybackParameters*);

static inline Recovered_PlaybackPools* PlaybackPools(void) { return &D_0040F510->playbackPools; }

/* The reset's returned cursor is preserved; its caller contract is unknown. */
void* PlaybackRequest_Reset(Recovered_PlaybackRequest* self) {
    s32 remaining;
    u8* cursor;
    self->valueCount = 0;
    remaining = 1;
    self->playback = NULL;
    cursor = (u8*)self + 0x18;
    do {
        *(u32*)cursor = 0;
        remaining--;
        cursor -= 4;
    } while (remaining >= 0);
    self->state = 0;
    self->scale = 1.0f;
    return cursor;
}

#ifdef NON_MATCHING
// Unmatched: global pool address and offset register assignment differ.
s32 func_001D8E38(Recovered_PlaybackRequest* self, const u32* values, s32 count, s32 kind) {
    s32 i;
    void** buffer;
    switch (self->state) {
        case 0:
        case 10:
            self->valueCount = count;
            for (i = 0; i < self->valueCount; i++) self->values[i] = *values++;
            self->playback = func_001D9768(PlaybackPools()->states, kind);
            buffer = self->buffers;
            for (i = 1; i >= 0; i--, buffer++) *buffer = func_001D8478(PlaybackPools()->buffers);
            self->state = 3;
            /* fallthrough */
        case 3: return 1;
        default: return 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8_1d8df8", func_001D8E38);
#endif

void PlaybackRequest_Update(Recovered_PlaybackRequest* self, Recovered_PlaybackParameters* parameters) {
    switch (self->state) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 8: break;
        case 6:
            parameters->scale = self->scale;
            parameters->flags |= 8;
            func_001DD158(self->playback, parameters);
            if (func_001DD728(self->playback)) break;
            self->state = 7;
            /* fallthrough */
        case 7:
            if (func_001DD3E0(self->playback)) self->state = 8;
            break;
        default: break;
    }
}

#ifdef NON_MATCHING
// Unmatched: pool-offset constant and cleanup-loop setup scheduling differ.
s32 func_001D8FD8(Recovered_PlaybackRequest* self) {
    s32 i;
    void** buffer;
    switch (self->state) {
        case 5:
        case 6:
            func_001DD6C0(self->playback);
            /* fallthrough */
        case 3:
        case 8:
            self->state = 9;
            /* fallthrough */
        case 7:
        case 9:
            if (func_001DD3E0(self->playback)) goto release;
            /* fallthrough */
        default:
            return 0;
        release:
            func_001D97C8(PlaybackPools()->states, self->playback);
            self->playback = NULL;
            buffer = self->buffers;
            for (i = 1; i >= 0; i--, buffer++) {
                func_001D84C8(PlaybackPools()->buffers, *buffer);
                *buffer = NULL;
            }
            for (i = 0; i < self->valueCount; i++) self->values[i] = 0;
            self->valueCount = 0;
            self->state = 10;
            /* fallthrough */
        case 0:
        case 10: return 1;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8_1d8df8", func_001D8FD8);
#endif

#ifdef NON_MATCHING
// Unmatched: switch return joins and predicate branch layout differ.
s32 func_001D9100(Recovered_PlaybackRequest* self, u64 key, s32 variant) {
    switch (self->state) {
        case 5:
            if (self->variant == variant && self->key == key) goto complete;
            self->state = 7;
            break;
        case 3:
        case 8:
            self->key = key;
            self->variant = variant;
            func_001D9450(self->playback, self->buffers, 2);
            self->state = 4;
            /* fallthrough */
        case 4:
            if (func_001D92A0(self->playback, self->key, self->variant, self->values, self->valueCount, 0)) {
                self->state = 5;
                if (self->variant == variant && self->key == key) goto complete;
            }
            break;
        case 6:
        case 7:
        default: break;
    }
    return 0;
complete:
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d76e8_1d8df8", func_001D9100);
#endif

void PlaybackRequest_Begin(Recovered_PlaybackRequest* self, Recovered_PlaybackParameters* parameters) {
    Recovered_PlaybackState* playback;
    parameters->scale = self->scale;
    parameters->unk_58 = 0;
    parameters->flags |= 0x18;
    func_001DD5D8(self->playback, parameters);
    playback = self->playback;
    playback->unk_34 = 1.0f;
    playback->unk_3C = 1.0f;
    self->state = 6;
}
