#ifndef BLACK_MATCHING_AVOIDANCE_ENGINE_HPP
#define BLACK_MATCHING_AVOIDANCE_ENGINE_HPP
#include "kynapse/alloc.hpp"
#ifndef offsetof
#define offsetof(T,F) ((unsigned int)&(((T*)0)->F))
#endif
#ifndef FLT_MAX
#define FLT_MAX 3.402823466e38f
#endif


namespace KaimAvoidance {

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3 operator+(const Vec3& b) const { return Vec3(x+b.x,y+b.y,z+b.z); }
    Vec3 operator-(const Vec3& b) const { return Vec3(x-b.x,y-b.y,z-b.z); }
    Vec3 operator*(float k) const { return Vec3(x*k,y*k,z*k); }
    Vec3 operator/(float k) const { return Vec3(x/k,y/k,z/k); }
    float Dot(const Vec3& b) const { return x*b.x+y*b.y+z*b.z; }
    float Length() const { return (float)sqrt(x*x+y*y+z*z); }
    Vec3 Normalized() const { return *this * (1.0f/Length()); }
};
__forceinline void CopyVector(Vec3* destination,const Vec3* source) {
    destination->x=source->x; destination->y=source->y; destination->z=source->z;
}
Vec3 ScaleVectorLeft(float scalar,const Vec3& vector);
Vec3 ScaleVectorRight(const Vec3& vector,float scalar);
Vec3 AddVectors(const Vec3& left,const Vec3& right);
Vec3 SubtractVectors(const Vec3& left,const Vec3& right);
float DotVectors(const Vec3& left,const Vec3& right);
Vec3 DivideVector(const Vec3& vector,float divisor);
Vec3 NormalizeVector(const Vec3& vector);
void AccumulateVector(Vec3* target,const Vec3* increment);

struct PropertyKey;
struct ScalarProperty;

// PS2 views verified at entity+0x30, binding+0x14, route callback+0x9c and speed+0x15c.
struct Entity {
    unsigned char unknown00[28];
    unsigned int flags;
    unsigned char unknown20[16];
    Vec3 position;
    unsigned char unknown3c[12];
    Vec3 forward;
    float speed;
    ScalarProperty* GetAuthoredProperty(const PropertyKey*);
};
struct EntityBinding { unsigned char unknown00[20]; Entity* entity; };
struct ScalarProperty { const void* table; float value; };
struct PropertyKey; // Authored, initialized engine key; its implementation is external.
extern PropertyKey obstacleWidthKey, obstacleHeightKey, obstacleSpanKey, movementSpeedKey;
struct Property {
    unsigned char unknown00[16]; const char* key; const char* text;
    const char* GetKey() const;
    const char* GetText() const;
};
struct RouteFollower {
    const void* table;
    EntityBinding* binding;
    unsigned char unknown08[148];
    unsigned char (__cdecl *acceptPoint)(RouteFollower*, const Vec3*);
    unsigned char unknowna0[188];
    ScalarProperty* requestedSpeed;
};
struct WorldRow { const void* table; Entity* entity; WorldRow* previous; WorldRow* next; };
struct WorldList { const void* table; unsigned int unknown04; WorldRow* head; };
struct World {
    unsigned char unknown00[12];
    float units;
    unsigned int entityCapacity;
    WorldList* entities;
};
struct Movement { float speed; Vec3 direction; Vec3 orientation; unsigned char useOrientation; };
struct ClassDefinition { unsigned int unknown00; unsigned int unknown04; void* factory; char name[1]; };
struct ClassRegistry { ClassDefinition* definitions[256]; int count; };
struct Allocator {
    virtual void Unknown0() = 0;
    virtual void Unknown1() = 0;
    virtual void Unknown2() = 0;
    virtual void Unknown3() = 0;
    virtual void Unknown4() = 0;
    virtual unsigned int Allocate(unsigned int bytes, void** output) = 0;
};

extern Allocator* engineAllocator;
extern void (__cdecl *allocationPublished)(void*, unsigned int, unsigned int);
void* __cdecl arrayAllocate(size_t);
void* __cdecl emptyArrayAllocate(size_t);
extern void (__cdecl *memoryRelease)(void*);
extern World* world;
extern float gameTime;
extern unsigned int avoidanceEntityMask;
extern Vec3 zeroVector;
extern Vec3 upVector;
extern Vec3 forwardVector;
extern unsigned short intervalCapacity;
extern unsigned short candidateCapacity;
extern ClassDefinition steeringDefinition, avoidanceDefinition;

// Named compatibility contracts. Their concrete world/route/media owners remain
// external to this reconstruction; the build fixture supplies them explicitly.
void RegisterActorCreated(World*, void (__cdecl *)(Entity*,void*), void*);
void RegisterActorRemoved(World*, void (__cdecl *)(Entity*,void*), void*);
void UnregisterActorCreated(World*, void (__cdecl *)(Entity*,void*), void*);
void UnregisterActorRemoved(World*, void (__cdecl *)(Entity*,void*), void*);
void BeginRouteSegment(RouteFollower*);
void GenerateRouteMove(RouteFollower*, Movement*, const Vec3*);
Vec3* DirectionOrientation(Vec3* output,const Vec3* direction);
ClassRegistry* AvoidanceRegistry();
void ReleaseEmptyArray(void*);

inline float WorldUnits() { return world ? world->units : 0.0f; }
float EngineWorldUnits();
inline Entity* RouteEntity(RouteFollower* route) { return route->binding->entity; }

typedef char EntityPositionOffset[(offsetof(Entity, position)==48)?1:-1];
typedef char RouteCallbackOffset[(offsetof(RouteFollower, acceptPoint)==156)?1:-1];
typedef char RouteSpeedOffset[(offsetof(RouteFollower, requestedSpeed)==348)?1:-1];
}
#endif
