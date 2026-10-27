#include "include_asm.h"
#include "game/audio/resource_owner.h"

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

extern s32 func_002842E8(void*);
extern s32 func_00284298(void*);
extern s32 func_001D7A60(void*);
extern s32 func_00281C98(void*);

extern void* D_0040F0E0;
extern void* D_0040F510;
extern void func_001EA518(void*, s32, s32);
extern f32 func_001ED820(void*);
extern void func_001F0F28(void*, s32, s32);
extern void func_001F0678(void*);
extern void func_001D7020(void*);
extern void func_001D6E78(Recovered_PlaybackSlots*, void*, u64, s32);
extern void ResourcePool_Update(void*);
extern s32 func_00283C38(void*, Recovered_AudioParameters*);
extern void* func_00283E78(void*, Recovered_AudioParameters*, void*);
extern void* func_00280BC0(void*);

extern f32 D_003BD294, D_003BD298, D_003BD29C, D_003BD2A0;
typedef struct Recovered_ParameterMethod {
    s16 adjustment;
    u16 unk_02;
    s32 (*call)(void*, Recovered_AudioParameters*);
} Recovered_ParameterMethod;
typedef struct Recovered_ParameterVtable {
    u8 unk_00[0x10];
    Recovered_ParameterMethod play;
} Recovered_ParameterVtable;
typedef struct Recovered_ParameterResource {
    const Recovered_ParameterVtable* vtable;
} Recovered_ParameterResource;
extern Recovered_ParameterResource* ResourcePool_Acquire(void*);

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

s32 func_001D63A8(void* owner, void* source) {
    Recovered_AudioParameters params;
    Recovered_ParameterResource* resource;
    params.flags = 0;
    M2C_FIELD(M2C_FIELD(source, void**, 0x18), u32*, 0x54) &= ~2U;
    params.source = source;
    params.kind = 0xC;
    params.gain = 1.0f;
    params.rate = 1.0f;
    params.flags = 0x85C;
    params.unk_60 = 0;
    if (M2C_FIELD(D_0040F510, u8*, 0xCB9D)) {
        params.field88 = D_003BD294;
        params.field8C = D_003BD29C;
        params.field90 = D_003BD294;
        params.field94 = D_003BD2A0;
        params.field98 = D_003BD298;
        params.field9C = D_003BD298;
        params.fieldAB = 1;
        params.flags |= 0x800000;
    }
    resource = ResourcePool_Acquire((u8*)owner + 0x94);
    return resource->vtable->play.call((u8*)resource + resource->vtable->play.adjustment, &params);
}
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
void func_001D6F90(Recovered_PlaybackSlots* self) {
    if (self->current == self->alternate) { func_001D6E78(self, self->saved, self->savedKey, self->savedActive); }
    func_001F0678(self->current);
    if (M2C_FIELD(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 0x24), u8*, 0x1E54) == 0) {
        func_001D7020(self);
    }
    self->time = TimeState_Get()->time;
}
void func_001D7020(void* self) {
    Recovered_AudioParameters params;
    params.flags = 0;
    if (M2C_FIELD(self, u8*, 0x1C44)) {
        void* source;
        void* resource;
        s32* state = (s32*)((u8*)self + 0x2A0);
        s32 value = M2C_FIELD(self, s32*, 0x2A0);
        s32 rotated = (value << 16) + (value >> 16);
        s32 combined;
        M2C_FIELD(self, s32*, 0x2A0) = rotated;
        combined = rotated + state[1];
        M2C_FIELD(self, s32*, 0x2A0) = combined;
        state[1] += combined;
        if (M2C_FIELD(self, s32*, 0x2A0) & 1) {
            source = M2C_FIELD(self, void**, 0x1C0C);
        } else {
            source = M2C_FIELD(self, void**, 0x1C10);
        }
        resource = func_00280BC0((u8*)self + 0x40);
        if (resource && source) {
            M2C_FIELD(M2C_FIELD(source, void**, 0x18), u32*, 0x54) &= ~2U;
            params.source = source;
            params.gain = 1.0f;
            params.kind = 1;
            params.rate = M2C_FIELD(self, f32*, 0x1C48);
            params.flags = 0x85C;
            params.unk_60 = 0;
            func_00283E78(resource, &params, 0);
        }
    }
}

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
extern void func_001F02C8(const char*);
extern void* func_00280200(void*, const u64*, s32);
// A complete native label, separate from the intervening assembly-owned constants.
static const char D_003F7678[] __attribute__((section(".rodata.resource_click"), aligned(8))) = "*click*";

void func_001D7500(void* self) {
    Recovered_AudioParameters params;
    u64 key;
    void* source;
    void* resource;
    if (M2C_FIELD(self, s32*, 0x1C40) > 0) {
        M2C_FIELD(self, s32*, 0x1C40) = 3;
        return;
    }
    M2C_FIELD(self, s32*, 0x1C40) = 3;
    func_001F02C8(D_003F7678);
    key = 0x5fa7a564f24ce600UL;
    params.flags = 0;
    source = func_00280200(D_0040F510, &key, 0);
    if (M2C_FIELD(self, void**, 0x1BE0)) {
        resource = func_001D6178(M2C_FIELD(self, void**, 0x1BE0))->resource;
        if (source) {
            params.flags = 0x4C;
            params.gain = 1.0f;
            params.unk_60 = 0;
            params.source = source;
            M2C_FIELD(M2C_FIELD(source, void**, 0x18), u32*, 0x54) &= ~2U;
            func_00283E78(resource, &params, 0);
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D75E0);
