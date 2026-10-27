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
#ifdef NON_MATCHING
extern void func_00382348(void*, s32);
extern s32 func_0035D728(char*, const char*, ...);
extern void* func_00107CF8(s32);
extern void func_00280A08(void*);
extern char D_0042A3D0[];
static const char D_003F7580[] = "PlyrWpn%d";
static const char D_003F7590[] = "Grd%d";
// Unmatched: loop cursor lifetimes, short-loop padding and allocation differ.
void func_001D6488(void* self) {
    s32 index;
    u8* slot;
    u8* name;
    u8* item;
    u8* active;
    u8* resources;
    void* pool;
    M2C_FIELD(self, void**, 0x1BE0) = 0;
    M2C_FIELD(self, u64*, 0x2A8) = 0;
    M2C_FIELD(self, s32*, 0x1C24) = 0;
    M2C_FIELD(self, s32*, 0x29C) = 0;
    M2C_FIELD(self, void**, 0x1C18) = 0;
    M2C_FIELD(self, s32*, 0x1C1C) = 0;
    M2C_FIELD(self, void**, 0x1BE4) = 0;
    M2C_FIELD(self, u64*, 0x2B0) = 0;
    M2C_FIELD(self, f32*, 0x1C48) = 0.0f;
    M2C_FIELD(self, s32*, 0x1C34) = 0;
    M2C_FIELD(self, s32*, 0x1C38) = 0;
    M2C_FIELD(self, s32*, 0x1C14) = 0;
    M2C_FIELD(self, u8*, 0x1C44) = 0;
    M2C_FIELD(self, void**, 0x1C0C) = 0;
    M2C_FIELD(self, void**, 0x1C10) = 0;
    func_00382348((u8*)self + 0x2A0, 0x02B9D6F8);
    D_0042A3D0[0] = 0;
    slot = (u8*)self + 0x2C0;
    for (index = 5; index >= 0; index--) {
        M2C_FIELD(slot, u8*, 0x90) = 0;
        slot += 0x430;
    }
    resources = (u8*)self + 0x20;
    pool = (u8*)self + 0x40;
    name = (u8*)self + 4;
    item = self;
    for (index = 0; index < 2; index++) {
        func_0035D728((char*)name, D_003F7580, index);
        name += 0x10;
        M2C_FIELD(item, u8*, 0xF) = 0;
        M2C_FIELD(item, void**, 0) = func_00107CF8(0xB8);
        item += 0x10;
    }
    active = (u8*)self + 0x2F;
    name = (u8*)self + 0x24;
    for (index = 0; index < 2; index++) {
        func_0035D728((char*)name, D_003F7590, index);
        name += 0x10;
        *active = 0;
        active += 0x10;
        M2C_FIELD(resources, void**, 0) = func_00107CF8(0xB8);
        resources += 0x10;
    }
    func_00280A08(pool);
    M2C_FIELD(self, s32*, 0x1C2C) = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6488);
#endif
#ifdef NON_MATCHING
/* Partial native access views; original identities and untouched fields are UNVERIFIED. */
typedef struct Recovered_PlaybackSetup {
    u32 entryCount;
    void* resources;
    s32 resourceCount;
    void* pooledResources;
    s32 pooledCount;
} Recovered_PlaybackSetup;
typedef struct Recovered_PlaybackKey {
    u64 key;
    u32 address, length;
} Recovered_PlaybackKey;
typedef struct Recovered_PlaybackStream {
    u8 unk_00[8];
    s32 field08;
    u8 unk_0C[0x14];
    s16 field20;
} Recovered_PlaybackStream;
typedef struct Recovered_PlaybackInitialization {
    u8 unk_00[0xC];
    s32 field0C, field10;
} __attribute__((aligned(16))) Recovered_PlaybackInitialization;

extern u8 D_0040D9F9;
__asm__(".extern D_0040D9F9, 1");
extern u8* D_003C09E8[];
extern f32 PlaybackParameterWords[] __asm__("D_003BD2A8");
extern const char* D_003BD2CC[];
extern const char D_003F7598[];
extern char D_0042A3D0[];
extern void* PlaybackRuntimeWords[] __asm__("D_0040F510");
extern u8* D_0040F4D0[];
extern u8* D_0040F4C4[];
extern s32 D_003BD2A4[];
extern const char D_003F75A8[], D_003F8BF8[];
extern void func_002726D0(u64, void*);
extern void func_0027B950(void*, void*, const char*, const char*, const char*, s32, f32, f32, s32);
extern Recovered_PlaybackKey* func_001E89B0(void*, u64);
extern void func_001D75E0(void*, void*, u32, u32);
extern s32 func_00280A38(void*, void*, s32);
extern void func_001F0320(void*, void*);
extern void* func_00281808(void*);
extern Recovered_PlaybackStream* func_001D8478(void*);
extern s32 func_0035D728(char*, const char*, ...);
extern void* func_0027FF78(void*, const char*, s32, s32, s32, u32, u32, const char*, s32);
extern void func_001D84C8(void*, Recovered_PlaybackStream*);
extern void* func_00280200(void*, const u64*, s32);
extern void func_001093C0(void*, const char*, s32, s32, void (*)(s32, void*), void*, u32, u32);
extern void func_001D72C0(s32, void*);
extern void func_001D72E8(s32, void*);
extern void func_001D7310(s32, void*);
extern void func_001D7338(s32, void*);
extern Recovered_PlaybackSlot* func_001D7278(Recovered_PlaybackSlots*);
extern void* func_001D7460(Recovered_ResourceSlots*);
extern s32 func_001F03D0(void*, u64, u64, void*, s32, s32, u8);

// Unmatched: GP flag access, stack lifetimes and state-dispatch scheduling differ.
s32 func_001D65F8(void* self, Recovered_PlaybackSetup* setup) {
    Recovered_PlaybackInitialization initialization;
    char filename[64];
    s32 index;
    u8* name;
    u8* resource;
    u32 address;
    u32 firstValue, secondValue;
    s32 streamValue, streamBytes;
    void* runtime;
    Recovered_PlaybackStream* stream;
    Recovered_ResourceEntry* entry;
    Recovered_PlaybackSlot* slot;
    if (!D_0040D9F9) {
        func_002726D0(0x544614b7182c0000UL, D_0042A3D0);
        func_0027B950(D_003C09E8[0] + 4, PlaybackParameterWords, D_0042A3D0, D_003F7598, D_003BD2CC[0], 0, 0.0f, 0.0f,
                      0);
        D_0040D9F9 = 1;
    }
    M2C_FIELD(self, f32*, 0x1C28) = 0.0f;
    switch (M2C_FIELD(self, u32*, 0x1C2C)) {
        case 0:
            address = func_001E89B0(M2C_FIELD(PlaybackRuntimeWords[0], void**, 0xCBD8), 0xa69c7fcda253d080UL)->address;
            name = (u8*)self + 4;
            resource = self;
            for (index = 1; index >= 0; index--) {
                func_001D75E0(M2C_FIELD(resource, void**, 0), name, address, 0x10000);
                address += 0x14000;
                name += 0x10;
                resource += 0x10;
            }
            name = (u8*)self + 0x24;
            resource = (u8*)self + 0x20;
            for (index = 1; index >= 0; index--) {
                func_001D75E0(M2C_FIELD(resource, void**, 0), name, address, 0x4000);
                address += 0x4000;
                resource += 0x10;
                name += 0x10;
            }
            M2C_FIELD(self, u32*, 0x1C2C) = 13;
        case 13:
            if (!func_00280A38((u8*)self + 0x40, setup->resources, setup->resourceCount)) return 0;
            slot = (Recovered_PlaybackSlot*)((u8*)self + 0x2C0);
            for (index = 5; index >= 0; index--) {
                initialization.field0C = 0;
                initialization.field10 = 0;
                func_001F0320(slot++, &initialization);
            }
            M2C_FIELD(self, u32*, 0x29C) = setup->entryCount;
            index = 0;
            if (M2C_FIELD(self, u32*, 0x29C)) {
                entry = (Recovered_ResourceEntry*)((u8*)self + 0x284);
                do {
                    index++;
                    entry->resource = func_00281808((u8*)PlaybackRuntimeWords[0] + 0xB308);
                    entry->stamp = 0;
                    M2C_FIELD(entry->resource, u8*, 0x34) = 1;
                    entry++;
                } while ((u32)index < M2C_FIELD(self, u32*, 0x29C));
            }
            M2C_FIELD(self, void**, 0x1C18) = setup->pooledResources;
            M2C_FIELD(self, u8*, 0x1C44) = 1;
            M2C_FIELD(self, s32*, 0x1C1C) = setup->pooledCount;
            M2C_FIELD(self, s32*, 0x1C20) = 0;
            M2C_FIELD(self, u8*, 0x1C3C) = 1;
            M2C_FIELD(self, Recovered_PlaybackStream**, 0x1C14) =
                func_001D8478(M2C_FIELD(PlaybackRuntimeWords[0], void**, 0xCBD4));
            M2C_FIELD(self, u32*, 0x1C2C) = 1;
        case 1:
            func_0035D728(filename, D_003F75A8, M2C_FIELD(D_0040F4D0[0], s8*, 0x5AAC), D_003BD2A4[0]);
            stream = M2C_FIELD(self, Recovered_PlaybackStream**, 0x1C14);
            runtime = PlaybackRuntimeWords[0];
            streamValue = stream->field08;
            streamBytes = stream->field20 << 11;
            firstValue = func_001E89B0(M2C_FIELD(runtime, void**, 0xCBD8), 0x8e4c293508000000UL)->address;
            secondValue =
                func_001E89B0(M2C_FIELD(PlaybackRuntimeWords[0], void**, 0xCBD8), 0x8e4c293508000000UL)->length;
            M2C_FIELD(self, void**, 0x1C00) =
                func_0027FF78(runtime, filename, 1, streamValue, streamBytes, firstValue, secondValue, D_003F8BF8, 0);
            if (!M2C_FIELD(self, void**, 0x1C00)) return 0;
            func_001D84C8(M2C_FIELD(PlaybackRuntimeWords[0], void**, 0xCBD4),
                          M2C_FIELD(self, Recovered_PlaybackStream**, 0x1C14));
            M2C_FIELD(self, void**, 0x1C14) = 0;
            resource = M2C_FIELD(D_0040F4D0[0], u8**, 0x5AEC);
            M2C_FIELD(self, void**, 0x1C0C) = func_00280200(PlaybackRuntimeWords[0], (const u64*)(resource + 0x220), 0);
            M2C_FIELD(self, void**, 0x1C10) = func_00280200(PlaybackRuntimeWords[0], (const u64*)(resource + 0x228), 0);
            M2C_FIELD(self, u32*, 0x1C2C) = 2;
        case 2:
            if (D_0040F4C4[0][0xB38] || D_0040F4C4[0][0xB39]) return 0;
            M2C_FIELD(self, void**, 0x1BEC) = 0;
            func_001093C0(D_0040F4C4[0], "Sound\\PCM\\GrdPin.dav", 8, 9, func_001D72C0, self, 1, 0x02000000);
            M2C_FIELD(self, u32*, 0x1C2C) = 3;
        case 3:
            if (!M2C_FIELD(self, void**, 0x1BEC)) return 0;
            if (D_0040F4C4[0][0xB38] || D_0040F4C4[0][0xB39]) return 0;
            M2C_FIELD(self, s32*, 0x1C04) = 0;
            func_001093C0(D_0040F4C4[0], "chars\\guns\\GrdPin.wdo", 8, 9, func_001D72E8, self, 0, 0x02000000);
            M2C_FIELD(self, u32*, 0x1C2C) = 4;
        case 4:
            if (!M2C_FIELD(self, s32*, 0x1C04)) return 0;
            M2C_FIELD(self, void**, 0x1BE8) = func_001D7278(self);
            M2C_FIELD(self, void**, 0x1BF8) = func_001D7460(self);
            M2C_FIELD(self, u32*, 0x1C2C) = 5;
        case 5:
            if (!func_001F03D0(M2C_FIELD(self, void**, 0x1BE8), 0x73055beb13032000UL, 0x73055bea7dc80000UL,
                               M2C_FIELD(self, void**, 0x1BEC), M2C_FIELD(self, s32*, 0x1C04),
                               M2C_FIELD(self, s32*, 0x1BF8), 0))
                return 0;
            M2C_FIELD(self, void**, 0x1BF4) = 0;
            func_001093C0(D_0040F4C4[0], "Sound\\PCM\\GrdLnchr.dav", 8, 9, func_001D7310, self, 0, 0x02000000);
            M2C_FIELD(self, u32*, 0x1C2C) = 6;
        case 6:
            if (!M2C_FIELD(self, void**, 0x1BF4)) return 0;
            M2C_FIELD(self, s32*, 0x1C08) = 0;
            if (D_0040F4C4[0][0xB38] || D_0040F4C4[0][0xB39]) return 0;
            func_001093C0(D_0040F4C4[0], "chars\\guns\\GrdLnchr.wdo", 8, 9, func_001D7338, self, 0, 0x02000000);
            M2C_FIELD(self, u32*, 0x1C2C) = 7;
        case 7:
            if (!M2C_FIELD(self, s32*, 0x1C08)) return 0;
            M2C_FIELD(self, void**, 0x1BF0) = func_001D7278(self);
            M2C_FIELD(self, void**, 0x1BFC) = func_001D7460(self);
            M2C_FIELD(self, u32*, 0x1C2C) = 8;
        case 8:
            if (!func_001F03D0(M2C_FIELD(self, void**, 0x1BF0), 0x730544c7b719c080UL, 0x730544c7b701e000UL,
                               M2C_FIELD(self, void**, 0x1BF4), M2C_FIELD(self, s32*, 0x1C08),
                               M2C_FIELD(self, s32*, 0x1BFC), 0))
                return 0;
            M2C_FIELD(self, u32*, 0x1C2C) = 9;
        case 9: M2C_FIELD(self, s32*, 0x1C40) = 0; return 1;
        default: return 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D65F8);
#endif

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

#ifdef NON_MATCHING
extern s32 func_001F05D0(void*);
extern void func_001F03C0(void*);
extern void func_002818D0(void*, void*);
extern void func_001D7498(s32, s32);
extern void func_001D72B8(s32, void*);
extern s32 func_00280B10(void*);
extern s32 func_00280100(void*, void*);
extern char D_0042A3D0[];
// Unmatched: native short-loop padding and the final reset-store order differ.
s32 func_001D6CB8(void* self) {
    s32 index;
    u8* slot;
    switch (M2C_FIELD(self, s32*, 0x1C2C)) {
        case 9: M2C_FIELD(self, s32*, 0x1C2C) = 10;
        case 10:
            for (index = 0; index < 6; index++) {
                if (!func_001F05D0((u8*)self + 0x2C0 + index * 0x430)) return 0;
            }
            slot = (u8*)self + 0x2C0;
            for (index = 5; index >= 0; index--) {
                func_001F03C0(slot);
                slot += 0x430;
            }
            for (index = 0; (u32)index < M2C_FIELD(self, u32*, 0x29C); index++) {
                Recovered_ResourceEntry* entry = &((Recovered_ResourceEntry*)((u8*)self + 0x284))[index];
                func_002818D0((u8*)D_0040F510 + 0xB308, entry->resource);
                entry->resource = 0;
                entry->stamp = 0;
            }
            func_001D7498((s32)self, M2C_FIELD(self, s32*, 0x1BF8));
            func_001D7498((s32)self, M2C_FIELD(self, s32*, 0x1BFC));
            M2C_FIELD(self, s32*, 0x1C34) = 0;
            M2C_FIELD(self, s32*, 0x1C38) = 0;
            func_001D72B8((s32)self, M2C_FIELD(self, void**, 0x1BE8));
            M2C_FIELD(self, void**, 0x1BE8) = 0;
            func_001D72B8((s32)self, M2C_FIELD(self, void**, 0x1BF0));
            M2C_FIELD(self, void**, 0x1BF0) = 0;
            M2C_FIELD(self, s32*, 0x1C2C) = 11;
        case 11:
            if (!func_00280B10((u8*)self + 0x40)) return 0;
            M2C_FIELD(self, s32*, 0x1C2C) = 12;
        case 12:
            if (M2C_FIELD(self, void**, 0x1C00) && !func_00280100(D_0040F510, M2C_FIELD(self, void**, 0x1C00)))
                return 0;
            M2C_FIELD(self, void**, 0x1C00) = 0;
            M2C_FIELD(self, s32*, 0x1C2C) = 13;
        case 13:
            M2C_FIELD(self, void**, 0x1C10) = 0;
            M2C_FIELD(self, u64*, 0x2A8) = 0;
            M2C_FIELD(self, u64*, 0x2B0) = 0;
            M2C_FIELD(self, void**, 0x1C18) = 0;
            M2C_FIELD(self, s32*, 0x1C1C) = 0;
            M2C_FIELD(self, void**, 0x1C0C) = 0;
            M2C_FIELD(self, u8*, 0x1C44) = 0;
            D_0042A3D0[0] = 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D6CB8);
#endif
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
#ifdef NON_MATCHING
extern void* D_0040F510;
extern u8 D_004092D0[];
extern void func_00285980(void*, s32, s32, s32, s32);
extern void* func_00328C08(void*, void*, void*, s32, void*);
// Unmatched: native short-loop padding and initialization-store scheduling differ.
void func_001D75E0(void* self, void* arg1, u32 arg2, u32 arg3) {
    s32 index;
    s32* item = (s32*)((u8*)self + 0x90);
    for (index = 1; index >= 0; index--) {
        *item = 0;
        item--;
    }
    M2C_FIELD(self, u8*, 0x70) = 4;
    M2C_FIELD(self, s32*, 0x64) = 0x3E80;
    M2C_FIELD(self, s32*, 0xA0) = arg2;
    M2C_FIELD(self, s32*, 0xA4) = arg3;
    M2C_FIELD(self, s32*, 0x6C) = arg3;
    M2C_FIELD(self, void**, 0x68) = D_004092D0;
    M2C_FIELD(self, u8*, 0x71) = 1;
    M2C_FIELD(self, u8*, 0x7C) = 0;
    M2C_FIELD(self, s32*, 0x74) = 0;
    M2C_FIELD(self, s32*, 0x78) = 0;
    func_00285980(M2C_FIELD(D_0040F510, void**, 0xCBF4), 1, 0, arg2, arg3);
    func_00328C08(M2C_FIELD(D_0040F510, void**, 0xCBA8), (u8*)self + 0x64, (u8*)self + 0x64, 0, (u8*)self + 8);
    M2C_FIELD(self, u32*, 0x5C) &= ~0x40U;
    M2C_FIELD(self, void**, 0xC) = arg1;
    M2C_FIELD(self, s32*, 0xA8) = 0;
    M2C_FIELD(self, s32*, 0xB0) = 0;
    M2C_FIELD(self, s32*, 0x88) = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1d5e40", func_001D75E0);
#endif
