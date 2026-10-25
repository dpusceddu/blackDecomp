#include "include_asm.h"

// Collision-definition layout and caller-visible storage requirements.
#include "physics/collision_storage.hpp"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_32e3d0_32e5d8", func_0032E3D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_32e3d0_32e5d8", func_0032E490);






extern "C" PhysicsStorageRequirement* func_0032E5D8(PhysicsStorageRequirement* storage,const PhysicsSceneSettings* settings){
 PhysicsCollisionDefinitionsLayout layout=func_0032E3D0(settings);storage->alignment=128;storage->size=layout.total;return storage;
}


extern "C" void func_0032E490(int,int);
extern "C" void func_0032E6D0(){func_0032E490(1,65535);}
extern "C" void func_0032E6F0(){func_0032E490(0,65535);}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_32e3d0_32e5d8", func_0032E618);
