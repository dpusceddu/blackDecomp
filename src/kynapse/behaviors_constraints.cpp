#include "context/behaviors/constraints.hpp"
namespace Kaim {
inline float NavEdge::GetAuthoredLength() const {
 NodeGraph* owner=graph;
 if(this==&owner->syntheticEdge)return owner->syntheticLength;
 if(!owner->edgeLengths) {
 NavNode* from=const_cast<NavEdge*>(this)->RawStart();
 NavNode* to=const_cast<NavEdge*>(this)->RawEnd();
 const Vec3& a=from->position;const Vec3& b=to->position;
 float dx=b.x-a.x;float dz=b.z-a.z;float dy=b.y-a.y;
 return sqrtf(dz*dz+dx*dx+dy*dy);
 }
 return owner->edgeLengths[index];
}
bool SphereConstraint::Cost(void* context, NavEdge* edge, float* cost)
{
    if (radius == 0.0f)
        return false;
    NavNode* start = edge->StartNode();
    Vec3 delta=start->position-center;
    float squared=delta.x*delta.x+delta.y*delta.y+delta.z*delta.z;
    if(squared>radius*radius)return false;
    *cost = edge->GetAuthoredLength();
    return true;
}
bool PointToFleeConstraint::Cost(void* context, NavEdge* edge, float* cost)
{
    unsigned i;
    float length = edge->GetAuthoredLength();
    NavNode* start = edge->StartNode();
    const Vec3* position = &start->position;
    *cost = 0.0f;
    for (i = 0; i < entityCount; ++i) {
        const Vec3* observer = &entities[i]->position;
        float dz = position->z - observer->z;
        float dx = position->x - observer->x;
        float dy = position->y - observer->y;
        if (!(range * range < dz * dz + dx * dx + dy * dy)) {
            if ((unsigned char)gConstraintCallbacks.visibility(position, observer, context, 1))
                *cost += penalty;
        }
    }
    for (i = 0; i < pointCount; ++i) {
        const Vec3* point = &points[i];
        float dz = position->z - point->z;
        float dx = position->x - point->x;
        float dy = position->y - point->y;
        if (!(range * range < dz * dz + dx * dx + dy * dy)) {
            if ((unsigned char)gConstraintCallbacks.visibility(position, point, context, 1))
                *cost += penalty;
        }
    }
    *cost += length;
    return true;
}
bool ConeVisionConstraint::Cost(void* context, NavEdge* edge, float* cost)
{
    unsigned i;
    float length = edge->GetAuthoredLength();
    NavNode* start = edge->StartNode();
    Vec3 position(start->position);
    *cost = 0.0f;
    for (i = 0; i < entityCount; ++i) {
        Actor* entity = entities[i];
        const Vec3* observer = &entity->position;
        float dz = position.z - observer->z;
        float dx = position.x - observer->x;
        float dy = position.y - observer->y;
        if (range * range < dz * dz + dx * dx + dy * dy) continue;
        if (!Kaim_InSightCone(&position, entity)) continue;
        if ((unsigned char)gConstraintCallbacks.visibility(&position, observer, entities[i], 1))
            *cost += penalty;
    }
    *cost += length;
    return true;
}
float StealthConstraint::Factor(void* context, NavEdge* edge, const Vec3* position, const Vec3* direction, float length)
{
    NavNode* end = edge->EndNode();
    Vec3 delta=*position-end->position;
    float along=direction->Dot(delta)/length;
    if(along>length)along=length;
    else if(along<0.0f)along=0.0f;
    float distance=position->DistanceTo(edge->EndNode()->position+(*direction*(along/length)));
    if(distance>range)return 1.0f;
    float closeness=(range-distance)/range;
    return penalty*(closeness*(closeness*closeness))+1.0f;
}
bool StealthConstraint::Cost(void* context, NavEdge* edge, float* cost)
{
    unsigned i;
    *cost = edge->GetAuthoredLength();
    const Vec3* start=&edge->StartNode()->position;
    const Vec3* end=&edge->EndNode()->position;
    Vec3 direction;
    float dx=start->x-end->x;
    float dy=start->y-end->y;
    float dz=start->z-end->z;
    direction.z=dz;direction.x=dx;direction.y=dy;
    float length = sqrtf(direction.Squared());
    for (i = 0; i < pointCount; ++i)
        *cost *= Factor(context, edge, &points[i], &direction, length);
    for (i = 0; i < entityCount; ++i)
        *cost *= Factor(context, edge, &entities[i]->position, &direction, length);
    return true;
}
}
namespace Kaim {
struct EngineScale {char unknown[12];float unit;};
extern EngineScale* gConstraintEngine;
PointToFleeConstraint::PointToFleeConstraint() {
    pointCount=0;entityCount=0;
    float unit=gConstraintEngine?gConstraintEngine->unit:0.0f;
    penalty=unit*100.0f;
    range=gConstraintEngine->unit*20.0f;
}
SphereConstraint* SphereConstraint::Create() {return new SphereConstraint;}
bool PointToFleeConstraint::AddPoint(const Vec3& point) {
    if(pointCount>=20)return false;
    points[pointCount]=point;++pointCount;return true;
}
bool PointToFleeConstraint::AddEntity(Actor* entity) {
    if(entityCount>=20)return false;
    entities[entityCount]=entity;++entityCount;return true;
}
bool ConeVisionConstraint::AddEntity(Actor* entity) {
    if(entityCount>=20)return false;
    entities[entityCount]=entity;++entityCount;return true;
}
bool StealthConstraint::AddPoint(const Vec3& point) {
    if(pointCount>=20)return false;
    points[pointCount]=point;++pointCount;return true;
}
bool StealthConstraint::AddEntity(Actor* entity) {
    if(entityCount>=20)return false;
    entities[entityCount]=entity;++entityCount;return true;
}
struct BasicConstraint:PolyRoot {
    virtual ~BasicConstraint();virtual void Slot1();
    virtual bool Cost(void*,NavEdge*,float*) __asm__("func_002F20A0");
};
bool BasicConstraint::Cost(void*,NavEdge* edge,float* cost) {*cost=edge->GetAuthoredLength();return true;}
struct ByteGrid {char unknown[8];unsigned char* cells;int stride;float scale;};
struct GridConstraint:PolyRoot {
    ByteGrid* grid;
    virtual bool Sample(void*,const int*,const int*,float*) __asm__("func_002F2318");
};
bool GridConstraint::Sample(void*,const int* x,const int* y,float* out) {
    ByteGrid* source=grid;
    if(!source){*out=0;return false;}
    unsigned char cell=source->cells[*x * source->stride + *y];
    if(cell!=255) { *out=float(cell)/source->scale;return true; }
    return false;
}
}
// Unmatched: class registration retains address-grouping and scheduling differences.
