#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/playback_state_pool.h"
#include "game/effects/random_state.h"

extern void func_001DFC78(void);
extern s32 func_001E0FE8(void *);
extern s32 func_001DEEB8();
extern s32 func_001E0D28();
extern s32 func_001E0F28(void *);
extern s32 func_001E0E70(void *);
extern s32 func_001E0A30(void *);
extern f32 func_001ED820(s32);
extern void * D_0040F510;
extern s8 func_00281120();
extern f32 D_003BD390;
extern s32 func_001DE520(void*,void*);
extern f32 func_001DFB20(void*,void*);
extern void* D_0040F4D8;
extern BkEffectRandomStatePS2 D_0040EB30;
extern f32 func_001E1708(s32, s32);
extern void func_001E0930(void*, void*, s32);
extern s32 func_001DF028(void*, s128, s32, s32*);
/* Matched requests have a 0x40-byte copy extent and an aligned quadword at +0x20.
 * Original request identity, field meanings and unaccessed bytes are UNVERIFIED. */
typedef struct {
    s32 unk_00, unk_04;
    f32 unk_08, unk_0C, unk_10;
    u8 unk_14[0xC];
    s128 unk_20;
    s32 unk_30, unk_34, unk_38;
    u32 unk_3C;
} Recovered_AudioRequest;
typedef char AudioRequestExtent[sizeof(Recovered_AudioRequest) == 0x40 ? 1 : -1];
static inline Recovered_PlaybackPools* GameplayPools(void) {
    return &((Recovered_PlaybackServices*)D_0040F510)->playbackPools;
}
/* Keep the state-member return form used by the native unsigned-to-float path. */
static inline u32 NextAudioRandom(BkEffectRandomStatePS2* random) {
    random->state = (random->state << 16) + ((s32)random->state >> 16) + random->accumulator;
    random->accumulator += random->state;
    return random->state;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DD838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DD9C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DDE78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DE070);
void func_001DE078(void* owner, s128 value, void* input, void* actor) {
    Recovered_AudioRequest request;
    f32 first;
    f32 second;
    f32 random;
    s32 selector;
    s32 status;
    u8 field;
    void* manager;

    request.unk_30 = 0;
    request.unk_34 = 0;
    status = func_001DE520(owner, actor);
    first = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 0);
    manager = M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10);
    selector = M2C_FIELD(M2C_FIELD(manager, void**, 0x2424), s32*, 8);
    second = func_001DFB20(owner, M2C_FIELD(input, void**, 0x24));
    field = M2C_FIELD(input, u8*, 0x28);
    random = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_00 = selector;
    request.unk_08 = first;
    request.unk_20 = (s128)value;
    request.unk_34 = status;
    request.unk_04 = (s32)field;
    request.unk_0C = second;
    request.unk_10 = random * 2.3283064e-10f;
    request.unk_30 = 5;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 1);
}

extern const u64 D_003F9190[4];
void func_001DE1F0(void* owner, void* input, void* actor) {
    Recovered_AudioRequest request;
    f32 first, second, random;
    s32 kind, status;
    u8 field;
    s32 i, found, enabled;
    void* manager;
    request.unk_30 = 0;
    request.unk_34 = 0;
    status = func_001DE520(owner, actor);
    first = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 0);
    manager = M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10);
    kind = M2C_FIELD(M2C_FIELD(manager, void**, 0x2424), s32*, 8);
    second = func_001DFB20(owner, M2C_FIELD(input, void**, 0x24));
    field = M2C_FIELD(input, u8*, 0x28);
    random = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_04 = field;
    request.unk_00 = kind;
    request.unk_08 = first;
    request.unk_0C = second;
    request.unk_10 = random * 2.3283064365386963e-10f;
    request.unk_20 = M2C_FIELD(input, s128*, 0);
    request.unk_34 = status;
    request.unk_38 = 0;
    request.unk_30 = 1;
    found = 0;
    for (i = 0; i < 4; i++) {
        if (M2C_FIELD(M2C_FIELD(M2C_FIELD(actor, void**, 0x2A4), void**, 0xE8), u64*, 0) == D_003F9190[i]) {
            found = 1;
            break;
        }
    }
    enabled = 1;
    if (found) {
        if (status == 2) enabled = 0;
    }
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, enabled);
}

/* Four native membership keys; their original names and meanings are UNVERIFIED. */
const u64 D_003F9190[4] __attribute__((section(".rodata.audio_request_keys"))) = {
    0x544614B7182C0000UL, 0x5446127AD7970000UL, 0x5446151EBC278000UL, 0x54461524B8230000UL
};

void func_001DE3D0(void* unused, s128 value, void* input) {
    Recovered_AudioRequest request;
    f32 first;
    f32 second;
    f32 random;
    s32 selector;
    u8 field;
    void* manager;

    request.unk_30 = 0;
    request.unk_34 = 0;
    first = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 1);
    manager = M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10);
    selector = M2C_FIELD(M2C_FIELD(manager, void**, 0x2424), s32*, 8);
    second = func_001E1708((s32)manager, 3);
    field = M2C_FIELD(input, u8*, 0x28);
    random = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_00 = selector;
    request.unk_08 = first;
    request.unk_20 = (s128)value;
    request.unk_04 = (s32)field;
    request.unk_0C = second;
    request.unk_10 = random * 2.3283064e-10f;
    request.unk_30 = 0;
    request.unk_34 = 0;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 1);
}
#ifdef NON_MATCHING
// Unmatched: the final predicate result and return constants use another saved register.
#include "game/ai_manager.h"
extern s32 func_0018DDD8(void*);
s32 func_001DE520(void* unused, void* input) {
    Recovered_ManagedActor* actor = input;
    Recovered_ManagedSlot* slot;
    s32 type;
    if (!actor) return 0;
    type = actor->unk_C4;
    if (type != 1) return 0;
    slot = Actor_GetManagedSlot(actor);
    if (!slot) return 2;
    if (slot->unk_80 != type) return 2;
    if (!func_0018DDD8(slot->query)) return 2;
    return 1;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DE520);
#endif
void func_001DE598(void* unused, void* input, s128 value) {
    Recovered_AudioRequest request;
    f32 first;
    f32 second;
    f32 random;
    s32 selector;
    s32 field;
    void* component;
    void* manager;

    request.unk_30 = 0;
    request.unk_34 = 0;
    first = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 0);
    manager = M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10);
    selector = M2C_FIELD(M2C_FIELD(manager, void**, 0x2424), s32*, 8);
    second = func_001E1708((s32)manager, 3);
    component = M2C_FIELD(input, void**, 0x74);
    field = 0;
    if (component != NULL) { field = M2C_FIELD(component, s32*, 0x378); }
    random = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_00 = selector;
    request.unk_08 = first;
    request.unk_20 = (s128)value;
    request.unk_04 = field;
    request.unk_0C = second;
    request.unk_10 = random * 2.3283064e-10f;
    request.unk_30 = 0;
    request.unk_34 = 0;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 1);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DE6F0);
void func_001DEC08(void* unused, s128 value) {
    Recovered_AudioRequest request;
    s32 configured;
    f32 first;
    f32 second;
    f32 random;
    s32 selector;
    void* manager;

    request.unk_30 = 0;
    request.unk_34 = 0;
    first = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 0);
    manager = M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10);
    selector = M2C_FIELD(M2C_FIELD(manager, void**, 0x2424), s32*, 8);
    second = func_001E1708((s32)manager, 2);
    configured = (s32)M2C_FIELD(M2C_FIELD(D_0040F4D8, void**, 0x873F0), u16*, 0x3A);
    random = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_00 = selector;
    request.unk_04 = configured;
    request.unk_08 = first;
    request.unk_20 = (s128)value;
    request.unk_0C = second;
    request.unk_10 = random * 2.3283064e-10f;
    request.unk_30 = 4;
    request.unk_34 = 0;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 1);
}
void func_001DED60(void* unused, s128 value, s128 input) {
    Recovered_AudioRequest request;
    s32 configured;
    f32 first;
    f32 second;
    f32 random;
    s32 selector;
    void* manager;

    request.unk_30 = 0;
    request.unk_34 = 0;
    first = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 0);
    manager = M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10);
    selector = M2C_FIELD(M2C_FIELD(manager, void**, 0x2424), s32*, 8);
    second = func_001E1708((s32)manager, 1);
    configured = (s32)M2C_FIELD(M2C_FIELD(D_0040F4D8, void**, 0x873F0), u16*, 0x3A);
    random = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_00 = selector;
    request.unk_04 = configured;
    request.unk_08 = first;
    request.unk_20 = (s128)value;
    request.unk_0C = second;
    request.unk_10 = random * 2.3283064e-10f;
    request.unk_30 = 1;
    request.unk_34 = 0;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 1);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DEEB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF080);
void func_001DF278(void* unused, s128 value, s128 input) {
    Recovered_AudioRequest request;
    s32 configured;
    f32 first;
    f32 second;
    f32 random;
    s32 selector;
    void* manager;

    request.unk_30 = 0;
    request.unk_34 = 0;
    first = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 0);
    manager = M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10);
    selector = M2C_FIELD(M2C_FIELD(manager, void**, 0x2424), s32*, 8);
    second = func_001E1708((s32)manager, 0);
    configured = (s32)M2C_FIELD(M2C_FIELD(D_0040F4D8, void**, 0x873F0), u16*, 0x3A);
    random = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_00 = selector;
    request.unk_04 = configured;
    request.unk_08 = first;
    request.unk_20 = (s128)value;
    request.unk_0C = second;
    request.unk_10 = random * 2.3283064e-10f;
    request.unk_30 = 4;
    request.unk_34 = 0;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 1);
}
#ifdef NON_MATCHING
// Unmatched: saved-register allocation and request-store scheduling differ.
extern f32 D_003BD358;
void func_001DF3D0(void* arg0, void* arg1, s128 arg2, f32 fparg0) {
    Recovered_AudioRequest request;
    f32 temp_f0;
    f32 temp_f20;
    s32 temp_18;
    s32 temp_20;
    void* temp_4;

    request.unk_30 = 0;
    request.unk_34 = 0;
    temp_20 = func_001DE520(arg0, arg1);
    temp_f20 = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 1);
    temp_4 = M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10);
    temp_18 = M2C_FIELD(M2C_FIELD(temp_4, void**, 0x2424), s32*, 0x10);
    temp_f0 = func_001E1708((s32)temp_4, 1);
    request.unk_00 = temp_18;
    request.unk_08 = temp_f20;
    request.unk_20 = (s128)arg2;
    request.unk_34 = temp_20;
    request.unk_04 =
        M2C_FIELD(M2C_FIELD(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), void**, 0x2424), s32*, 0x10);
    request.unk_0C = temp_f0;
    request.unk_10 = D_003BD358;
    request.unk_30 = 4;
    request.unk_38 = 1;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 0);
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF3D0);
#endif
void func_001DF4D0(void* owner, void* actor) {
    Recovered_AudioRequest request;
    f32 second;
    f32 first;
    f32 random;
    s32 kind;
    s32 query;
    void* manager;

    request.unk_30 = 0;
    request.unk_34 = 0;
    first = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 1);
    manager = M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10);
    kind = M2C_FIELD(M2C_FIELD(manager, void**, 0x2424), s32*, 0x10);
    second = func_001E1708((s32)manager, 3);
    query = func_001DF028(owner, M2C_FIELD(actor, s128*, 0x100), 1, NULL);
    random = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_00 = kind;
    request.unk_08 = first;
    request.unk_0C = second;
    request.unk_04 = query;
    request.unk_10 = random * 2.3283064e-10f;
    request.unk_20 = M2C_FIELD(actor, s128*, 0xA0);
    request.unk_30 = 1;
    request.unk_34 = 0;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 0);
}
void func_001DF640(void* unused, s128 value) {
    Recovered_AudioRequest request;
    s32 after;
    f32 first;
    f32 second;
    f32 random;
    u16 before;

    request.unk_30 = 0;
    request.unk_34 = 0;
    first = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 0);
    before = M2C_FIELD(M2C_FIELD(D_0040F4D8, void**, 0x873F0), u16*, 0x3E);
    second = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 1);
    after = (s32)M2C_FIELD(M2C_FIELD(D_0040F4D8, void**, 0x873F0), u16*, 0x3E);
    random = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_00 = (s32)before;
    request.unk_04 = after;
    request.unk_08 = first;
    request.unk_20 = (s128)value;
    request.unk_0C = second;
    request.unk_10 = random * 2.3283064e-10f;
    request.unk_30 = 2;
    request.unk_34 = 0;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 0);
}
#ifdef NON_MATCHING
// Unmatched: mode/id constant lifetimes and final setup scheduling differ.
void func_001DF7B0(void* arg0, s128 arg1) {
    Recovered_AudioRequest request;
    f32 temp_f20;
    f32 temp_f2;
    f32 var_f1;
    u16 temp_17;

    request.unk_30 = 0;
    request.unk_34 = 0;
    temp_f20 = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 1);
    temp_17 = M2C_FIELD(M2C_FIELD(D_0040F4D8, void**, 0x873F0), u16*, 0x3E);
    temp_f2 = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 3);
    var_f1 = (f32)NextAudioRandom(&D_0040EB30);
    request.unk_00 = (s32)temp_17;
    request.unk_08 = temp_f20;
    request.unk_20 = (s128)arg1;
    request.unk_04 = 2;
    request.unk_0C = temp_f2;
    request.unk_10 = var_f1 * 2.3283064e-10f;
    request.unk_30 = 2;
    request.unk_34 = 0;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 0);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF7B0);
#endif
void func_001DF908(void* owner, s128 position, s32 kind) {
    Recovered_AudioRequest request;
    f32 firstLevel, secondLevel;
    request.unk_30 = 0;
    request.unk_34 = 0;
    firstLevel = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 1);
    secondLevel = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 1);
    request.unk_04 = request.unk_00 = kind;
    request.unk_08 = firstLevel;
    request.unk_20 = position;
    request.unk_0C = secondLevel;
    request.unk_10 = 1.0f;
    request.unk_30 = 2;
    request.unk_34 = 0;
    request.unk_38 = 0;
    func_001E0930(M2C_FIELD(GameplayPools()->unk_4BD8, void**, 0x10), &request, 1);
}

extern u8 func_00148438(void*);
extern u8 func_00152108(void*);
s32 func_001DF9E0(void* arg0, void* arg1) {
    u32 temp_3;
    void* temp_4;
    void* temp_4_2;

    if (arg1 != NULL) {
        temp_3 = M2C_FIELD(arg1, u32*, 0xC4);
        switch (temp_3) {
            case 1:
            case 2:
                return M2C_FIELD(
                    M2C_FIELD(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x10), void**, 0x2424), s32*,
                    0x10);
            case 7:
                return M2C_FIELD(
                    M2C_FIELD(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x10), void**, 0x2424), s32*, 8);
            case 4: return func_00148438(arg1);
            case 3: return func_00152108(arg1);
            case 0:
                temp_4_2 = M2C_FIELD(arg1, void**, 0xBC);
                if (temp_4_2 != NULL) {
                    temp_4 = M2C_FIELD(M2C_FIELD(temp_4_2, void**, 0x40), void**, 0x34);
                    if (temp_4 != NULL) { return (s32)M2C_FIELD(temp_4, u8*, 0xC); }
                }
                /* Duplicate return node #11. Try simplifying control flow for better match */
                return 0;
            default: return 0;
        }
    } else {
        return 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFAB0);
#ifdef NON_MATCHING
// Unmatched: two temporary registers are reversed while loading the shared pool view.
extern f32 func_0025D9C0(void*);
f32 func_001DFB20(void* arg0, void* arg1) {
    f32 var_f0;
    s32 var_5;
    Recovered_PlaybackPools* pools;
    u32 temp_3;
    void* temp_4;

    var_f0 = 0.0f;
    if (arg1 == NULL) { return func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 3); }
    temp_3 = M2C_FIELD(arg1, u32*, 0xC4);
    switch (temp_3) {
        case 0:
            pools = GameplayPools();
            var_5 = 3;
            goto block_6;
        case 5:
            pools = GameplayPools();
            var_5 = 1;
        block_6:
            return func_001E1708(M2C_FIELD(pools->unk_4BD8, s32*, 0x10), var_5);
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
            temp_4 = M2C_FIELD(arg1, void**, 0xB4);
            if (temp_4 != NULL) { return func_0025D9C0(temp_4); }
            var_f0 = func_001E1708(M2C_FIELD(GameplayPools()->unk_4BD8, s32*, 0x10), 1);
        default: return var_f0;
    }
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFB20);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFC00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFC08);
#ifdef NON_MATCHING
// Unmatched: the second array's base address is hoisted into the first loop's setup.
extern s32 func_001DD838(void);
extern s32 D_003BD310[7];
/* Native entries have a 16-byte stride and a countdown byte at +0x0C; original identities are UNVERIFIED. */
typedef struct {
    u8 unk_00[0xC];
    u8 unk_0C;
    u8 unk_0D[3];
} Recovered_AudioCounterEntry;
extern Recovered_AudioCounterEntry D_0042A3F0[4];
void func_001DFC78(void) {
    u32 i;
    s32* counter;
    Recovered_AudioCounterEntry* entry;
    u8 value;
    func_001DD838();
    i = 0;
    counter = D_003BD310;
    /* The native prefix walk stops at the first zero, not just the seventh entry. */
    if (*counter) {
        (*counter)--;
    next_counter:
        i++;
        counter++;
        if (i < 7U) {
            s32 value = *counter;
            if (value) {
                *counter = value - 1;
                goto next_counter;
            }
        }
    }
    i = 0;
    entry = D_0042A3F0;
    do {
        value = entry->unk_0C;
        i++;
        if (value) entry->unk_0C = value - 1;
        entry++;
    } while (i < 4U);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFC78);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFD08);
extern void func_001E1690(void*,s32,s32);
void func_001DFE38(void* arg0) {
    s32* var_2;
    s32* var_2_2;
    s32 var_3;

    var_3 = 3;
    M2C_FIELD(arg0, s32*, 0x2418) = 1;
    M2C_FIELD(arg0, s32*, 0x2428) = 0;
    var_2 = (s32*)(((s8*)arg0) + 0x2448);
    M2C_FIELD(arg0, s32*, 0x2430) = 0;
    M2C_FIELD(arg0, s32*, 0x241C) = 0;
    M2C_FIELD(arg0, s32*, 0x2424) = 0;
    do {
        *var_2 = 0;
        var_3 -= 1;
        var_2 = (s32*)(((s8*)var_2) + -4);
    } while (var_3 >= 0);
    var_3 = 3;
    var_2_2 = (s32*)(((s8*)arg0) + 0x2458);
    do {
        *var_2_2 = 0;
        var_3 -= 1;
        var_2_2 = (s32*)(((s8*)var_2_2) + -4);
    } while (var_3 >= 0);
    func_001E1690(arg0, 0, 0);
}

/* Partial input and record views; field meanings, original identities and unused storage are UNVERIFIED. */
typedef struct {
    u8 unk_00[0x100];
    s128 unk_100;
} Recovered_IndirectActorData;
typedef struct {
    Recovered_IndirectActorData* data;
} Recovered_IndirectActor;
typedef struct {
    Recovered_IndirectActor* actor;
    u8 unk_04[0xC];
    s128 unk_10;
    s32 unk_20;
    s8 unk_24;
} Recovered_ActorAudioRecord;
void func_001DFEB0(Recovered_ActorAudioRecord* self, Recovered_IndirectActor* actor, s32 value) {
    Recovered_IndirectActorData* data;
    s128 position;
    self->actor = actor;
    data = actor->data;
    position = data->unk_100;
    self->unk_24 = value;
    self->unk_10 = position;
    self->unk_20 = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001E0028);

void func_001E0440(void *arg0) {
    func_001DFC78();
    func_001E0FE8(arg0);
    func_001E10C0(arg0);
    func_001E1068(arg0);
}

#include "ps2/recovered_types.h"
extern s32 func_00280100(s32, void *);
extern void * D_0040F510;
extern void func_001DFE38(void *);

s32 func_001E0480(void *arg0) {
    s32 *var_16;
    s32 var_20;
    void **var_17;
    void **var_18;
    void *temp_3;
    void *temp_5;
    void *temp_5_2;

    var_17 = (void **) (((s8 *) arg0) + 0x50);
    var_16 = (s32 *) (((s8 *) arg0) + 0x30);
    var_18 = var_17;
    var_20 = 7;
    do {
        if (*var_16 != 0) {
            temp_3 = *var_17;
            M2C_FIELD(temp_3, M2C_UNK (**)(void *), 0x1C)((void *) (((s8 *) var_18) + M2C_FIELD(temp_3, s16 *, 0x18)));
            *var_16 = 0;
        }
        var_18 = (void **) (((s8 *) var_18) + 0x10);
        var_17 = (void **) (((s8 *) var_17) + 0x10);
        var_20 -= 1;
        var_16 = (s32 *) (((s8 *) var_16) + 4);
    } while (var_20 >= 0);
    temp_5 = M2C_FIELD(arg0, void **, 0x241C);
    if (temp_5 != NULL) {
        func_00280100((s32) D_0040F510, temp_5);
        M2C_FIELD(arg0, void **, 0x241C) = NULL;
    }
    temp_5_2 = M2C_FIELD(arg0, void **, 0x2420);
    if (temp_5_2 != NULL) {
        func_00280100((s32) D_0040F510, temp_5_2);
        M2C_FIELD(arg0, void **, 0x2420) = NULL;
    }
    M2C_FIELD(arg0, s32 *, 0x2434) = 0;
    M2C_FIELD(arg0, s32 *, 0x2438) = 0;
    func_001DFE38(arg0);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001E0550);
extern s32 func_001E07F0(void*,s32*);
/* Partial native slot and dispatch views; original identities and complete
 * owner extent remain UNVERIFIED. The callback's returned word is discarded. */
typedef struct Recovered_AudioObjectDispatch Recovered_AudioObjectDispatch;
struct Recovered_AudioObjectDispatch {
    u8 unk_00[8];
    s16 adjust;
    u16 unk_0A;
    s32 (*apply)(void*, Recovered_PlaybackParameters*);
};
typedef struct {
    Recovered_AudioObjectDispatch* dispatch;
    u8 unk_04[0xC];
} Recovered_AudioObject;
typedef struct {
    u8 unk_00[0x30];
    s32* ids[8];
    Recovered_AudioObject objects[8];
} Recovered_AudioObjectOwner;
typedef char AudioObjectStride[sizeof(Recovered_AudioObject) == 0x10 ? 1 : -1];
typedef char AudioObjectArrayOffset[(u32) & ((Recovered_AudioObjectOwner*)0)->objects == 0x50 ? 1 : -1];
void func_001E06F0(Recovered_AudioObjectOwner* owner, s32* key, s128 position) {
    Recovered_PlaybackParameters parameters;
    s32 index;
    parameters.flags = 0;
    index = func_001E07F0(owner, key);
    if (index != -1) {
        Recovered_AudioObjectDispatch* dispatch;
        M2C_FIELD(&parameters, s128*, 0x30) = position;
        parameters.flags = 1;
        dispatch = M2C_FIELD((u8*)owner + index * 0x10, Recovered_AudioObjectDispatch**, 0x50);
        dispatch->apply((u8*)owner + (index * 0x10 + 0x50) + dispatch->adjust, &parameters);
    }
}
#ifdef NON_MATCHING
// Unmatched: table access and adjusted-object address formation are coalesced differently.
extern void func_001DF7B0(void*, s128);
/* Partial release entry in the native dispatch table; original identities are UNVERIFIED. */
typedef struct {
    u8 unk_00[0x18];
    s16 adjust;
    u16 unk_1A;
    s32 (*release)(void*);
} Recovered_AudioReleaseDispatch;
void func_001E0768(Recovered_AudioObjectOwner* owner, s32* key, s128 position) {
    u8 token[8];
    s32 index = func_001E07F0(owner, key);
    if (index != -1) {
        Recovered_AudioObject* object;
        Recovered_AudioReleaseDispatch* dispatch;
        s16 adjust;

        func_001DF7B0(token, position);
        object = &owner->objects[index];
        dispatch = (Recovered_AudioReleaseDispatch*)object->dispatch;
        adjust = dispatch->adjust;
        dispatch->release((u8*)object + adjust);
        owner->ids[index] = 0;
    }
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001E0768);
#endif

#include "ps2/recovered_types.h"

s32 func_001E07F0(void *arg0, s32 *arg1) {
    s32 *var_4;
    s32 var_3;

    var_4 = (s32 *) (((s8 *) arg0) + 0x30);
    var_3 = 0;
loop_1:
    if (*var_4 != arg1) {
        var_3 += 1;
        var_4 = (s32 *) (((s8 *) var_4) + 4);
        if (var_3 >= 8) {
            return -1;
        }
        goto loop_1;
    }
    return var_3;
}

/* Native selection values are copied as sixteen unaligned bytes. Original
 * identities and member meanings remain UNVERIFIED. */
typedef struct __attribute__((packed)) {
    u64 unk_00, unk_08;
} Recovered_AudioSelectionValue;
extern s32 func_0028BBA0(Recovered_AudioSelectionValue*);
extern s32 func_0028B948(void*, Recovered_AudioSelectionValue*);
s32 func_001E0820(void* owner, Recovered_AudioSelectionValue* input, s32 unused, s32 twice) {
    Recovered_AudioSelectionValue value;
    s32 passes;
    s32 pass;
    s32 best;
    s32 selected;
    u32 i;
    passes = twice ? 2 : 1;
    best = (s32)0x80000000;
    selected = -1;
    pass = 0;
    value = *input;
    if (passes) {
        do {
            if (pass) func_0028BBA0(&value);
            for (i = 0; i < M2C_FIELD(M2C_FIELD(owner, void**, 0x2424), u32*, 0x24); i++) {
                s32 result =
                    func_0028B948((u8*)M2C_FIELD(M2C_FIELD(owner, void**, 0x2424), void**, 0x34) + i * 16, &value);
                if (best < result) {
                    best = result;
                    selected = i;
                }
            }
            pass++;
        } while (pass < passes);
    }
    return best ? selected : -1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001E0928);

#include "ps2/recovered_types.h"

void func_001E0930(void *arg0, void *arg1, s32 arg2) {
    u32 temp_3;
    void *temp_4;
    void *temp_4_2;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x2410);
    if (temp_3 < 0x40U) {
        temp_4 = (temp_3 * 0x50) + arg0;
        M2C_FIELD(temp_4, s128 *, 0xD0) = (s128) M2C_FIELD(arg1, s128 *, 0);
        temp_4_2 = temp_4 + 0xD0;
        M2C_FIELD(temp_4_2, s128 *, 0x10) = (s128) M2C_FIELD(arg1, s128 *, 0x10);
        M2C_FIELD(temp_4_2, s128 *, 0x20) = (s128) M2C_FIELD(arg1, s128 *, 0x20);
        M2C_FIELD(temp_4_2, s128 *, 0x30) = (s128) M2C_FIELD(arg1, s128 *, 0x30);
        M2C_FIELD(((M2C_FIELD(arg0, u32 *, 0x2410) * 0x50) + arg0), s8 *, 0x114) = 0;
        M2C_FIELD(((M2C_FIELD(arg0, u32 *, 0x2410) * 0x50) + arg0), s8 *, 0x115) = (s8) arg2;
        M2C_FIELD(arg0, u32 *, 0x2410) = (u32) (M2C_FIELD(arg0, u32 *, 0x2410) + 1);
    }
}


void func_001E1068(void *arg0) {
    u8 sp[8];
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x20);
    if (temp_3 != -1) {
        if (temp_3 == 0) {
            func_001DEEB8(sp, M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, u8 *, 0x24), 0);
        }
        M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) - 1);
    }
}

void func_001E10C0(void *arg0) {
    func_001E0D28();
    func_001E0F28(arg0);
    func_001E0E70(arg0);
    func_001E0A30(arg0);
}


s32 func_001E1240(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x30);
}


void func_001E1690(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        M2C_FIELD(arg0, f32 *, 0x242C) = func_001ED820(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x2C));
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x242C) = 0.0f;
}

void func_001E16E0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x18) = func_00281120();
}

f32 func_001E1708(s32 arg0, s32 arg1) {
    return (&D_003BD390)[arg1];
}
