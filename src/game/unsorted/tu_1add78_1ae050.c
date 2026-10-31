#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/timed_value_pool.h"
#include "game/effects/damage_window.h"
#include "game/graphics/resource_collection.h"

// Accessed attachment-pool and owner-row fields; original class identities remain UNVERIFIED.
extern void* func_00107D20(u32);
typedef struct {
    void* children[8];
    u8 unknown20[0x40];
    void* resource;
    u8 unknown64[0xC];
} PoolEntry;
typedef struct {
    u16* indices;
    u16* reverse;
    u16 count, capacity;
} IndexPool;
static inline void InitializeReverse(IndexPool* indices, u16 capacity) {
    indices->reverse = func_00107D20(capacity * 2);
    indices->count = 0;
    indices->capacity = capacity;
}
typedef char PoolEntryStride[sizeof(PoolEntry) == 0x70 ? 1 : -1];
typedef char PoolEntryResourceOffset[(u32) & ((PoolEntry*)0)->resource == 0x60 ? 1 : -1];
extern void* D_0040F510;
extern void* func_001E69E8(void*);
typedef struct {
    void* resource;
    s32 field4, field8;
    u8 flag, unknownD[3];
} OwnerRow;
extern f32 D_003BD9DC, D_003BD9E0, D_003BD9E4, D_003BD9E8, D_003BD9EC, D_003BD9F0;
extern f32 D_003BD9F4, D_003BD9F8, D_003BD9FC, D_003BDA00, D_003BDA04;

/* Accessed slot layout; original field meanings remain UNVERIFIED. */
typedef struct {
    u16 field0, field2, field4, field6;
    void* object;
    u8 fieldC, fieldD, unknownE[2];
} BkEffectSlotPS2;
typedef char EffectSlotSize[(sizeof(BkEffectSlotPS2) == 0x10) ? 1 : -1];
typedef char EffectSlotObjectOffset[((unsigned)&((BkEffectSlotPS2*)0)->object == 8) ? 1 : -1];

extern void func_001B3CD8(BkEffectSlotPS2*);
extern s32 func_001B3D18(BkEffectSlotPS2*);
extern void func_001D3040(void);
extern void func_001D3078(void);
extern void func_001D3090(void*);
extern void func_001D3368(void);
extern void func_001D3408(void*, u16);
extern void func_001D37C8(void*, u16, void*);
extern void* func_00148508(void*, u8);
extern void* D_0040F4C0;
void func_001B2BC0(BkEffectSlotPS2*);
void func_001B2C40(BkEffectSlotPS2*);
void func_001B2CD0(BkEffectSlotPS2*);

// Partial native views; original identities and unused allocation extents remain UNVERIFIED.
typedef struct {
    s32 x, y;
    u64 field8, field10, field18;
} TextureBinding;
typedef struct {
    void* resource;
    TextureBinding* binding;
} MaterialBinding;
extern void func_0026A6F0(void*);
extern void func_0026A460(u64, u64, u64, u64, void*, s32);
typedef struct {
    s32 kind;
    void* object;
} TimedPair;
typedef struct {
    Recovered_TimedValuePool pool;
    TimedPair pairs[128];
} TrackedPool;
static inline s32 EntryActive(f32 remaining) {
    s32 result = 0;
    if (remaining >= 0.0f) result = 1;
    return result;
}
static inline Recovered_TimedValueEntry* EntryAt(Recovered_TimedValuePool* pool, s16 index) {
    s32 byteOffset = index * sizeof(Recovered_TimedValueEntry);
    return (Recovered_TimedValueEntry*)(byteOffset + (s32)pool->entries);
}
extern void func_002822C8(Recovered_TimedValuePool*, u128, void*, f32);
typedef char TimedPairOffset[(u32) & ((TrackedPool*)0)->pairs == 0x1220 ? 1 : -1];
extern void* D_0040F4D0;

/* Scalar writes preserve the native stack temporary before its quadword copy. */
typedef union {
    struct {
        volatile f32 x, y, z, w;
    } f;
    s128 quad;
} FloatQuad;
static inline f32 ColorZeroPS2(void) { return 0.0f; }
extern void func_001CFB00(void*);
extern void func_001CFB30(void*);
extern s128 D_004164A0;
extern void* D_0040F4C4;
extern s32 func_00108328(void*, u32);
extern void func_001D9EC8(void*, s32);
extern void func_001ED718(void*, s32, u32);
static inline u32 TokenAt(const u32* tokens, s32 index) { return tokens[index]; }

/* FRAME encodes 8 KiB pages; these accessors use 32-bit word addresses and pixel widths. */
static inline u64 FrameBaseWords(u64 frame) { return (frame & 0x1FF) << 11; }
static inline s32 FrameWidthPixels(u64 frame) { return (frame >> 10) & 0xFC0; }
static inline s32 FrameFormat(u64 frame) { return (frame >> 24) & 0x3F; }
static inline s32 ScissorWidth(u64 rect) { return ((rect >> 16) & 0x3FF) - (rect & 0x3FF) + 1; }
static inline s32 ScissorHeight(u64 rect) { return ((rect >> 48) & 0x3FF) - ((rect >> 32) & 0x3FF) + 1; }
extern s32 func_001C79D0(u64, u64, u64, s32, s32, u64, s128);
static inline u64 TextureFromFrame(u32 baseWords, u32 widthPixels, s32 format) {
    return (baseWords >> 6) | ((u64)(widthPixels >> 6) << 14) | ((u64)format << 20) | ((u64)0xAA00 << 18);
}

extern s32 func_001ADEA8(s32);
extern s32 func_001ADF18();
extern s32 func_001ADF30();

void func_001AE050(void) {

}

void func_001AE058(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 1);
}

void func_001AE068(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) - 1);
}

void func_001AE078(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x24) = arg1;
    M2C_FIELD(arg0, s32 *, 0x28) = arg2;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

void func_001AE088(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
}

void func_001AE090(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001AE098);

void func_001AE0A8(void *arg0) {
    func_001ADEA8(arg0 + 0xC);
}

void func_001AE0C8(s32 arg0) {
    func_001ADF18(arg0 + 0xC);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001AE0E8);

s32 func_001AE0F0(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = arg0 + 0xC;
    func_001ADF18(temp_16, arg1);
    return func_001ADF30(temp_16, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0070);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0740);
void func_001B0988(void* object) {
    FloatQuad value;
    s128 first;
    void* second = (s8*)object + 0x40;
    M2C_FIELD(object, u8*, 0xB0) = 0;
    func_001CFB00(object);
    M2C_FIELD(object, u8*, 0x10) = 0;
    M2C_FIELD(object, u32*, 0x34) = 0;
    func_001CFB00(second);
    value.f.x = 1.0f;
    value.f.y = 1.0f;
    value.f.z = 1.0f;
    value.f.w = ColorZeroPS2();
    M2C_FIELD(second, u8*, 0x10) = 1;
    first = value.quad;
    value.f.x = 1.0f;
    value.f.y = 1.0f;
    value.f.z = 1.0f;
    value.f.w = ColorZeroPS2();
    M2C_FIELD(object, f32*, 0x80) = 0.0f;
    M2C_FIELD(object, s128*, 0x70) = first;
    M2C_FIELD(object, s128*, 0xA0) = value.quad;
    M2C_FIELD(object, f32*, 0x84) = 0.0f;
    M2C_FIELD(object, f32*, 0x88) = 0.0f;
}
s32 func_001B0A20(void* object) {
    FloatQuad value;
    f32 zero;
    s128 first;
    M2C_FIELD(object, u8*, 0xB0) = 0;
    M2C_FIELD(object, u8*, 0xB1) = 0;
    func_001CFB30(object);
    func_001CFB30((s8*)object + 0x40);
    M2C_FIELD(object, u32*, 0x34) = 0;
    zero = M2C_FIELD(object, f32*, 0x34);
    value.f.x = 1.0f;
    value.f.y = 1.0f;
    value.f.z = 1.0f;
    value.f.w = zero;
    M2C_FIELD(object, f32*, 0x84) = zero;
    first = value.quad;
    value.f.x = 1.0f;
    value.f.y = 1.0f;
    value.f.z = 1.0f;
    value.f.w = zero;
    M2C_FIELD(object, s128*, 0x70) = first;
    M2C_FIELD(object, f32*, 0x88) = zero;
    M2C_FIELD(object, s128*, 0xA0) = value.quad;
    M2C_FIELD(object, f32*, 0x80) = zero;
    return 1;
}
#ifdef NON_MATCHING
// Unmatched: Stock assembler pads the six-word loop; scalar stores are scheduled differently.
void func_001B0D88(void* base) {
    s32 i;
    s32* history = (s32*)((s8*)base + 0x15C);
    for (i = 31; i >= 0; i--) *history-- = 0;
    M2C_FIELD(base, f32*, 0x164) = 15.0f;
    M2C_FIELD(base, u8*, 0x178) = 1;
    M2C_FIELD(base, u8*, 0xB0) = 12;
    M2C_FIELD(base, f32*, 0x174) = 1.0f;
    M2C_FIELD(base, s32*, 0x160) = 0;
    M2C_FIELD(base, u8*, 0xA0) = 12;
    M2C_FIELD(base, u8*, 0xA1) = 0;
    M2C_FIELD(base, u8*, 0xD0) = 0;
    M2C_FIELD(base, u8*, 0xD1) = 0;
    M2C_FIELD(base, s32*, 0x168) = 66;
    M2C_FIELD(base, s32*, 0x16C) = 66;
    M2C_FIELD(base, s32*, 0x170) = 66;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0D88);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B0E00);
void func_001B2A78(BkEffectSlotPS2* slots) {
    u16 i;
    for (i = 0; i < 28; i++) { func_001B3CD8(slots + i); }
}
s32 func_001B2AC8(BkEffectSlotPS2* slots) {
    u16 i;
    s8* objects = (s8*)slots + 8;
    for (i = 0; i < 28; i++) {
        void** objectAddress = (void**)(objects + i * 16);
        void* object = *objectAddress;
        if (object) {
            void* table = M2C_FIELD(object, void**, 0x10);
            BkEffectSlotPS2* slot = slots + i;
            ((void (*)(void*, u8))M2C_FIELD(table, void**, 0x7C))((s8*)object + M2C_FIELD(table, s16*, 0x78),
                                                                  slot->fieldC);
            func_001B3D18(slot);
        }
    }
    func_001D3040();
    return 1;
}
void func_001B2B68(BkEffectSlotPS2* slots) {
    func_001D3090(M2C_FIELD(D_0040F4C0, void**, 0xD540));
    func_001B2BC0(slots);
    func_001B2C40(slots);
    func_001B2CD0(slots);
    func_001D3368();
}
void func_001B2BC0(BkEffectSlotPS2* slots) {
    u16 i;
    for (i = 0; i < 8; i++) {
        BkEffectSlotPS2* slot = slots + i;
        if (slot->fieldD && slot->field0) { func_001D3408((s8*)slots + 0x1C0 + slot->field4 * 32, slot->field0); }
    }
}
void func_001B2C40(BkEffectSlotPS2* slots) {
    u16 i;
    s8* objects = (s8*)slots + 8;
    for (i = 8; i < 20; i++) {
        BkEffectSlotPS2* slot = slots + i;
        if (slot->fieldD && slot->field0) {
            void** objectAddress = (void**)(objects + i * 16);
            func_001D37C8((s8*)slots + 0x1C0 + slot->field4 * 32, slot->field0, (s8*)*objectAddress + 0x70);
        }
    }
}
void func_001B2CD0(BkEffectSlotPS2* slots) {
    u16 i;
    s8* objects = (s8*)slots + 8;
    for (i = 20; i < 28; i++) {
        BkEffectSlotPS2* slot = slots + i;
        if (slot->fieldD && slot->field0) {
            void** objectAddress = (void**)(objects + i * 16);
            void* transform = func_00148508(*objectAddress, slot->fieldC);
            func_001D37C8((s8*)slots + 0x1C0 + slot->field4 * 32, slot->field0, transform);
        }
    }
}
s32 func_001B2D70(BkEffectSlotPS2* slots) {
    u16 i;
    s8* objects = (s8*)slots + 8;
    func_001D3078();
    for (i = 0; i < 28; i++) {
        void** objectAddress = (void**)(objects + i * 16);
        void* object = *objectAddress;
        if (object) {
            void* table = M2C_FIELD(object, void**, 0x10);
            BkEffectSlotPS2* slot = slots + i;
            ((void (*)(void*, u8))M2C_FIELD(table, void**, 0x7C))((s8*)object + M2C_FIELD(table, s16*, 0x78),
                                                                  slot->fieldC);
            func_001B3D18(slot);
        }
    }
    return 1;
}
void func_001B6188(void* base) {
    u8 i;
    for (i = 0; i < 4; i++) { M2C_FIELD(base, u8*, 0x734 + i * 0xC20) = 0; }
}
#ifdef NON_MATCHING
// Unmatched: Flag-array pointer lifetimes and zero-store scheduling differ.
void func_001B61C0(void* base, void* object) {
    u8 i, j;
    u8* a = (u8*)base + 0x1340;
    u8* b = (u8*)base + 0x1343;
    for (i = 0; i < 4; i++) {
        if (M2C_FIELD(base, void**, i * 0xC20 + 0x730) == object) {
            M2C_FIELD(base, u8*, i * 0xC20 + 0x734) = 0;
            M2C_FIELD(base, void**, i * 0xC20 + 0x730) = 0;
            for (j = 0; j < 3; j++) {
                a[i * 0xC20 + j] = 0;
                b[i * 0xC20 + j] = 0;
            }
            return;
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B61C0);
#endif
void func_001B6250(void* base) {
    u16 i;
    PoolEntry* entries = base;
    s32* a = (s32*)((s8*)base + 0x2300);
    s32* b = (s32*)((s8*)base + 0x2440);
    s32* c = (s32*)((s8*)base + 0x2580);
    IndexPool* indices = (IndexPool*)((s8*)base + 0x3440);
    M2C_FIELD(base, s32*, 0x3450) = 0;
    M2C_FIELD(base, u16*, 0x3458) = 0;
    for (i = 0; i < 80; i++) {
        PoolEntry* entry = entries + i;
        u16 j;
        for (j = 0; j < 8; j++) entry->children[j] = 0;
        entry->resource = 0;
        {
            s32* pa = a + i;
            s32* pb = b + i;
            s32* pc = c + i;
            *pa = 0;
            *pb = 8;
            *pc = -1;
        }
    }
    M2C_FIELD(base, u16**, 0x3440) = func_00107D20(160);
    InitializeReverse(indices, 80);
}
#ifdef NON_MATCHING
extern s32 func_001B1518(PoolEntry*);
// Unmatched: Release-loop constant/register allocation and final clock-store scheduling differ.
s32 func_001B6328(void* base, void* owner) {
    u16 i;
    PoolEntry* entries = base;
    s32* a = (s32*)((s8*)base + 0x2300);
    s32* b = (s32*)((s8*)base + 0x2440);
    s32* c = (s32*)((s8*)base + 0x2580);
    for (i = 0; i < 80; i++) {
        if (entries[i].resource) {
            func_001B1518(entries + i);
            {
                s32* pa = a + i;
                s32* pb = b + i;
                s32* pc = c + i;
                *pa = 0;
                *pb = 8;
                *pc = -1;
            }
        }
    }
    M2C_FIELD(base, u16*, 0x3458) = 0;
    {
        IndexPool* indices = (IndexPool*)((s8*)base + 0x3440);
        s8* b = (s8*)base + 0x32C4;
        s8* a = (s8*)base + 0x32C0;
        s8* c = (s8*)base + 0x32C8;
        for (i = 0; i < 32; i++) {
            s32* pb = (s32*)(b + i * 12);
            s32* pa = (s32*)(a + i * 12);
            f32* pc = (f32*)(c + i * 12);
            *pb = 0;
            *pa = 0;
            *pc = -1.0f;
        }
        M2C_FIELD(base, void**, 0x344C) = owner;
        M2C_FIELD(base, void**, 0x3450) = M2C_FIELD(owner, void**, 0x873F0);
        {
            u16 j;
            for (j = 0; j < indices->capacity; j++) {
                indices->indices[j] = j;
                indices->reverse[j] = j;
            }
            indices->count = 0;
        }
    }
    M2C_FIELD(base, f32*, 0x3454) = M2C_FIELD(D_0040F4D0, f32*, 0x20) - M2C_FIELD(D_0040F4D0, f32*, 0x1C);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001B6328);
#endif
void func_001BEBA0(BkEffectDamageWindowsPS2* windows, void* effect, void* actor, f32 delay, f32 damage) {
    s16 i;
    f32 now = M2C_FIELD(D_0040F4D0, f32*, 0x20);
    for (i = 0; i < 32; i++) {
        BkEffectDamageWindowPS2* window = windows->records + i;
        if (window->end <= now) {
            window->effect = effect;
            window->actor = actor;
            window->begin = now + delay + M2C_FIELD(actor, f32*, 0x244);
            window->end = window->begin + M2C_FIELD(actor, f32*, 0x248);
            window->damage = damage;
            return;
        }
    }
}
void func_001C1A68(void* out, void* input, void* data) {
    M2C_FIELD(out, void**, 8) = data;
    M2C_FIELD(out, void**, 4) = input;
    M2C_FIELD(out, f32*, 0) = __ee_max_s(__ee_max_s(M2C_FIELD(input, f32*, 0x80), M2C_FIELD(input, f32*, 0x84)),
                                         M2C_FIELD(input, f32*, 0x88));
    M2C_FIELD(out, f32*, 0) = __ee_max_s(M2C_FIELD(out, f32*, 0), M2C_FIELD(input, f32*, 0x8C));
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C1C48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C1CD0);
void func_001C2210(void* object) {
    FloatQuad value;
    value.f.x = 1.0f;
    value.f.y = 1.0f;
    value.f.z = 1.0f;
    value.f.w = ColorZeroPS2();
    M2C_FIELD(object, u8*, 0x10) = 0;
    M2C_FIELD(object, s128*, 0) = value.quad;
}
s32 func_001C2250(void* object) {
    M2C_FIELD(object, s32*, 0x14) = 0;
    M2C_FIELD(object, f32*, 0x18) = 1.0f;
    M2C_FIELD(object, s32*, 0x10) = 0;
    M2C_FIELD(object, s32*, 0x34) = 0;
    M2C_FIELD(object, s32*, 0x38) = 0;
    M2C_FIELD(object, s128*, 0) = D_004164A0;
    M2C_FIELD(object, s32*, 0x1C) = 0;
    M2C_FIELD(object, s32*, 0x20) = 0;
    M2C_FIELD(object, s32*, 0x24) = 0;
    M2C_FIELD(object, s32*, 0x28) = 0;
    M2C_FIELD(object, s32*, 0x2C) = 0;
    M2C_FIELD(object, s32*, 0x30) = 0;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C79D0);
s32 func_001C7D08(u64 frame, u64 scissor, u64 sourceFrame, u64 sourceScissor, u64 flags, s128 color) {
    u64 texture =
        TextureFromFrame(FrameBaseWords(sourceFrame), FrameWidthPixels(sourceFrame), FrameFormat(sourceFrame));
    return func_001C79D0(frame, scissor, texture, ScissorWidth(sourceScissor), ScissorHeight(sourceScissor), flags,
                         color);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C7DB8);
#ifdef NON_MATCHING
extern u64 func_001C7DB8(u64, u64, s32, s32, u64);
// Unmatched: Masked frame-page updates retain different register lifetimes and scheduling.
u64 func_001C8108(u64 sourceFrame, u64 destinationFrame, s32 flags, u32 height, u64 data) {
    u64 result;
    if (height >= 512) {
        u64 first = func_001C7DB8(sourceFrame, destinationFrame, flags, 480, data);
        {
            u32 pageCount = 15 * ((u32)destinationFrame >> 16 & 0x3F);
            u32 sourcePage = ((u32)sourceFrame & 0x1FF) + pageCount;
            u32 destinationPage = ((u32)destinationFrame & 0x1FF) + pageCount;
            sourceFrame = (sourceFrame & ~0x1FFUL) | (u64)sourcePage;
            destinationFrame = (destinationFrame & ~0x1FFUL) | (u64)destinationPage;
            func_001C7DB8(sourceFrame, destinationFrame, flags, height - 480, data);
        }
        result = first;
    } else {
        result = func_001C7DB8(sourceFrame, destinationFrame, flags, height, data);
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C8108);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C81F0);
#ifdef NON_MATCHING
extern u8 D_00440280[];
extern void func_00270FD8(void*);
extern void func_002707D8(void*, void*, f32, s32, s32, s32);
// Unmatched: Global renderer-address lifetime and capacity-test lowering differ.
void func_001C8478(BkResourceCollectionPS2* collection) {
    u8* state = D_00440280;
    s32 slot = M2C_FIELD(state, s32*, 0x2C0);
    if (M2C_FIELD(state, s32*, 0x2DC) - M2C_FIELD(state, s32*, slot * 0x100 + 0xC4) < collection->total ||
        M2C_FIELD(state, s32*, 0x2E8) - M2C_FIELD(state, s32*, slot * 0x100 + 0xC0) < collection->count) {
        func_00270FD8(state);
    }
    {
        s32 i;
        for (i = 0; i < collection->count; i++) { func_002707D8(state, collection->items[i], 0.0f, 1, 0, 1); }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C8478);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001C8560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CAB20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CADD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CB3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CC3A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CCAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CCF48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CD360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CD650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CD8D8);
void func_001CDA28(void* unused, void* record, const u32* tokens) {
    s32 value = M2C_FIELD(record, s32*, 8);
    if (value) M2C_FIELD(record, u32*, 8) = func_00108328(D_0040F4C4, TokenAt(tokens, value - 1));
    value = M2C_FIELD(record, s32*, 4);
    if (value) M2C_FIELD(record, u32*, 4) = func_00108328(D_0040F4C4, TokenAt(tokens, value - 1));
}
void func_001CDAE8(void* unused, void* record, const u32* tokens) {
    s32 value = M2C_FIELD(record, s32*, 8);
    if (value) M2C_FIELD(record, u32*, 8) = func_00108328(D_0040F4C4, TokenAt(tokens, value - 1));
    value = M2C_FIELD(record, s32*, 4);
    if (value) M2C_FIELD(record, u32*, 4) = func_00108328(D_0040F4C4, TokenAt(tokens, value - 1));
    value = M2C_FIELD(record, s32*, 0xC);
    if (value) M2C_FIELD(record, u32*, 0xC) = func_00108328(D_0040F4C4, TokenAt(tokens, value - 1));
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CDB98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CDD98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CE1B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CE3B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CE780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CE9E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CEB50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CEDA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CEF38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF1D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF6C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CF8C0);
void func_001CFA58(MaterialBinding* material) {
    if (!material->binding) {
        func_0026A6F0(material->resource);
    } else {
        TextureBinding* binding = material->binding;
        u64 offset = (u32)(0x8000 - binding->x * 8) | ((u64)(u32)(0x8000 - binding->y * 8) << 32);
        func_0026A460(binding->field8, binding->field10, offset, binding->field18, material->resource, 0);
    }
}
void func_001CFB00(void* object) {
    func_001C2210(object);
    M2C_FIELD(object, u8*, 0x20) = 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CFB50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001CFE50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001DD7B8);
void func_001DD7C0(void* state, s32 flag) {
    s32 i = 0;
    for (; i < M2C_FIELD(state, s32*, 0x58); i++) { func_001D9EC8(M2C_FIELD(state, void**, 0x30 + i * 8), flag); }
}
void func_001E45A8(void* state) {
    u32 i;
    u8* flag = (u8*)state + 0x14;
    for (i = 0; i < 2; i++) {
        OwnerRow* row = (OwnerRow*)(flag - 12);
        row->resource = func_001E69E8(M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 4));
        ((OwnerRow*)(flag - 12))->field4 = 0;
        ((OwnerRow*)(flag - 12))->field8 = 0;
        ((OwnerRow*)(flag - 12))->flag = 0;
        flag += sizeof(OwnerRow);
    }
    {
        void* owner = M2C_FIELD(M2C_FIELD(D_0040F510, void**, 0xCBD8), void**, 4);
        M2C_FIELD(state, s32*, 0) = 1;
        M2C_FIELD(state, void**, 0x3C) = owner;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001E8B60);
#ifdef NON_MATCHING
// Unmatched: resource-loop setup scheduling and a few register choices differ.
// Accessed sound-manager layout; original classes and unused array extents are UNVERIFIED.
typedef struct SoundResourceManagerView {
    s8 counts[3];
    u8 pad3;
    void* primary[16];
    void* single44[1];
    void* secondary[8];
    void* fixed68[4];
    void* single78[2];
    void* tertiary[50];
    void* pair148[2];
    void* fixed150[4];
    void* fixed160[4];
    void* components[17];
    s32 state;
} SoundResourceManagerView;

extern s32 func_001E5940(void*);
extern s32 func_001ED6B0(void*);
extern s32 func_001D8AD0(void*);
extern void func_002818D0(void*, void*);
extern void* D_0040F510;
extern s32 func_001EF710(void*);
extern s32 func_001EED58(void*);
extern s32 func_001EA898(s32);
extern s32 func_001E79F0(void*);
extern s32 func_001EBC88(void*);
extern void func_00281908(void*, void*);
extern s32 func_001DBDB8(void*);
extern s32 func_001E3BB0(void*);
extern s32 func_001E2B48(void*);
extern s32 func_001E0480(void*);
extern s32 func_001D6CB8(void*);
extern s32 func_001EA4F0(s32);
extern s32 func_001E8248(void*);

s32 func_001E9250(SoundResourceManagerView* self) {
    void** cursor;
    s32 index;
    switch (self->state) {
        case 0:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 17:
        case 18: self->state = 23;
        case 23:
            if (!func_001E5940(self->components[0])) return 0;
            self->state = 19;
        case 19:
            if (!func_001ED6B0(self->components[10])) return 0;
            self->state = 20;
        case 20:
            if (!func_001D8AD0(self->components[14])) return 0;
            cursor = self->pair148;
            index = 1;
            do {
                --index;
                func_002818D0((u8*)D_0040F510 + 0xB308, *cursor);
                *cursor = 0;
                ++cursor;
            } while (index >= 0);
            self->state = 21;
        case 21:
            if (!func_001EF710(self->components[12])) return 0;
            self->state = 22;
        case 22:
            if (!func_001EED58(self->components[11])) return 0;
            index = 0;
            if (self->counts[2] > 0) {
                cursor = self->tertiary;
                do {
                    void* resource = *cursor;
                    if (resource) {
                        func_002818D0((u8*)D_0040F510 + 0xB308, resource);
                        *cursor = 0;
                    }
                    ++cursor;
                    ++index;
                } while (index < self->counts[2]);
            }
            self->state = 24;
        case 24:
            if (!func_001EA898((s32)self->components[9])) return 0;
            self->state = 25;
        case 25:
            if (!func_001E79F0(self->components[5])) return 0;
            self->state = 26;
        case 26:
            if (!func_001EBC88(self->components[8])) return 0;
            cursor = self->single78;
            index = 0;
            do {
                void* resource = *cursor;
                if (resource) {
                    func_002818D0((u8*)D_0040F510 + 0xB308, resource);
                    *cursor = 0;
                }
                ++cursor;
                --index;
            } while (index >= 0);
            cursor = self->fixed150;
            index = 3;
            do {
                void* resource = *cursor;
                if (resource) {
                    func_00281908((u8*)D_0040F510 + 0xB308, resource);
                    *cursor = 0;
                }
                ++cursor;
                --index;
            } while (index >= 0);
            self->state = 27;
        case 27:
            if (!func_001DBDB8(self->components[7])) return 0;
            cursor = self->fixed68;
            index = 3;
            do {
                void* resource = *cursor;
                if (resource) {
                    func_002818D0((u8*)D_0040F510 + 0xB308, resource);
                    *cursor = 0;
                }
                ++cursor;
                --index;
            } while (index >= 0);
            self->state = 28;
        case 28:
            if (!func_001E3BB0(self->components[6])) return 0;
            index = 0;
            if (self->counts[1] > 0) {
                cursor = self->secondary;
                do {
                    void* resource = *cursor;
                    if (resource) {
                        func_002818D0((u8*)D_0040F510 + 0xB308, resource);
                        *cursor = 0;
                    }
                    ++cursor;
                    ++index;
                } while (index < self->counts[1]);
            }
            self->state = 29;
        case 29:
            if (!func_001E2B48(self->components[4])) return 0;
            index = 0;
            if (self->counts[0] > 0) {
                cursor = self->primary;
                do {
                    void* resource = *cursor;
                    if (resource) {
                        func_002818D0((u8*)D_0040F510 + 0xB308, resource);
                        *cursor = 0;
                    }
                    ++cursor;
                    ++index;
                } while (index < self->counts[0]);
            }
            self->state = 30;
        case 30:
            if (!func_001E0480(self->components[3])) return 0;
            self->state = 31;
        case 31:
            if (!func_001D6CB8(self->components[2])) return 0;
            cursor = self->single44;
            index = 0;
            do {
                void* resource = *cursor;
                if (resource) {
                    func_002818D0((u8*)D_0040F510 + 0xB308, resource);
                    *cursor = 0;
                }
                ++cursor;
                --index;
            } while (index >= 0);
            cursor = self->fixed160;
            index = 3;
            do {
                void* resource = *cursor;
                if (resource) {
                    func_00281908((u8*)D_0040F510 + 0xB308, resource);
                    *cursor = 0;
                }
                ++cursor;
                --index;
            } while (index >= 0);
            self->state = 32;
        case 32:
            if (!func_001EA4F0((s32)self->components[1])) return 0;
            self->state = 33;
        case 33:
            if (!func_001E8248(self)) return 0;
            self->state = 34;
        case 34: return 1;
        case 35:
        default: return 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001E9250);
#endif
#ifdef NON_MATCHING
extern s32 func_001EF710(void*);
extern void func_002818D0(void*, void*);
// Unmatched: Global sound-state address setup is scheduled after the loop iterators.
s32 func_001E9C68(void* state) {
    s32 status = M2C_FIELD(state, s32*, 0x1B4);
    switch (status) {
        case 3: M2C_FIELD(state, s32*, 0x1B4) = 4;
        case 4: {
            s32 i;
            void** entry;
            if (!func_001EF710(M2C_FIELD(state, void**, 0x1A0))) return 0;
            entry = (void**)((u8*)state + 0x80);
            for (i = 27; i >= 0; i--) {
                if (*entry) {
                    func_002818D0((u8*)D_0040F510 + 0xB308, *entry);
                    *entry = 0;
                }
                entry++;
            }
            M2C_FIELD(state, s32*, 0x1B4) = 5;
            break;
        }
        case 5: break;
        default: break;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001E9C68);
#endif
void func_001ED2C8(void* state, u64 value, s32 data) {
    M2C_FIELD(state, s32*, 0x14) = 1;
    M2C_FIELD(state, u64*, 0) = value;
    M2C_FIELD(state, s32*, 8) = data;
    M2C_FIELD(state, s32*, 0x1C)++;
}
f32 func_001ED2E8(void* unused, s32 kind) {
    switch (kind) {
        case 3: return D_003BD9DC;
        case 4: return D_003BD9E0;
        case 5: return D_003BD9E4;
        case 6: return D_003BD9F0;
        case 7: return D_003BD9E8;
        case 8: return D_003BD9EC;
        case 9: return D_003BD9F4;
        case 10: return D_003BD9F8;
        case 11: return D_003BD9FC;
        case 12: return D_003BDA00;
        case 13: return D_003BDA04;
        default: return 0.0f;
    }
}
void func_001ED3E0(TrackedPool* pool, u128 context, void* parameters, f32 elapsed) {
    s32 i;
    for (i = 0; i < pool->pool.count; i++) {
        if ((u8)EntryActive(pool->pool.entries[i].remaining) && pool->pairs[i].kind && pool->pairs[i].kind == 1) {
            pool->pool.entries[i].value = M2C_FIELD(pool->pairs[i].object, u128*, 0xA0);
        }
    }
    func_002822C8(&pool->pool, context, parameters, elapsed);
}
void func_001ED4A0(Recovered_TimedValuePool* pool, u128 value, f32 duration, s32 kind, void* object) {
    s32 index = TimedValuePool_Add(pool, value, duration);
    TrackedPool* tracked = (TrackedPool*)pool;
    tracked->pairs[index].kind = kind;
    tracked->pairs[index].object = object;
}
void func_001ED4F0(TrackedPool* pool) {
    s32 i;
    for (i = 0; i < pool->pool.count; i++) {
        if ((u8)EntryActive(pool->pool.entries[i].remaining) == 1 && pool->pairs[i].kind == 1) {
            EntryAt(&pool->pool, i)->remaining = -1.0f;
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED578);
void func_001ED648(void* state) {
    void* active = M2C_FIELD(state, void**, 0x10);
    if (active) {
        void* table = M2C_FIELD(active, void**, 0x50);
        ((void (*)(void*))M2C_FIELD(table, void**, 0x1C))((s8*)active + M2C_FIELD(table, s16*, 0x18));
        {
            s32* current = M2C_FIELD(state, s32**, 0x10);
            if (current[0] == 0 && current[6] != 0) { func_001ED718(state, 0, 1); }
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78_1ae050", func_001ED830);
