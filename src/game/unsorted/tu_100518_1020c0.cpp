#include "include_asm.h"
#include "ps2/prelude.h"

#ifdef NON_MATCHING

struct Recovered_FrameState;
struct Recovered_FrontendControllerScreen;
struct Recovered_FrontendLoadState;
struct Recovered_FrontendMenuState;
struct Recovered_FrontendNamedArchiveManager;
struct Recovered_FrontendProfilePool;
struct Recovered_FrontendSaveDialog;
struct Recovered_InventoryManager;
struct Recovered_PairedBank;
struct Recovered_ScratchpadBuffers;
struct Recovered_SlotPool;
struct Recovered_Vtable_003DB490;
struct Recovered_Vtable_003DB598;

extern "C" void* D_0040F548;
extern "C" void* func_00107CF8(u32);
extern "C" void* func_003826A8(void*);
extern "C" s8* D_0040F4C0;
extern "C" void* D_0040F4D4;
extern "C" void* func_00382838(void*);
extern "C" void* D_0040F50C;
extern "C" void* func_00382D60(void*);
extern "C" s32 D_0040F4D8;
extern "C" void* func_003828D8(void*);
extern "C" M2C_UNK D_003DB3B8;
extern "C" M2C_UNK D_003E2580;
extern "C" M2C_UNK D_003E25B0;
extern "C" void* D_0040F0E4;
extern "C" M2C_UNK D_003E2508;
extern "C" Recovered_FrontendControllerScreen* D_0040F0E8;
extern "C" void* D_0040F4CC;
extern "C" void* D_0040F4BC;
extern "C" void* func_00382500(void*);
extern "C" M2C_UNK D_003DCC60;
extern "C" void* func_00382740(void*);
extern "C" void* D_0040F514;
extern "C" Recovered_FrontendNamedArchiveManager* D_0040F4C4;
extern "C" void* func_00382358(void*);
extern "C" void* D_0040F510;
extern "C" M2C_UNK D_003DB640;
extern "C" void* func_00382BF0(void*);
extern "C" void* D_0040F508;
extern "C" void* D_0040F518;
extern "C" void* D_0040F51C;
extern "C" void* D_0040F4F4;
extern "C" void* D_0040F4D0;
extern "C" void* func_00382778(void*);
extern "C" void* D_0040F4F8;
extern "C" Recovered_InventoryManager* D_0040F4E0;
extern "C" s32* D_0040F520;
extern "C" s32* func_00382E78(s32*);
extern "C" s8** D_0040F4DC;
extern "C" void* D_0040F4E8;
extern "C" void* D_0040F524;
extern "C" void* D_0040F528;
extern "C" void* D_0040F52C;
extern "C" u8 D_003DCB38[];
extern "C" Recovered_SlotPool* D_0040F4E4;
extern "C" s8* D_0040F544;
extern "C" void* func_00382EE0(void*);
extern "C" M2C_UNK D_003DC2A8;
extern "C" void* D_0040F530;
extern "C" void* D_0040F504;
extern "C" Recovered_PairedBank* D_0040F534;
extern "C" Recovered_PairedBank* D_0040F538;
extern "C" Recovered_FrontendProfilePool* D_0040F53C;
extern "C" void* D_0040F4EC;
extern "C" s32 D_0040F4F0;
extern "C" Recovered_ScratchpadBuffers* D_0040F4C8;
extern "C" void* D_0040F540;
extern "C" s32 func_001250D0(void*);
extern "C" s32 func_00108A40(void*);
extern "C" s8 D_0040EAD8;
extern "C" s32 func_0027F730(s32);
extern "C" s32 func_0027F790(Recovered_FrameState*);
extern "C" void func_00107D58(void*);
extern "C" s32 func_001C4F30(void*);
extern "C" s32 func_0020A058(void*);
extern "C" s32 func_001AB780(void*);
extern "C" s32 func_001B19E8(s32);
extern "C" void func_00107010(void*);
extern "C" u32 func_00259DA8(void*);
extern "C" s32 func_0010F758(void*);
extern "C" s32 func_001384C8(void*);
extern "C" s32 func_00107E30(void*);
extern "C" s32 func_001D5828(void*);
extern "C" s32 func_0016D7F0(void*);
extern "C" void func_0011A0A8(void*);
extern "C" s32 func_001F21E8(void*);
extern "C" void func_001F27F0(void*);
extern "C" void func_00165CC0(void*);
extern "C" void func_0015C970(Recovered_InventoryManager*);
extern "C" s32* func_00121DE8(void*);
extern "C" void func_00122708(void*);
extern "C" s32 func_002050B8(void*);
// This native call supplies a receiver to an otherwise empty producer.
// Keep the explicit ABI view without changing the parent session's producer.
extern "C" void func_0016ADE0_WithReceiver(void*) __asm__("func_0016ADE0");
extern "C" void func_0014D908(void*);
extern "C" void func_00126200(Recovered_SlotPool*);
extern "C" void func_0011A130(void*);
extern "C" void func_0011BF20(void*);
extern "C" void func_0012F388(Recovered_PairedBank*);
extern "C" void func_0012EEE8(Recovered_PairedBank*);
extern "C" s32 func_0010F188(Recovered_FrontendProfilePool*);
extern "C" void func_0010F258(void*);
extern "C" s32 func_0010A870(Recovered_FrontendSaveDialog*);
extern "C" void func_001C2A48(Recovered_ScratchpadBuffers*);
extern "C" void func_00143688(void*);
extern "C" s32 func_0027C0D8(void*, s32);
extern "C" void* D_0040F54C;
extern "C" void* func_00107D20(u32);
extern "C" void func_00107E00(void*, s32);
extern "C" void* func_001282E0(void*);
extern "C" void func_00105848(s32*);
extern "C" void func_001041A8(Recovered_FrontendMenuState*);
extern "C" void func_00105308(Recovered_Vtable_003DB598*);
extern "C" void func_00106008(void*);
extern "C" s32 func_00106068(Recovered_FrontendLoadState*);
extern "C" void func_00106830(Recovered_Vtable_003DB490*);
extern "C" s32 func_00107A88(s32);
extern "C" M2C_UNK D_0040F0F0;

// Native constructor views; original identities and unaccessed fields are UNVERIFIED.
// Array extents and strides follow existing actor, physics and inventory consumers.
template <unsigned Size> struct NativeEmptyRecord {
    u8 unknown[Size];
    NativeEmptyRecord() {}
} __attribute__((aligned(16)));
struct RenderEntry {
    u8 unknown0[0x28];
    void* table;
    u8 unknown2C[0x14];
    RenderEntry() { table = &D_003E25B0; }
};
struct RenderRootPrefix {
    u8 unknown0[0xA4];
    void* table;
    RenderRootPrefix() { table = &D_003DB3B8; }
};
struct RenderSubPrefix {
    void* table;
    u8 unknown4[0xC];
    RenderSubPrefix() { table = &D_003E2580; }
};
struct RenderSub : RenderSubPrefix {
    RenderEntry entries[1];
    RenderSub() {}
};
struct RenderRoot : RenderRootPrefix {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    u8 unknownA8[0x188];
    RenderSub component;
    u8 unknown280[0x10040];
    RenderRoot() {}
};
struct FrontendInputSample {
    u8 unknown0[8];
    void* table;
    u8 unknownC[0xE4];
    FrontendInputSample() { table = &D_003E2508; }
};
struct FrontendInput {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    u8 unknown0[0x2C0];
    FrontendInputSample samples[2];
    u8 unknown4A0[0x320];
    FrontendInput() {}
};
struct GamePhysicsPool {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    u8 unknown0[0x50];
    NativeEmptyRecord<0x50> owners[110];
    u8 occupied[110], unknown231E[2];
    NativeEmptyRecord<0x50> temporary[20];
    u8 temporaryOccupied[20], unknown2974[12];
    NativeEmptyRecord<0x30> records[520];
    u8 unknown8B00[0x50];
    GamePhysicsPool() {}
};
struct SelectorActor {
    u8 unknown[0x3C0];
    SelectorActor() __asm__("func_00382740");
};
struct SelectorPrefix {
    u8 unknown0[0x84];
    void* table;
    u8 unknown88[8];
    SelectorPrefix() { table = &D_003DCC60; }
};
struct SelectorOwner : SelectorPrefix {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    SelectorActor actors[32];
    u8 unknown7890[0xCA0];
    SelectorOwner() {}
};
struct GroupedController {
    u8 unknown[0x4F0];
    GroupedController() __asm__("func_00382BF0");
};
struct GroupedControllers {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    u8 unknown0[0x20];
    GroupedController controllers[8];
    GroupedControllers() {}
};
struct OverlayChannel {
    u8 unknown[0xA8];
    OverlayChannel() {}
};
struct OverlayChannels {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    OverlayChannel channels[2];
    u8 unknown150[0xF0];
    OverlayChannels() {}
};
struct WeaponInventory {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    u8 unknown0[0x20];
    NativeEmptyRecord<0x30> delayed[36];
    NativeEmptyRecord<0x90> moving[16];
    WeaponInventory() {}
};
struct ObjectActorEntry {
    u8 unknown0[0x10];
    void* table;
    u8 unknown14[0x14C];
    ObjectActorEntry() { table = &D_003DCB38; }
};
struct ObjectActors {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    ObjectActorEntry actors[64];
    u8 unknown5800[0x60];
    ObjectActors() {}
};
struct CameraRecord {
    u8 unknown0[0x10];
    void* table;
    u8 unknown14[0x10C];
    CameraRecord() { table = &D_003DC2A8; }
};
struct CameraRecords {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    u8 unknown0[0x20];
    CameraRecord records[1];
    u8 unknown140[0x60];
    CameraRecords() {}
};
struct CameraSingleton {
    static void* operator new(u32 bytes) { return func_00107CF8(bytes); }
    u8 unknown0[0x40];
    void* table;
    u8 unknown44[0x12C];
    CameraSingleton() { table = &D_003DC2A8; }
};
typedef char PhysicsCtorSize[sizeof(GamePhysicsPool) == 0x8B50 ? 1 : -1];
typedef char RenderCtorSize[sizeof(RenderRoot) == 0x102C0 ? 1 : -1];
typedef char InputCtorSize[sizeof(FrontendInput) == 0x7C0 ? 1 : -1];
typedef char SelectorCtorSize[sizeof(SelectorOwner) == 0x8530 ? 1 : -1];
typedef char GroupsCtorSize[sizeof(GroupedControllers) == 0x27A0 ? 1 : -1];
typedef char OverlayCtorSize[sizeof(OverlayChannels) == 0x240 ? 1 : -1];
typedef char InventoryCtorSize[sizeof(WeaponInventory) == 0xFE0 ? 1 : -1];
typedef char ActorsCtorSize[sizeof(ObjectActors) == 0x5860 ? 1 : -1];
typedef char CameraCtorSize[sizeof(CameraRecords) == 0x1A0 ? 1 : -1];
typedef char SingletonCtorSize[sizeof(CameraSingleton) == 0x170 ? 1 : -1];

// Unmatched: the video-mode byte load uses V1 instead of V0 as its address base (two operands).
extern "C" void func_001020C0(void* arg0) {
    s32* temp_17;
    s32 var_17;
    s8* temp_2_2;
    void* temp_2_12;
    void* temp_2_14;
    void* var_16_3;

    M2C_FIELD(arg0, s8*, 0x210CC) = 0;
    D_0040F548 = func_00107CF8(4U);
    temp_2_2 = (s8*)func_00107CF8(0xD600U);
    func_003826A8(temp_2_2);
    D_0040F4C0 = temp_2_2;
    D_0040F4D4 = func_00382838(func_00107CF8(0x22BF0U));
    D_0040F50C = func_00382D60(func_00107CF8(0x970U));
    D_0040F4D8 = (s32)func_003828D8(func_00107CF8(0x87400U));
    D_0040F0E4 = new RenderRoot;
    D_0040F0E8 = (Recovered_FrontendControllerScreen*)new FrontendInput;
    D_0040F4CC = new GamePhysicsPool;
    D_0040F4BC = func_00382500(func_00107CF8(0x1680U));
    D_0040F514 = new SelectorOwner;
    D_0040F4C4 = (Recovered_FrontendNamedArchiveManager*)func_00107CF8(0xE18U);
    temp_2_12 = func_00107CF8(0xCC08U);
    func_00382358(temp_2_12);
    D_0040F510 = temp_2_12;
    M2C_FIELD(temp_2_12, void**, 0xCBA0) = &D_003DB640;
    M2C_FIELD(temp_2_12, u8*, 0xCBB4) = 0;
    D_0040F508 = new GroupedControllers;
    D_0040F518 = new OverlayChannels;
    D_0040F51C = func_00107CF8(1U);
    D_0040F4F4 = func_00107CF8(0xD8U);
    D_0040F4D0 = func_00382778(func_00107CF8(0x5CB0U));
    D_0040F4F8 = func_00107CF8(0x9CU);
    D_0040F4E0 = (Recovered_InventoryManager*)new WeaponInventory;
    D_0040F520 = func_00382E78((s32*)func_00107CF8(0x3740U));
    D_0040F4DC = (s8**)func_00107CF8(0x10U);
    D_0040F4E8 = func_00107CF8(8U);
    D_0040F524 = func_00107CF8(0x1CU);
    D_0040F528 = func_00107CF8(0x140U);
    D_0040F52C = func_00107CF8(0xF0U);
    D_0040F4E4 = (Recovered_SlotPool*)new ObjectActors;
    D_0040F544 = (s8*)func_00382EE0(func_00107CF8(0x3960U));
    D_0040F530 = new CameraRecords;
    D_0040F504 = new CameraSingleton;
    D_0040F534 = (Recovered_PairedBank*)func_00107CF8(0x10U);
    D_0040F538 = (Recovered_PairedBank*)func_00107CF8(0x10U);
    D_0040F53C = (Recovered_FrontendProfilePool*)func_00107CF8(0x6B0U);
    D_0040F4EC = func_00107CF8(0x790U);
    D_0040F4F0 = (s32)func_00107CF8(0x21B8U);
    D_0040F4C8 = (Recovered_ScratchpadBuffers*)func_00107CF8(0xCU);
    D_0040F540 = func_00107CF8(0xD0U);
    func_001250D0(D_0040F548);
    func_00108A40((void*)(((s8*)arg0) + 0x2014C));
    if (D_0040EAD8 != 0) {
        func_0027F730(0x19);
    } else {
        func_0027F730(0x1E);
    }
    var_17 = 0;
    func_0027F790((Recovered_FrameState*)(((s8*)arg0) + 0x20120));
    func_00107D58(D_0040F4F8);
    func_001C4F30(D_0040F4C0);
    func_0020A058(D_0040F544);
    func_001AB780(D_0040F50C);
    func_001B19E8(D_0040F4D8);
    temp_2_14 = M2C_FIELD(D_0040F0E4, void**, 0xA4);
    M2C_FIELD(temp_2_14, void (**)(void*), 0xC)((void*)(((s8*)D_0040F0E4) + M2C_FIELD(temp_2_14, s16*, 8)));
    func_00107010(D_0040F0E8);
    func_00259DA8(D_0040F4CC);
    func_0010F758(D_0040F4BC);
    func_001384C8(D_0040F514);
    func_00107E30(D_0040F4C4);
    func_001D5828(D_0040F510);
    func_0016D7F0(D_0040F4D4);
    func_0011A0A8(D_0040F508);
    func_001F21E8(D_0040F518);
    func_001F27F0(D_0040F51C);
    func_00165CC0(D_0040F4F4);
    func_0015C970(D_0040F4E0);
    func_00121DE8(D_0040F4DC);
    func_00122708(D_0040F4E8);
    func_002050B8(D_0040F524);
    func_0016ADE0_WithReceiver(D_0040F528);
    func_0014D908(D_0040F52C);
    func_00126200(D_0040F4E4);
    func_0011A130(D_0040F530);
    func_0011BF20(D_0040F504);
    func_0012F388(D_0040F534);
    func_0012EEE8(D_0040F538);
    func_0010F188(D_0040F53C);
    func_0010F258(D_0040F4EC);
    func_0010A870((Recovered_FrontendSaveDialog*)D_0040F4F0);
    func_001C2A48(D_0040F4C8);
    func_00143688(D_0040F540);
    func_0027C0D8(arg0, 0);
    D_0040F54C = func_00107D20(0x3000U);
    var_16_3 = (void*)(((s8*)arg0) + 0x21060);
    do {
        func_00107E00(var_16_3, var_17);
        var_17 += 1;
        var_16_3 = (void*)(((s8*)var_16_3) + 0xC);
    } while (var_17 <= 0);
    func_001282E0(D_0040F4D0);
    temp_17 = (s32*)(((s8*)arg0) + 0x20210);
    func_00105848(temp_17);
    func_001041A8((Recovered_FrontendMenuState*)(((s8*)arg0) + 0x20220));
    func_00105308((Recovered_Vtable_003DB598*)(((s8*)arg0) + 0x20F78));
    func_00106008((u8*)arg0 + 0x20F90);
    func_00106068((Recovered_FrontendLoadState*)(((s8*)arg0) + 0x20FA0));
    func_00106830((Recovered_Vtable_003DB490*)(((s8*)arg0) + 0x20FD8));
    M2C_FIELD(arg0, s32**, 0x21074) = temp_17;
    M2C_FIELD(arg0, s32*, 0x21084) = 1;
    M2C_FIELD(arg0, s32*, 0x21070) = 0;
    M2C_FIELD(arg0, s8*, 0x210CA) = 0;
    M2C_FIELD(arg0, s32*, 0x21088) = 0;
    M2C_FIELD(arg0, s32*, 0x2108C) = 0;
    M2C_FIELD(arg0, s32*, 0x21090) = 0;
    M2C_FIELD(arg0, s32*, 0x21094) = 0;
    M2C_FIELD(arg0, s32*, 0x21098) = 0;
    M2C_FIELD(arg0, s32*, 0x2109C) = 0;
    M2C_FIELD(arg0, s8*, 0x210C8) = 0;
    M2C_FIELD(arg0, s8*, 0x210C9) = 0;
    M2C_FIELD(arg0, s32*, 0x210C4) = 0;
    func_00107A88((s32)&D_0040F0F0);
    M2C_FIELD(arg0, s32*, 0x21078) = 1;
    M2C_FIELD(arg0, s32*, 0x21080) = 0;
    M2C_FIELD(arg0, s8*, 0x2020C) = 0;
    M2C_FIELD(arg0, s8*, 0x2020D) = 0;
    M2C_FIELD(arg0, s32*, 0x2107C) = 0;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_100518_1020c0", func_001020C0);
#endif
