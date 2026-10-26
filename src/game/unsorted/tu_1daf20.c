#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001DD6C0();

/* Partial playback controller; field meanings and resource types are UNVERIFIED. */
typedef struct Recovered_PlaybackController {
    void* playback;
    u32 unk_04;
    u32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    void* resources[2];
    u32 state;
} Recovered_PlaybackController;
extern void* D_0040F510;
extern void* func_001D8478(void*);
extern s32 func_001D9450(void*, void*, s32);
extern void func_001D97C8(void*, void*);
extern void func_001D84C8(void*, void*);
extern s32 func_001D92A0(void*, u64, s32, u32, u32, u32);
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

#ifdef NON_MATCHING
// Unmatched: saved-register allocation differs for the two-resource loop.
s32 func_001DAF20(Recovered_PlaybackController* owner, void* playback, u32 first, u32 second) {
    void** resources;
    void** resource;
    s32 remaining;
    s32 result;
    remaining = 1;
    resources = owner->resources;
    owner->playback = playback;
    resource = resources;
    M2C_FIELD(playback, f32*, 0x34) = 1.0f;
    M2C_FIELD(playback, f32*, 0x3C) = 1.0f;
    owner->unk_04 = first;
    owner->unk_08 = second;
    do {
        remaining--;
        *resource = func_001D8478(M2C_FIELD(D_0040F510, void**, 0xCBD4));
        resource++;
    } while (remaining >= 0);
    result = func_001D9450(owner->playback, resources, 2);
    owner->state = 0;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DAF20);
#endif
#ifdef NON_MATCHING
// Unmatched: setup and release-loop scheduling differ.
s32 func_001DAFD0(Recovered_PlaybackController* owner) {
    void** resource;
    s32 remaining;
    s32 result = 1;
    if (owner->state == 0) { func_001D9450(owner->playback, 0, 0); }
    resource = owner->resources;
    remaining = 1;
    func_001D97C8(M2C_FIELD(D_0040F510, void**, 0xCBDC), owner->playback);
    owner->playback = 0;
    do {
        void* value;
        remaining--;
        value = *resource++;
        func_001D84C8(M2C_FIELD(D_0040F510, void**, 0xCBD4), value);
    } while (remaining >= 0);
    owner->state = result;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DAFD0);
#endif
#ifdef NON_MATCHING
// Unmatched: state initialization uses a different temporary register.
s32 func_001DB088(Recovered_PlaybackController* owner, const u64* key, s32 value, u32 flags) {
    switch (owner->state) {
        case 0:
        case 2:
            func_001D9450(owner->playback, owner->resources, 2);
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DB088);
#endif

#include "ps2/recovered_types.h"
extern s32 func_001DD3E0(void *);

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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DB2B0);

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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC038);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC1A0);
#ifdef NON_MATCHING
// Unmatched: large-offset addressing and field-store scheduling differ.
s32 func_001DC278(Recovered_PlaybackTransitionOwner* owner, Recovered_PlaybackTransition* transition) {
    f32 previous = owner->unk_191C;
    owner->unk_1920 = previous;
    owner->unk_1918 = M2C_FIELD((u8*)D_0040F0E0 + 0x20120, f32*, 0x20);
    owner->unk_1924 = transition->unk_0C - previous;
    owner->unk_192C = 1;
    owner->unk_1928 = transition->unk_10;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC278);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC2C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC448);
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC690);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC6E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DC790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCC08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCCF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCDC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DCF70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DD158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DD3E0);

void func_001DD4C8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x4C) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DD4D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DD508);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DD5D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DD6B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1daf20", func_001DD6C0);
