#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "ps2/vu0_math.h"

/* Partial views. Original type and field names are UNVERIFIED. */
typedef struct SlotEntry {
    void* owner;
    u32 priority;
} SlotEntry;
typedef struct SlotList {
    SlotEntry* entries;
    void* context;
    void* compound;
    s16 capacity;
    s16 count;
} SlotList;

typedef char SlotEntrySize[sizeof(SlotEntry) == 8 ? 1 : -1];
typedef char SlotListCountOffset[(u32) & ((SlotList*)0)->count == 0xE ? 1 : -1];

/* Partial native physics views; original names and unaccessed fields are UNVERIFIED. */
typedef struct SolverView {
    u8 unknown0[0x370];
    BkVuVector unknown370;
    float scale;
    float inverseScale;
} SolverView;
typedef struct BodyView {
    u8 unknown0[0x20];
    BkVuVector linearStep;
    BkVuVector angularStep;
    u8 unknown40[0xC];
    SolverView* solver;
    u8 unknown50[0x3C];
    s32 state;
    BkVuVector unknown90;
    BkVuVector unknownA0;
} BodyView;

typedef struct ChildView {
    u8 unknown0[0x54];
    void* definition;
    BodyView* body;
    u8 unknown5C[0x14];
} ChildView;
typedef struct CompoundView {
    u8 unknown0[8];
    u32 count;
    ChildView* children;
} CompoundView;
typedef struct OwnerView {
    BkVuVector unknown0, normal, unknown20;
    s32 owner;
    CompoundView* compound;
    float time;
    u8 unknown3C[4];
    u16 flags;
    u8 unknown42[0xE];
} OwnerView;
typedef struct ResourcePoolView {
    s32 scene;
    u8 unknown4[0x4C];
    OwnerView slots[110];
    u8 occupied[110];
    u8 unknown231E[2];
    OwnerView temporary[20];
    u8 temporaryOccupied[20];
} ResourcePoolView;
typedef struct PoolView {
    u8 unknown0[0xC];
    CompoundView* compound;
} PoolView;

/* Same native float-to-VU transport used by BkEffectScalePS2. */
static inline BkVuVector ScaleXYZ(BkVuVector value, float scale) {
    BkVuVector scalar;
    __asm__("qmtc2.ni bitsv, scalarv" : "=j scalarv"(scalar) : "r bitsv"(scale));
    return BkVuScaleXYZ(value, scalar);
}

/* Replace XYZ while preserving the destination's native fourth lane. */
static inline BkVuVector AssignXYZ(BkVuVector old, BkVuVector value) {
    __asm__("vmove.xyz targetv, valuev" : "+j targetv"(old) : "j valuev"(value));
    return old;
}

extern void func_0032B700(CompoundView*);

typedef char SolverScaleOffset[(u32) & ((SolverView*)0)->scale == 0x380 ? 1 : -1];
typedef char BodyStepOffset[(u32) & ((BodyView*)0)->linearStep == 0x20 ? 1 : -1];
typedef char BodySolverOffset[(u32) & ((BodyView*)0)->solver == 0x4C ? 1 : -1];
typedef char BodyStateOffset[(u32) & ((BodyView*)0)->state == 0x8C ? 1 : -1];
typedef char ChildStride[sizeof(ChildView) == 0x70 ? 1 : -1];

typedef char BodyStride[sizeof(BodyView) == 0xB0 ? 1 : -1];

extern void func_0032CB58(s32, s32, u32);
static inline u8* Occupancy(void* self) { return (u8*)self + 0x22B0; }
static inline s32* CompoundArray(s32* self) { return (s32*)((u8*)self + 8); }
static inline u32 BodyCount(OwnerView* self) { return self->compound->count; }
static inline BkVuVector ZeroXYZ(BkVuVector old) {
    __asm__("vsub.xyz targetv, vf0, vf0" : "+j targetv"(old));
    return old;
}

typedef char ResourceSlotSize[sizeof(OwnerView) == 0x50 ? 1 : -1];
typedef char ResourceFlagsOffset[(u32) & ((ResourcePoolView*)0)->occupied == 0x22B0 ? 1 : -1];
typedef char TemporarySlotsOffset[(u32) & ((ResourcePoolView*)0)->temporary == 0x2320 ? 1 : -1];
typedef char TemporaryFlagsOffset[(u32) & ((ResourcePoolView*)0)->temporaryOccupied == 0x2960 ? 1 : -1];

extern void* func_0025C758(ResourcePoolView*);
extern void func_0025CEF8(OwnerView*, void*);
extern void func_0025C870(void*, s32);
extern void func_00388190(void*);
extern s32 func_00152690(s32);
extern void func_0025DB20(OwnerView*);
extern s32* D_0040F4CC;

static inline ChildView* ChildByOffset(ChildView* base, s32 offset) { return (ChildView*)((u8*)base + offset); }
static inline s32 CompoundCount(PoolView* self) { return self->compound->count; }
static inline BodyView* CompoundBody(PoolView* self, s32 index) {
    return ChildByOffset(self->compound->children, index * sizeof(ChildView))->body;
}
static inline float VectorY(BkVuVector value) {
    union {
        BkVuVector vector;
        float lane[4];
    } view;
    view.vector = value;
    return view.lane[1];
}

extern void func_0025DAC0(void*);
extern s32 func_00260C70(void*, s32);
extern void func_001A5B10(s32, s32);
extern void func_00263558(SlotList*, s16);
extern s32 func_00263360(void*, s32);

extern void func_002611C8(void);
#ifdef NON_MATCHING
extern void func_0032B798(CompoundView*);
extern s32 func_002632B8(SlotList*, s32);
extern s32 func_002633D0(void*);
extern void func_00387FC0(OwnerView*);
extern void func_001529D0(s32);
extern void func_0012C650(void*, OwnerView*, BkVuVector);
static inline BkVuVector MakeXYZ(float x, float y, float z) {
    float components[4] __attribute__((aligned(16)));
    components[0] = x;
    components[1] = y;
    components[2] = z;
    return *(BkVuVector*)components;
}
static inline u8 SupportedType(s32 type) {
    u8 supported = 0;
    if (type == 3 || type == 4 || type == 7) supported = 1;
    return supported;
}
#endif
static inline void* PhysicsSettings(void* game) { return (u8*)game + 0x20120; }
extern void* D_0040F0E0;

extern void func_0014C380(s32);

extern void func_0025C4C8(s32*, void*);
extern s32 func_00136F10();
extern s32 func_0025C798();
extern s32 func_0025CA10();
extern void func_0025DA20(OwnerView*);
extern s32 func_0025C910();
extern s32 func_0032E1B0(s32, void *);
extern s32 func_00100290(s32, s32, M2C_UNK);
extern s32 func_00107B78();
extern M2C_UNK D_0040F0F0;
extern s32 func_00107D20();
extern s32 func_0014C330(s32);
extern s32 func_0025DD38();
extern s32 func_00135570();
extern void * D_0040F4D0;
extern s32 func_0025E2D0();
extern s32 func_0032B6E0();
extern s32 func_002611D0();
extern s32 func_0032CDE0(s32, s32);
extern s32 func_00264130(M2C_UNK, M2C_UNK);
extern s32 * func_0032E320();
extern M2C_UNK D_0043F3F0;

s32 func_0025B5D0(ResourcePoolView* self) {
    SolverView* solver = (SolverView*)func_0032E320(self->scene);
    float scale = M2C_FIELD(PhysicsSettings(D_0040F0E0), float*, 0x1C);
    float inverse = 1.0f / scale;
    s32 i;
    u8* flag;
    solver->scale = scale;
    solver->unknown370 = ScaleXYZ(ScaleXYZ(M2C_FIELD(solver, BkVuVector*, 0x360), scale), scale);
    solver->inverseScale = inverse;
    for (i = 109, flag = self->occupied + 109; i >= 0; i--, flag--) *flag = 0;
    for (i = 165; i >= 0; i--) (&D_0043F3F0)[i] = 0;
    for (i = 1; i >= 0; i--) M2C_FIELD((u8*)self + i, u8*, 0x8B40) = 0;
    M2C_FIELD(self, s32*, 0x8B04) = -1;
    M2C_FIELD(self, s32*, 0x8B44) = 28;
    M2C_FIELD(self, s32*, 0x8B00) = 0;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025B6D0);

void func_0025C020(void) {

}

s32 func_0025C028(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8B44) = 0x37;
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: Index temporaries and setup/epilogue scheduling differ (16 instructions).
void func_0025C040(ResourcePoolView* self, void* owner) {
    s32* compounds = CompoundArray((s32*)self);
    u8* definition = (u8*)owner + 0x700;
    s32 left = 3;
    s8 group = M2C_FIELD(owner, s8*, 0x39);
    s32* compound = (s32*)(group * 4 + (u32)compounds);
    do {
        M2C_FIELD(M2C_FIELD(*compound, void**, 0xC), void**, 0) = definition;
        if (M2C_FIELD(definition, s32*, 0x40)) {
            BodyView* body;
            s32 index;
            func_0032CB58(self->scene, *compound, 1);
            body = M2C_FIELD(M2C_FIELD(*compound, void**, 0xC), BodyView**, 0x58);
            index = body - *(BodyView**)func_0032E320(self->scene);
            ((OwnerView**)&D_0043F3F0)[index] = 0;
        }
        definition += 0x60;
        left--;
        compound += 2;
    } while (left >= 0);
    {
        void* motion = (u8*)self + (group * 0x10 + 0x28);
        BodyView* body;
        s32 index;
        func_002632B8(motion, self->scene);
        body = (BodyView*)func_002633D0(motion);
        index = body - *(BodyView**)func_0032E320(self->scene);
        ((OwnerView**)&D_0043F3F0)[index] = 0;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025C040);
#endif
s32 func_0025C180(s32* self, void* owner) {
    s32* compounds = CompoundArray(self);
    s32 left = 3;
    s8 group = M2C_FIELD(owner, s8*, 0x39);
    s32* compound = (s32*)(group * 4 + (u32)compounds);
    do {
        if (func_0032E1B0(*self, (void*)*compound)) func_0032CDE0(*self, *compound);
        left--;
        compound += 2;
    } while (left >= 0);
    return func_00263360((u8*)self + (group * 0x10 + 0x28), *self);
}
s32 func_0025C210(ResourcePoolView* self, void* owner) {
    OwnerView* slot = func_0025C758(self);
    func_0025CEF8(slot, owner);
    slot->unknown3C[0] = 0;
    func_0032CB58(self->scene, (s32)slot->compound, 4);
    {
        BodyView* body = slot->compound->children->body;
        body->state |= 8;
    }
    {
        BodyView* body = slot->compound->children->body;
        s32 index = body - *(BodyView**)func_0032E320(self->scene);
        ((OwnerView**)&D_0043F3F0)[index] = slot;
    }
    return 1;
}

s32 func_0025C2C8(s32 arg0, s32 arg1) {
    s32 temp_5;
    s32 temp_v0;

    temp_5 = M2C_FIELD(arg1, s32 *, 0x350);
    if (temp_5 != 0) { func_0025C4C8((s32*)arg0, (void*)temp_5); }
    func_00136F10(arg1, 1);
    temp_v0 = func_0025C798(arg0, M2C_FIELD(arg1, s32 *, 0xB4));
    M2C_FIELD(arg1, s32 *, 0xB4) = 0;
    return temp_v0;
}

#ifdef NON_MATCHING
// Unmatched: Pointer allocation and the selected-slot join differ (19 instructions).
void* func_0025C320(void* self) {
    float best = -1.0f;
    u8* slot = (u8*)self + 0x8B08;
    u8* occupied = (u8*)self + 0x8B40;
    void* result = 0;
    s32 index = -1;
    s32 i;
    for (i = 0; i < 2; i++, slot += 0x1C) {
        float time = M2C_FIELD(slot, float*, 0x14);
        if (!occupied[i] && best < time) {
            best = time;
            index = i;
        }
    }
    if (index >= 0) {
        result = (u8*)self + (index * 0x1C + 0x8B08);
        occupied[index] = 1;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025C320);
#endif
void func_0025C3B8(ResourcePoolView* self, void* motion, void* actor) {
    CompoundView* compound;
    s32 i;
    if (func_0032E1B0(self->scene, M2C_FIELD(motion, void**, 0xC)))
        func_0032CDE0(self->scene, M2C_FIELD(motion, s32*, 0xC));
    func_00260C70(motion, M2C_FIELD(actor, s32*, 0x30));
    compound = M2C_FIELD(motion, CompoundView**, 0xC);
    func_0032CB58(self->scene, (s32)compound, 4);
    for (i = 0; i < (s32)compound->count; i++)
        ChildByOffset(compound->children, i * sizeof(ChildView))->body->state |= 8;
    M2C_FIELD(M2C_FIELD(actor, void**, 0x34), s32*, 0x18) = 12;
    func_0032B700(M2C_FIELD(motion, CompoundView**, 0xC));
    func_001A5B10(M2C_FIELD(M2C_FIELD(motion, void**, 0), s32*, 0x330), 0);
    {
        u8* owner = M2C_FIELD(motion, u8**, 0);
        BkVuVector* frame = (BkVuVector*)(owner + 0x70);
        M2C_FIELD(owner, BkVuVector*, 0x150) = frame[0];
        M2C_FIELD(owner, BkVuVector*, 0x160) = frame[1];
        M2C_FIELD(owner, BkVuVector*, 0x170) = frame[2];
        M2C_FIELD(owner, BkVuVector*, 0x180) = frame[3];
    }
}
void func_0025C4C8(s32* self, void* target) {
    u8* occupied = (u8*)self + 0x8B40;
    u8* slot = (u8*)self + 0x8B08;
    s32 i;
    i = 0;
    do {
        if (slot == target) {
            func_0032CDE0(*self, M2C_FIELD(slot, s32*, 0xC));
            func_0032CB58(*self, M2C_FIELD(slot, s32*, 0xC), 1);
            func_00260FA0(slot);
            occupied[i] = 0;
            break;
        }
        i++;
        slot += 0x1C;
    } while (i < 2);
}
#ifdef NON_MATCHING
// Unmatched: Four register operands differ around the mode-byte store and override load.
s32 func_0025C558(ResourcePoolView* self, void* owner, s32 active, s32 priority, s32 requested) {
    OwnerView* slot = func_0025C6B8(self, priority, requested);
    if (!slot) return 0;
    func_0025CEF8(slot, owner);
    slot->unknown3C[0] = 1;
    if (M2C_FIELD(owner, u8*, 0x13B) || !(M2C_FIELD(M2C_FIELD(owner, void**, 0xB4), u16*, 0x40) & 4)) {
        func_0032CB58(self->scene, (s32)slot->compound, 1);
    } else if (active) {
        func_0032CB58(self->scene, (s32)slot->compound, 4);
    } else {
        func_0032CB58(self->scene, (s32)slot->compound, 4);
        func_0032B798(slot->compound);
    }
    {
        BodyView* body = slot->compound->children->body;
        body->state |= 8;
    }
    {
        BodyView* body = slot->compound->children->body;
        s32 index = body - *(BodyView**)func_0032E320(self->scene);
        ((OwnerView**)&D_0043F3F0)[index] = slot;
    }
    M2C_FIELD(self, s32*, 0x8B04) = -1;
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025C558);
#endif

void func_0025C690(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg1, s32 *, 0xB4);
    if (temp_5 != 0) {
        func_0025CA10(arg0, temp_5);
    }
}

void* func_0025C6B8(void* self, s32 priority, s32 requested) {
    s32 slot;
    u8* occupied;
    if (requested != -1)
        slot = requested;
    else
        slot = func_0025C910(self, priority);
    if (slot == -1) return 0;
    occupied = Occupancy(self) + slot;
    if (*occupied) func_0025C870(self, slot);
    *occupied = 1;
    return (u8*)self + (slot * 0x50 + 0x50);
}
void* func_0025C758(ResourcePoolView* self) {
    s32 i;
    for (i = 0; i < 20; i++) {
        if (self->temporaryOccupied[i] == 0) {
            self->temporaryOccupied[i] = 1;
            return &self->temporary[i];
        }
    }
    return 0;
}

#ifdef NON_MATCHING
// Unmatched: The slot-address setup and loop-invariant multiply constant are scheduled differently.
s32 func_0025C798(ResourcePoolView* self, OwnerView* target) {
    s32 more;
    s32 i = 0;
    u8* occupied = self->temporaryOccupied;
    OwnerView* slot = self->temporary;
    do {
        i++;
        if (slot == target && *occupied) {
            void* owner;
            BodyView* body = slot->compound->children->body;
            s32 index = body - *(BodyView**)func_0032E320(self->scene);
            ((OwnerView**)&D_0043F3F0)[index] = 0;
            func_0032CDE0(self->scene, (s32)slot->compound);
            owner = (void*)slot->owner;
            M2C_FIELD(owner, s32*, 0xB4) = 0;
            slot->owner = 0;
            *occupied = 0;
            return (s32)owner;
        }
        occupied++;
        slot++;
        more = i < 20;
    } while (more);
    return more;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025C798);
#endif
void func_0025C870(void* manager, s32 index) {
    OwnerView* slot = (OwnerView*)((u8*)manager + (index * 0x50 + 0x50));
    void* owner = (void*)slot->owner;
    void* vtable = M2C_FIELD(owner, void**, 0x10);
    s32 enabled = ((slot->compound->children->body->state >> 2) & 1) ^ 1;
    M2C_FIELD(vtable, void (**)(void*, s32), 0x74)((u8*)owner + M2C_FIELD(vtable, s16*, 0x70), enabled);
    if ((slot->compound->children->body->state >> 2) & 1) func_0025DAC0(slot);
    func_0025CA10(manager, slot);
}
s32 func_0025C910(ResourcePoolView* self, s32 priority) {
    float bestTime = -1.0f;
    s32 chosen = -1;
    s32 i;
    OwnerView* slot;
    float* time;
    for (i = 0; i < 110; i++) {
        if (!self->occupied[i]) return i;
    }
    for (i = 0, time = (float*)((u8*)self + 0x88), slot = self->slots; i < 110;
         i++, time = (float*)((u8*)time + 0x50), slot++) {
        s32 value = func_0025CCE8(self, slot);
        if (value == priority && bestTime < *time) {
            bestTime = *time;
            chosen = i;
        }
        if (value < priority) {
            bestTime = *time;
            priority = value;
            chosen = i;
        }
    }
    return chosen;
}
#ifdef NON_MATCHING
// Unmatched: The slot-address setup and loop-invariant multiply constant are scheduled differently.
s32 func_0025CA10(ResourcePoolView* self, OwnerView* target) {
    s32 more;
    s32 i = 0;
    u8* occupied = self->occupied;
    OwnerView* slot = self->slots;
    do {
        i++;
        if (slot == target && *occupied) {
            void* owner;
            BodyView* body = slot->compound->children->body;
            s32 index = body - *(BodyView**)func_0032E320(self->scene);
            ((OwnerView**)&D_0043F3F0)[index] = 0;
            func_0032CDE0(self->scene, (s32)slot->compound);
            owner = (void*)slot->owner;
            M2C_FIELD(owner, s32*, 0xB4) = 0;
            slot->owner = 0;
            *occupied = 0;
            return (s32)owner;
        }
        occupied++;
        slot++;
        more = i < 110;
    } while (more);
    return more;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025CA10);
#endif

void func_0025CAE8(s32 arg0, s32 arg1) { func_0025DA20((OwnerView*)arg1); }

void func_0025CB08(s32* self, OwnerView* owner) {
    func_0032CDE0(*self, (s32)owner->compound);
    func_0032CB58(*self, (s32)owner->compound, 1);
    {
        BodyView* body = owner->compound->children->body;
        body->state |= 8;
    }
    {
        BodyView* body = owner->compound->children->body;
        s32 index = body - *(BodyView**)func_0032E320(*self);
        ((OwnerView**)&D_0043F3F0)[index] = owner;
    }
}
void func_0025CBA8(s32* self, OwnerView* owner) {
    func_0032CDE0(*self, (s32)owner->compound);
    func_0032CB58(*self, (s32)owner->compound, 4);
    {
        BodyView* body = owner->compound->children->body;
        body->state |= 8;
    }
    {
        BodyView* body = owner->compound->children->body;
        s32 index = body - *(BodyView**)func_0032E320(*self);
        ((OwnerView**)&D_0043F3F0)[index] = owner;
    }
}

s32 func_0025CC48(s32 *arg0, s32 arg1) {
    return M2C_FIELD(((((s32) ((arg1 - *func_0032E320(*arg0)) * 0xBA2E8BA3) >> 4) * 4) + ((s32) &D_0043F3F0)), s32 *, 0);
}

s32 func_0025CCA0(void* self, void* body) {
    void** items = (void**)((u8*)self + 0x20);
    s32 i;
    for (i = 0; i < 2; i++, items++) {
        if (M2C_FIELD(M2C_FIELD(*items, void**, 0xC), void**, 0x58) == body) return 1;
    }
    return 0;
}

void * func_0025CCD8(void *arg0, void *arg1) {
    return arg0 + (((s32) arg1 * 0x10) + 0x28);
}

s32 func_0025CCE8(void* self, void* slot) {
    void* owner = M2C_FIELD(slot, void**, 0x30);
    s32 type = M2C_FIELD(owner, s32*, 0xC4);
    void* compound;
    void* body;
    s32 flags;
    if (type == 1 || type == 2) return 9;
    if (M2C_FIELD(owner, u8*, 0x13B)) return 8;
    compound = M2C_FIELD(slot, void**, 0x34);
    body = M2C_FIELD(M2C_FIELD(compound, void**, 0xC), void**, 0x58);
    flags = M2C_FIELD(body, s32*, 0x8C);
    if (flags & 1) return 6;
    if (M2C_FIELD(slot, u16*, 0x40) & 0x40) return 7;
    if ((flags >> 2) & 1) return M2C_FIELD(owner, u8*, 0x13A) ? 3 : 5;
    if (type == 7) return 2;
    if ((flags >> 1) & 1) return M2C_FIELD(owner, u8*, 0x13A) ? 1 : 4;
    return 8;
}

s32 func_0025CDA0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;

    temp_2 = func_0025C910((ResourcePoolView*)arg0, arg2);
    M2C_FIELD(arg0, s32 *, 0x8B04) = temp_2;
    M2C_FIELD(arg1, s32 *, 0) = temp_2;
    return ~M2C_FIELD(arg0, s32 *, 0x8B04) != 0;
}

s32 func_0025CDF0(void* self) {
    u8* occupied = (u8*)self + 0x2960;
    s32 i;
    for (i = 0; i < 20; i++) {
        if (occupied[i] == 0) return 1;
    }
    return 0;
}

void func_0025CE28(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8B04) = -1;
}

void func_0025CE40(s32 *arg0, void *arg1) {
    if (func_0032E1B0(*arg0, M2C_FIELD(arg1, void **, 0x34)) != 0) {
        func_00100290(*arg0, M2C_FIELD(M2C_FIELD(arg1, void **, 0x34), s32 *, 0xC), 1);
    }
}

void func_0025CE90(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s8 *, 0x3D) = 0;
    M2C_FIELD(arg0, s8 *, 0x3E) = 0;
    M2C_FIELD(arg0, s8 *, 0x3F) = 0;
    M2C_FIELD(arg0, s16 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s8 *, 0x3C) = 1;
    func_00107B78(&D_0040F0F0, 0xB, 0x10, 0);
    M2C_FIELD(arg0, s32 *, 0x34) = func_00107D20(0x90);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025CEF8);
void func_0025D098(void* self) {
    func_00388190(self);
    if (!M2C_FIELD(self, u8*, 0x3C)) {
        M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(self, void**, 0x34), void**, 0xC), void**, 0x58), s32*, 0xAC) = 0;
    }
    if (M2C_FIELD(M2C_FIELD(self, void**, 0x30), s32*, 0xC4) == 3) {
        if (func_00152690(M2C_FIELD(self, s32*, 0x30))) func_0025DB20(self);
    }
    M2C_FIELD(self, u8*, 0x3E) = 0;
    M2C_FIELD(self, u8*, 0x3D) = 0;
}
#ifdef NON_MATCHING
// Unmatched: Zero-vector scalar transport, byte predicate lowering and register allocation differ.
void func_0025D110(OwnerView* self) {
    func_00387FC0(self);
    if (!self->unknown3C[0]) {
        BkVuVector zero = MakeXYZ(0.0f, 0.0f, 0.0f);
        BodyView* body;
        body = self->compound->children->body;
        body->linearStep = AssignXYZ(body->linearStep, ScaleXYZ(zero, body->solver->scale));
        body = self->compound->children->body;
        body->angularStep = AssignXYZ(body->angularStep, ScaleXYZ(zero, body->solver->scale));
    }
    {
        u8 state = self->unknown3C[3];
        if (state != ((self->compound->children->body->state >> 2) & 1)) {
            s32 type = M2C_FIELD(self->owner, s32*, 0xC4);
            u8 supported = SupportedType(type);
            if (supported) {
                if (state) {
                    func_0025DAC0(self);
                    if (M2C_FIELD(self->owner, s32*, 0xC4) == 3) func_001529D0(self->owner);
                } else
                    func_0025DAF0(self);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025D110);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025D240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025D510);
void func_0025D840(OwnerView* self, BkVuVector value) {
    BodyView* body = self->compound->children->body;
    body->linearStep = AssignXYZ(body->linearStep, value);
}
void func_0025D860(OwnerView* self, BkVuVector value) {
    CompoundView* compound = self->compound;
    if ((compound->children->body->state >> 1) & 1) func_0032B700(compound);
    {
        BodyView* body = self->compound->children->body;
        body->linearStep = AssignXYZ(body->linearStep, ScaleXYZ(value, body->solver->scale));
    }
}
BkVuVector func_0025D8E0(OwnerView* self) {
    BodyView* body = self->compound->children->body;
    return ScaleXYZ(body->linearStep, body->solver->inverseScale);
}
void func_0025D910(OwnerView* self, BkVuVector value) {
    CompoundView* compound = self->compound;
    if ((compound->children->body->state >> 1) & 1) func_0032B700(compound);
    {
        BodyView* body = self->compound->children->body;
        body->angularStep = AssignXYZ(body->angularStep, ScaleXYZ(value, body->solver->scale));
    }
}
BkVuVector func_0025D990(OwnerView* self) {
    BodyView* body = self->compound->children->body;
    return ScaleXYZ(body->angularStep, body->solver->inverseScale);
}
float func_0025D9C0(OwnerView* self) {
    float total = 0.0f;
    u32 i;
    for (i = 0; i < BodyCount(self); i++) {
        total += 1.0f / M2C_FIELD(self->compound->children[i].definition, float*, 0x10);
    }
    return total;
}

s32 func_0025DA10(void *arg0) {
    return ((u16) M2C_FIELD(arg0, u16 *, 0x40) >> 9) & 1;
}

void func_0025DA20(OwnerView* self) {
    if (self->compound->children->body->state & 1) func_0025CBA8(D_0040F4CC, self);
    {
        CompoundView* compound = self->compound;
        if ((compound->children->body->state >> 1) & 1) func_0032B700(compound);
    }
    {
        BodyView* body = self->compound->children->body;
        body->unknown90 = AssignXYZ(body->unknown90, body->solver->unknown370);
        body->unknownA0 = ZeroXYZ(body->unknownA0);
    }
}

void func_0025DAC0(void *arg0) {
    func_0014C330(M2C_FIELD(arg0, s32 *, 0x30));
    M2C_FIELD(arg0, s8 *, 0x3F) = 0;
}

void func_0025DAF0(void* self) {
    func_0014C380(M2C_FIELD(self, s32*, 0x30));
    M2C_FIELD(self, u8*, 0x3F) = 1;
}
void func_0025DB20(OwnerView* self) {
    if (M2C_FIELD(self->compound->children->body, s32*, 0xAC) == 10 && self->unknown3C[1]) {
        if (VectorY(self->normal) >= 0.5f) {
            func_0025DAC0(self);
            func_0025CA10(D_0040F4CC, self);
        }
    }
}
#ifdef NON_MATCHING
// Unmatched: The game-clock load moves across the body-vector stores (15 instructions).
void func_0025DBA8(OwnerView* self) {
    if ((self->compound->children->body->state & 1) && !func_0025DA10(self)) func_0025CBA8(D_0040F4CC, self);
    if (!func_0025DA10(self)) {
        CompoundView* compound = self->compound;
        if ((compound->children->body->state >> 1) & 1) {
            BodyView* body;
            func_0032B700(compound);
            body = self->compound->children->body;
            body->unknown90 = AssignXYZ(body->unknown90, body->solver->unknown370);
            body->unknownA0 = ZeroXYZ(body->unknownA0);
            func_0012C650(D_0040F4D0, self, M2C_FIELD(self->owner, BkVuVector*, 0xA0));
        }
    }
    self->unknown3C[3] = 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025DBA8);
#endif

void func_0025DC80(void *arg0) {
    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), void **, 0xC), void **, 0x58), s32 *, 0xAC) = 0;
}

s32 func_0025DC98(PoolView* self) {
    s32 result = 1;
    s32 count = CompoundCount(self);
    s32 i;
    for (i = 0; i < count && result; i++) result = result && ((CompoundBody(self, i)->state & 2) != 0);
    return result;
}
BkVuVector func_0025DD08(PoolView* self) {
    BodyView* body = self->compound->children[1].body;
    return ScaleXYZ(body->linearStep, body->solver->inverseScale);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025DD38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_0025E2D0);

void func_00260C18(void *arg0)
{
  int new_var;
  M2C_FIELD(arg0, s32 *, 0) = 0;
  M2C_FIELD(arg0, s32 *, 4) = 0;
 do { M2C_FIELD(arg0, s32 *, 0x14) = 0; func_0025DD38(); func_00107B78(&D_0040F0F0, 0xB, 0x10, 0); M2C_FIELD(arg0, s32 *, 0xC) = func_00107D20(0x750); } while (0);
  new_var = 0x10;
  *((s8 *) (((s8 *) arg0) + new_var)) = 0;
  arg0++;
  arg0--;
}

s32 func_00260C70(void *arg0, s32 arg1) {
    s32 temp_2;

    M2C_FIELD(arg0, s32 *, 0) = arg1;
    temp_2 = func_00135570(arg1);
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
    if (M2C_FIELD(arg0, u8 *, 0x10) == 0) {
        M2C_FIELD(arg0, u8 *, 0x10) = 1U;
        func_0025E2D0(arg0, temp_2);
    }
    func_0032B6E0(M2C_FIELD(arg0, void **, 0xC), M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), s32 *, 0x18) = 7;
    func_002611D0(arg0);
    M2C_FIELD(arg0, s8 *, 0x18) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00260CF8);

void func_00260F80(void) {
    func_002611C8();
}

s32 func_00260FA0(s32 *arg0) {
    *arg0 = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00260FB0);

void func_002611C8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_002611D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00261C50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00262668);
s32 func_002632B8(SlotList* self, s32 scene) {
    s32 i;
    void* shapes = M2C_FIELD(M2C_FIELD(M2C_FIELD(self->context, void**, 4), void**, 0), void**, 0x40);
    for (i = 0; i < self->capacity; i++) func_00263558(self, (s16)i);
    {
        void* vtable = M2C_FIELD(shapes, void**, 0x20);
        M2C_FIELD(vtable, void (**)(void*), 0x18)((u8*)shapes + M2C_FIELD(vtable, s16*, 0x14));
    }
    func_0032CB58(scene, (s32)self->compound, 1);
    return 1;
}

s32 func_00263360(void *arg0, s32 arg1) {
    func_0032CDE0(arg1, M2C_FIELD(arg0, s32 *, 8));
    return 1;
}

void func_00263388(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
}

void func_00263390(SlotList* self, void* owner, s32 count, s32 first) {
    s32 i;
    for (i = first; i < first + count; i++) self->entries[i].owner = owner;
}

s32 func_002633D0(void *arg0) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 8), void **, 0xC), s32 *, 0x58);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_002633E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00263558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00263630);
#ifdef NON_MATCHING
// Unmatched: Signed-short induction and entry-load placement differ (24 instructions).
void func_00263798(SlotList* self, s16 first, void* owner) {
    s16 i = first;
    void* shapes = M2C_FIELD(M2C_FIELD(M2C_FIELD(self->context, void**, 4), void**, 0), void**, 0x40);
    while (i < self->count && self->entries[i].owner == owner) {
        self->entries[i].owner = 0;
        self->entries[i].priority = 255;
        func_00263558(self, i);
        i++;
    }
    {
        void* vtable = M2C_FIELD(shapes, void**, 0x20);
        M2C_FIELD(vtable, void (**)(void*), 0x18)((u8*)shapes + M2C_FIELD(vtable, s16*, 0x14));
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00263798);
#endif
#ifdef NON_MATCHING
// Unmatched: The initial owner capture and byte-offset cursor allocation differ (11 instructions).
void func_002638B0(SlotList* self, u8 priority, s16 first) {
    s32 offset = first * sizeof(SlotEntry);
    void* owner = ((SlotEntry*)((u8*)self->entries + offset))->owner;
    SlotEntry* entry = (SlotEntry*)((u8*)self->entries + offset);
    do {
        if (priority < entry->priority) entry->priority--;
        offset += sizeof(SlotEntry);
        entry = (SlotEntry*)((u8*)self->entries + offset);
    } while (entry->owner == owner);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_002638B0);
#endif
s32 func_00263908(SlotList* self, s16 count, void* owner) {
    s16 first = self->count;
    s16 i;
    if (self->capacity - first < count) return -1;
    for (i = first; i < first + count; i++) {
        self->entries[i].owner = owner;
        self->entries[i].priority = 255;
    }
    self->count += count;
    return first;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_002639A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00263B70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00263C58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00263E80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00264008);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00264018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_25b5d0", func_00264130);

void func_00265C18(void) {
    func_00264130(1, 0xFFFF);
}
