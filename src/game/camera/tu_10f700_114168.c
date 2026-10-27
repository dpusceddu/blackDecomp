#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/effects/random_state.h"
#include "game/ai_manager.h"

// Partial Game view; only the random-state placement is recovered here.
typedef struct Recovered_GameRandomView {
    u8 unk_0[0x5AD8];
    BkEffectRandomStatePS2 random;
} Recovered_GameRandomView;

typedef char GameRandomOffset[(u32) & ((Recovered_GameRandomView*)0)->random == 0x5AD8 ? 1 : -1];
typedef char GameRandomStateSize[sizeof(BkEffectRandomStatePS2) == 8 ? 1 : -1];

typedef struct Recovered_PairedBank {
    void* unk_0[2];
    s8 unk_8[2];
    u8 unk_A[2];
    s8 unk_C;
} Recovered_PairedBank;

// Partial transition layouts; field meanings remain UNVERIFIED.
typedef struct Recovered_SlotOwnerView {
    u8 unk_0[0x6F0];
    u64 unk_6F0;
} Recovered_SlotOwnerView;
typedef struct Recovered_SlotTransition {
    u8 unk_0[0xC0];
    Recovered_SlotOwnerView* unk_C0;
    s32 unk_C4;
    s32 unk_C8;
} Recovered_SlotTransition;
extern void func_0027ACC8(void*);
extern void func_00118188(void*, s32, s32, f32);
extern void func_00110860(Recovered_SlotOwnerView*, s32);

typedef struct Recovered_TransitionQuery {
    u8 unk_0[0x1C];
    void* unk_1C;
    u8 unk_20;
    u8 unk_21[3];
    f32 unk_24;
} Recovered_TransitionQuery;
extern f32 func_00118158(void*, f32);
extern void func_00110C90(void*, f32, void*, s32);

// Partial views; original class identities and unused field meanings remain UNVERIFIED.
typedef struct Recovered_PoolDispatch {
    u8 unk_0[0x20];
    s16 unk_20;
    u16 unk_22;
    void (*unk_24)(void*);
    u8 unk_28[0x68];
    s16 unk_90;
    u16 unk_92;
    void (*unk_94)(void*);
} Recovered_PoolDispatch;
typedef struct Recovered_PoolSlot {
    u8 unk_0[0x10];
    Recovered_PoolDispatch* unk_10;
    u8 unk_14[0x128];
    u8 unk_13C;
    u8 unk_13D[0x15];
    u8 unk_152;
    u8 unk_153[0xD];
} Recovered_PoolSlot;
typedef struct Recovered_PoolDescriptor {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2[2];
    void* unk_4;
    void* unk_8;
    void* unk_C;
} Recovered_PoolDescriptor;
typedef struct Recovered_SlotPool {
    Recovered_PoolSlot unk_0[64];
    void** unk_5800;
    u8 unk_5804[64];
    Recovered_PoolDescriptor* unk_5844;
    u32 unk_5848;
    u8 unk_584C[4];
    u8 unk_5850;
} Recovered_SlotPool;
typedef struct Recovered_CameraRequest {
    void* unk_0;
    void* unk_4;
    f32 unk_8;
    u8 unk_C;
    u8 unk_D[3];
    s128 unk_10;
    u32 unk_20;
} Recovered_CameraRequest;
extern const s128 D_004432A0;

typedef struct Recovered_IndirectView {
    u8 unk_0[0x328];
    s32* unk_328;
} Recovered_IndirectView;

typedef struct Recovered_ArrayView {
    u32 unk_0;
    s32 unk_4;
    s32 unk_8;
    void** unk_C;
} Recovered_ArrayView;

typedef struct Recovered_SmallArray {
    void* unk_0;
    s8 unk_4;
} Recovered_SmallArray;
extern void* func_00107D20(s32);
extern void* func_0035C6EC(void*, s32, s32);

typedef struct Recovered_QuadRecord {
    u64 unk_0;
    u8 unk_8[0x18];
    s128 unk_20;
    u8 unk_30[0x30];
} Recovered_QuadRecord;
typedef struct Recovered_Record14 {
    u32 unk_0, unk_4, unk_8, unk_C, unk_10;
} Recovered_Record14;
typedef char PoolSlotSize[sizeof(Recovered_PoolSlot) == 0x160 ? 1 : -1];
typedef char PoolStateOffset[(u32) & ((Recovered_SlotPool*)0)->unk_5804 == 0x5804 ? 1 : -1];
typedef char PoolDescriptorOffset[(u32) & ((Recovered_SlotPool*)0)->unk_5844 == 0x5844 ? 1 : -1];
typedef char CameraRequestVectorOffset[(u32) & ((Recovered_CameraRequest*)0)->unk_10 == 0x10 ? 1 : -1];
typedef char QuadRecordSize[sizeof(Recovered_QuadRecord) == 0x60 ? 1 : -1];
typedef char SmallRecordSize[sizeof(Recovered_Record14) == 0x14 ? 1 : -1];

typedef struct Recovered_RecordDispatch {
    u8 unk_0[8];
    s16 unk_8;
    u16 unk_A;
    void (*unk_C)(void*, f32);
} Recovered_RecordDispatch;
typedef struct Recovered_Record60 {
    u64 unk_0;
    u8 unk_8[8];
    Recovered_RecordDispatch* unk_10;
    u8 unk_14[0x4C];
} Recovered_Record60;
typedef struct Recovered_TimeView {
    u8 unk_0[0x1C];
    f32 unk_1C;
} Recovered_TimeView;
extern Recovered_TimeView* D_0040F4D0;
extern void func_00130690(Recovered_Record14*, f32);
typedef struct Recovered_RecordD0 {
    u8 unk_0[0xC8];
    u32 unk_C8;
    u8 unk_CC[4];
} Recovered_RecordD0;
typedef struct Recovered_RecordOwner {
    u8 unk_0[0x48];
    Recovered_RecordD0* unk_48;
    u8 unk_4C[0x1D];
    s8 unk_69;
} Recovered_RecordOwner;

typedef struct Recovered_FrameDispatch {
    u8 unk_0[8];
    s16 unk_8;
    u16 unk_A;
    void (*unk_C)(void*, f32);
    u8 unk_10[0x18];
    s16 unk_28;
    u16 unk_2A;
    void (*unk_2C)(void*, f32);
} Recovered_FrameDispatch;
typedef struct Recovered_FrameObject {
    u8 unk_0[0x1C];
    f32 unk_1C;
    u8 unk_20[0x20];
    Recovered_FrameDispatch* unk_40;
} Recovered_FrameObject;
extern void* D_0040F530;
extern void* D_0040F51C;
extern void* D_0040F518;
extern void func_0011A270(void*);
extern void func_001F2828(void*, f32);
extern void func_001F25A8(void*, f32);
extern void func_0013BAC8(void*, f32);

typedef struct Recovered_FrameState {
    u8 unk_0[4];
    s32 unk_4;
    u8 unk_8[0x154];
    u8 unk_15C;
} Recovered_FrameState;
extern Recovered_FrameState* D_0040F504;
extern void* D_0040F0E0;
extern void func_0011C0F0(Recovered_FrameState*);
extern void func_001B1CB8(s32);
extern void func_00103918(void*, s32);

typedef struct Recovered_SubDispatch {
    u8 unk_0[0x10];
    s16 unk_10;
    u16 unk_12;
    void (*unk_14)(void*, f32);
} Recovered_SubDispatch;
typedef struct Recovered_SubObject {
    u8 unk_0[0x14];
    Recovered_SubDispatch* unk_14;
} Recovered_SubObject;
typedef struct Recovered_UpdateManager {
    u8 unk_0[0xC];
    Recovered_SubObject* unk_C;
    u8 unk_10[4];
    Recovered_SubObject* unk_14;
} Recovered_UpdateManager;
extern void func_001C22A0(void*, f32);

extern Recovered_AIManager* D_0040F4D4;
extern s32 func_001891C0(Recovered_ActorRecords*);
extern void* func_0018A678(Recovered_ActorRecords*);
extern s32 func_00178F28(void*);
typedef struct Recovered_ManagerPredicate {
    u8 unk_0[0x8B3];
    u8 unk_8B3;
} Recovered_ManagerPredicate;

typedef struct Recovered_MaskRecord {
    u8 unk_0[0x68];
    u64 unk_68[12];
    u8 unk_C8[8];
} Recovered_MaskRecord;
typedef struct Recovered_MaskOwner {
    u8 unk_0[0x48];
    Recovered_MaskRecord* unk_48;
    u8 unk_4C[0x1D];
    u8 unk_69;
} Recovered_MaskOwner;
typedef struct Recovered_CombinedMask {
    u8 unk_0[0x370];
    u64 unk_370;
} Recovered_CombinedMask;

typedef struct Recovered_PoseSourceA {
    u8 unk_0[0x30];
    void* unk_30;
} Recovered_PoseSourceA;
typedef struct Recovered_PoseSourceB {
    u8 unk_0[0x50];
    void* unk_50;
} Recovered_PoseSourceB;
typedef struct Recovered_PoseSources {
    u8 unk_0[0x50];
    Recovered_PoseSourceA* unk_50;
    Recovered_PoseSourceB* unk_54;
} Recovered_PoseSources;
typedef struct Recovered_SavedPose {
    u8 unk_0[0x70];
    s128 unk_70[4];
    u8 unk_B0[0xA0];
    s128 unk_150[4];
    u8 unk_190[0x1A0];
    Recovered_PoseSources* unk_330;
    u8 unk_334[0x1C];
    void* unk_350;
    u8 unk_354[0x5C];
    u8 unk_3B0;
    u8 unk_3B1;
} Recovered_SavedPose;
extern void func_00261C50(void*, void*, void*);

extern void func_00165C40(void*, Recovered_Record60*);
extern void func_00130660(Recovered_Record14*);
extern s32 func_00130678(Recovered_Record14*);

extern s32 func_001B6CF8(s32, s32, M2C_UNK);
extern s32 D_0040F4D8;
extern s32 func_00149AC8(s32);

void func_00114168(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00114170);

void func_00114228(void) {

}

void func_00114230(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00114238);

void func_001145D0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001145D8);

void func_00114968(void) {

}

void func_00114970(void) {

}

s32 func_00114978(void) {
    return 1;
}

void func_00114980(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00114988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00115D38);
void func_00115D70(Recovered_CameraRequest* self, void* arg1, s128 arg2, f32 value) {
    self->unk_C = 1;
    self->unk_8 = value;
    self->unk_10 = arg2;
    self->unk_4 = arg1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00115DA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00115DC8);
void func_001168E0(Recovered_SlotTransition* self, Recovered_SlotOwnerView* owner) {
    func_0027ACC8(self);
    self->unk_C0 = owner;
}
void func_00116918(Recovered_SlotTransition* self, s32 slot, s32 target, s32 arg3, s32 arg4, f32 duration) {
    func_00118188(self, arg3, arg4, duration);
    self->unk_C8 = target;
    self->unk_C4 = slot;
    self->unk_C0->unk_6F0 &= ~(1UL << slot);
    func_00110860(self->unk_C0, 2);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00116990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00116A78);
void func_00116E80(Recovered_TransitionQuery* self, void* value) {
    if (self->unk_20) {
        if (self->unk_24 == -1.0f) {
            func_00110C90(self->unk_1C, func_00118158(self, self->unk_24), value, 1);
        } else {
            func_00110C90(self->unk_1C, self->unk_24, value, 1);
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125970);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125B10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125C60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125D18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125E98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00125F88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126058);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126098);
void func_00126200(Recovered_SlotPool* self) {
    s8 i;
    self->unk_5850 = 0;
    for (i = 0; i < 64; i++) {
        Recovered_PoolSlot* slot = &self->unk_0[i];
        slot->unk_10->unk_94((u8*)slot + slot->unk_10->unk_90);
        self->unk_5804[i] = 0;
    }
}
s32 func_00126290(Recovered_SlotPool* self) {
    s8 i;
    self->unk_5848 = 0;
    self->unk_5850 = 0;
    for (i = 0; i < 64; i++) {
        self->unk_5804[i] = 0;
        self->unk_0[i].unk_152 = 0;
        self->unk_0[i].unk_13C = 0;
    }
    for (i = 0; i < self->unk_5844->unk_0; i++) self->unk_5800[i] = NULL;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001264C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126710);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126980);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126BC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126D78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126E48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126E50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126F08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126F10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126F80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00127060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012C650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012C790);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012CBA0);
static inline u32 GameRandomStep(BkEffectRandomStatePS2* random) {
    random->state = (random->state << 16) + ((s32)random->state >> 16);
    random->state += random->accumulator;
    random->accumulator += random->state;
    return random->state;
}

static inline f32 GameRandomRange(Recovered_GameRandomView* self, f32 minimum, f32 maximum) {
    f32 fraction = (f32)GameRandomStep(&self->random) * 2.3283064365386963e-10f;
    return minimum + (maximum - minimum) * fraction;
}

f32 func_0012D058(Recovered_GameRandomView* self) {
    return (f32)GameRandomStep(&self->random) * 2.3283064365386963e-10f;
}
f32 func_0012D0D0(Recovered_GameRandomView* self, f32 minimum, f32 maximum) {
    return GameRandomRange(self, minimum, maximum);
}
s32 func_0012D158(Recovered_GameRandomView* self, s32 minimum, s32 maximum) {
    return (s32)GameRandomRange(self, (f32)minimum, (f32)maximum + 1.0f - 0.0000152587890625f);
}
s32 func_0012D218(Recovered_GameRandomView* self, f32 probability) {
    if (probability == 0.0f) return 0;
    return func_0012D058(self) <= probability;
}
void func_0012D270(Recovered_FrameObject* self, f32 time) {
    void* component = (u8*)self + 0x30;
    func_0011A270(D_0040F530);
    func_001F2828(D_0040F51C, time);
    func_001F25A8(D_0040F518, time);
    func_0013BAC8(component, time);
    self->unk_40->unk_C((u8*)component + self->unk_40->unk_8, time);
    self->unk_40->unk_2C((u8*)component + self->unk_40->unk_28, time);
}
void func_0012D310(Recovered_FrameObject* self) {
    func_0011C0F0(D_0040F504);
    if (D_0040F504->unk_4 == 1) {
        void* component = (u8*)self + 0x30;
        self->unk_40->unk_C((u8*)component + self->unk_40->unk_8, self->unk_1C);
    }
    if (D_0040F504->unk_4 == 3) {
        void* component = (u8*)self + 0x30;
        self->unk_40->unk_C((u8*)component + self->unk_40->unk_8, self->unk_1C);
        func_001B1CB8(D_0040F4D8);
    }
    if (D_0040F504->unk_15C) func_00103918(D_0040F0E0, 0);
}
void func_0012D3D0(Recovered_FrameObject* self) {
    Recovered_SubObject* first = ((Recovered_UpdateManager*)D_0040F518)->unk_C;
    first->unk_14->unk_14((u8*)first + first->unk_14->unk_10, self->unk_1C);
    first = ((Recovered_UpdateManager*)D_0040F518)->unk_14;
    first->unk_14->unk_14((u8*)first + first->unk_14->unk_10, self->unk_1C);
    func_001C22A0((u8*)D_0040F4D8 + 0x83CA0, self->unk_1C);
}
void func_0012EEE8(Recovered_PairedBank* self) {
    s8 i;
    for (i = 0; i < 2; i++) {
        self->unk_0[i] = NULL;
        self->unk_8[i] = 0;
    }
}
s32 func_0012EF28(Recovered_PairedBank* self) {
    s8 i;
    for (i = 0; i < 2; i++) {
        self->unk_0[i] = NULL;
        self->unk_8[i] = 0;
    }
    return 1;
}
void func_0012EF68(Recovered_PairedBank* self) {
    f32 time = D_0040F4D0->unk_1C;
    s8 group;
    for (group = 0; group < 2; group++) {
        s8 i;
        for (i = 0; i < self->unk_8[group]; i++) {
            Recovered_Record60* record = (Recovered_Record60*)(i * 0x60 + (u32)self->unk_0[group]);
            record->unk_10->unk_C((u8*)record + record->unk_10->unk_8, time);
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F060);
void func_0012F1B8(Recovered_PairedBank* self) {
    s8 next = (self->unk_C + 1) % 2;
    if (self->unk_A[next]) {
        self->unk_0[next] = NULL;
        self->unk_8[next] = 0;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F208);
s32 func_0012F2D8(Recovered_PairedBank* self, u64 id, void* result) {
    s8 group;
    for (group = 0; group < 2; group++) {
        s8 i;
        for (i = 0; i < self->unk_8[group]; i++) {
            Recovered_Record60* record = (Recovered_Record60*)(i * 0x60 + (u32)self->unk_0[group]);
            if (record->unk_0 == id) {
                func_00165C40(result, record);
                return 1;
            }
        }
    }
    return 0;
}
void func_0012F388(Recovered_PairedBank* self) {
    s8 i;
    for (i = 0; i < 2; i++) {
        self->unk_0[i] = NULL;
        self->unk_8[i] = 0;
    }
}
s32 func_0012F3C8(Recovered_PairedBank* self) {
    s8 i;
    for (i = 0; i < 2; i++) {
        self->unk_0[i] = NULL;
        self->unk_8[i] = 0;
    }
    return 1;
}
void func_0012F408(Recovered_PairedBank* self) {
    f32 time = D_0040F4D0->unk_1C;
    s8 group;
    for (group = 0; group < 2; group++) {
        s8 i;
        for (i = 0; i < self->unk_8[group]; i++) { func_00130690(&((Recovered_Record14*)self->unk_0[group])[i], time); }
    }
}
void func_0012F4F0(Recovered_PairedBank* self, s8 count) {
    self->unk_C = (s8)(self->unk_C + 1) % 2;
    if (count == 0) {
        self->unk_A[self->unk_C] = 0;
    } else {
        s8 i;
        void** destination;
        self->unk_A[self->unk_C] = 1;
        self->unk_8[self->unk_C] = count;
        destination = &self->unk_0[self->unk_C];
        *destination = func_00107D20(count * (s32)sizeof(Recovered_Record14));
        for (i = 0; i < count; i++) {
            func_00130660(&((Recovered_Record14*)self->unk_0[self->unk_C])[i]);
            func_00130678(&((Recovered_Record14*)self->unk_0[self->unk_C])[i]);
        }
    }
}
void func_0012F610(Recovered_PairedBank* self) {
    s8 next = (self->unk_C + 1) % 2;
    if (self->unk_A[next]) {
        self->unk_0[next] = NULL;
        self->unk_8[next] = 0;
    }
}
s32 func_0012F660(Recovered_RecordOwner* self) {
    s8 count = self->unk_69;
    s8 i;
    for (i = 0; i < count; i++) {
        if (self->unk_48[i].unk_C8 != 0) return 1;
    }
    return 0;
}
static inline u8 SetIfEmpty(Recovered_Record14* record, u32 value) {
    if (record->unk_0 != 0) return 0;
    record->unk_0 = value;
    return 1;
}
void func_0012F6A8(Recovered_PairedBank* self, u32 value) {
    s8 i;
    for (i = 0; i < self->unk_8[self->unk_C]; i++) {
        if (SetIfEmpty(&((Recovered_Record14*)self->unk_0[self->unk_C])[i], value)) break;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F738);
s32 func_00130640(Recovered_QuadRecord* self, u64 id, s128 value) {
    if (self->unk_0 != 0) return 0;
    self->unk_0 = id;
    self->unk_20 = value;
    return 1;
}
s32 func_00130678(Recovered_Record14* self) {
    self->unk_0 = 0;
    self->unk_C = 0;
    self->unk_10 = 0;
    self->unk_4 = 0;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001306D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00131EF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00132188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00132610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001327F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001334E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00133BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00133E60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135580);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135A38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135AC0);
s32 func_00135B60(Recovered_IndirectView* self) {
    if (self->unk_328 != NULL) return *self->unk_328;
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001368F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00136BD0);
void func_00136D60(Recovered_CombinedMask* self, Recovered_MaskOwner* source, s32 index) {
    s32 i;
    self->unk_370 = 0;
    if (source->unk_69 != 0) {
        for (i = 0; i < source->unk_69; i++) {
            Recovered_MaskRecord* record =
                (Recovered_MaskRecord*)((u32)source->unk_48 + i * sizeof(Recovered_MaskRecord));
            self->unk_370 |= record->unk_68[index];
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00136DC0);
void func_00136E88(Recovered_SavedPose* self, void* state) {
    if (state) {
        s128* pose = self->unk_70;
        self->unk_150[0] = pose[0];
        self->unk_150[1] = pose[1];
        self->unk_150[2] = pose[2];
        self->unk_150[3] = pose[3];
        self->unk_3B0 = 1;
        self->unk_3B1 = 0;
    } else {
        func_00261C50(self->unk_350, self->unk_330->unk_54->unk_50, self->unk_330->unk_50->unk_30);
    }
    self->unk_350 = state;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001386C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001387C8);
void func_00139B68(Recovered_ArrayView* self) {
    s32 i;
    self->unk_8 = 0;
    for (i = 0; i < self->unk_4; i++) self->unk_C[i] = NULL;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00139BA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013C868);
void func_0013CE08(Recovered_ManagerPredicate* self) {
    s8 i;
    self->unk_8B3 = 0;
    for (i = 0; i < 16; i++) {
        Recovered_ManagedSlot* slot = &D_0040F4D4->slots[i];
        if (slot->active && func_001891C0(&slot->records) && func_00178F28(func_0018A678(&slot->records))) {
            self->unk_8B3 = 1;
            break;
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013CED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013CF38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D048);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D8D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D9A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00140AD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00140BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001415A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00142AB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00142B90);
void func_00142E30(Recovered_SmallArray* self, s8 count) {
    self->unk_4 = count;
    self->unk_0 = func_00107D20(count * 12);
    func_0035C6EC(self->unk_0, 0, self->unk_4 * 12);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00143590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001444A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001448C8);

s32 func_00144E00(s32 arg0) {
    func_001B6CF8(D_0040F4D8 + 0x66290, arg0, 0);
    func_00149AC8(arg0);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00144E50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00144E58);
