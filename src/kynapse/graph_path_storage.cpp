#include "include_asm.h"

#include "kynapse/graph/tables.hpp"
namespace Kaim {
struct RoutePointCell {
    Vec3 value;
    RoutePointCell() {}
    ~RoutePointCell() {}
    static void *operator new[](unsigned int bytes) { return Allocate(bytes); }
    static void operator delete[](void *p) { D_003C87E0(p); }
};

void RouteBuffers::Reserve(int newCapacity) {
    // The PS2 point array has a 16-byte count/alignment cookie before its data.
    if (points)
        D_003C87E0((unsigned char *)points-16);
    if (guards)
        D_003C87E0(guards);
    capacity = newCapacity;
    count = 0;
    if (newCapacity == 0) {
        nodeIds = 0;
        edgeIds = 0;
        points = 0;
        guards = 0;
        return;
    }
    nodeIds = (unsigned int *)Allocate(newCapacity * 4);
    edgeIds = (unsigned int *)Allocate(newCapacity * 4);
    points = (Vec3 *)new RoutePointCell[newCapacity];
    guards = (void **)Allocate(newCapacity * 4);
}
// Scoped three-float vector recipe; scalar assignment preserves the native temporary stores.
struct PathVector {
    float x, y, z;
    PathVector(float px, float py, float pz) : x(px), y(py), z(pz) {}
    ~PathVector() {}
    PathVector &operator=(const PathVector &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }
    PathVector operator-(const Vec3 &b) const { return PathVector(x-b.x, y-b.y, z-b.z); }
    float WeightedSquare() const { return z*z + x*x + y*y*10.0f; }
};
static inline float WaypointDistance(const Vec3 *a, const Vec3 *b) {
    PathVector delta = (*(const PathVector *)a)-*b;
    return delta.WeightedSquare();
}
unsigned int RouteBuffers::ClosestWeightedWaypoint(const Vec3 *point) const {
    if (!count)
        return (unsigned int)-1;
    unsigned int best = 0;
    PathVector delta = (*(const PathVector *)points)-*point;
    float bestDistance = delta.WeightedSquare();
    for (unsigned int i = 1; i < count; ++i) {
        delta = (*(const PathVector *)&points[i])-*point;
        float distance = delta.WeightedSquare();
        if (distance < bestDistance) {
            bestDistance = distance;
            best = i;
        }
    }
    return best;
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FB4D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FB538);
