#include "physics/collision_work.h"

/* Inferred storage-request type; the PS2 object stores size and alignment. */
struct CollisionStorageRequestPS2 {
    u32 size, alignment;
    CollisionStorageRequestPS2() {}
    CollisionStorageRequestPS2(u32 bytes, u32 boundary): size(bytes), alignment(boundary) {}
};

extern "C" {
void func_0033B610(CollisionStorageRequestPS2 *, u32, u32);
void func_0032E810(CollisionWorkPS2 *, const CollisionPairPS2 *);
int func_0032ED80(CollisionWorkPS2 *, const CollisionPairPS2 *);
void func_0032F928(int, int);

// Unmatched: 0032E810 pair-frame composition and dispatch; vector temporary allocation differs.
// Unmatched: 0032ED80 contact publication; packed point copies and VU register scheduling differ.
// Unmatched: 0032F1A0 convex clipping; support-feature object lifetimes and VU allocation differ.
// Unmatched: 0032F928 static vector construction; temporary lifetime and small-data scheduling differ.

CollisionStorageRequestPS2 *func_0032FA70(CollisionStorageRequestPS2 *storage, u32 pairs)
{
    CollisionStorageRequestPS2 pair(8, 4), scratch;
    func_0033B610(&scratch, 256, 256);
    storage->size = (((scratch.alignment + 31) & -scratch.alignment) + scratch.size) + pair.size * pairs;
    storage->alignment = scratch.alignment;
    return storage;
}

int func_0032FAF0(void)
{
    return 1;
}

int func_0032FAF8(CollisionWorkPS2 *work)
{
    CollisionSolverPS2 *solver = work->solver;
    CollisionPairPS2 *pair = work->pairs;
    u32 remaining;
    solver->contactCount = 0;
    solver->equationCount = 0;
    remaining = work->pairCount;
    while (--remaining != (u32)-1) {
        func_0032E810(work, pair);
        if (!func_0032ED80(work, pair))
            break;
        ++pair;
    }
    return work->pairCount > 0;
}

void func_0032FB80(void)
{
    func_0032F928(1, 65535);
}

void func_0032FBA0(void)
{
    func_0032F928(0, 65535);
}
}
