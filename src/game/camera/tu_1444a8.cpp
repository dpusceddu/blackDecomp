#include "include_asm.h"
#include "ps2/prelude.h"

#ifdef NON_MATCHING
// Unmatched: two descriptor-call argument moves exchange the branch delay slot.
// Native allocation and ABI views; original class names remain UNVERIFIED.
struct AllocationRequest {
    u32 bytes, alignment;
};
struct StorageBlock {
    void* memory;
    u32 unknown4;
};
extern "C" void* D_0040F4C4;
extern "C" u8 D_0040F0F0[], D_003D12C8[];
extern "C" void func_0014BD18(void*);
extern "C" void* func_00108120(void*, u64);
extern "C" void* func_00107D20(u32);
extern "C" void* func_00107CF8(u32);
extern "C" bool func_001AFBA8(void*);
extern "C" void func_0014CDB8(void*);
extern "C" void func_00107CC8(void*, u32);
extern "C" s32 func_00149178(void*);
extern "C" s32 func_00149CA0(void*);
extern "C" s32 func_00263908(void*, s16, void*);
extern "C" AllocationRequest* func_0032B860(AllocationRequest*, u32, u32);
extern "C" void* func_00107C98(void*, AllocationRequest*);
extern "C" void* func_0032BB28(StorageBlock*, u32, u32);
extern "C" void* func_003349C0(AllocationRequest*, s32, void*, s32);
extern "C" void* func_003349E0(StorageBlock*, u32, s32, s32);
extern "C" void* func_00334268(StorageBlock*, s32);
extern "C" void func_001AFC78(void*);
template <unsigned Size> struct ActorArraySlot {
    u8 unknown[Size];
    ActorArraySlot() {}
    static void* operator new[](u32 bytes) { return func_00107D20(bytes); }
};
static inline void ResetRequest(AllocationRequest* request, u32 size, u32 alignment) {
    request->bytes = size;
    request->alignment = alignment;
}
extern "C" void func_001444A8(void* self, void* definition, void* shared) {
    func_0014BD18(self);
    M2C_FIELD(self, void**, 0x114) = definition;
    M2C_FIELD(self, u64*, 0) = M2C_FIELD(definition, u64*, 0x48);
    M2C_FIELD(self, s32*, 0xC4) = 4;
    M2C_FIELD(self, s32*, 0x110) = 0;
    void* asset = func_00108120(D_0040F4C4, M2C_FIELD(definition, u64*, 0x40));
    M2C_FIELD(self, void**, 0x118) = asset;
    M2C_FIELD(self, u8*, 0x1F5) = M2C_FIELD(asset, u8*, 0x69);
    M2C_FIELD(self, u8*, 0x1F4) = M2C_FIELD(asset, u8*, 0x68);
    M2C_FIELD(self, u8*, 0x1F6) = M2C_FIELD(asset, u8*, 0x6A);
    s32 count = M2C_FIELD(asset, s32*, 0x5C);
    if (count > 0) {
        M2C_FIELD(self, void**, 0x198) = new ActorArraySlot<0x40>[count];
        M2C_FIELD(self, void**, 0x19C) =
            new ActorArraySlot<0x40>[M2C_FIELD(M2C_FIELD(self, void**, 0x118), s32*, 0x5C)];
    } else {
        M2C_FIELD(self, void**, 0x198) = 0;
        M2C_FIELD(self, void**, 0x19C) = 0;
    }
    M2C_FIELD(self, void**, 0x1A0) = func_00107D20(M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x69) * 12);
    M2C_FIELD(self, void**, 0x1A4) = func_00107D20(M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x69) * 4);
    M2C_FIELD(self, void**, 0x1A8) = func_00107D20(M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x69) * 6);
    M2C_FIELD(self, void**, 0x1AC) = func_00107D20(M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x69) * 2);
    M2C_FIELD(self, void**, 0x1B0) = func_00107D20(M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x6A) * 2);
    if (func_001AFBA8(M2C_FIELD(self, void**, 0x118))) {
        M2C_FIELD(self, void**, 0x1B4) = new ActorArraySlot<0x70>[M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x6A)];
        void* state = func_00107CF8(0x70);
        M2C_FIELD(self, void**, 0x120) = state;
        func_0014CDB8(state);
    } else {
        M2C_FIELD(self, void**, 0x1B4) = 0;
        M2C_FIELD(self, void**, 0x120) = 0;
    }
    M2C_FIELD(self, void**, 0x1BC) = func_00107D20(M2C_FIELD(M2C_FIELD(self, void**, 0x118), u32*, 0x3C));
    M2C_FIELD(self, void**, 0x1C0) = func_00107D20(M2C_FIELD(M2C_FIELD(self, void**, 0x118), u32*, 0x44));
    AllocationRequest request;
    request.alignment = 16;
    request.bytes = 96;
    func_00107CC8(D_0040F0F0, 16);
    void* shapes = new ActorArraySlot<0x60>[M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x68)];
    M2C_FIELD(self, void**, 0x1B8) = 0;
    M2C_FIELD(self, void**, 0xB8) = 0;
    M2C_FIELD(self, void**, 0x194) = shapes;
    M2C_FIELD(self, s16*, 0x1E8) = -1;
    s32 total = func_00149178(self);
    if (func_00149CA0(self) && shared) {
        s32 slot = func_00263908(shared, (s16)total, self);
        if (slot >= 0) {
            M2C_FIELD(self, void**, 0x1B8) = shared;
            M2C_FIELD(self, s16*, 0x1E8) = slot;
        }
    }
    if (!M2C_FIELD(self, void**, 0x1B8)) {
        StorageBlock storage;
        storage.memory = 0;
        func_0032B860(&request, 1, 0);
        storage.memory = func_00107C98(D_0040F0F0, &request);
        M2C_FIELD(self, void**, 0x128) = func_0032BB28(&storage, 1, 0);
        func_003349C0(&request, total, D_003D12C8, 0x40);
        storage.memory = func_00107C98(D_0040F0F0, &request);
        void* list = func_003349E0(&storage, total, (s32)D_003D12C8, 0x40);
        ResetRequest(&request, 96, 16);
        storage.memory = func_00107C98(D_0040F0F0, &request);
        void* holder = func_00334268(&storage, 5);
        M2C_FIELD(self, void**, 0xB8) = holder;
        M2C_FIELD(holder, void**, 0x40) = list;
    }
    s32 i = 0;
    if (M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x69)) {
        s32 offset = 0;
        do {
            i++;
            func_001AFC78(M2C_FIELD(self, u8**, 0x1A0) + offset);
            offset += 12;
        } while (i < M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x69));
    }
    if (M2C_FIELD(self, void**, 0x1B4)) {
        i = 0;
        if (M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x6A)) {
            s32 offset = 0;
            do {
                i++;
                func_0014CDB8(M2C_FIELD(self, u8**, 0x1B4) + offset);
                offset += 0x70;
            } while (i < M2C_FIELD(M2C_FIELD(self, void**, 0x118), u8*, 0x6A));
        }
    }
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1444a8", func_001444A8);
#endif
