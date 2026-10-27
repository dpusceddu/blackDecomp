#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/playback_state_pool.h"
#include "game/audio_transfer.h"
#include "game/frontend_options.h"

extern void func_001DD6C0();

/* Partial native playback controller. Original class identity and numeric state meanings are UNVERIFIED. */
typedef struct Recovered_PlaybackController {
    Recovered_PlaybackState* playback;
    u32* unk_04;
    s32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    Recovered_StreamBuffer* resources[2];
    u32 state;
} Recovered_PlaybackController;
extern Recovered_PlaybackServices* D_0040F510;
extern s32 func_001D92A0(Recovered_PlaybackState*, u64, Recovered_StreamRange*, u32*, s32, u32);
/* Partial larger owner and transition payload; field meanings are UNVERIFIED. */
typedef struct Recovered_PlaybackTransitionOwner {
    u8 unk_00[0x1918];
    f32 unk_1918;
    f32 unk_191C;
    f32 unk_1920;
    f32 unk_1924;
    s32 unk_1928;
    s32 unk_192C;
} Recovered_PlaybackTransitionOwner;
typedef struct Recovered_PlaybackTransition {
    u8 unk_00[0x0C];
    f32 unk_0C;
    s32 unk_10;
} Recovered_PlaybackTransition;
extern void* D_0040F0E0;

static inline Recovered_AudioMixPreferences* MixPreferences(void) { return &FrontendOptions_Preferences->audioMix; }

static inline Recovered_PlaybackPools* PlaybackPools(void) { return &D_0040F510->playbackPools; }
#ifdef NON_MATCHING
// Unmatched: saved-register allocation differs in the buffer-acquisition loop.
void func_001DAF20(Recovered_PlaybackController* owner, Recovered_PlaybackState* playback, u32* first, s32 second) {
    Recovered_StreamBuffer** resources;
    Recovered_StreamBuffer** resource;
    s32 remaining;
    remaining = 1;
    resources = owner->resources;
    owner->playback = playback;
    resource = resources;
    playback->unk_34 = 1.0f;
    playback->unk_3C = 1.0f;
    owner->unk_04 = first;
    owner->unk_08 = second;
    do {
        remaining--;
        *resource = StreamBufferPool_Acquire(PlaybackPools()->buffers);
        resource++;
    } while (remaining >= 0);
    PlaybackState_SetBuffers(owner->playback, resources, 2);
    owner->state = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DAF20);
#endif
#ifdef NON_MATCHING
// Unmatched: pool-offset setup scheduling differs before releasing the playback state.
s32 func_001DAFD0(Recovered_PlaybackController* owner) {
    Recovered_StreamBuffer** resource;
    s32 remaining;
    s32 result = 1;
    if (owner->state == 0) { PlaybackState_SetBuffers(owner->playback, 0, 0); }
    resource = owner->resources;
    remaining = 1;
    PlaybackStatePool_Release(PlaybackPools()->states, owner->playback);
    owner->playback = 0;
    do {
        void* value;
        remaining--;
        value = *resource++;
        StreamBufferPool_Release(PlaybackPools()->buffers, value);
    } while (remaining >= 0);
    owner->state = result;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DAFD0);
#endif
s32 func_001DB088(Recovered_PlaybackController* owner, const u64* key, Recovered_StreamRange* value, u32 flags) {
    switch (owner->state) {
        case 0:
        case 2:
            PlaybackState_SetBuffers(owner->playback, owner->resources, 2);
            owner->state = 3;
            /* fallthrough */
        case 3:
            if (func_001D92A0(owner->playback, *key, value, owner->unk_04, owner->unk_08, flags) != 0) {
                owner->state = 4;
                case 4: return 1;
            }
        default:
        case 1:
        case 5: return 0;
    }
}

#include "ps2/recovered_types.h"
extern s32 func_001DD3E0(Recovered_PlaybackState*);

s32 func_001DB140(void *arg0) {
    u32 temp_3;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x28);
    switch (temp_3) {
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
        M2C_FIELD(arg0, u32 *, 0x28) = 5U;
        /* fallthrough */
    case 5:
        if (func_001DD3E0(M2C_FIELD(arg0, void **, 0)) != 0) {
            M2C_FIELD(arg0, u32 *, 0x28) = 2U;
        case 0:
        case 2:
            return 1;
        }
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DB1B0);
void func_001DB2B0(Recovered_PlaybackController* owner, f32 value) {
    switch ((s32)owner->state) {
        case 7:
        case 8:
        case 9:
            owner->unk_10 = value;
            owner->unk_0C = value;
            owner->unk_18 = owner->unk_14;
            owner->state = 9;
        case 6:
        default: break;
    }
}

void func_001DB2F0(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x1C) = fparg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DB2F8);

s32 func_001DB4A0(s32 arg0) {
    s32 temp_3;
    s32 var_2;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x28);
    var_2 = temp_3 < 7;
    if ((temp_3 >= 0) && (var_2 == 0)) {
        var_2 = temp_3 < 0xA;
        if (var_2 != 0) {
            func_001DD6C0(M2C_FIELD(arg0, s32 *, 0));
            var_2 = 6;
            M2C_FIELD(arg0, s32 *, 0x28) = 6;
        }
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DB4F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DB5F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DBA00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DBDB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DBED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DBF38);
extern void func_001DC038(void*, void*);
void func_001DC000(void* owner) {
    if (M2C_FIELD(owner, u8*, 0x19A0)) {
        M2C_FIELD(owner, u8*, 0x19A0) = 0;
        M2C_FIELD(owner, u8*, 0x19A1) = 0;
        if (M2C_FIELD(owner, u8*, 0x1997)) func_001DC038(owner, (u8*)owner + 0x1980);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC1A0);
s32 func_001DC278(Recovered_PlaybackTransitionOwner* owner, Recovered_PlaybackTransition* transition) {
    f32 previous = owner->unk_191C;
    owner->unk_1918 = MixPreferences()->unk_20;
    owner->unk_1924 = transition->unk_0C - previous;
    owner->unk_1920 = previous;
    owner->unk_1928 = transition->unk_10;
    owner->unk_192C = 1;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC2C0);
s32 func_001DC448(void* owner) {
    switch (M2C_FIELD(owner, u32*, 0x1930)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 14:
        case 15:
        default: break;
        case 6: M2C_FIELD(owner, u32*, 0x1930) = 5; break;
        case 10:
        case 11: M2C_FIELD(owner, u32*, 0x1930) = 12;
        case 7:
        case 8:
        case 9:
        case 12:
        case 13: return 0;
    }
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC498);

/* Recovered_Vtable_003E26B8: accessed fields only, at their PS2 offsets (unk_XX); the size is unknown. */
typedef struct Recovered_Vtable_003E26B8 {
    u8 unk_0[4];
    u8 unk_4;
    u8 unk_5[3];
    void * unk_8;
    s32 unk_C;
} Recovered_Vtable_003E26B8;

#include "ps2/recovered_types.h"
extern s32 func_002810A0(Recovered_Vtable_003E26B8 *);

s32 func_001DC5A8(void *arg0) {
    Recovered_Vtable_003E26B8 *var_17;
    f32 *var_16;
    s32 temp_v0;
    s32 var_18;

    var_16 = (f32 *) (((s8 *) arg0) + 0x68);
    var_17 = (Recovered_Vtable_003E26B8 *) (((s8 *) arg0) + 0x58);
    var_18 = 0;
    do {
        var_18 -= 1;
        temp_v0 = func_002810A0(var_17);
        var_17 = (Recovered_Vtable_003E26B8 *) (((s8 *) var_17) + 0x14);
        *var_16 = -1.0f;
        var_16 = (f32 *) (((s8 *) var_16) + 0x14);
    } while (var_18 >= 0);
    return temp_v0;
}

/* The returned flag cursor has no established caller contract. */
u8* func_001DC610(void* owner) {
    s32* state = (s32*)((u8*)owner + 0x80);
    Recovered_Vtable_003E26B8* handle = (Recovered_Vtable_003E26B8*)((u8*)owner + 0x84);
    s32 i = 0;
    u8* flags = (u8*)owner + 0x1880;
    do {
        flags[i] = 0;
        *state = 8;
        func_002810A0(handle);
        i++;
        handle = (Recovered_Vtable_003E26B8*)((u8*)handle + 0x60);
        state = (s32*)((u8*)state + 0x60);
    } while (i < 64);
    return flags + i;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC690);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC6E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCC08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCCF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCDC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DD158);
extern s32 AudioTransferGroup_TryReset(Recovered_AudioTransferGroup*);
extern void* func_0035C6EC(void*, s32, u32);
typedef struct { Recovered_AudioTransferGroup* group; f32 scale; } PlaybackTransfer;
extern s32 func_001DD508(Recovered_PlaybackState*);
s32 func_001DD3E0(Recovered_PlaybackState* self) {
    s32 i;
    if (self->buffers[self->unk_54] && !func_001DD508(self)) return 0;
    for (i = 0; i < 4; i++) {
        Recovered_StreamBuffer* buffer = self->buffers[i];
        if (buffer) {
            if (!StreamBuffer_TryReset(buffer)) return 0;
            self->buffers[i] = 0;
        }
    }
    for (i = 0; i < self->unk_58; i++) {
        if (!AudioTransferGroup_TryReset(((PlaybackTransfer*)((u8*)self + 0x30))[i].group)) return 0;
    }
    func_0035C6EC(self, 0, 16);
    self->unk_14 = 9;
    return 1;
}

void func_001DD4C8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x4C) = arg1;
}

u8* func_001DD4D0(Recovered_PlaybackState* self, s32 index) {
    Recovered_StreamBuffer* buffer = self->buffers[self->unk_4C];
    return (u8*)buffer->data + ((buffer->blockCapacity << 11) / self->unk_58) * index;
}
extern s32 func_001D7C20(Recovered_StreamBuffer*, u64, Recovered_StreamRange*, s16, s32, s32);
s32 func_001DD508(Recovered_PlaybackState* self) {
    Recovered_StreamBuffer* buffer;
    s32 next;
    s32 end;
    if (!self->unk_64) {
        buffer = self->buffers[self->unk_54];
        if (buffer != self->unk_44) {
            if (func_001D7C20(buffer, self->unk_20, self->unk_40, self->unk_60, self->unk_18, 0)) {
                next = buffer->firstBlock + buffer->unk_1C;
                end = next >= buffer->record->blockCount;
                if (end) {
                    if (self->unk_65)
                        self->unk_60 = 0;
                    else
                        self->unk_64 = 1;
                } else {
                    self->unk_60 = next;
                }
                self->unk_54 = (self->unk_54 + 1) % self->bufferCount;
                return 1;
            }
            return 0;
        }
        return 1;
    }
    return 1;
}
extern void func_001D9DC0(Recovered_AudioTransferGroup*, Recovered_PlaybackParameters*);
static inline PlaybackTransfer* PlaybackTransfers(Recovered_PlaybackState* self) { return (PlaybackTransfer*)((u8*)self+0x30); }
void func_001DD5D8(Recovered_PlaybackState* self, Recovered_PlaybackParameters* parameters) {
    Recovered_PlaybackParameters copy;
    s32 i;
    copy.flags = 0;
    copy = *parameters;
    if (((s32)parameters->flags >> 12) & 1)
        self->unk_65 = parameters->unk_A9;
    else
        self->unk_65 = 0;
    for (i = 0; i < self->unk_58; i++) {
        copy.scale = PlaybackTransfers(self)[i].scale * parameters->scale;
        copy.flags |= 8;
        func_001D9DC0(PlaybackTransfers(self)[i].group, &copy);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DD6B8);
extern void func_001D9E40(Recovered_AudioTransferGroup*);
void func_001DD6C0(Recovered_PlaybackState* self) {
    s32 i;
    for (i = 0; i < self->unk_58; i++) { func_001D9E40(((PlaybackTransfer*)((u8*)self + 0x30))[i].group); }
}
