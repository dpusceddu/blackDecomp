// Xbox mesh_scratch.cpp supplies the algorithm; offsets below follow PS2 accesses.
// Class/field names are provisional; unknown members have no inferred semantics.
namespace MeshScratchRecovery {
struct ManifoldScratch;
struct StorageRequirement {
    unsigned int size;
    unsigned int alignment;
    unsigned int unknown08;
    unsigned int unknown0c;
};
struct StorageBlock { void* memory; };
struct MeshScratch {
    unsigned char unknown00[0x10];
    unsigned int unknown10;
    unsigned int unknown14;
    void* unknown18;
    unsigned int unknown1c;
    unsigned int capacity;
    unsigned int unknown24;
    unsigned int unknown28;
    void* unknown2c;
    void* unknown30;
    unsigned int unknown34;
    unsigned int unknown38;
    unsigned int unknown3c;
    ManifoldScratch* first;
    ManifoldScratch* second;
    unsigned char unknown48[8];
    unsigned char storage[0];
    MeshScratch(unsigned int vertices, unsigned int triangles);
};
}
using namespace MeshScratchRecovery;
// SN returns the storage requirement through its hidden aggregate-result pointer.
extern "C" StorageRequirement func_0033A3B0(unsigned int, unsigned int);
extern "C" ManifoldScratch* func_0033A3F0(StorageBlock*, unsigned int, unsigned int);

inline MeshScratch::MeshScratch(unsigned int vertices, unsigned int triangles)
{
    capacity = triangles;
    first = reinterpret_cast<ManifoldScratch*>(storage);
    StorageRequirement manifold = func_0033A3B0(vertices, triangles);
    unsigned int manifoldSize = manifold.size;
    second = reinterpret_cast<ManifoldScratch*>(reinterpret_cast<char*>(first) + manifoldSize);
    unknown18 = reinterpret_cast<char*>(second) + manifoldSize;
    unknown30 = static_cast<char*>(unknown18) + capacity * 8;
    unknown2c = static_cast<char*>(unknown30) + triangles * 0x420;
    unknown34 = capacity;
    unknown10 = 0;
}

inline void* operator new(unsigned int, void* place) { return place; }

extern "C" MeshScratch* func_0033AEE8(StorageBlock* block, unsigned int vertices, unsigned int triangles)
{
    MeshScratch* scratch = static_cast<MeshScratch*>(block->memory);
    if (scratch)
        scratch = new (scratch) MeshScratch(vertices, triangles);
    else
        scratch = 0;
    StorageBlock firstSlot;
    firstSlot.memory = scratch->first;
    func_0033A3F0(&firstSlot, vertices, triangles);
    StorageBlock secondSlot;
    secondSlot.memory = scratch->second;
    func_0033A3F0(&secondSlot, vertices, triangles);
    return scratch;
}
