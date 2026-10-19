// PS2 wander behavior and the temporary virtual query it sends to a target.
#ifndef BLACK_CONTEXT_BEHAVIORS_WANDER_HPP
#define BLACK_CONTEXT_BEHAVIORS_WANDER_HPP
#include "kynapse/compat.hpp"
#include "kynapse/alloc.hpp"
#include "ps2/kynapse/list.hpp"
#include "ps2/kynapse/property.hpp"
extern void (*gKaimFree)(void*);
namespace Kaim {
struct Vec3 {
    float x,y,z;
    Vec3() {}
    Vec3(const Vec3& v):x(v.x),y(v.y),z(v.z) {}
    Vec3& operator=(const Vec3& v) {x=v.x;y=v.y;z=v.z;return *this;}
};
struct ChildBuffers {const char* GetSecond() const;const char* GetValue() const;};
struct ClassInfo;
struct BehaviorContext;
struct ActionBank {
    virtual void Slot0();virtual void Select(int);
    void ClearActivation();
};
struct TargetBase {virtual void Slot0();};
struct TargetEntity:TargetBase {
    unsigned char unknown04[4];int id;
    virtual void Slot0();virtual void Slot1();virtual void Slot2();virtual void Slot3();virtual void Slot4();
    virtual bool Query(void*);
    virtual bool QueryTransform(void*);
    virtual void Slot7();virtual void Slot8();virtual void Slot9();
    virtual bool IsActive();
};
struct Behavior:PolyRoot {
    Behavior(BehaviorContext*);
    virtual ~Behavior();
    virtual bool Init(ChildBuffers*);
    ActionBank* bank;
    BehaviorContext* context;
};
struct ZeroedBase:PolyRoot {
    virtual ~ZeroedBase() {}
    int field04,field08,field0c,field10,field14,field18,field1c,field20;
    ZeroedBase();
};
struct FollowQuery:ZeroedBase {
    Vec3 axis;int component0,extra;
    FollowQuery(const Vec3& source,int component,int value):axis(source),component0(component),extra(value) {}
    virtual ~FollowQuery() {}
};
struct WanderAgent:Behavior {
    WanderAgent(BehaviorContext*) __asm__("func_002D7500");
    virtual ~WanderAgent();
    static void* operator new(unsigned size) {return KaimAllocate(size);}
    static void operator delete(void* p) {gKaimFree(p);}
    static WanderAgent* Create(BehaviorContext*) __asm__("func_002D7260");
    unsigned index;
    Vec3 vector;
    int fieldC;
    unsigned fieldD;
    TargetEntity* provider;
    void* pending;
    bool reached;
    virtual bool Configure(ChildBuffers*) __asm__("func_002D75B0");
    virtual void Slot3();virtual void Slot4();virtual void Slot5();virtual void Slot6();virtual void Slot7();
    virtual void Refresh();
    bool Update();
    bool Start() __asm__("func_002D7748");
    void Pick() __asm__("func_002D77A0");
    void SetType(int) __asm__("func_002D7840");
};
typedef char WanderSize[sizeof(WanderAgent)==0x30?1:-1];
typedef char FollowQuerySize[sizeof(FollowQuery)==0x38?1:-1];
}
#endif
