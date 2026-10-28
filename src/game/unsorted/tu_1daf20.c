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
/* Native transition records have a 32-byte copy extent. Original identities,
 * field meanings and complete owner allocation remain UNVERIFIED. */
typedef struct Recovered_PlaybackTransition {
    u64 key;
    f32 unk_08, unk_0C;
    s32 unk_10;
    s16 unk_14;
    u8 unk_16, active;
    u64 unk_18;
} Recovered_PlaybackTransition;
typedef struct Recovered_PlaybackTransitionOwner {
    u8 unk_00[0x1918];
    f32 unk_1918, unk_191C, unk_1920, unk_1924;
    s32 unk_1928, unk_192C;
    u32 state;
    void* unk_1934;
    u8 unk_1938[8];
    Recovered_PlaybackTransition current, pending, previous;
    u8 deferred, unk_19A1;
} Recovered_PlaybackTransitionOwner;
/* A separate native producer supplies a signed selection halfword and three
 * words at 0x14/0x18/0x1C; their original meanings remain UNVERIFIED. */
typedef struct {
    u8 unk_00[0x10];
    s16 unk_10;
    u8 unk_12[2];
    f32 unk_14;
    s32 unk_18;
    f32 unk_1C;
} Recovered_PlaybackDeferredInput;
typedef char PlaybackTransitionCopyExtent[sizeof(Recovered_PlaybackTransition) == 0x20 ? 1 : -1];
/* Slot lookup views; original identities and unaccessed storage are UNVERIFIED. */
typedef struct {
    u128 position;
    u8 unk_10[0x1C];
    s32 id;
    f32 time;
    s32 index;
} Recovered_PlaybackPosition;
typedef struct {
    u8 unk_00[0x18];
    Recovered_PlaybackPosition* point;
    u8 unk_1C[0x34];
    s32 index;
} Recovered_PlaybackMotion;
typedef struct {
    u8 unk_00[0x18];
    Recovered_PlaybackPosition* point;
    u8 unk_1C[0x44];
} Recovered_PlaybackSlot;

/* Expanded local owner view used by native initialization. The slot storage, loader
 * payload, selected/fading roles and original class identity remain UNVERIFIED. */
typedef struct {
    u64 key;
    u8 unk_08[0x0E];
    s16 unk_16;
    Recovered_StreamRange* ranges;
} Recovered_PlaybackDefinition;
typedef struct {
    Recovered_PlaybackController controllers[2];
    u8 handle[0x14];
    void* references[4];
    u32 unk_7C;
    Recovered_PlaybackSlot slots[64];
    u8 flags[64];
    s8 path[0x40];
    s32 referenceCount, controllerCount;
    Recovered_StreamBuffer* loaderBuffer;
    Recovered_PlaybackDefinition* definition;
    Recovered_PlaybackController* selected;
    Recovered_PlaybackController* fading;
    f32 unk_1918, unk_191C, unk_1920, unk_1924;
    s32 unk_1928, unk_192C;
    u32 state;
    void* resource;
    u64 unk_1938;
    Recovered_PlaybackTransition current, pending, previous;
    u8 deferred, deferredReady;
} Recovered_PlaybackOwner;
typedef char Recovered_OwnerFlagsOffset[(u32) & ((Recovered_PlaybackOwner*)0)->flags == 0x1880 ? 1 : -1];
typedef char Recovered_OwnerStateOffset[(u32) & ((Recovered_PlaybackOwner*)0)->state == 0x1930 ? 1 : -1];

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

extern void* func_0035C6EC(void*, s32, u32);
extern void func_00280FE0(void*, void*);
extern void func_001DC498(void*, s32, s32);
s32 func_001DB4F0(Recovered_PlaybackOwner* owner) {
    f32* expiry = (f32*)(owner->handle + 0x10);
    u8* handle = owner->handle;
    s32 i = 0;
    s32 result = 1;
    u8* flag;
    func_0035C6EC(owner, 0, 0x58);
    func_0035C6EC(owner->references, 0, 0x10);
    owner->controllerCount = 0;
    owner->referenceCount = 0;
    owner->loaderBuffer = 0;
    do {
        func_00280FE0(handle, 0);
        handle += 0x14;
        *expiry = -1.0f;
        i--;
        expiry = (f32*)((u8*)expiry + 0x14);
    } while (i >= 0);
    i = 63;
    func_001DC498(owner, 0, 0);
    owner->unk_1918 = 0;
    owner->current.unk_14 = -1;
    owner->unk_191C = 0;
    flag = owner->flags + 63;
    owner->unk_1924 = 0;
    owner->unk_192C = 0;
    owner->pending.active = 0;
    owner->current.active = 0;
    owner->previous.active = 0;
    do {
        *flag = 0;
        i--;
        flag--;
    } while (i >= 0);
    owner->state = result;
    return result;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DB5F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DBA00);
/* Partial loaded-definition view; unaccessed storage and original identity are UNVERIFIED. */

extern u8* func_001DC610(void*);
extern s32 func_001DC5A8(void*);
extern s32 func_001DC6E8(void*);
/* Native consumer view: this command's returned value is discarded. */
extern void func_001EFE08(void*, void*, f32);
extern u8 D_003F8D10[];
s32 func_001DBDB8(void* owner) {
    s32 i;
    if (M2C_FIELD(owner, s32*, 0x1930) == 9) {
        Recovered_PlaybackDefinition* definition = M2C_FIELD(owner, Recovered_PlaybackDefinition**, 0x190C);
        if (!func_001DB088(M2C_FIELD(owner, Recovered_PlaybackController**, 0x1910), &definition->key,
                           definition->ranges + M2C_FIELD(owner, s16*, 0x1954), M2C_FIELD(owner, u8*, 0x1958)))
            return 0;
        M2C_FIELD(owner, s32*, 0x1930) = 14;
    }
    for (i = 0; i < M2C_FIELD(owner, s32*, 0x1904); i++) {
        if (!func_001DB140(&((Recovered_PlaybackController*)owner)[i])) return 0;
    }
    for (i = 0; i < M2C_FIELD(owner, s32*, 0x1904); i++) func_001DAFD0(&((Recovered_PlaybackController*)owner)[i]);
    M2C_FIELD(owner, u8*, 0x1977) = 0;
    M2C_FIELD(owner, u8*, 0x1957) = 0;
    M2C_FIELD(owner, u8*, 0x1997) = 0;
    func_001DC5A8(owner);
    func_001DC610(owner);
    func_001DC6E8(owner);
    func_001EFE08(D_0040F510, D_003F8D10, 0);
    M2C_FIELD(owner, s32*, 0x192C) = 0;
    M2C_FIELD(owner, s32*, 0x1930) = 15;
    return 1;
}
#ifdef NON_MATCHING
// Unmatched: the loaded-definition reload and empty-loop setup differ (eight instructions).
extern void* func_001092F8(void*);
void func_001DBED8(void* input, void* owner) {
    Recovered_PlaybackDefinition* definition;
    s16 i;
    M2C_FIELD(owner, Recovered_PlaybackDefinition**, 0x190C) = func_001092F8(input);
    definition = M2C_FIELD(owner, Recovered_PlaybackDefinition**, 0x190C);
    definition->ranges = (Recovered_StreamRange*)((u32)definition->ranges + (u8*)definition);
    for (i = 0; i < definition->unk_16; i++) {}
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DBED8);
#endif
extern void* D_0040F4D0;
extern u32 D_0040EAE4;
void func_001DBF38(Recovered_PlaybackTransitionOwner* owner, Recovered_PlaybackDeferredInput* transition) {
    if (transition->unk_10 >= 0 && (M2C_FIELD(D_0040F4D0, s8*, 0x5AAC) || D_0040EAE4 < 2)) {
        owner->deferred = 1;
        if (owner->pending.active) {
            owner->previous = owner->pending;
            owner->previous.active = 1;
        } else if (owner->current.active) {
            owner->previous = owner->current;
            owner->previous.active = 1;
        } else
            owner->previous.active = 0;
        owner->pending.key = 0;
        owner->pending.unk_10 = transition->unk_18;
        owner->pending.unk_08 = transition->unk_1C;
        owner->pending.unk_0C = transition->unk_14;
        owner->pending.unk_14 = transition->unk_10;
        owner->pending.active = 1;
        M2C_FIELD(&owner->pending, u8*, 0x18) = 0;
        owner->pending.unk_16 = 0;
    }
}
extern void func_001DC038(void*, void*);
void func_001DC000(void* owner) {
    if (M2C_FIELD(owner, u8*, 0x19A0)) {
        M2C_FIELD(owner, u8*, 0x19A0) = 0;
        M2C_FIELD(owner, u8*, 0x19A1) = 0;
        if (M2C_FIELD(owner, u8*, 0x1997)) func_001DC038(owner, (u8*)owner + 0x1980);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC038);
extern u8 func_00103870(void*);
extern s32 func_001DC278(Recovered_PlaybackTransitionOwner*, Recovered_PlaybackTransition*);
s32 func_001DC1A0(Recovered_PlaybackTransitionOwner* owner, Recovered_PlaybackTransition* transition) {
    s32 state = owner->state;
    if (state != 6 && state != 8 && state != 9) {
        if (!func_00103870(D_0040F0E0)) {
            owner->state = 6;
            owner->current = *transition;
            owner->current.active = 1;
            func_001DC278(owner, transition);
            M2C_FIELD(M2C_FIELD(PlaybackPools()->unk_4BD8, void**, 0x24), u8*, 0x1E54) = transition->unk_16;
            owner->unk_191C = transition->unk_0C;
            owner->unk_1928 = transition->unk_10;
            return 1;
        }
        return 0;
    }
    return 0;
}
s32 func_001DC278(Recovered_PlaybackTransitionOwner* owner, Recovered_PlaybackTransition* transition) {
    f32 previous = owner->unk_191C;
    owner->unk_1918 = MixPreferences()->unk_20;
    owner->unk_1924 = transition->unk_0C - previous;
    owner->unk_1920 = previous;
    owner->unk_1928 = transition->unk_10;
    owner->unk_192C = 1;
    return 1;
}
#ifdef NON_MATCHING
// Unmatched: both interpolation multiplications reverse their native operand order (two instructions).
/* Native table entries have a 0x30-byte stride; their full identities are UNVERIFIED. */
typedef struct {
    u8 unk_00[0x30];
} Recovered_PlaybackGainChannel;
void func_001DC2C0(Recovered_PlaybackTransitionOwner* owner) {
    switch ((u32)owner->unk_192C) {
        case 0:
        default: break;
        case 1:
        case 2: {
            f32 now = MixPreferences()->unk_20;
            f32 previous = owner->unk_1918;
            f32 duration = owner->current.unk_08;
            if (now < previous + duration) {
                owner->unk_191C = owner->unk_1924;
                owner->unk_191C *= (now - previous) / duration;
                owner->unk_191C += owner->unk_1920;
            } else {
                owner->unk_192C = 3;
                owner->unk_191C = owner->current.unk_0C;
            }
            func_001EFE08(D_0040F510, &((Recovered_PlaybackGainChannel*)D_003F8D10)[owner->unk_1928], owner->unk_191C);
        }
        case 3:
            func_001EFE08(D_0040F510, &((Recovered_PlaybackGainChannel*)D_003F8D10)[owner->unk_1928], owner->unk_191C);
            break;
        case 4: {
            f32 now = MixPreferences()->unk_20;
            f32 previous = owner->unk_1918;
            if (now < previous + 0.5f) {
                owner->unk_191C = owner->unk_1924;
                owner->unk_191C *= now - 2.0f * previous;
                owner->unk_191C += owner->unk_1920;
            } else {
                owner->unk_191C = 0;
                owner->unk_192C = 0;
            }
            func_001EFE08(D_0040F510, &((Recovered_PlaybackGainChannel*)D_003F8D10)[owner->unk_1928], owner->unk_191C);
            break;
        }
    }
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC2C0);
#endif

#ifdef NON_MATCHING
// Unmatched: the controller end pointer lives across the reference loops, adding a saved register.
extern f32 func_001ED820(void*);
extern void func_00283B38(void*, f32);
/* The callee forwards f12 to its own callee; both enabled and disabled paths supply it. */
void func_001DC498(void* input, s32 unused, s32 enabled) {
    Recovered_PlaybackOwner* owner = input;
    Recovered_PlaybackController* controller;
    f32 level;
    s32 i;
    if (enabled) {
        level = func_001ED820(M2C_FIELD(PlaybackPools()->unk_4BD8, void**, 0x2C));
        for (i = 0; i < owner->referenceCount; i++) {
            func_00283B38(owner->references[i], level);
            M2C_FIELD(owner->references[i], u8*, 0x35) = 1;
        }
    } else {
        level = 0.0f;
        for (i = 0; i < owner->referenceCount; i++) {
            M2C_FIELD(owner->references[i], u8*, 0x35) = 0;
            func_00283B38(owner->references[i], 0.0f);
        }
    }
    controller = owner->controllers;
    do {
        func_001DB2F0(controller, level);
        controller++;
    } while ((s32)controller < (s32)(owner->controllers + 2));
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC498);
#endif

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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCC08);
s32 func_001DCCF8(Recovered_PlaybackOwner* owner, Recovered_PlaybackMotion* motion, u128* position, f32* time) {
    u8* flags = owner->flags;
    s32 current = motion->index;
    s32 id = motion->point->id;
    s32 nearest = 9999;
    s32 selected = -1;
    s32 i;

    *time = 0;
    for (i = 0; i < 64; i++) {
        if (flags[i]) {
            Recovered_PlaybackPosition* point = owner->slots[i].point;
            if (point->id == id) {
                s32 index = point->index;
                if (index == current)
                    *time = point->time;
                else {
                    if (current < index && (selected == -1 || index < nearest)) {
                        selected = i;
                        nearest = index;
                    }
                    if (index == 0 && selected == -1) selected = i;
                }
            }
        }
    }
    *position = M2C_FIELD(M2C_FIELD((u8*)owner + selected * 0x60, Recovered_PlaybackPosition**, 0x98), u128*, 0);
    return M2C_FIELD((u8*)owner + selected * 0x60, Recovered_PlaybackPosition**, 0x98)->index;
}

extern void func_00272488(u64, s8*);
extern void* func_00107CF8(u32);
extern void func_001D97D0(Recovered_AudioTransferGroup*, u64, const s8*, s32, s32, s32, void*, s32, u8);
typedef struct {
    Recovered_AudioTransferGroup* group;
    f32 scale;
} PlaybackTransfer;
static inline PlaybackTransfer* PlaybackTransfers(Recovered_PlaybackState* self) {
    return (PlaybackTransfer*)((u8*)self + 0x30);
}

void func_001DCDC0(Recovered_PlaybackState* self, u64 key, u32 value, s32 format, s32 bytes, void* scratch, s32 unknown,
                   s8 count, s8 mode, u8 final) {
    s8 name[16];
    s32 i;
    PlaybackTransfer* transfer;
    self->unk_58 = count;
    self->poolKey = key;
    func_00272488(key, name);
    for (i = 0; i < 13; i++) {
        if (name[i] == ' ') {
            name[i] = 0;
            break;
        }
    }
    for (i = 0; i < self->unk_58; i++) {
        transfer = &((PlaybackTransfer*)((u8*)self + 0x30))[i];
        transfer->group = func_00107CF8(sizeof(Recovered_AudioTransferGroup));
        func_001D97D0(transfer->group, self->poolKey, name, format, mode, bytes, scratch, unknown, final);
        ((PlaybackTransfer*)((u8*)self + 0x30))[i].scale = 0;
    }
    for (i = 3; i >= 0; i--) self->buffers[i] = 0;
    self->unk_14 = 1;
    self->unk_44 = 0;
    self->unk_18 = value;
    self->unk_40 = 0;
    self->bufferCount = 0;
    self->unk_60 = 0;
    self->unk_50 = 0;
    self->unk_4C = 0;
    self->unk_54 = 0;
    self->unk_62 = 0;
    self->unk_64 = 0;
    self->unk_65 = 0;
    self->claimed = 0;
    self->unk_48 = 0x8000 / count;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCF70);
typedef struct {
    u8* data;
    s32 bytes;
    s32 final;
} PlaybackInput;
extern void func_001D9AB8(Recovered_AudioTransferGroup*, Recovered_PlaybackParameters*);
extern s32 func_001D9D58(Recovered_AudioTransferGroup*);
extern void func_001D9C00(Recovered_AudioTransferGroup*, PlaybackInput*);
extern void func_001DD4C8(void*, s32);
extern u8* func_001DD4D0(Recovered_PlaybackState*, s32);
extern s32 func_001DD508(Recovered_PlaybackState*);
static inline s32 AtEnd(Recovered_StreamBuffer* buffer) {
    return buffer->firstBlock + buffer->unk_1C >= buffer->record->blockCount;
}
void func_001DD158(Recovered_PlaybackState* self, Recovered_PlaybackParameters* parameters) {
    PlaybackInput input;
    Recovered_PlaybackParameters copy;
    s32 i;
    copy.flags = 0;
    copy = *parameters;
    if (((s32)parameters->flags >> 12) & 1) self->unk_65 = parameters->unk_A9;
    for (i = 0; i < self->unk_58; i++) {
        copy.scale = PlaybackTransfers(self)[i].scale * parameters->scale;
        copy.flags |= 8;
        func_001D9AB8(PlaybackTransfers(self)[i].group, &copy);
    }
    switch (self->unk_14) {
        case 5:
        case 7:
            if (func_001D9D58(PlaybackTransfers(self)[0].group)) {
                Recovered_StreamBuffer* buffer = self->buffers[self->unk_4C];
                s32 end = AtEnd(buffer);
                if (end && !self->unk_65) {
                    StreamBuffer_TryReset(buffer);
                    self->unk_14 = 8;
                } else {
                    StreamBuffer_TryReset(self->buffers[self->unk_4C]);
                    self->unk_14 = 6;
                    self->unk_4C = (self->unk_4C + 1) % self->bufferCount;
                    goto ready;
                }
            }
            break;
        case 6:
        ready:
            if ((self->buffers[self->unk_4C]->state ^ 4) == 0) {
                func_001DD4C8(self, self->unk_4C);
                for (i = 0; i < self->unk_58; i++) {
                    s32 final;
                    input.data = func_001DD4D0(self, i);
                    input.bytes = self->unk_48;
                    final = 0;
                    if (!self->unk_65) {
                        if (AtEnd(self->buffers[self->unk_4C])) final = 1;
                    }
                    input.final = final;
                    func_001D9C00(PlaybackTransfers(self)[i].group, &input);
                    self->unk_44 = self->buffers[self->unk_4C];
                }
                self->unk_14 = 7;
            }
            break;
        default: break;
    }
    func_001DD508(self);
}
extern s32 AudioTransferGroup_TryReset(Recovered_AudioTransferGroup*);
extern void* func_0035C6EC(void*, s32, u32);
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
