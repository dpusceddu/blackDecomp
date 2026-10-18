#ifndef BLACK_PHYSICS_COLLISION_WORK_H
#define BLACK_PHYSICS_COLLISION_WORK_H
#include "auto/prelude.h"
/* Accessed prefixes verified by collision pair processing; names are inferred. */
typedef struct {void *first, *second;} CollisionPairPS2;
typedef struct {u8 unknown00[0x30];u32 contactCount, equationCount;} CollisionSolverPS2;
typedef struct {
    u8 unknown00[0xc];
    CollisionSolverPS2 *solver;
    CollisionPairPS2 *pairs;
    u8 unknown14[4];
    u32 pairCount;
} CollisionWorkPS2;
typedef char CollisionSolverContactOffset[((int)&((CollisionSolverPS2*)0)->contactCount==0x30)?1:-1];
typedef char CollisionWorkPairsOffset[((int)&((CollisionWorkPS2*)0)->pairs==0x10)?1:-1];
typedef char CollisionWorkCountOffset[((int)&((CollisionWorkPS2*)0)->pairCount==0x18)?1:-1];
#endif
