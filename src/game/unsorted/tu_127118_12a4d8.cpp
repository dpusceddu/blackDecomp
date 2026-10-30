#include "ps2/prelude.h"
#include "game/frontend_resources.hpp"
#include "game/actor/world_objects.hpp"
#include "physics/scene.hpp"
typedef PhysicsStorageRequirement AllocationRequest;
typedef PhysicsStorageBlock StorageBlock;
extern FrontendResourceTable D_0040F0F0;
// Native callers supply both unused context words to these selection helpers.
extern "C" void ClearSelection_WithContext(void*, s32, s32) __asm__("func_00107B08");
extern "C" u32 SelectBuffer_WithContext(void*, s32, s32) __asm__("func_00107AB8");
// SN returns these requirement aggregates through a hidden output pointer.
extern "C" AllocationRequest SegmentRequirements(s32, s32) __asm__("func_0033AD90");
extern "C" void* func_0033ADD0(StorageBlock*, s32, s32);
extern "C" AllocationRequest MeshRequirements(u32, u32) __asm__("func_0033B610");
extern "C" void* func_0033AEE8(StorageBlock*, u32, u32);
extern "C" AllocationRequest ManifoldRequirements(s32, s32) __asm__("func_0033A3B0");
extern "C" void* func_0033A3F0(StorageBlock*, u32, u32);
extern "C" void func_0012A4D8(WorldObjects::World* self) {
    StorageBlock block;
    block.memory = NULL;
    ClearSelection_WithContext(&D_0040F0F0, 0, 0);
    SelectBuffer_WithContext(&D_0040F0F0, 11, 0);
    {
        AllocationRequest request = SegmentRequirements(200, 200);
        block.memory = D_0040F0F0.AllocateAligned((FrontendAllocationSpec*)&request);
        self->collision = func_0033ADD0(&block, 200, 200);
    }
    {
        AllocationRequest request = MeshRequirements(200, 200);
        block.memory = D_0040F0F0.AllocateAligned((FrontendAllocationSpec*)&request);
        self->collection = func_0033AEE8(&block, 200, 200);
    }
    {
        AllocationRequest request = ManifoldRequirements(10, 10);
        block.memory = D_0040F0F0.AllocateAligned((FrontendAllocationSpec*)&request);
        self->helper = func_0033A3F0(&block, 10, 10);
    }
    ClearSelection_WithContext(&D_0040F0F0, 11, 0);
    SelectBuffer_WithContext(&D_0040F0F0, 0, 0);
}
