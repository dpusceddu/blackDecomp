#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/effects/random_state.h"
#include "game/ai_manager.h"
#include "game/actor_slots.h"

// Partial configuration view; field meanings remain UNVERIFIED.
typedef struct Recovered_ConfigFloat {
    u8 unk_0[0x60];
    f32 unk_60;
} Recovered_ConfigFloat;
typedef struct Recovered_ConfigIndirect {
    u8 unk_0[4];
    Recovered_ConfigFloat* unk_4;
} Recovered_ConfigIndirect;
typedef struct Recovered_SlotConfiguration {
    u8 unk_0[0x10];
    s128 unk_10;
    u8 unk_20[0x14];
    s8 unk_34;
    u8 unk_35[0xB];
    s32 unk_40;
    s32 unk_44;
    Recovered_ConfigIndirect* unk_48;
    u8 unk_4C[4];
    u64 unk_50;
    u8 unk_58;
} Recovered_SlotConfiguration;
extern void func_0013EC38(void*, void*);
extern void func_0018D9A0(void*, s32, s32, s8);
extern void func_0018D9F0(void*, f32);
extern void func_0017C9F8(void*, void*);
extern void func_001804F8(void*, s128, f32);
extern void func_00173FE8(u16*);
extern void func_0018D410(void*, u64);
extern s32 func_0018DCE0(void*);
extern void func_00181AB0(void*, s32);
extern void func_001856B0(void*, s32);
extern void func_00185D10(void*);
extern void func_00180F18(void*);
extern void func_00188B98(void*);
extern void func_00187EC8(void*);
extern void func_00183918(void*);
extern void func_00182078(void*);
extern void func_0018AD88(void*);
extern void func_00181F28(void*);
extern void func_0018CFD8(void*);
extern void func_0018C1E0(void*);
extern void func_001831E0(void*);
extern void func_00181348(void*);
extern void func_0016ABA0(void*);

// Private catalog and observer views; unused spans remain UNVERIFIED.
typedef struct Recovered_CatalogItem {
    u64 unk_0;
    u8 unk_8[0x18];
} Recovered_CatalogItem;
typedef struct Recovered_Catalog {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2[2];
    Recovered_CatalogItem* unk_4;
} Recovered_Catalog;
typedef struct Recovered_PoolBinding {
    u64 unk_0;
    u8 unk_8[8];
    s8 unk_10;
    u8 unk_11[7];
} Recovered_PoolBinding;
typedef struct Recovered_BindingDescriptor {
    u8 unk_0;
    u8 unk_1[7];
    Recovered_PoolBinding* unk_8;
} Recovered_BindingDescriptor;
typedef struct Recovered_BindingPool {
    u8 unk_0[0x5844];
    Recovered_BindingDescriptor* unk_5844;
} Recovered_BindingPool;
extern Recovered_Catalog** D_0040F4E0;
static inline s32 FindCatalogItem(u64 id) {
    Recovered_Catalog* self = *D_0040F4E0;
    s8 i = 0;
    u8 count = self->unk_1;
    if (count) {
        Recovered_CatalogItem* item = self->unk_4;
        do {
            if (item->unk_0 == id) return i;
            item++;
            i++;
        } while (i < count);
    }
    return -1;
}

// Private catalog and observer views; unused spans remain UNVERIFIED.
typedef struct Recovered_ObserverSetupEntry {
    u8 unk_0[0x30];
    s32 unk_30[8];
    u8 unk_50[0x1F0];
} Recovered_ObserverSetupEntry;
typedef struct Recovered_ObserverControl {
    u8 unk_0[0x38];
    s32 unk_38;
} Recovered_ObserverControl;
typedef struct Recovered_ObserverOwner {
    u8 unk_0[0x25C];
    void* unk_25C[8];
    u8 unk_27C[0xAC];
    Recovered_ObserverControl* unk_328;
    u8 unk_32C[4];
    Recovered_ObserverSetupEntry* unk_330;
    u8 unk_334[0x79];
    u8 unk_3AD;
} Recovered_ObserverOwner;
extern u8* D_0040F50C;
extern void* D_0040F514;
extern s32 func_00138C68(void*);
extern s32 func_00138C50(void*);
extern void func_00138338(Recovered_ObserverControl*, s32);
extern s32 func_00142ED8(void*, s32, s32);
extern void func_00137320(Recovered_ObserverOwner*);
extern void func_00136B50(Recovered_ObserverOwner*);

// Native resource table prefixes; unused spans and class identities remain UNVERIFIED.
typedef struct Recovered_Resource18 {
    u64 unk_0; // Catalog key; also consumed by the exact binding loop.
    u64 unk_8;
    s8 unk_10; // UNVERIFIED: spawn-by-catalog draft.
    u8 unk_11[7];
} Recovered_Resource18;
typedef struct Recovered_Resource10 {
    u64 unk_0, unk_8;
} Recovered_Resource10;
typedef struct Recovered_PoolResources {
    u8 unk_0, unk_1, unk_2, unk_3, unk_4;
    u8 unk_5[3];
    Recovered_Resource18* unk_8;
    Recovered_Resource18* unk_C;
    Recovered_Resource10* unk_10;
    u64* unk_14;
    Recovered_Resource10* unk_18;
} Recovered_PoolResources;
typedef struct Recovered_ResourcePool {
    u8 unk_0[0x5800];
    void** unk_5800;
    u8 unk_5804[0x40];
    Recovered_PoolResources* unk_5844;
} Recovered_ResourcePool;
extern void* func_00108120(void*, u64);
extern u8* D_0040F4C4;

typedef char Resource18Stride[sizeof(Recovered_Resource18) == 0x18 ? 1 : -1];
typedef char Resource10Stride[sizeof(Recovered_Resource10) == 0x10 ? 1 : -1];
typedef char ResourcePoolDescriptorOffset[(u32) & ((Recovered_ResourcePool*)0)->unk_5844 == 0x5844 ? 1 : -1];
typedef char ObserverSetupStride[sizeof(Recovered_ObserverSetupEntry) == 0x240 ? 1 : -1];
typedef char ObserverControlOffset[(u32) & ((Recovered_ObserverOwner*)0)->unk_328 == 0x328 ? 1 : -1];
typedef char ObserverSetupOffset[(u32) & ((Recovered_ObserverOwner*)0)->unk_330 == 0x330 ? 1 : -1];

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
    u8 unk_13D[3];
    s32 unk_140; // UNVERIFIED: pool release and weapon eligibility drafts.
    u8 unk_144[4];
    u8 unk_148; // UNVERIFIED: descriptor choice index.
    u8 unk_149[9];
    u8 unk_152;
    u8 unk_153;
    u8 unk_154; // UNVERIFIED: release marker.
    u8 unk_155[0xB];
} Recovered_PoolSlot;
typedef struct Recovered_PoolDescriptor {
    u8 unk_0;
    u8 unk_1;
    u8 unk_2[2];
    u8 unk_4[4];
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
extern s128 D_004432A0;

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

typedef struct Recovered_PoolChoice {
    s32 unk_0;
    u8 unk_4[0x14];
} Recovered_PoolChoice;
typedef char PoolChoiceSize[sizeof(Recovered_PoolChoice) == 0x18 ? 1 : -1];

extern void func_00181030(void*, Recovered_ManagedSlot*);
extern void func_00185D08(void*, Recovered_ManagedSlot*);
extern void func_00180F10(void*, Recovered_ManagedSlot*);
extern void func_00188B90(void*, Recovered_ManagedSlot*);
extern void func_00187E08(void*, Recovered_ManagedSlot*);
extern void func_0017C9F0(void*, Recovered_ManagedSlot*);
extern void func_00183910(void*, Recovered_ManagedSlot*);
extern void func_00181FF0(void*, Recovered_ManagedSlot*);
extern void func_001804D0(void*, Recovered_ManagedSlot*);
extern void func_0018AD80(void*, Recovered_ManagedSlot*);
extern void func_0018CEE0(void*, Recovered_ManagedSlot*);
extern void func_00181F20(void*, Recovered_ManagedSlot*);
extern void func_0018D978(void*, Recovered_ManagedSlot*);
extern void func_0018C178(void*, Recovered_ManagedSlot*);
extern void func_001831D8(void*, Recovered_ManagedSlot*);
extern void func_0013EC10(Recovered_ManagedSlot*, s32);
extern void func_00176EE0(void*);
extern void func_0017B260(void*, Recovered_ManagedSlot*);
extern void func_0016AB58(void*, s32);
extern void func_00189B90(Recovered_ActorRecords*, s32);
extern void func_00188A18(void*, s32);
extern void func_00183BC0(void*, s32);
extern void func_001815D8(void*, s32);
extern Recovered_ActorSlot* func_00179258(Recovered_ActorSlotTable*, s32);
extern s32 func_00178F18(Recovered_ActorSlot*);
extern Recovered_ManagedSlot* func_00135550(Recovered_ManagedActor*);
extern void func_00174018(u16*, void*);

extern s32 func_001B6CF8(s32, s32, M2C_UNK);
extern s32 D_0040F4D8;
extern s32 func_00149AC8(s32);

#ifdef NON_MATCHING
#include "game/weapons/state.h"
#include "game/weapons/inventory.h"
// Partial views used only by drafts; these fields remain UNVERIFIED.
typedef struct Recovered_SpawnState {
    u8 unk_0[0x18];
    s32 unk_18;
} Recovered_SpawnState;
typedef struct Recovered_SpawnRecord {
    u8 unk_0[0x34];
    Recovered_SpawnState* unk_34;
} Recovered_SpawnRecord;
typedef struct Recovered_SpawnSlot {
    u8 unk_0[0xB4];
    Recovered_SpawnRecord* unk_B4;
    u8 unk_B8[0x9D];
    u8 unk_155;
} Recovered_SpawnSlot;
typedef struct Recovered_SpawnPool {
    u8 unk_0[0x5800];
    void** unk_5800;
    u8 unk_5804[0x40];
    Recovered_PoolResources* unk_5844;
    u8 unk_5848[8];
    s8 unk_5850;
} Recovered_SpawnPool;
typedef struct Recovered_SpawnDefinition {
    u8 unk_0[0x60];
    s16 unk_60;
} Recovered_SpawnDefinition;
extern void* D_0040F4CC;

extern s32 func_0025CDA0(void*, s32*, s32);
extern Recovered_SpawnSlot* func_00127550(Recovered_SpawnPool*);
extern Recovered_SpawnDefinition* func_0015D248(void*, s8, s32);
extern void func_0014EF58(Recovered_SpawnSlot*, s32, s32, void*, s32, s32, s32, s32);
extern void func_00129108(void*, Recovered_SpawnSlot*, s32, s32, s32);
extern void func_0025D860(Recovered_SpawnRecord*, s128);
extern void func_0025D910(Recovered_SpawnRecord*, s128);
extern void func_0025CE28(void*);

extern void* func_001276B8(Recovered_SpawnPool*, s32);

typedef struct Recovered_TransitionPose {
    s128 unk_0[5];
} Recovered_TransitionPose;
typedef struct Recovered_PoseReceiverDispatch {
    u8 unk_0[0x18];
    s16 unk_18;
    u16 unk_1A;
    void (*unk_1C)(void*, Recovered_TransitionPose*);
} Recovered_PoseReceiverDispatch;
typedef struct Recovered_PoseReceiver {
    Recovered_PoseReceiverDispatch* unk_0;
} Recovered_PoseReceiver;
typedef struct Recovered_PoseReceivers {
    u8 unk_0[0x1C0];
} Recovered_PoseReceivers;
typedef struct Recovered_TransitionPoses {
    u8 unk_0[0x20];
    Recovered_TransitionPose unk_20;
    Recovered_TransitionPose unk_70;
    Recovered_PoseReceivers* unk_C0;
    s32 unk_C4;
    s32 unk_C8;
} Recovered_TransitionPoses;
extern void func_00118088(Recovered_TransitionPoses*);
static inline void CopyTransitionPose(Recovered_TransitionPose* self, Recovered_TransitionPose* source) {
    u32 saved = M2C_FIELD(self, u32*, 0x40);
    *self = *source;
    M2C_FIELD(self, u32*, 0x40) = saved;
}
typedef struct Recovered_MaskPair {
    s16 unk_0, unk_2, unk_4;
} Recovered_MaskPair;
typedef struct Recovered_MaskPayload {
    u8 unk_0[0x30];
} Recovered_MaskPayload;
typedef struct Recovered_MaskInputs {
    u8 unk_0[0x1C];
    Recovered_MaskPayload* unk_1C;
    Recovered_MaskPair* unk_20;
    s32 unk_24;
} Recovered_MaskInputs;
typedef struct Recovered_MaskRender {
    u8 unk_0[0x70];
    s128 unk_70[4];
    u8 unk_B0[0x220];
    u8 unk_2D0[0x84];
    u8* unk_354;
    u8* unk_358;
    u8 unk_35C[0x14];
    u64 unk_370;
} Recovered_MaskRender;
extern u8* D_0040F4C0;
extern void func_001B0740(void*, Recovered_MaskRender*, s128*);
extern void* func_001AF738(void*, void*, void*, void*, void*, void*, u8, s32, f32);

extern void func_00136D60(Recovered_CombinedMask*, Recovered_MaskOwner*, s32);
#include "game/camera/selection_pool.h"
typedef struct Recovered_SelectionActor {
    Recovered_SelectionMember member;
    u8 unk_3B0[0x10];
} Recovered_SelectionActor;
typedef struct Recovered_SelectionOwner {
    u8 unk_0[0x90];
    Recovered_SelectionActor unk_90[32];
    u8 unk_7890[0x100];
    Recovered_SelectionPool unk_7990[4];
    u8 unk_79D0[0xB44];
    s32 unk_8514;
    u8 unk_8518[4];
    s32 unk_851C;
    s32 unk_8520;
} Recovered_SelectionOwner;
typedef struct Recovered_SelectionGate {
    u8 unk_0[0x138];
    u8 unk_138, unk_139;
} Recovered_SelectionGate;
extern u8* D_0040F4C4;
extern void* D_0040F540;
extern s32 func_00143700(void*);
extern s32 func_001397F8(Recovered_SelectionPool*);
extern s32 func_00139838(Recovered_SelectionPool*, Recovered_SelectionMember*);
static inline s32 SelectionBlocked(Recovered_SelectionGate* self) {
    s32 result = 0;
    if (self->unk_138 || self->unk_139) result = 1;
    return result;
}
typedef struct Recovered_Record12 {
    f32 unk_0, unk_4;
    u8 unk_8, unk_9, unk_A, unk_B;
} Recovered_Record12;
static inline void SetDimensions(Recovered_SmallArray* self, s8 index, f32 x, f32 y, s32 arg3, s32 arg4, u8 arg5) {
    ((Recovered_Record12*)self->unk_0)[index].unk_4 = y;
    ((Recovered_Record12*)self->unk_0)[index].unk_0 = x;
    ((Recovered_Record12*)self->unk_0)[index].unk_9 = arg4;
    ((Recovered_Record12*)self->unk_0)[index].unk_8 = arg3;
    ((Recovered_Record12*)self->unk_0)[index].unk_A = arg5;
}

typedef struct Recovered_WeaponChoice {
    s32 unk_0;
    u8 unk_4[0x14];
} Recovered_WeaponChoice;
typedef struct Recovered_InventoryQuery {
    BkInventoryPS2 inventory;
    u8 unk_1C[8];
    BkWeaponControllerPS2* unk_24;
} Recovered_InventoryQuery;
extern Recovered_SlotPool* D_0040F4E4;
extern BkWeaponDefinitionPS2* func_0015D228(void*, s32);
extern u16 func_00155198(BkInventoryPS2*);
extern s16 func_001580E0(BkWeaponControllerPS2*);
extern s32 func_00155178(BkInventoryPS2*, s32, u8);
extern void func_00129240(void*, Recovered_PoolSlot*, s32);
extern void func_001F2958(void*, s32, s32, s32, s32);
extern s32 func_00130640(Recovered_QuadRecord*, u64, s128);
typedef struct Recovered_RequestEntry {
    u32 unk_0;
    u8 unk_4[8];
} Recovered_RequestEntry;
typedef struct Recovered_RequestState {
    u8 unk_0[0xB0];
    u32 unk_B0;
    u8 unk_B4[0x4C];
    s8 unk_100;
    u8 unk_101;
    u8 unk_102;
} Recovered_RequestState;
typedef struct Recovered_ThreeSlots {
    u8 unk_0[0xC];
    void* unk_C[3];
    u8 unk_18;
    u8 unk_19;
    u8 unk_1A;
} Recovered_ThreeSlots;
#endif

typedef struct Recovered_ObserverArray {
    u8 unk_0[0x25C];
    void* unk_25C[8];
    u8 unk_27C[0x54];
    u8 unk_2D0[1]; // Payload prefix; its complete extent is unknown.
} Recovered_ObserverArray;
extern void func_00142F80(void*, s32, void*);

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
void func_00115D38(Recovered_CameraRequest* self) {
    self->unk_C = 0;
    self->unk_4 = NULL;
    self->unk_8 = 0.0f;
    self->unk_10 = D_004432A0;
    self->unk_20 = 0;
}
void func_00115D70(Recovered_CameraRequest* self, void* arg1, s128 arg2, f32 value) {
    self->unk_C = 1;
    self->unk_8 = value;
    self->unk_10 = arg2;
    self->unk_4 = arg1;
}
void func_00115DA8(Recovered_CameraRequest* self) {
    self->unk_C = 0;
    self->unk_10 = D_004432A0;
    self->unk_20 = 0;
}
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
#ifdef NON_MATCHING
// Unmatched: 80-byte copies keep the saved tail word in a register; native uses a stack temporary.
s32 func_00116990(Recovered_TransitionPoses* self, Recovered_TransitionPose* source) {
    Recovered_PoseReceiver* receiver;
    func_00118088(self);
    CopyTransitionPose(&self->unk_20, source);
    CopyTransitionPose(&self->unk_70, source);
    receiver = ((Recovered_PoseReceiver**)((u8*)self->unk_C0 + 0x1C0))[self->unk_C8];
    receiver->unk_0->unk_1C((u8*)receiver + receiver->unk_0->unk_18, &self->unk_70);
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00116990);
#endif
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
void func_001264C8(Recovered_ResourcePool* self, Recovered_PoolResources* descriptor) {
    u8 i = 0;
    s32 current = 0;
    self->unk_5844 = descriptor;
    self->unk_5800 = func_00107D20(
        (descriptor->unk_0 + descriptor->unk_1 + descriptor->unk_2 + descriptor->unk_3 + descriptor->unk_4) * 4);
    for (i = 0; i < self->unk_5844->unk_0; i++) {
        void* resource = func_00108120(D_0040F4C4, self->unk_5844->unk_8[i].unk_8);
        self->unk_5800[current++] = resource;
    }
    for (i = 0; i < self->unk_5844->unk_1; i++) {
        void* resource = func_00108120(D_0040F4C4, self->unk_5844->unk_C[i].unk_8);
        self->unk_5800[current++] = resource;
    }
    for (i = 0; i < self->unk_5844->unk_2; i++) {
        void* resource = func_00108120(D_0040F4C4, self->unk_5844->unk_10[i].unk_0);
        self->unk_5800[current++] = resource;
    }
    for (i = 0; i < self->unk_5844->unk_3; i++) {
        void* resource = func_00108120(D_0040F4C4, self->unk_5844->unk_14[i]);
        self->unk_5800[current++] = resource;
    }
    for (i = 0; i < self->unk_5844->unk_4; i++) {
        void* resource = func_00108120(D_0040F4C4, self->unk_5844->unk_18[i].unk_8);
        self->unk_5800[current++] = resource;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126710);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126978);
#ifdef NON_MATCHING
// Unmatched: inline catalog search, boolean setup and saved-register lifetimes differ.
void func_00126980(Recovered_SpawnPool* self, s32 kind, u8 index, s32 arg3, s128 position, s128 direction) {
    s32 token;
    s32 created = func_0025CDA0(D_0040F4CC, &token, 2);
    s32 capacity = 0;
    Recovered_SpawnSlot* slot = func_00127550(self);
    if (slot) {
        u8 offset = 0;
        s32 selected;
        switch (kind) {
            case 4: offset += self->unk_5844->unk_3;
            case 3: offset += self->unk_5844->unk_2;
            case 0: offset += self->unk_5844->unk_1;
            case 1: offset += self->unk_5844->unk_0;
        }
        selected = offset + index;
        if (kind == 2) {
            s8 definitionIndex = FindCatalogItem(self->unk_5844->unk_8[index].unk_0);
            capacity = func_0015D248(D_0040F4E0, definitionIndex, 0)->unk_60;
        }
        func_0014EF58(slot, kind, index, self->unk_5800[(u8)selected], arg3, capacity, 7, self->unk_5850);
        func_00129108(D_0040F4D0, slot, created, created != 0, token);
        if (created) {
            func_0025D860(slot->unk_B4, position);
            func_0025D910(slot->unk_B4, direction);
            slot->unk_B4->unk_34->unk_18 = 13;
        } else
            slot->unk_155 = 1;
    } else if (created)
        func_0025CE28(D_0040F4CC);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126980);
#endif
#ifdef NON_MATCHING
// Unmatched: selected-index/result registers and activation-flag materialization differ (22 instructions).
void func_00126BC8(Recovered_SpawnPool* self, s8 catalogIndex, s32 arg2, s128 position, s128 direction, s16 capacity) {
    u8 selected = 0;
    u8 i;
    s32 token;
    s32 created;
    Recovered_SpawnSlot* slot;
    for (i = 0; i < self->unk_5844->unk_0; i++) {
        if (catalogIndex == self->unk_5844->unk_8[i].unk_10) {
            selected = i;
            break;
        }
    }
    created = func_0025CDA0(D_0040F4CC, &token, 2);
    func_001276B8(self, selected);
    slot = func_00127550(self);
    if (slot) {
        u32 attach = 0;
        func_0014EF58(slot, 2, selected, self->unk_5800[selected], arg2, capacity, 7, self->unk_5850);
        attach = created ? 1 : 0;
        func_00129108(D_0040F4D0, slot, created, attach, token);
        if (created) {
            func_0025D860(slot->unk_B4, position);
            func_0025D910(slot->unk_B4, direction);
            slot->unk_B4->unk_34->unk_18 = 13;
        } else
            slot->unk_155 = 1;
    } else if (created)
        func_0025CE28(D_0040F4CC);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126BC8);
#endif
#ifdef NON_MATCHING
// Unmatched: the pool base is captured in a different register (6 instructions).
void func_00126D78(Recovered_SlotPool* self, Recovered_PoolSlot* slot, s32 notify) {
    if (slot->unk_152 & 8) {
        func_001F2958(D_0040F51C, 0, slot->unk_140, slot->unk_148, 0);
        slot->unk_154 = 1;
    } else {
        u8* states = self->unk_5804;
        Recovered_PoolSlot* current = self->unk_0;
        s8 i = 0;
        do {
            if (current == slot) {
                states[i] = 0;
                if (notify) func_001F2958(D_0040F51C, 0, current->unk_140, current->unk_148, 0);
                current->unk_154 = 1;
                break;
            }
            current++;
            i++;
        } while (i < 64);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126D78);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126E48);
#ifdef NON_MATCHING
// Unmatched: dispatch and iterator setup use different registers (7 instructions).
void func_00126E50(Recovered_SlotPool* self) {
    s8 i;
    for (i = 0; i < 64; i++) {
        Recovered_PoolSlot* slot = &self->unk_0[i];
        if (self->unk_5804[i] == 1 && (slot->unk_152 & 4)) {
            func_00129240(D_0040F4D0, slot, 0);
            slot->unk_10->unk_24((u8*)slot + slot->unk_10->unk_20);
            self->unk_5804[i] = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126E50);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126F08);
u32 func_00126F10(Recovered_SlotPool* self, s32 value) {
    u32 result = 0;
    u8 i;
    for (i = 0; i < self->unk_5844->unk_1; i++) {
        Recovered_PoolChoice* choices = self->unk_5844->unk_C;
        if (value == choices[i].unk_0) {
            result = i;
            break;
        }
    }
    return result;
}
#ifdef NON_MATCHING
// Unmatched: inventory and catalog address loads are scheduled differently (7 instructions).
s32 func_00126F80(void* self, Recovered_PoolSlot* slot) {
    if (slot->unk_140 == 1) {
        Recovered_InventoryQuery* inventory = (Recovered_InventoryQuery*)((u8*)D_0040F4D0 + 0x2B0);
        s32 kind = ((Recovered_WeaponChoice*)D_0040F4E4->unk_5844->unk_C)[slot->unk_148].unk_0;
        BkWeaponDefinitionPS2* definition = func_0015D228(D_0040F4E0, inventory->unk_24->weaponId);
        if (kind == 7 && !func_00155198(&inventory->inventory)) return 1;
        if (definition->reserveIndex == kind && !func_001580E0(inventory->unk_24)) {
            if (!func_00155178(&inventory->inventory, kind, (u8)definition->capacity)) return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00126F80);
#endif
void func_00127060(Recovered_BindingPool* self) {
    s8 i;
    for (i = 0; i < self->unk_5844->unk_0; i++) {
        self->unk_5844->unk_8[i].unk_10 = FindCatalogItem(self->unk_5844->unk_8[i].unk_0);
    }
}
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
void func_0012F1B8(Recovered_PairedBank* self) {
    s8 next = (self->unk_C + 1) % 2;
    if (self->unk_A[next]) {
        self->unk_0[next] = NULL;
        self->unk_8[next] = 0;
    }
}
#ifdef NON_MATCHING
// Unmatched: count-view capture and loop setup scheduling differ (15 instructions).
void func_0012F208(Recovered_PairedBank* self, u64 id, s128 value) {
    if (self->unk_8[self->unk_C] > 0) {
        s8* counts = self->unk_8;
        s8 i = 0;
        do {
            if (func_00130640(&((Recovered_QuadRecord*)self->unk_0[self->unk_C])[i], id, value)) break;
            i++;
        } while (i < counts[self->unk_C]);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0012F208);
#endif
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
#ifdef NON_MATCHING
// Unmatched: table address lifetime, stores and return joins differ (18 instructions).
s32 func_001306D0(Recovered_RequestState* self, void* arg1, s8 index) {
    if (!self->unk_102) {
        func_0013EC38(self, arg1);
        self->unk_102 = 1;
        self->unk_B0 = ((Recovered_RequestEntry*)((u8*)D_0040F0E0 + 0x21060))[index].unk_0;
        self->unk_100 = index;
        return 1;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001306D0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00131EF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00132188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00132610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001327F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001334E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00133BA0);
void func_00133E60(Recovered_ObserverArray* self, s32 kind) {
    void** cursor = self->unk_25C;
    s32 count = 7;
    do {
        void* observer = *cursor++;
        if (observer) func_00142F80(observer, kind, self->unk_2D0);
        count--;
    } while (count >= 0);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135580);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135A38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00135AC0);
s32 func_00135B60(Recovered_IndirectView* self) {
    if (self->unk_328 != NULL) return *self->unk_328;
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001368F0);
#ifdef NON_MATCHING
// Unmatched: mask/payload iterator strength reduction and saved-register allocation differ.
void func_00136BD0(Recovered_MaskRender* self, Recovered_MaskOwner* source, s32 mask, s32 flag, s128* transform) {
    Recovered_MaskInputs* inputs = (Recovered_MaskInputs*)source;
    s32 i;
    if (transform == NULL) transform = self->unk_70;
    func_001B0740(D_0040F4C0 + 0xCBE0, self, transform);
    func_00136D60((Recovered_CombinedMask*)self, source, mask);
    for (i = 0; i < inputs->unk_24; i++) {
        if (self->unk_370 & (1 << i)) {
            Recovered_MaskPair* pair = (Recovered_MaskPair*)((u8*)inputs->unk_20 + i * 6);
            Recovered_MaskPayload* payload = &inputs->unk_1C[i];
            u8* left = self->unk_354 + pair->unk_0;
            u8* right = self->unk_358 + pair->unk_2;
            u8 kind = *left;
            if ((u32)(kind - 5) < 3) {
                func_001AF738(D_0040F4C0 + 0x14, payload, left, right, self->unk_2D0, transform, flag ^ 1,
                              (s8)kind != 7, 0.0f);
            } else {
                func_001AF738(D_0040F4C0 + 0x14, payload, left, right, NULL, transform, flag ^ 1, (s8)kind != 4, 0.0f);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00136BD0);
#endif
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
#ifdef NON_MATCHING
// Unmatched: selection-pool address is computed in the saved register rather than copied from the receiver.
s32 func_001386C8(Recovered_SelectionOwner* self) {
    if ((u8)SelectionBlocked((Recovered_SelectionGate*)(D_0040F4C4 + 0xA00))) return 0;
    if (!func_00143700(D_0040F540)) return 0;
    {
        Recovered_SelectionActor* actor = self->unk_90;
        Recovered_SelectionPool** marker = &actor->member.pool;
        Recovered_SelectionPool* pool = &self->unk_7990[0];
        s32 count;
        func_001397F8(pool);
        count = 31;
        func_001397F8(&self->unk_7990[1]);
        func_001397F8(&self->unk_7990[2]);
        func_001397F8(&self->unk_7990[3]);
        do {
            *marker = NULL;
            func_00139838(pool, &actor->member);
            actor++;
            count--;
            marker = (Recovered_SelectionPool**)((u8*)marker + 0x3C0);
        } while (count >= 0);
        self->unk_8520 = 3;
        self->unk_8514 = 1;
        self->unk_851C = 0;
        return 1;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001386C8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001387C8);
void func_00139B68(Recovered_ArrayView* self) {
    s32 i;
    self->unk_8 = 0;
    for (i = 0; i < self->unk_4; i++) self->unk_C[i] = NULL;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00139BA8);
void func_0013C868(Recovered_ObserverOwner* self, s32 index) {
    Recovered_ObserverSetupEntry* entry = (Recovered_ObserverSetupEntry*)(D_0040F50C + 0x470 + index * 0x240);
    s32* source = entry->unk_30;
    void** destination = self->unk_25C;
    s32 count = 7;
    s32 first = func_00138C68(D_0040F514);
    func_00138338(self->unk_328, func_00138C50(D_0040F514));
    self->unk_328->unk_38 = first;
    self->unk_3AD = 0;
    do {
        if (*destination) func_00142ED8(*destination, *source, 0);
        source++;
        count--;
        destination++;
    } while (count >= 0);
    func_00137320(self);
    func_00136B50(self);
    self->unk_330 = entry;
}
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
void func_0013CF38(Recovered_ManagedSlot* self) {
    func_00181030((u8*)self + 0xEC0, self);
    func_00185D08((u8*)self + 0x90, self);
    func_00180F10((u8*)self + 0x140, self);
    func_00188B90((u8*)self + 0x150, self);
    func_00187E08((u8*)self + 0x290, self);
    func_0017C9F0((u8*)self + 0x650, self);
    func_00183910((u8*)self + 0x6F0, self);
    func_00181FF0((u8*)self + 0x810, self);
    func_001804D0((u8*)self + 0xB30, self);
    func_0018AD80((u8*)self + 0xCC0, self);
    func_0018CEE0((u8*)self + 0xD10, self);
    func_00181F20((u8*)self + 0xC80, self);
    func_0018D978((u8*)self + 0xC94, self);
    func_0018C178((u8*)self + 0x1DA0, self);
    func_001831D8((u8*)self + 0x1EB0, self);
    self->freeNext = NULL;
    *(s32*)self->unk_1EF4 = -1;
    func_0013EC10(self, 1);
    func_00176EE0(self->unk_1FCC);
    func_0017B260((u8*)self + 0x1F60, self);
    func_0016AB58((u8*)self + 0x1F90, 8);
}
s32 func_0013D048(Recovered_ManagedSlot* self, void* owner, Recovered_SlotConfiguration* config) {
    void* history;
    void* goals;
    void* actions;
    void* configuration = (u8*)self + 0xC94;
    func_0013EC38(self, owner);
    func_0018D9A0(configuration, config->unk_40, config->unk_44, config->unk_34);
    if (config->unk_40 == 0x27) func_0018D9F0(configuration, config->unk_48->unk_4->unk_60);
    func_00185D10((u8*)self + 0x90);
    history = self->events;
    goals = (u8*)self + 0xD10;
    func_00180F18((u8*)self + 0x140);
    actions = (u8*)self + 0xEC0;
    func_00188B98(&self->records);
    func_00187EC8((u8*)self + 0x290);
    func_0017C9F8((u8*)self + 0x650, configuration);
    func_00183918(history);
    func_00182078((u8*)self + 0x810);
    func_001804F8((u8*)self + 0xB30, config->unk_10, 30.0f);
    func_0018AD88((u8*)self + 0xCC0);
    func_00181F28((u8*)self + 0xC80);
    func_0018CFD8(goals);
    func_0018C1E0((u8*)self + 0x1DA0);
    func_001831E0((u8*)self + 0x1EB0);
    func_00181348(actions);
    M2C_FIELD(self, u8*, 0x1FC0) = 0;
    M2C_FIELD(self, u32*, 0x1F98) = 0;
    M2C_FIELD(self, u32*, 0x1F9C) = 0;
    M2C_FIELD(self, u8*, 0x1FC1) = 0;
    self->unk_1FC4 = 0;
    self->unk_1FC8 = 0;
    func_00173FE8((u16*)((u8*)self + 0x1EF8));
    func_00173FE8((u16*)((u8*)self + 0x1EFA));
    func_0016ABA0((u8*)self + 0x1F90);
    if (config->unk_50) func_0018D410(goals, config->unk_50);
    func_00181AB0(actions, func_0018DCE0(configuration));
    func_001856B0(history, config->unk_58 ^ 1);
    self->freeNext = NULL;
    return 1;
}
void func_0013D7A0(Recovered_ManagedSlot* self, s32 id) {
    Recovered_ActorRecords* records = &self->records;
    if (records->actorMask & (1U << id)) func_00189B90(records, id);
    func_00188A18((u8*)self + 0x290, id);
    func_00183BC0(self->events, id);
    func_001815D8((u8*)self + 0xEC0, id);
    if (func_00178F18(func_00179258((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), id))) {
        Recovered_ManagedActor* actor = func_00179258((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), id)->actor;
        if (func_00135550(actor) && func_00135550(actor)->unk_80 == 1) {
            Recovered_ManagedSlot* other = func_00135550(actor);
            func_00174018((u16*)((u8*)self + 0x1EF8), other);
            func_00174018((u16*)((u8*)self + 0x1EFA), other);
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D8D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_0013D9A0);
extern void func_00142AB8(Recovered_SmallArray*, s32, s32, s32, s32, u8, u64);

/* Preset cases retain the native catalog order and all 64 bits of each ID. */
s32 func_001415A8(Recovered_SmallArray* self, s32 preset) {
    switch (preset) {
        case 36:
            func_00142AB8(self, 2, 1, 0, 0, 0U, 0x544614B7182C0000UL);
            func_00142AB8(self, 2, 1, 0, 0, 0U, 0x5446135779860000UL);
            func_00142AB8(self, 1, 1, 0, 0, 0U, 0x5446143910FD0000UL);
            func_00142AB8(self, 2, 2, 0, 0, 0U, 0x5446151EBC278000UL);
            func_00142AB8(self, 2, 2, 0, 0, 0U, 0x544614FCFFAE0000UL);
            func_00142AB8(self, 3, 3, 0, 0, 0U, 0x5446152380DB8000UL);
            func_00142AB8(self, 3, 3, 0, 0, 0U, 0x544614411FFA0000UL);
            func_00142AB8(self, 3, 3, 0, 0, 0U, 0x5446152331830000UL);
            func_00142AB8(self, 4, 3, 0, 0, 0U, 0x544614A4487F8000UL);
            func_00142AB8(self, 4, 4, 0, 0, 0U, 0x5446127AD7970000UL);
            func_00142AB8(self, 4, 4, 0, 0, 0U, 0x5446127297C60000UL);
            func_00142AB8(self, 4, 4, 0, 0, 0U, 0x5446142A5B1E8000UL);
            func_00142AB8(self, 3, 3, 0, 0, 0U, 0x54461388E61C8000UL);
            func_00142AB8(self, 1, 1, 0, 0, 0U, 0x54461524B8230000UL);
            func_00142AB8(self, 4, 4, 0, 0, 0, 0x5446129C3E9D8000UL);
            break;
        case 37:
            func_00142AB8(self, 3, 2, 1, 1, 0U, 0x544614B7182C0000UL);
            func_00142AB8(self, 3, 2, 1, 1, 0U, 0x5446135779860000UL);
            func_00142AB8(self, 1, 1, 1, 1, 0U, 0x5446143910FD0000UL);
            func_00142AB8(self, 3, 3, 1, 1, 0U, 0x5446151EBC278000UL);
            func_00142AB8(self, 3, 3, 1, 1, 0U, 0x544614FCFFAE0000UL);
            func_00142AB8(self, 5, 5, 1, 1, 0U, 0x5446152380DB8000UL);
            func_00142AB8(self, 5, 5, 1, 1, 0U, 0x544614411FFA0000UL);
            func_00142AB8(self, 5, 5, 1, 1, 0U, 0x5446152331830000UL);
            func_00142AB8(self, 7, 7, 1, 1, 0U, 0x544614A4487F8000UL);
            func_00142AB8(self, 9, 9, 1, 1, 0U, 0x5446127AD7970000UL);
            func_00142AB8(self, 9, 9, 1, 1, 0U, 0x5446127297C60000UL);
            func_00142AB8(self, 9, 9, 1, 1, 0U, 0x5446142A5B1E8000UL);
            func_00142AB8(self, 6, 6, 1, 1, 0U, 0x54461388E61C8000UL);
            func_00142AB8(self, 1, 1, 1, 1, 0U, 0x54461524B8230000UL);
            func_00142AB8(self, 9, 9, 1, 1, 0, 0x5446129C3E9D8000UL);
            break;
        case 38:
            func_00142AB8(self, 8, 8, 1, 0, 1U, 0x544614B7182C0000UL);
            func_00142AB8(self, 7, 7, 1, 0, 1U, 0x5446135779860000UL);
            func_00142AB8(self, 2, 2, 1, 0, 0U, 0x5446143910FD0000UL);
            func_00142AB8(self, 0xB, 0xB, 1, 0, 2U, 0x5446151EBC278000UL);
            func_00142AB8(self, 0xD, 0xD, 1, 0, 2U, 0x544614FCFFAE0000UL);
            func_00142AB8(self, 0x1E, 0x1E, 1, 0, 2U, 0x5446152380DB8000UL);
            func_00142AB8(self, 0x1E, 0x1E, 1, 0, 2U, 0x544614411FFA0000UL);
            func_00142AB8(self, 0x1E, 0x1E, 1, 0, 2U, 0x5446152331830000UL);
            func_00142AB8(self, 0x1E, 0x1E, 1, 0, 2U, 0x544614A4487F8000UL);
            func_00142AB8(self, 0x1E, 0x1E, 1, 0, 2U, 0x5446127AD7970000UL);
            func_00142AB8(self, 0x1E, 0x1E, 1, 0, 2U, 0x5446127297C60000UL);
            func_00142AB8(self, 0x1E, 0x1E, 1, 0, 2U, 0x5446142A5B1E8000UL);
            func_00142AB8(self, 0x10, 0x10, 1, 0, 2U, 0x54461388E61C8000UL);
            func_00142AB8(self, 1, 1, 1, 0, 0U, 0x54461524B8230000UL);
            func_00142AB8(self, 30, 30, 1, 0, 0, 0x5446129C3E9D8000UL);
            break;
        case 39:
            func_00142AB8(self, 2, 2, 0, 0, 0U, 0x544614B7182C0000UL);
            func_00142AB8(self, 2, 2, 0, 0, 0U, 0x5446135779860000UL);
            func_00142AB8(self, 1, 1, 0, 0, 0U, 0x5446143910FD0000UL);
            func_00142AB8(self, 3, 3, 0, 0, 0U, 0x5446151EBC278000UL);
            func_00142AB8(self, 3, 3, 0, 0, 0U, 0x544614FCFFAE0000UL);
            func_00142AB8(self, 5, 5, 0, 0, 0U, 0x5446152380DB8000UL);
            func_00142AB8(self, 7, 7, 0, 0, 0U, 0x544614411FFA0000UL);
            func_00142AB8(self, 5, 5, 0, 0, 0U, 0x5446152331830000UL);
            func_00142AB8(self, 5, 5, 0, 0, 0U, 0x544614A4487F8000UL);
            func_00142AB8(self, 9, 9, 0, 0, 0U, 0x5446127AD7970000UL);
            func_00142AB8(self, 9, 9, 0, 0, 0U, 0x5446127297C60000UL);
            func_00142AB8(self, 9, 9, 0, 0, 0U, 0x5446142A5B1E8000UL);
            func_00142AB8(self, 6, 6, 0, 0, 0U, 0x54461388E61C8000UL);
            func_00142AB8(self, 1, 1, 0, 0, 0U, 0x54461524B8230000UL);
            func_00142AB8(self, 9, 9, 0, 0, 0, 0x5446129C3E9D8000UL);
            break;
        case 40:
            func_00142AB8(self, 0x10, 1, 1, 1, 2U, 0x544614B7182C0000UL);
            func_00142AB8(self, 0xE, 1, 1, 1, 2U, 0x5446135779860000UL);
            func_00142AB8(self, 3, 1, 1, 1, 2U, 0x5446143910FD0000UL);
            func_00142AB8(self, 0x16, 1, 1, 1, 4U, 0x5446151EBC278000UL);
            func_00142AB8(self, 0x1A, 1, 1, 1, 4U, 0x544614FCFFAE0000UL);
            func_00142AB8(self, 0x3C, 1, 1, 1, 4U, 0x5446152380DB8000UL);
            func_00142AB8(self, 0x3C, 1, 1, 1, 4U, 0x544614411FFA0000UL);
            func_00142AB8(self, 0x3C, 1, 1, 1, 4U, 0x5446152331830000UL);
            func_00142AB8(self, 0x3C, 2, 1, 1, 6U, 0x544614A4487F8000UL);
            func_00142AB8(self, 0x3C, 2, 1, 1, 6U, 0x5446127AD7970000UL);
            func_00142AB8(self, 0x3C, 2, 1, 1, 6U, 0x5446127297C60000UL);
            func_00142AB8(self, 0x3C, 1, 1, 1, 5U, 0x5446142A5B1E8000UL);
            func_00142AB8(self, 0x20, 1, 1, 1, 4U, 0x54461388E61C8000UL);
            func_00142AB8(self, 1, 1, 1, 1, 0U, 0x54461524B8230000UL);
            func_00142AB8(self, 60, 2, 1, 1, 4, 0x5446129C3E9D8000UL);
            break;
        case 41:
            func_00142AB8(self, 3, 2, 0, 0, 0U, 0x544614B7182C0000UL);
            func_00142AB8(self, 2, 2, 0, 0, 0U, 0x5446135779860000UL);
            func_00142AB8(self, 1, 1, 0, 0, 0U, 0x5446143910FD0000UL);
            func_00142AB8(self, 5, 5, 0, 0, 0U, 0x5446151EBC278000UL);
            func_00142AB8(self, 7, 7, 0, 0, 0U, 0x544614FCFFAE0000UL);
            func_00142AB8(self, 0xE, 0xE, 0, 0, 0U, 0x5446152380DB8000UL);
            func_00142AB8(self, 0xE, 0xE, 0, 0, 0U, 0x544614411FFA0000UL);
            func_00142AB8(self, 0xE, 0xE, 0, 0, 0U, 0x5446152331830000UL);
            func_00142AB8(self, 0xE, 0xE, 0, 0, 0U, 0x544614A4487F8000UL);
            func_00142AB8(self, 0xE, 0xE, 0, 0, 0U, 0x5446127AD7970000UL);
            func_00142AB8(self, 0xE, 0xE, 0, 0, 0U, 0x5446127297C60000UL);
            func_00142AB8(self, 0xE, 0xE, 0, 0, 0U, 0x5446142A5B1E8000UL);
            func_00142AB8(self, 0xA, 0xA, 0, 0, 0U, 0x54461388E61C8000UL);
            func_00142AB8(self, 1, 1, 0, 0, 0U, 0x54461524B8230000UL);
            func_00142AB8(self, 14, 14, 0, 0, 0, 0x5446129C3E9D8000UL);
            break;
        case 42:
            func_00142AB8(self, 5, 5, 1, 1, 2U, 0x544614B7182C0000UL);
            func_00142AB8(self, 5, 5, 1, 1, 2U, 0x5446135779860000UL);
            func_00142AB8(self, 2, 2, 1, 1, 0U, 0x5446143910FD0000UL);
            func_00142AB8(self, 0xA, 0xA, 1, 1, 6U, 0x5446151EBC278000UL);
            func_00142AB8(self, 0xD, 0xD, 1, 1, 6U, 0x544614FCFFAE0000UL);
            func_00142AB8(self, 0x14, 0x14, 1, 1, 6U, 0x5446152380DB8000UL);
            func_00142AB8(self, 0x14, 0x14, 1, 1, 6U, 0x544614411FFA0000UL);
            func_00142AB8(self, 0x14, 0x14, 1, 1, 6U, 0x5446152331830000UL);
            func_00142AB8(self, 0x14, 0x14, 1, 1, 6U, 0x544614A4487F8000UL);
            func_00142AB8(self, 0x14, 0x14, 1, 1, 6U, 0x5446127AD7970000UL);
            func_00142AB8(self, 0x14, 0x14, 1, 1, 6U, 0x5446127297C60000UL);
            func_00142AB8(self, 0x14, 0x14, 1, 1, 6U, 0x5446142A5B1E8000UL);
            func_00142AB8(self, 0xF, 0xF, 1, 1, 6U, 0x54461388E61C8000UL);
            func_00142AB8(self, 1, 1, 1, 1, 0U, 0x54461524B8230000UL);
            func_00142AB8(self, 0x14, 0x14, 1, 1, 0U, 0x5446129C3E9D8000UL);
            break;
    }
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: inline search joins and destination address lifetimes differ (19 instructions).
void func_00142AB8(Recovered_SmallArray* self, s32 width, s32 height, s32 arg3, s32 arg4, u8 arg5, u64 id) {
    f32 x = 1.02f / width;
    f32 y = 1.02f / height;
    SetDimensions(self, FindCatalogItem(id), x, y, arg3, arg4, arg5);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00142AB8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00142B90);
void func_00142E30(Recovered_SmallArray* self, s8 count) {
    self->unk_4 = count;
    self->unk_0 = func_00107D20(count * 12);
    func_0035C6EC(self->unk_0, 0, self->unk_4 * 12);
}
#ifdef NON_MATCHING
// Unmatched: scalar maximum does not lower to the native pmaxw/pextlw pair.
void func_00143590(Recovered_ThreeSlots* self, void* value, u8 index) {
    u32 selected = index == 0xFF ? self->unk_19 : index;
    if (selected < 3) self->unk_C[selected] = value;
    self->unk_1A = self->unk_1A > selected + 1 ? self->unk_1A : selected + 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00143590);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_001448C8);

s32 func_00144E00(s32 arg0) {
    func_001B6CF8(D_0040F4D8 + 0x66290, arg0, 0);
    func_00149AC8(arg0);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00144E50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_10f700_114168", func_00144E58);
