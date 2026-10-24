#ifndef BLACK_CAMPAIGN_FOLLOWER_HPP
#define BLACK_CAMPAIGN_FOLLOWER_HPP
#include "classes/kynapse/Kaim_CFollowerAgent.hpp"

namespace BehaviorCampaign {
struct Vec3 {
    float x,y,z;
    Vec3() {}
    Vec3(float a,float b,float c) : x(a), y(b), z(c) {}
    Vec3(const Vec3& q) : x(q.x), y(q.y), z(q.z) {}
    Vec3& operator=(const Vec3& p) { x=p.x;y=p.y;z=p.z;return *this; }
    Vec3 operator*(float scale) const { return Vec3(scale*x,scale*y,scale*z); }
    Vec3 operator+(const Vec3& q) const { return Vec3(x+q.x,y+q.y,z+q.z); }
    // The original comparison typedef is unknown; this narrow result is always zero or one.
    short operator==(const Vec3& q) const { return x==q.x && y==q.y && z==q.z; }
};
struct ChildBuffers { const char* GetSecond() const __asm__("func_002E3920"); const char* GetValue() const __asm__("func_002E3918"); };
struct NameTable { int FindName(const char*) __asm__("func_002E93B8"); };
NameTable* GetNames() __asm__("func_002E91C0");
struct ActionBank { virtual void Slot0();virtual void Select(void*); void ClearActivation() __asm__("func_002DFBF8"); };
struct EntityInterfaceBase { virtual void Slot0(); };
struct TargetEntity : EntityInterfaceBase { virtual void Slot0();unsigned char unknown04[4];void* id;
    virtual void Slot1();virtual void Slot2();virtual void Slot3();virtual void Slot4();virtual int Query(Vec3*);
};
struct Actor { unsigned char unknown00[0x30];Vec3 position;Vec3 angles; };
struct Context { unsigned char unknown00[0x14];Actor* actor; };
struct Engine { unsigned char unknown00[0xc];float unit; };
extern Engine* gEngine __asm__("D_003C9ED4");extern Vec3 gOrigin __asm__("D_004514F8");extern float gNow __asm__("D_003C958C");
struct Property { unsigned int unknown00;float value; };
struct ClassInfo;extern ClassInfo gTargetClass __asm__("D_004512B0");extern unsigned int gKey __asm__("D_00450940");
struct Registry { void* FindByClass(ClassInfo*) __asm__("func_002E1C58");Actor* FindByName(const char*) __asm__("func_002EB398"); };
struct PropertyOwner { Property* GetProperty(const void*) __asm__("func_002E4CE0"); };
struct ParameterTables { bool Consume(int,void*) __asm__("func_002E8AB8");void Accumulate(int,void*) __asm__("func_002E9978"); };
// CFollowerAgent: RTTI identity and virtual order come from the generated view.
// The accessed fields are PS2 offsets; unaccessed semantic types remain inferred.
struct ObjectBase { virtual ~ObjectBase(); };
struct Follower : ObjectBase {
    virtual ~Follower();
    ActionBank* bank;Context* context;TargetEntity* target;Property* property;
    Vec3 position,lastTarget;int nameIndex;float nextTime,distance;bool arrived;
    Actor* followed;float limit,angle;
    virtual bool Init(ChildBuffers*) __asm__("func_002D31F0");
    virtual bool Configure(ChildBuffers*) __asm__("func_002D30A0");
    virtual void Slot3();virtual void* ClassInfoOf();
    virtual bool IsReady() __asm__("func_002D35D8");
    virtual bool Update() __asm__("func_002D3610");
    virtual int HasTarget();virtual int HasName();
    virtual void Refresh() __asm__("func_002D3300");
    virtual void ComputeDistance(void*) __asm__("func_002D36A8");

    bool ConfigureAll(ChildBuffers*) __asm__("func_002E0018");
};
}
#endif
