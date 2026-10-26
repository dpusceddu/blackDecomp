#include "include_asm.h"

// Collision-definition layout and caller-visible storage requirements.
#include "physics/collision_storage.hpp"

static inline unsigned AlignCollisionStorage(unsigned bytes, unsigned alignment) {
    return (bytes + (alignment - 1u)) & -alignment;
}

extern "C" PhysicsCollisionDefinitionsLayout MeasureCollisionDefinitionsLayout(const PhysicsSceneSettings*)
    __asm__("func_0032E3D0");

extern "C" PhysicsCollisionDefinitionsLayout MeasureCollisionDefinitionsLayout(const PhysicsSceneSettings* settings) {
    PhysicsCollisionDefinitionsLayout layout;
    PhysicsStorageRequirement shapes, work;
    func_0037C190(&shapes, settings->solverJoints, settings->unknown38);
    func_0032FA70(&work, settings->pairBudget);
    layout.shapeAlignment = shapes.alignment;
    layout.shapeSize = shapes.size;
    layout.workAlignment = work.alignment;
    layout.workSize = work.size;
    layout.total = AlignCollisionStorage(
                       AlignCollisionStorage(sizeof(PhysicsCollisionDefinitions), shapes.alignment) + shapes.size,
                       work.alignment) +
                   work.size;
    return layout;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_32e3d0_32e5d8", func_0032E490);






extern "C" PhysicsStorageRequirement* func_0032E5D8(PhysicsStorageRequirement* storage,const PhysicsSceneSettings* settings){
 PhysicsCollisionDefinitionsLayout layout=func_0032E3D0(settings);storage->alignment=128;storage->size=layout.total;return storage;
}


extern "C" void func_0032E490(int,int);
extern "C" void func_0032E6D0(){func_0032E490(1,65535);}
extern "C" void func_0032E6F0(){func_0032E490(0,65535);}

#ifdef NON_MATCHING
extern "C" PhysicsCollisionDefinitions* CreateCollisionDefinitions(PhysicsStorageBlock*, const PhysicsSceneSettings*)
    __asm__("func_0032E618");

// Unmatched: storage-wrapper conversion/copy interface and offset lifetimes remain unresolved.
extern "C" PhysicsCollisionDefinitions* CreateCollisionDefinitions(PhysicsStorageBlock* storage,
                                                                  const PhysicsSceneSettings* settings) {
    PhysicsCollisionDefinitionsLayout layout = MeasureCollisionDefinitionsLayout(settings);
    PhysicsCollisionDefinitions* definitions = (PhysicsCollisionDefinitions*)storage->memory;
    unsigned offset = AlignCollisionStorage(sizeof(PhysicsCollisionDefinitions), layout.shapeAlignment);
    PhysicsStorageBlock shapes((char*)definitions + offset);
    offset += layout.shapeSize;
    void* shapeDefinitions = func_0037C1F0(&shapes, settings->solverJoints, settings->unknown38);
    definitions->pairCapacity = settings->pairBudget;
    definitions->shapeDefinitions = shapeDefinitions;
    definitions->meshCount = settings->unknown38;
    offset = AlignCollisionStorage(offset, layout.workAlignment);
    definitions->workMemory = (char*)definitions + offset;
    definitions->shapeCount = settings->solverJoints;
    definitions->workSize = layout.total;
    return definitions;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_32e3d0_32e5d8", func_0032E618);
#endif
