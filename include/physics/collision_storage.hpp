#ifndef BLACK_PHYSICS_COLLISION_STORAGE_HPP
#define BLACK_PHYSICS_COLLISION_STORAGE_HPP
#include "physics/scene.hpp"
struct PhysicsCollisionDefinitionsLayout {unsigned shapeAlignment,shapeSize,workAlignment,workSize,total;};
extern "C" {
 PhysicsCollisionDefinitionsLayout func_0032E3D0(const PhysicsSceneSettings*);
 void func_0037C190(PhysicsStorageRequirement*,unsigned,unsigned);
 void func_0032FA70(PhysicsStorageRequirement*,unsigned);
 void* func_0037C1F0(void*,unsigned,unsigned);
}
#endif
