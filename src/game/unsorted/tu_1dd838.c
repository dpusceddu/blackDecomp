#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/playback_state_pool.h"
#include "game/effects/random_state.h"

extern s32 func_001DFC78();
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
extern void* D_0040F4D8;
extern BkEffectRandomStatePS2 D_0040EB30;
extern f32 func_001E1708(s32, s32);
extern void func_001E0930(void*, void*, s32);
extern s32 func_001DF028(void*, s128, s32, s32*);
/* Matched requests have a 0x40-byte copy extent and an aligned quadword at +20.
 * Original request identity, field meanings and unaccessed bytes are UNVERIFIED. */
typedef struct {
    s32 unk_00, unk_04;
    f32 unk_08, unk_0C, unk_10;
    u8 unk_14[0xC];
    s128 unk_20;
    s32 unk_30, unk_34, unk_38;
    u32 unk_3C;
} AudioRequest;
typedef char AudioRequestExtent[sizeof(AudioRequest) == 0x40 ? 1 : -1];
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DE078);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DE1F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DE3D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DE520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DE598);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DE6F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DEC08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DED60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DEEB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF3D0);
void func_001DF4D0(void* owner, void* actor) {
    AudioRequest request;
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF7B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DF908);
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFB20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFC00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFC08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001DFC78);
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
} IndirectActorData;
typedef struct {
    IndirectActorData* data;
} IndirectActor;
typedef struct {
    IndirectActor* actor;
    u8 unk_04[0xC];
    s128 unk_10;
    s32 unk_20;
    s8 unk_24;
} ActorAudioRecord;
void func_001DFEB0(ActorAudioRecord* self, IndirectActor* actor, s32 value) {
    IndirectActorData* data;
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001E06F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001E0768);

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838", func_001E0820);
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
