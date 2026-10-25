// Scoped source view for RTTI Kaim::CEntityManager (retained legacy name Perception).
// Existing PS2 prefixes come from the source-backed legacy view. Iterator and
// authored-vector value-return contracts in unmatched consumers remain UNVERIFIED.
#ifndef BLACK_GRAPH_ENTITY_MANAGER_HPP
#define BLACK_GRAPH_ENTITY_MANAGER_HPP
#include "kynapse/behaviors/entities.hpp"
extern unsigned int D_00455F24;
extern "C" float sqrtf(float);
static inline World *PerceptionWorld() { return gWorld; }
static inline Vec3 EntityPropertyValue(const AuthoredVector *property) { return property->value; }
inline float Vec3_Length(const Vec3 *a,const Vec3 *b) {
    float x=b->x-a->x,y=b->y-a->y,z=b->z-a->z;
    return sqrtf(x*x+y*y+z*z);
}
#endif
