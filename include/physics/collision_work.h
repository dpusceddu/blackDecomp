#ifndef BLACK_PHYSICS_COLLISION_WORK_H
#define BLACK_PHYSICS_COLLISION_WORK_H
#include "auto/prelude.h"
/* Inferred names; field offsets follow the PS2 collision-work accesses. */
typedef struct { float x,y,z; } PhysicsPoint;
typedef union {s128 v;float f[4];u32 u[4];} __attribute__((aligned(16))) PhysicsVector;
typedef struct PhysicsBody {
 u8 unknown00[0x10]; PhysicsVector position,linear,angular,basisX,basisY,basisZ;
 u8 unknown70[0x1c]; u32 state;
} PhysicsBody;
typedef struct {u32 kind;u8 unknown04[0x4c];u32 collisionIndex;u8 unknown54[4];void *shape;} PhysicsDefinition;
typedef struct {float friction,restitution,penetration;} PhysicsMaterial;
typedef struct {
 PhysicsDefinition *definition;u8 unknown04[0xc];PhysicsVector frame[4];
 PhysicsVector *offset;u8 unknown54[4];PhysicsBody *body;PhysicsMaterial *material;
} PhysicsInstance;
typedef struct {PhysicsInstance *first,*second;} PhysicsPair;
typedef struct {u8 unknown00[0xc];void *contacts;u8 unknown10[0x18];u32 stride;u8 unknown2c[4];u32 contactCount,equationCount;u8 unknown38[8];u32 contactCapacity;} PhysicsSolver;
typedef struct {void *scratch;u32 manifoldCount;void *memory;PhysicsSolver *solver;PhysicsPair *pairs;u32 pairCapacity,pairCount;void *filter;} PhysicsCollisionWork;
typedef struct {u8 unknown00[0x2b0];PhysicsVector normal,centerA,centerB;float separation;u8 unknown2e4[0xc];PhysicsVector pointA[8],pointB[8];float distances[8];u32 count;u8 unknown414[0xc];} PhysicsManifold;
typedef char PhysicsBodyStateOffset[((int)&((PhysicsBody*)0)->state==0x8c)?1:-1];
#endif
