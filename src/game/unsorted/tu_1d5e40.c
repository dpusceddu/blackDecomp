#include "include_asm.h"
#include "ps2/prelude.h"

extern void ResourcePool_Initialize(void*);
extern void func_001D6230(void*, s32, s32);
extern s32 func_001D76E8();
extern s32 func_001D7BB8();
extern s32 func_00281BB8();
extern void ResourcePool_Rebind(void*, void**, s32);
extern s32 func_00280A80();
extern void func_001D7128();
extern s32 func_001F0620();
extern s32 func_001F0770(s32, f32);
extern f32 D_003BD2A8;
extern s32 func_001F0C98();
extern s32 func_001F08E8(s32);
extern s32 func_001F0958(s32);
extern void * func_001092F8();

/* Partial resource owner; object and timestamp meanings are UNVERIFIED. */
typedef struct Recovered_ResourceEntry {
    void* resource;
    u32 unk_04;
    u32 stamp;
} Recovered_ResourceEntry;
typedef struct Recovered_ResourceOwner {
    u8 unk_00[0x5C];
    Recovered_ResourceEntry* entries;
    u32 count;
    u8 unk_64[0x1C];
    u32 stamp;
    u32 state;
    u8 unk_88[0x12C];
    void* playback;
} Recovered_ResourceOwner;
extern s32 func_002842E8(void*);
extern s32 func_00284298(void*);
extern s32 func_001D7A60(void*);
extern s32 func_00281C98(void*);

// Partial slot views; original identities and unused fields are UNVERIFIED.

typedef struct Recovered_ResourceSlot {
    void* resource;
    u8 unk_04[0xB];
    u8 active;
} Recovered_ResourceSlot;
typedef struct Recovered_ResourceSlots {
    u8 unk_00[0x20];
    Recovered_ResourceSlot slots[2];
} Recovered_ResourceSlots;

/* Partial controller access view; identities and unused storage are UNVERIFIED. */
typedef struct Recovered_PlaybackSlot {
    u8 unk_00[0x90];
    u8 active;
    u8 unk_91[0x39F];
} Recovered_PlaybackSlot;
typedef struct Recovered_PlaybackSlots {
    u8 unk_00[0x2A8];
    u64 key;
    u64 savedKey;
    u8 unk_2B8[8];
    Recovered_PlaybackSlot slots[6];
    void* current;
    void* saved;
    void* alternate;
    void* field1BEC;
    void* field1BF0;
    u8 unk_1BF4[0x34];
    f32 time;
    u8 unk_1C2C[0x18];
    u8 active;
    u8 savedActive;
    u8 unk_1C46[2];
    f32 gain;
} Recovered_PlaybackSlots;
typedef char PlaybackSlotsOffset[(u32) & ((Recovered_PlaybackSlots*)0)->slots == 0x2C0 ? 1 : -1];
typedef char PlaybackCurrentOffset[(u32) & ((Recovered_PlaybackSlots*)0)->current == 0x1BE0 ? 1 : -1];
typedef char PlaybackTimeOffset[(u32) & ((Recovered_PlaybackSlots*)0)->time == 0x1C28 ? 1 : -1];
typedef char PlaybackActiveOffset[(u32) & ((Recovered_PlaybackSlots*)0)->active == 0x1C44 ? 1 : -1];

extern void* D_0040F0E0;
extern void* D_0040F510;
extern void func_001EA518(void*, s32, s32);
extern f32 func_001ED820(void*);
extern void func_001F0F28(void*, s32, s32);
extern void func_001F0678(void*);
extern void func_001D7020(void*);
extern void func_001D6E78(void*, void*, u64, s32);
extern void ResourcePool_Update(void*);
typedef struct Recovered_AudioParameters {
    u8 unk_00[0x50];
    void* source;
    f32 gain;
    f32 rate;
    u8 unk_5C[4];
    u32 unk_60;
    u8 unk_64[0x24];
    f32 field88, field8C, field90, field94, field98, field9C;
    u32 unk_A0;
    u32 flags;
    u8 kind;
    u8 unk_A9[2];
    u8 fieldAB;
    u8 unk_AC[4];
} __attribute__((aligned(16))) Recovered_AudioParameters;
typedef char AudioParametersSize[sizeof(Recovered_AudioParameters) == 0xB0 ? 1 : -1];
extern s32 func_00283C38(void*, Recovered_AudioParameters*);

typedef struct Recovered_TimeState {
    u8 unk_00[0x20];
    f32 time;
} Recovered_TimeState;
static inline Recovered_TimeState* TimeState_Get(void) { return (Recovered_TimeState*)((u8*)D_0040F0E0 + 0x20120); }

s32 func_001D5E40(void) {
    return 0;
}

s32 func_001D5E48(void) {
    return 0;
}

void func_001D5E50(void) {

}

void func_001D5E58(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x1B4) = 0;
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    ResourcePool_Initialize(arg0 + 0x94);
    func_001D6230(arg0, 0, 0);
}

s32 func_001D5EA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x84);
    switch (temp_3) {                               /* irregular */
    case 1:
        M2C_FIELD(arg0, s64 *, 0x1A8) = (s64) arg2;
        M2C_FIELD(arg0, s32 *, 0x1B4) = arg4;
        M2C_FIELD(arg0, s32 *, 0x1B0) = arg3;
        if (func_001D76E8(arg4, arg3, 1, arg2) == 0) {
            return 0;
        }
        M2C_FIELD(arg0, s32 *, 0x78) = func_001D7BB8(M2C_FIELD(arg0, s32 *, 0x1B4), arg1);
        M2C_FIELD(arg0, s32 *, 0x84) = 2;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    case 2:
        func_00281BB8(arg0 + 0x94, 0, 0);
        M2C_FIELD(arg0, s32 *, 0x80) = 0;
        return 1;
    default:
        return 0;
    }
}

s32 func_001D5F58(Recovered_ResourceOwner* owner) {
    u32 index;
    switch (owner->state) {
        case 1:
            owner->state = 2;
            /* fallthrough */
        case 2:
        case 3:
        case 4:
            for (index = 0; index < owner->count; index++) { func_00284298(owner->entries[index].resource); }
            if (func_001D7A60(owner->playback) != 0) {
                M2C_FIELD(owner, void**, 0x78) = 0;
                owner->state = 5;
                owner->playback = 0;
                case 5:
                    func_00281C98((u8*)owner + 0x94);
                    owner->count = 0;
                    owner->state = 7;
                    owner->entries = 0;
                case 7: return 1;
            }
        default: return 0;
    }
}
void func_001D6038(Recovered_ResourceOwner* owner, s32 stamp) {
    Recovered_AudioParameters params;
    u32 index = 0;
    owner->stamp = stamp;
    ResourcePool_Update((u8*)owner + 0x94);
    params.flags = 0;
    for (; index < owner->count; index++) { func_00283C38(owner->entries[index].resource, &params); }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D60B8);
Recovered_ResourceEntry* func_001D6178(Recovered_ResourceOwner* owner) {
    u32 index;
    Recovered_ResourceEntry* oldest = owner->entries;
    for (index = 0; index < owner->count; index++) {
        Recovered_ResourceEntry* entry = &owner->entries[index];
        if (func_002842E8(entry->resource) == 0) {
            entry->stamp = owner->stamp;
            return entry;
        }
        oldest = entry->stamp < oldest->stamp ? entry : oldest;
    }
    func_00284298(oldest->resource);
    oldest->stamp = owner->stamp;
    return oldest;
}
void func_001D6230(void* self, s32 mode, s32 active) {
    Recovered_ResourceOwner* owner = self;
    u32 index;
    if (active) {
        for (index = 0; index < owner->count; index++) { M2C_FIELD(owner->entries[index].resource, u8*, 0x35) = 1; }
        M2C_FIELD(self, f32*, 0x7C) = func_001ED820(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x2C));
    } else {
        for (index = 0; index < owner->count; index++) { M2C_FIELD(owner->entries[index].resource, u8*, 0x35) = 0; }
        M2C_FIELD(self, f32*, 0x7C) = 1.0f;
    }
}
void func_001D62F8(Recovered_ResourceOwner* owner, Recovered_ResourceEntry* entries, u32 count) {
    u32 index;
    for (index = 0; index < owner->count; index++) { func_00284298(owner->entries[index].resource); }
    owner->count = count;
    owner->entries = entries;
}

void func_001D6388(s32 arg0, void** resources, s32 count) {
    ResourcePool_Rebind((void*)(arg0 + 0x94), resources, count);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D63A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D65F8);

void func_001D6C48(void *arg0)
{
  int temp_4;
  M2C_FIELD(arg0, s32 *, 0x1C24) = (s32) (((M2C_FIELD(arg0, s32 *, 0x1C24)) + 1) ^ 0);
  M2C_FIELD(arg0, s32 *, 0x1C40) = (s32) ((M2C_FIELD(arg0, s32 *, 0x1C40)) - 1);
  func_00280A80(arg0 + 0x40);
  if (((!D_003BD2A8) && (!D_003BD2A8)) && (!D_003BD2A8))
  {
    if (arg0)
    {
    }
  }
  func_001D7128(arg0);
  temp_4 = M2C_FIELD(arg0, s32 *, 0x1BE0);
  if (temp_4 != 0)
  {
    func_001F0620(temp_4, M2C_FIELD(arg0, s32 *, 0x1C24));
    func_001F0770(M2C_FIELD(arg0, s32 *, 0x1BE0), D_003BD2A8);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6CB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6E70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6E78);
void func_001D6F90(Recovered_PlaybackSlots* self) {
    if (self->current == self->alternate) { func_001D6E78(self, self->saved, self->savedKey, self->savedActive); }
    func_001F0678(self->current);
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x24), u8*, 0x1E54) == 0) {
        func_001D7020(self);
    }
    self->time = TimeState_Get()->time;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D7020);

void func_001D7100(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_11;

    temp_11 = M2C_FIELD(arg7, s32 *, 0x1BE0);
    if (temp_11 != 0) {
        func_001F0C98(arg0, arg1, arg2, arg3, arg4, arg5, arg6, temp_11 + 0x1D0);
    }
}

void func_001D7128(Recovered_PlaybackSlots* self) {
    s32 active = 1;
    if (!((TimeState_Get()->time - self->time) <= 0.5f)) { active = 0; }
    func_001EA518(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 8), 3, active);
}
void func_001D7198(Recovered_PlaybackSlots* self, s32 mode, s32 active) {
    s32 count;
    Recovered_PlaybackSlot* slot = self->slots;
    for (count = 5; count >= 0; count--) {
        func_001F0F28(slot, mode, active);
        slot++;
    }
    if (active) {
        self->gain = func_001ED820(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x2C));
    } else {
        self->gain = 0.0f;
    }
}

void func_001D7238(void *arg0) {
    func_001F08E8(M2C_FIELD(arg0, s32 *, 0x1BE0));
}

void func_001D7258(void *arg0) {
    func_001F0958(M2C_FIELD(arg0, s32 *, 0x1BE0));
}

Recovered_PlaybackSlot* func_001D7278(Recovered_PlaybackSlots* self) {
    s32 index;
    for (index = 0; index < 6; index++) {
        Recovered_PlaybackSlot* slot = &self->slots[index];
        if (slot->active == 0) {
            slot->active = 1;
            return slot;
        }
    }
    return 0;
}

void func_001D72B8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x90) = 0;
}

void func_001D72C0(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1BEC) = func_001092F8();
}

void func_001D72E8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1C04) = func_001092F8();
}

void func_001D7310(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1BF4) = func_001092F8();
}

void func_001D7338(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1C08) = func_001092F8();
}

void func_001D7360(Recovered_PlaybackSlots* self, s32 active) {
    if (active) {
        void* current = self->current;
        void* next = self->field1BF0;
        if (current != next) {
            self->saved = current;
            self->savedKey = self->key;
            func_001D6E78(self, next, 0x730544c7b701e000UL, 0);
        }
    } else {
        func_001D6E78(self, self->saved, self->savedKey, 1);
    }
}
void func_001D73D8(Recovered_PlaybackSlots* self) {
    void* current = self->current;
    void* next = self->alternate;
    if (current != next) {
        self->saved = current;
        self->savedActive = self->active;
        self->savedKey = self->key;
        func_001D6E78(self, next, 0x73055bea7dc80000UL, 0);
    }
    func_001F0678(self->current);
    self->time = TimeState_Get()->time;
}
void* func_001D7460(Recovered_ResourceSlots* self) {
    s32 index;
    for (index = 0; index < 2; index++) {
        if (self->slots[index].active == 0) {
            self->slots[index].active = 1;
            return self->slots[index].resource;
        }
    }
    return 0;
}

void func_001D7498(s32 arg0, s32 arg1) {
    s32 var_3;
    void *var_4;

    var_4 = arg0 + 0x2F;
    var_3 = 0;
loop_1:
    var_3 += 1;
    if (M2C_FIELD(var_4, s32 *, -0xF) == arg1) {
        M2C_FIELD(var_4, s8 *, 0) = 0;
        return;
    }
    var_4 += 0x10;
    if (var_3 >= 2) {
        return;
    }
    goto loop_1;
}

void* func_001D74C8(Recovered_ResourceSlot* slots) {
    s32 index;
    for (index = 0; index < 2; index++) {
        if (slots[index].active == 0) {
            slots[index].active = 1;
            return slots[index].resource;
        }
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D7500);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D75E0);
